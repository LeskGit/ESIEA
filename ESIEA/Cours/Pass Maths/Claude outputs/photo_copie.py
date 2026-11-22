"""
Photo de copie via webcam, avec détection de la feuille A4 et mise au point assistée.

  ESPACE  : compte à rebours 3 s (le temps de te placer), puis phase « mise au point » :
            le script attend que la feuille soit détectée, immobile et nette, garde
            l'image la plus nette, et l'enregistre (max ~7 s, sinon meilleure image vue).
  + / -   : mise au point manuelle (si la webcam le permet)   A : autofocus
  O       : ouvrir le dossier des photos       Q / Échap : quitter

Enregistre 2 fichiers dans %TEMP%/photos_copies :
  copie_<date>.jpg       -> feuille détourée et redressée (format A4) : c'est celle à envoyer
  copie_<date>_brut.jpg  -> l'image complète de la webcam

Installation : python -m pip install opencv-python numpy   |   Lancement : python photo_copie.py
"""
import os
import sys
import time
import tempfile
import subprocess
from collections import deque
from datetime import datetime

import cv2
import numpy as np

# ---------------- Réglages ----------------
DELAI = 3.0             # compte à rebours avant la mise au point (s)
FOCUS_MAX = 7.0         # durée max de la phase mise au point (s)
STABLE_MIN = 0.8        # durée mini où la feuille doit rester immobile (s)
PLATEAU = 0.7           # on déclenche quand la netteté ne progresse plus depuis X s
PROC_W = 640            # largeur de l'image utilisée pour la détection (vitesse)
A4_PX = (1654, 2339)    # taille de la feuille redressée (~200 dpi)
DOSSIER = os.path.join(tempfile.gettempdir(), "photos_copies")
FENETRE = "Photo copie  |  ESPACE photo  +/- focus  A autofocus  O dossier  Q quitter"

VERT, ORANGE, ROUGE, BLANC = (60, 200, 60), (0, 165, 255), (60, 60, 230), (255, 255, 255)


# ---------------- Caméra ----------------
def ouvrir_camera():
    backend = cv2.CAP_DSHOW if sys.platform == "win32" else cv2.CAP_ANY
    for index in range(3):
        cam = cv2.VideoCapture(index, backend)
        if cam.isOpened() and cam.read()[0]:
            cam.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
            cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
            cam.set(cv2.CAP_PROP_AUTOFOCUS, 1)
            return cam
        cam.release()
    return None


# ---------------- Géométrie ----------------
def ordonner(pts):
    """Coins dans l'ordre haut-gauche, haut-droit, bas-droit, bas-gauche (tri par angle)."""
    pts = np.asarray(pts, np.float32).reshape(4, 2)
    c = pts.mean(axis=0)
    ang = np.arctan2(pts[:, 1] - c[1], pts[:, 0] - c[0])
    return pts[np.argsort(ang)]


def dimensions(quad):
    tl, tr, br, bl = quad
    largeur = (np.linalg.norm(tr - tl) + np.linalg.norm(br - bl)) / 2
    hauteur = (np.linalg.norm(bl - tl) + np.linalg.norm(br - tr)) / 2
    return largeur, hauteur


def redresser(img, quad, taille_portrait):
    """Transformation perspective : la feuille devient un rectangle aux proportions A4."""
    largeur, hauteur = dimensions(quad)
    w, h = taille_portrait if hauteur >= largeur else taille_portrait[::-1]
    dst = np.array([[0, 0], [w - 1, 0], [w - 1, h - 1], [0, h - 1]], np.float32)
    M = cv2.getPerspectiveTransform(quad, dst)
    return cv2.warpPerspective(img, M, (w, h), flags=cv2.INTER_CUBIC)


# ---------------- Détection de la feuille ----------------
def _candidats(masque):
    cnts, _ = cv2.findContours(masque, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return sorted(cnts, key=cv2.contourArea, reverse=True)[:3]


def detecter_feuille(frame):
    """
    Feuille blanche = zone claire ET peu saturée (la peau et les fonds colorés sont saturés).
    1. plusieurs seuils de luminosité (Otsu + percentiles) + seuil de saturation
    2. fermeture morphologique pour boucher l'écriture
    3. variante de chaque masque coupée sur les contours (sépare feuille / fond blanc)
    4. pour chaque zone : enveloppe convexe (efface les doigts qui mordent le bord),
       approximation à 4 coins, score = rectangularité × proximité du ratio A4 × taille
    Renvoie (quad en pleine résolution, score) ou (None, 0).
    """
    h, w = frame.shape[:2]
    k = PROC_W / w
    petit = cv2.GaussianBlur(cv2.resize(frame, (PROC_W, int(h * k))), (5, 5), 0)
    aire_img = petit.shape[0] * petit.shape[1]

    hsv = cv2.cvtColor(petit, cv2.COLOR_BGR2HSV)
    s, v = hsv[..., 1], hsv[..., 2]
    gris = cv2.cvtColor(petit, cv2.COLOR_BGR2GRAY)
    med = float(np.median(gris))
    bords = cv2.dilate(cv2.Canny(gris, max(10, 0.4 * med), max(30, 0.9 * med)), np.ones((3, 3), np.uint8))
    noyau = np.ones((15, 15), np.uint8)

    # Balayage de seuils de luminosité : si la feuille est devant un mur / t-shirt blanc,
    # elle est en général un peu plus claire ; à un seuil plus haut, elle se détache seule.
    otsu, _ = cv2.threshold(v, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    seuils = sorted({int(max(otsu, 90))} | {int(np.percentile(v, q)) for q in (75, 85, 92, 96)})
    masques = []
    for seuil in seuils:
        if seuil < 90:
            continue
        clair = ((v >= seuil) & (s <= 75)).astype(np.uint8) * 255
        m = cv2.morphologyEx(clair, cv2.MORPH_CLOSE, noyau)
        masques.append(m)
        coupe = cv2.morphologyEx(cv2.bitwise_and(m, cv2.bitwise_not(bords)), cv2.MORPH_OPEN, np.ones((5, 5), np.uint8))
        masques.append(coupe)

    ph, pw = petit.shape[:2]
    marge = 0.015 * max(ph, pw)

    meilleur, meilleur_score = None, 0.0
    for masque in masques:
        for cnt in _candidats(masque):
            aire = cv2.contourArea(cnt)
            if not (0.05 * aire_img < aire < 0.85 * aire_img):
                continue
            # Une feuille tenue en main est entièrement dans l'image : une zone claire
            # qui touche le bord de l'image est un mur, un t-shirt, une porte… -> rejet
            x, y, bw, bh = cv2.boundingRect(cnt)
            if x <= marge or y <= marge or x + bw >= pw - marge or y + bh >= ph - marge:
                continue
            hull = cv2.convexHull(cnt)
            aire_hull = cv2.contourArea(hull)
            (_, _), (rw, rh), _ = cv2.minAreaRect(hull)
            if rw * rh == 0:
                continue
            remplissage = aire_hull / (rw * rh)          # ~1 pour un rectangle
            ratio = max(rw, rh) / min(rw, rh)              # A4 : 1.414
            if remplissage < 0.85 or not (1.15 < ratio < 1.75):
                continue
            approx = cv2.approxPolyDP(hull, 0.02 * cv2.arcLength(hull, True), True)
            if len(approx) == 4 and cv2.isContourConvex(approx):
                quad = approx.reshape(4, 2)
            else:
                quad = cv2.boxPoints(cv2.minAreaRect(hull))
            score_ratio = np.exp(-((ratio - 1.414) / 0.3) ** 2)
            solidite = aire / aire_hull
            score = remplissage * score_ratio * (0.5 + 0.5 * solidite) * np.sqrt(aire / aire_img)
            if score > meilleur_score:
                meilleur, meilleur_score = quad, score

    if meilleur is None:
        return None, 0.0
    return ordonner(np.asarray(meilleur, np.float32) / k), meilleur_score


class Suivi:
    """Lisse les coins dans le temps et dit si la feuille est immobile."""

    def __init__(self, diag):
        self.diag = diag
        self.quad = None
        self.perdu = 0
        self.historique = deque()
        self.stable_depuis = None

    def maj(self, quad, t):
        if quad is None:
            self.perdu += 1
            if self.perdu > 6:
                self.quad, self.stable_depuis = None, None
                self.historique.clear()
            return
        self.perdu = 0
        if self.quad is None or np.linalg.norm(quad - self.quad, axis=1).mean() > 0.15 * self.diag:
            self.quad = quad.copy()
            self.historique.clear()
        else:
            self.quad = 0.6 * self.quad + 0.4 * quad
        self.historique.append((t, quad))
        while self.historique and t - self.historique[0][0] > 0.5:
            self.historique.popleft()
        stable = False
        if len(self.historique) >= 5:
            pile = np.stack([q for _, q in self.historique])
            stable = pile.std(axis=0).mean() < 0.005 * self.diag
        if stable:
            self.stable_depuis = self.stable_depuis or t
        else:
            self.stable_depuis = None

    def duree_stable(self, t):
        return 0.0 if self.stable_depuis is None else t - self.stable_depuis


def nettete(frame, quad):
    """Variance du laplacien sur la feuille redressée (centre seulement, sans les doigts)."""
    feuille = redresser(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY), quad, (420, 594))
    h, w = feuille.shape
    centre = feuille[int(h * 0.1):int(h * 0.9), int(w * 0.1):int(w * 0.9)]
    return cv2.Laplacian(centre, cv2.CV_64F).var()


def ameliorer(scan):
    """Contraste local (CLAHE) : écriture plus lisible, feuille plus homogène."""
    lab = cv2.cvtColor(scan, cv2.COLOR_BGR2LAB)
    lab[..., 0] = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8)).apply(lab[..., 0])
    return cv2.cvtColor(lab, cv2.COLOR_LAB2BGR)


# ---------------- Affichage ----------------
def texte(img, txt, pos, echelle=0.8, couleur=BLANC, ep=2):
    cv2.putText(img, txt, pos, cv2.FONT_HERSHEY_SIMPLEX, echelle, (0, 0, 0), ep + 4, cv2.LINE_AA)
    cv2.putText(img, txt, pos, cv2.FONT_HERSHEY_SIMPLEX, echelle, couleur, ep, cv2.LINE_AA)


def texte_centre(img, txt, echelle, ep, couleur=BLANC):
    (w, h), _ = cv2.getTextSize(txt, cv2.FONT_HERSHEY_SIMPLEX, echelle, ep)
    texte(img, txt, ((img.shape[1] - w) // 2, (img.shape[0] + h) // 2), echelle, couleur, ep)


def ouvrir_dossier():
    if sys.platform == "win32":
        os.startfile(DOSSIER)
    elif sys.platform == "darwin":
        subprocess.run(["open", DOSSIER])
    else:
        subprocess.run(["xdg-open", DOSSIER])


def enregistrer(frame, quad):
    base = os.path.join(DOSSIER, datetime.now().strftime("copie_%Y%m%d_%H%M%S"))
    cv2.imwrite(base + "_brut.jpg", frame, [cv2.IMWRITE_JPEG_QUALITY, 95])
    if quad is None:
        print(f"Feuille non détectée, image brute seulement : {base}_brut.jpg")
        return os.path.basename(base) + "_brut.jpg"
    scan = ameliorer(redresser(frame, quad, A4_PX))
    cv2.imwrite(base + ".jpg", scan, [cv2.IMWRITE_JPEG_QUALITY, 95])
    print(f"Photo enregistrée : {base}.jpg  (+ _brut.jpg)")
    return os.path.basename(base) + ".jpg"


# ---------------- Boucle principale ----------------
def main():
    os.makedirs(DOSSIER, exist_ok=True)
    cam = ouvrir_camera()
    if cam is None:
        print("Aucune webcam détectée (ou déjà utilisée par une autre appli).")
        sys.exit(1)
    print(f"Photos enregistrées dans : {DOSSIER}")

    ok, frame = cam.read()
    H, W = frame.shape[:2]
    suivi = Suivi(np.hypot(W, H))
    zoom_apercu = min(1.0, 1280 / W)

    etat = "attente"              # attente -> compte -> focus -> attente
    t_etat = 0.0
    meilleure = None              # (netteté, frame, quad)
    t_progres = 0.0
    message, fin_message = "", 0.0
    focus_manuel = None

    while True:
        ok, frame = cam.read()
        if not ok:
            print("Lecture webcam impossible.")
            break
        t = time.time()

        quad_brut, _ = detecter_feuille(frame)
        suivi.maj(quad_brut, t)
        quad = suivi.quad
        stable = suivi.duree_stable(t)

        # ---- logique de capture ----
        net = None
        if etat == "compte" and t - t_etat >= DELAI:
            etat, t_etat, meilleure, t_progres = "focus", t, None, t
        if etat == "focus":
            if quad is not None and stable > 0.2:
                net = nettete(frame, quad)
                if meilleure is None or net > meilleure[0] * 1.03:
                    t_progres = t
                if meilleure is None or net > meilleure[0]:
                    meilleure = (net, frame.copy(), quad.copy())
            fini = (meilleure is not None and stable >= STABLE_MIN and t - t_progres >= PLATEAU)
            if fini or t - t_etat >= FOCUS_MAX:
                etat = "attente"
                if meilleure is not None:
                    nom = enregistrer(meilleure[1], meilleure[2])
                    message, fin_message = f"Enregistree : {nom}", t + 2.5
                    frame = np.full_like(frame, 255)  # flash
                    quad = None
                else:
                    print("Aucune feuille détectée : rien n'a été enregistré.")
                    message, fin_message = "Aucune feuille detectee : rien enregistre", t + 3

        # ---- affichage ----
        apercu = frame.copy()
        if quad is not None:
            if etat == "focus" and net is not None and meilleure is not None and net >= 0.9 * meilleure[0]:
                couleur = VERT
            elif stable > 0.2:
                couleur = VERT if etat == "attente" else ORANGE
            else:
                couleur = ORANGE
            cv2.polylines(apercu, [quad.astype(np.int32)], True, couleur, 6, cv2.LINE_AA)
            for p in quad.astype(np.int32):
                cv2.circle(apercu, tuple(p), 14, couleur, -1, cv2.LINE_AA)

        if zoom_apercu < 1:
            apercu = cv2.resize(apercu, None, fx=zoom_apercu, fy=zoom_apercu, interpolation=cv2.INTER_AREA)

        if etat == "compte":
            texte_centre(apercu, str(int(DELAI - (t - t_etat)) + 1), 6, 12)
        elif etat == "focus":
            if quad is None:
                info = "Feuille non detectee : montre-la entiere, sur fond sombre"
            elif stable < STABLE_MIN:
                info = "Ne bouge plus..."
            else:
                info = "Mise au point..."
            texte(apercu, info, (20, apercu.shape[0] - 60), 0.9, ORANGE)
            if meilleure is not None and net is not None:
                ratio = min(1.0, net / meilleure[0])
                x0, y0, lg = 20, apercu.shape[0] - 35, 300
                cv2.rectangle(apercu, (x0, y0), (x0 + lg, y0 + 14), (40, 40, 40), -1)
                cv2.rectangle(apercu, (x0, y0), (x0 + int(lg * ratio), y0 + 14), VERT, -1)
            restant = FOCUS_MAX - (t - t_etat)
            texte(apercu, f"{restant:.0f}s", (340, apercu.shape[0] - 22), 0.6)
        else:
            etat_feuille = "feuille detectee" if quad is not None else "feuille non detectee"
            texte(apercu, f"ESPACE pour photographier  ({etat_feuille})", (20, apercu.shape[0] - 25), 0.7,
                  VERT if quad is not None else ROUGE)

        mode_focus = "autofocus" if focus_manuel is None else f"focus manuel {focus_manuel}"
        texte(apercu, mode_focus, (apercu.shape[1] - 260, 30), 0.6)
        if t < fin_message:
            texte(apercu, message, (20, 40), 0.8, VERT)

        cv2.imshow(FENETRE, apercu)
        touche = cv2.waitKey(1) & 0xFF

        if touche == ord(" ") and etat == "attente":
            etat, t_etat = "compte", t
        elif touche in (ord("+"), ord("="), ord("-")):
            if focus_manuel is None:
                cam.set(cv2.CAP_PROP_AUTOFOCUS, 0)
                actuel = cam.get(cv2.CAP_PROP_FOCUS)
                focus_manuel = int(actuel) if actuel >= 0 else 30
            focus_manuel = max(0, focus_manuel + (5 if touche != ord("-") else -5))
            cam.set(cv2.CAP_PROP_FOCUS, focus_manuel)
        elif touche in (ord("a"), ord("A")):
            focus_manuel = None
            cam.set(cv2.CAP_PROP_AUTOFOCUS, 1)
        elif touche in (ord("o"), ord("O")):
            ouvrir_dossier()
        elif touche in (ord("q"), ord("Q"), 27):
            break
        if cv2.getWindowProperty(FENETRE, cv2.WND_PROP_VISIBLE) < 1:
            break

    cam.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
