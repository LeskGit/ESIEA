# Synthèse PASSMATHS3AFISA — Parties 1 et 2

*Source : cours d'Abdelrhani Daoudi (ESIEA). Synthèse de tous les sujets abordés, avec exemples détaillés.*

---

# PARTIE 1 — Primitives, intégrales, parité, périodicité, techniques d'intégration

## 1. Primitives et intégrales

### Définition

$G$ est une **primitive** de $f$ sur un intervalle $I$ si $G$ est dérivable sur $I$ et :

$$\forall x \in I,\ G'(x) = f(x)$$

Autrement dit : **dériver $G$ redonne $f$**. Prendre une primitive est l'opération inverse de dériver.

### Proposition (le lien primitive → intégrale)

Si $G$ est une primitive de $f$ sur $[a,b]$ :

$$\int_a^b f(t)\,dt = [G(t)]_a^b = G(b) - G(a)$$

### Distinction fondamentale

| Notation | Nature du résultat | Signification |
|---|---|---|
| $\int g(x)\,dx$ (sans bornes) | une **fonction** | une primitive de $g$ (+ constante) |
| $\int_a^b g(x)\,dx$ (bornes fixées) | un **nombre réel** | l'aire algébrique sous la courbe |

**Lettres muettes** : $\int_a^b g(x)dx = \int_a^b g(t)dt = \int_a^b g(u)du$. Le nom de la variable d'intégration n'a aucune importance.

### Exemple guidé

**Calculer** $\displaystyle\int_1^2 t^3\,dt$

1. Formule à utiliser : $\displaystyle\int t^n dt = \frac{t^{n+1}}{n+1}$, ici $n=3$
2. Primitive : $\dfrac{t^4}{4}$
3. Application des bornes :

$$\int_1^2 t^3 dt = \left[\frac{t^4}{4}\right]_1^2 = \frac{2^4}{4} - \frac{1^4}{4} = \frac{16-1}{4} = \frac{15}{4}$$

**Variante sans bornes** : $\displaystyle\int x^6 dx = \frac{x^7}{7} + c$ — noter que le résultat est une **fonction**, et qu'il faut le $+c$.

## 2. Table des primitives à retenir

| Fonction $f(t)$ | Primitive | Condition |
|---|---|---|
| $t^n$ | $\dfrac{t^{n+1}}{n+1}$ | $n \in \mathbb{N}$ |
| $(\alpha t+\beta)^n$ | $\dfrac{(\alpha t+\beta)^{n+1}}{\alpha(n+1)}$ | $n \in \mathbb{N}$ |
| $e^{\omega t}$ | $\dfrac{e^{\omega t}}{\omega}$ | $\omega \neq 0$ |
| $\sin(\omega t)$ | $-\dfrac{\cos(\omega t)}{\omega}$ | $\omega \neq 0$ |
| $\cos(\omega t)$ | $\dfrac{\sin(\omega t)}{\omega}$ | $\omega \neq 0$ |
| $\dfrac{u'(t)}{u(t)}$ | $\ln\lvert u(t)\rvert$ | $u$ dérivable, ne s'annule pas sur $[a,b]$ |
| $u'(t)\,e^{u(t)}$ | $e^{u(t)}$ | $u$ dérivable sur $[a,b]$ |
| $\dfrac{1}{1+x^2}$ | $\arctan(x)$ | — |
| $\cos^2(\omega t)$ | via $\cos^2 t = \dfrac{1+\cos(2t)}{2}$ | linéarisation |
| $\sin^2(\omega t)$ | via $\sin^2 t = \dfrac{1-\cos(2t)}{2}$ | linéarisation |

Objectif du cours également mentionné : **savoir calculer** $\displaystyle\int \frac{\alpha x + \beta}{ax^2+bx+c}dx$ lorsque $\Delta = b^2-4ac < 0$ (voir §7 et Partie 2).

### Exemples guidés (un par forme)

**a) Forme $(\alpha t+\beta)^n$** — Calculer $\displaystyle\int_{-1}^{1}(3x+2)^{11}dx$

Ici $\alpha=3$, $\beta=2$, $n=11$. On augmente la puissance de 1 et on divise par $\alpha(n+1) = 3 \times 12 = 36$ :

$$\left[\frac{(3x+2)^{12}}{36}\right]_{-1}^{1} = \frac{5^{12}}{36} - \frac{(-1)^{12}}{36} = \frac{5^{12}-1}{36}$$

**b) Forme $e^{\omega t}$** — Calculer $\displaystyle\int_0^1 e^{2x}dx$

$$\left[\frac{e^{2x}}{2}\right]_0^1 = \frac{e^2}{2} - \frac{e^0}{2} = \frac{e^2-1}{2}$$

**c) Forme $\sin(\omega t)$** — Calculer $\displaystyle\int_0^{\pi/3}\sin(3t)\,dt$

$$\left[\frac{-\cos(3t)}{3}\right]_0^{\pi/3} = \frac{-\cos(\pi)}{3} + \frac{\cos(0)}{3} = \frac{1}{3}+\frac{1}{3} = \frac{2}{3}$$

*(en utilisant $\cos(\pi)=-1$ et $\cos(0)=1$)*

**d) Forme $\cos(\omega t)$** — Calculer $\displaystyle\int_0^{\pi/2}\cos(2x)\,dx$

$$\left[\frac{\sin(2x)}{2}\right]_0^{\pi/2} = \frac{\sin(\pi)}{2} - \frac{\sin(0)}{2} = 0 - 0 = 0$$

**e) Forme $\frac{u'}{u}$** — Calculer $\displaystyle\int_0^1 \frac{1}{1+x}dx$

On pose $u(x) = 1+x$, donc $u'(x) = 1$ : le numérateur est bien la dérivée du dénominateur.

$$\left[\ln\lvert 1+x\rvert\right]_0^1 = \ln(2) - \ln(1) = \ln(2)$$

**f) Forme $\frac{u'}{u}$ avec ajustement** — Calculer $\displaystyle\int_0^1 \frac{x}{1+x^2}dx$

On pose $u(x) = 1+x^2$, donc $u'(x) = 2x$. Le numérateur est $x$, pas $2x$ : on **fabrique** le facteur manquant en sortant $\frac12$.

$$\int_0^1 \frac{x}{1+x^2}dx = \frac12\int_0^1 \frac{2x}{1+x^2}dx = \frac12\left[\ln(1+x^2)\right]_0^1 = \frac12\ln(2)$$

**g) Forme $u'e^u$** — Calculer $\displaystyle\int_0^1 t\,e^{t^2}dt$

On pose $u(t)=t^2$, donc $u'(t)=2t$. Même astuce : on sort $\frac12$.

$$\frac12\int_0^1 (2t)e^{t^2}dt = \frac12\left[e^{t^2}\right]_0^1 = \frac{e-1}{2}$$

**h) Forme $u'e^u$ (degré 3)** — Calculer $\displaystyle\int_0^1 x^2 e^{x^3}dx$

On pose $u(x)=x^3$, donc $u'(x)=3x^2$. On sort $\frac13$ :

$$\frac13\int_0^1 (3x^2)e^{x^3}dx = \frac13\left[e^{x^3}\right]_0^1 = \frac{e-1}{3}$$

**i) Linéarisation de $\cos^2$** — Calculer $\displaystyle\int_0^{\pi}\cos^2(2t)\,dt$

$\cos^2$ n'est pas dans la table. On utilise l'identité $\cos^2(\theta) = \dfrac{1+\cos(2\theta)}{2}$ avec $\theta = 2t$ :

$$\int_0^\pi \frac{1+\cos(4t)}{2}dt = \frac12\left[t + \frac{\sin(4t)}{4}\right]_0^\pi = \frac12\left(\pi + 0 - 0\right) = \frac{\pi}{2}$$

**j) Linéarisation de $\sin^2$** — Calculer $\displaystyle\int_0^{\pi/8}\sin^2(2x)\,dx$

Identité : $\sin^2(\theta) = \dfrac{1-\cos(2\theta)}{2}$

$$\frac12\int_0^{\pi/8}\bigl(1-\cos(4x)\bigr)dx = \frac12\left[x - \frac{\sin(4x)}{4}\right]_0^{\pi/8} = \frac12\left(\frac{\pi}{8} - \frac{\sin(\pi/2)}{4}\right) = \frac12\left(\frac{\pi}{8}-\frac14\right) = \frac{\pi-2}{16}$$

## 3. Propriétés des intégrales

Soient $a < b$, $\lambda \in \mathbb{R}$, et $f, g$ continues sur $[a,b]$.

| Propriété | Formule |
|---|---|
| Linéarité (somme) | $\displaystyle\int_a^b (f+g)\,dt = \int_a^b f\,dt + \int_a^b g\,dt$ |
| Linéarité (facteur) | $\displaystyle\int_a^b \lambda f(t)\,dt = \lambda\int_a^b f(t)\,dt$ |
| Relation de Chasles | $\displaystyle\int_a^b f = \int_a^c f + \int_c^b f$ (si $a<c<b$) |
| Bornes égales | $\displaystyle\int_a^a f(t)\,dt = 0$ |
| Inversion des bornes | $\displaystyle\int_a^b f(t)\,dt = -\int_b^a f(t)\,dt$ |

### Exemple guidé (Chasles) — Calculer $\displaystyle\int_{-1}^{1}\lvert x\rvert\,dx$

La valeur absolue **change de formule en $x=0$** : c'est exactement le cas où Chasles sert. On coupe l'intervalle en $0$.

**Rappel** : si $x \geq 0$ alors $\lvert x\rvert = x$ ; si $x \leq 0$ alors $\lvert x\rvert = -x$.

$$\int_{-1}^1 \lvert x\rvert dx = \int_{-1}^0 (-x)\,dx + \int_0^1 x\,dx = \left[-\frac{x^2}{2}\right]_{-1}^0 + \left[\frac{x^2}{2}\right]_0^1 = \frac12 + \frac12 = 1$$

## 4. Fonctions paires

### Définition

Soit $I$ un intervalle **centré en zéro**. $f$ est **paire** si :

$$\forall x \in I,\ f(-x) = f(x)$$

Sa courbe est **symétrique par rapport à l'axe des ordonnées**.

### Exemples de fonctions paires

- $x \mapsto \cos(x)$ et $x \mapsto \cos(ax)$
- $x \mapsto \lvert x\rvert$ et $x \mapsto \lvert ax\rvert$
- $x \mapsto x^2$ et $x \mapsto ax^2$

### Propriété d'intégration (le raccourci)

Si $f$ est paire sur $[-a,a]$ :

$$\int_{-a}^{a} f(x)\,dx = 2\int_0^a f(x)\,dx$$

L'intérêt : **on divise le travail par deux** en n'intégrant que sur la moitié positive.

### Exemple guidé — Calculer $\displaystyle\int_{-1}^{1}x^2\,dx$

$x \mapsto x^2$ est paire, donc :

$$\int_{-1}^1 x^2 dx = 2\int_0^1 x^2 dx = 2\left[\frac{x^3}{3}\right]_0^1 = 2\left(\frac13 - 0\right) = \frac23$$

## 5. Fonctions impaires

### Définition

Soit $I$ centré en zéro. $f$ est **impaire** si :

$$\forall x \in I,\ f(-x) = -f(x)$$

Sa courbe est **symétrique par rapport à l'origine** du repère.

### Exemples de fonctions impaires

- $x \mapsto \sin(x)$ et $x \mapsto \sin(ax)$
- $x \mapsto x$ et $x \mapsto ax$
- $x \mapsto x^3$ et $x \mapsto ax^3$

### Propriété d'intégration (le raccourci le plus puissant)

Si $f$ est impaire sur $[-a,a]$ :

$$\int_{-a}^{a} f(x)\,dx = 0$$

**Sans aucun calcul.** Les aires positives et négatives se compensent exactement.

### Exemple guidé

$$\int_{-1}^{1}\sin(x)\,dx = 0$$

$\sin$ est impaire, l'intervalle est symétrique → résultat immédiat, aucune primitive à calculer.

### Règles de parité d'un produit

Ces règles permettent de reconnaître la parité d'une fonction composée sans calcul :

| Produit | Résultat |
|---|---|
| paire × impaire | **impaire** |
| paire × paire | **paire** |
| impaire × impaire | **paire** |

**Applications du cours** :
- **Impaires** : $x \mapsto \lvert x\rvert\sin(x)$, $x \mapsto x^2\sin(x)$, $x \mapsto x\cos(x)$
- **Paires** : $x \mapsto x\sin(x)$, $x \mapsto x^2\cos(x)$

*Vérification sur $x\cos(x)$ : $x$ est impaire, $\cos$ est paire → impaire × paire = impaire. Donc $\int_{-a}^a x\cos(x)dx = 0$.*

## 6. Fonctions périodiques

### Définition

Soit $T > 0$. $f$ est **$T$-périodique** si :

$$\forall x \in \mathbb{R},\ f(x+T) = f(x)$$

**Construction de la courbe** : on représente $f$ sur un intervalle de longueur $T$, puis on **duplique indéfiniment** ce motif à gauche et à droite.

### Généralisation

$$\forall x \in \mathbb{R},\ \forall n \in \mathbb{Z},\ f(x + nT) = f(x)$$

En particulier : $\cos(x + 2n\pi) = \cos(x)$ et $\sin(x + 2n\pi) = \sin(x)$ (car $\sin$ et $\cos$ sont $2\pi$-périodiques).

### Propriété d'intégration

Si $f$ est continue et $T$-périodique :

$$\forall a, b \in \mathbb{R},\quad \int_a^{a+T} f(x)\,dx = \int_b^{b+T} f(x)\,dx = \int_0^T f(x)\,dx$$

**Interprétation** : intégrer sur **n'importe quelle période complète** donne toujours le même résultat. On peut donc toujours ramener le calcul à l'intervalle le plus simple, $[0,T]$.

### Exemple guidé — Calculer $\displaystyle A_n = \int_{n\pi}^{(n+1)\pi}\lvert\sin(x)\rvert\,dx$ pour $n \in \mathbb{N}$

**Étape 1 — montrer que $f : x \mapsto \lvert\sin(x)\rvert$ est $\pi$-périodique**

Rappel : $\sin(x+\pi) = -\sin(x)$. Donc :
$$f(x+\pi) = \lvert\sin(x+\pi)\rvert = \lvert-\sin(x)\rvert = \lvert\sin(x)\rvert = f(x)$$
(car $\lvert -a\rvert = \lvert a\rvert$). Donc $T = \pi$.

**Étape 2 — vérifier que l'intervalle est bien une période complète**

Longueur de $[n\pi, (n+1)\pi]$ : $(n+1)\pi - n\pi = \pi$ ✓ C'est exactement une période.

**Étape 3 — ramener à $[0,\pi]$** grâce à la propriété

$$A_n = \int_{n\pi}^{(n+1)\pi} f(x)\,dx = \int_0^\pi f(x)\,dx$$

**Étape 4 — supprimer la valeur absolue**

Sur $[0,\pi]$, on a $\sin(x) \geq 0$, donc $\lvert\sin(x)\rvert = \sin(x)$ :

$$A_n = \int_0^\pi \sin(x)\,dx = \left[-\cos(x)\right]_0^\pi = -\cos(\pi) + \cos(0) = 1+1 = 2$$

**Conclusion** : $A_n = 2$ — le résultat ne dépend pas de $n$, ce qui est logique puisque chaque intervalle couvre une période identique.

### Exercice du cours — fonction créneau

Soit $f$ la fonction $2\pi$-périodique définie par :

$$f(t) = \begin{cases} 1 & \text{si } t \in [0,\pi[ \\ 0 & \text{si } t \in [\pi, 2\pi[ \end{cases}$$

**1) Calculer $f(2\pi)$ et $f(3\pi)$**

Ces deux points sont **hors** de l'intervalle de définition $[0,2\pi[$. On utilise la périodicité pour les y ramener.

La relation est $f(x + 2\pi) = f(x)$. On cherche le $x$ connu qui, plus $2\pi$, donne le point voulu :

- $2\pi = 0 + 2\pi$, donc $f(2\pi) = f(0)$. Or $0 \in [0,\pi[$ → $\boxed{f(2\pi) = 1}$
- $3\pi = \pi + 2\pi$, donc $f(3\pi) = f(\pi)$. Or $\pi \in [\pi,2\pi[$ → $\boxed{f(3\pi) = 0}$

**2) Représenter $f$ sur $[-4\pi, 4\pi]$**

On recopie le motif (1 puis 0, sur des plages de longueur $\pi$) toutes les longueurs de $2\pi$, à gauche et à droite. On obtient un **signal carré** alternant entre 1 et 0.

## 7. Formule de changement de variable

### Rappel préalable

$f$ est de **classe $C^1$** sur $I$ si $f$ est dérivable sur $I$ **et** $f'$ est continue sur $I$.

### Théorème

Soient $f : I \to \mathbb{R}$ continue, $\phi : J \to I$ de classe $C^1$, et $(a,b) \in J^2$ avec $a<b$ :

$$\int_{\phi(a)}^{\phi(b)} f(x)\,dx = \int_a^b f(\phi(t))\,\phi'(t)\,dt$$

En pratique, on ne manipule pas cette écriture théorique : on applique la procédure ci-dessous.

### Deux cas à ne pas confondre

| | Sans bornes (primitive) | Avec bornes (intégrale) |
|---|---|---|
| Changer les bornes ? | Il n'y en a pas | **Oui, obligatoire** |
| Revenir à la variable $x$ ? | **Oui, obligatoire** | Non, inutile |
| Ajouter $+c$ ? | Oui | Non |

> **Piège majeur** : les nouvelles bornes se calculent avec la **relation** $t = \ldots$, **jamais** avec la dérivée $dt = \ldots dx$. La dérivée sert uniquement à convertir le $dx$ en $dt$.

### Exemple guidé A — sans bornes

**Calculer** $\displaystyle\int (2x+1)^5\,dx$ avec le changement $t = 2x+1$

1. **Poser** : $t = 2x+1$
2. **Dériver** : $dt = 2\,dx$, donc $dx = \dfrac{dt}{2}$
3. **Réécrire** : $\displaystyle\int (2x+1)^5 dx = \int t^5\cdot\frac{dt}{2} = \frac12\int t^5 dt$
4. **Calculer** : $\dfrac12 \times \dfrac{t^6}{6} = \dfrac{t^6}{12}$
5. **Revenir à $x$** (obligatoire ici) : remplacer $t$ par $2x+1$

$$\int (2x+1)^5 dx = \frac{(2x+1)^6}{12} + c,\quad c \in \mathbb{R}$$

### Exemple guidé B — avec bornes

**Calculer** $\displaystyle I = \int_0^1 t\sqrt{1+t^2}\,dt$ avec le changement $x = t^2+1$

1. **Poser** : $x = t^2+1$ (l'expression sous la racine)
2. **Dériver** : $dx = 2t\,dt$, donc $\dfrac{dx}{2} = t\,dt$
3. **Convertir les bornes** — avec la relation $x = t^2+1$ :
   - $t = 0 \rightarrow x = 0^2+1 = 1$
   - $t = 1 \rightarrow x = 1^2+1 = 2$
4. **Réécrire** en repérant les morceaux : $\sqrt{1+t^2} = \sqrt{x}$ et $t\,dt = \dfrac{dx}{2}$

$$I = \int_1^2 \sqrt{x}\cdot\frac{dx}{2} = \frac12\int_1^2\sqrt{x}\,dx$$

5. **Calculer** (primitive de $\sqrt x = x^{1/2}$ est $\frac23 x^{3/2}$) :

$$I = \frac12\left[\frac23 x^{3/2}\right]_1^2 = \frac13\left(2^{3/2} - 1^{3/2}\right) = \frac13\left(2\sqrt2 - 1\right)$$

*Rappel de calcul utilisé : $2^{3/2} = \sqrt{2^3} = \sqrt8 = 2\sqrt2$.*

**Rappels sur les puissances** (pour $a>0$, $p \in \mathbb{N}$, $n \in \mathbb{N}^*$) :
$$\frac{1}{a^n} = a^{-n} \qquad a^{np} = (a^n)^p \qquad a^{p/n} = \sqrt[n]{a^p}$$

### Exemple guidé C — méthode à retenir : intégrale du type $\int\frac{1}{ax^2+bx+c}dx$ avec $\Delta<0$

**Principe** : quand le trinôme au dénominateur n'a pas de racine réelle ($\Delta<0$), on le met sous **forme canonique** pour le ramener à la forme $\dfrac{1}{t^2+1}$, dont la primitive est $\arctan(t)$.

**Calculer** $\displaystyle\int_0^1 \frac{1}{x^2+x+1}dx$

**Étape 1 — forme canonique du dénominateur**

On utilise $(a+b)^2 = a^2+2ab+b^2$, d'où $\left(x+\frac12\right)^2 = x^2 + x + \frac14$.

Donc $x^2 + x = \left(x+\frac12\right)^2 - \frac14$, et :

$$x^2+x+1 = \left(x+\frac12\right)^2 - \frac14 + 1 = \left(x+\frac12\right)^2 + \frac34$$

**Étape 2 — factoriser pour faire apparaître un « $+1$ »**

$$\left(x+\frac12\right)^2 + \frac34 = \frac34\left[\frac43\left(x+\frac12\right)^2 + 1\right] = \frac34\left[\left(\frac{2}{\sqrt3}\left(x+\frac12\right)\right)^2 + 1\right]$$

L'intégrale devient :
$$\int_0^1 \frac{1}{x^2+x+1}dx = \frac43\int_0^1 \frac{1}{\left[\frac{2}{\sqrt3}\left(x+\frac12\right)\right]^2+1}dx$$

**Étape 3 — changement de variable**

On pose $t = \dfrac{2}{\sqrt3}\left(x+\dfrac12\right)$, donc $dt = \dfrac{2}{\sqrt3}dx$, soit $dx = \dfrac{\sqrt3}{2}dt$

Bornes (avec la relation, pas la dérivée) :
- $x=0 \rightarrow t = \frac{2}{\sqrt3}\cdot\frac12 = \frac{1}{\sqrt3} = \frac{\sqrt3}{3}$
- $x=1 \rightarrow t = \frac{2}{\sqrt3}\cdot\frac32 = \frac{3}{\sqrt3} = \sqrt3$

**Étape 4 — calculer**

$$= \frac43 \cdot \frac{\sqrt3}{2}\int_{\sqrt3/3}^{\sqrt3}\frac{1}{t^2+1}dt = \frac{2\sqrt3}{3}\left[\arctan(t)\right]_{\sqrt3/3}^{\sqrt3}$$

$$\boxed{\int_0^1 \frac{1}{x^2+x+1}dx = \frac{2\sqrt3}{3}\left(\arctan(\sqrt3) - \arctan\!\left(\frac{\sqrt3}{3}\right)\right)}$$

*Le cours signale qu'un exercice de TD porte sur la forme plus simple $\displaystyle\int_\alpha^\beta \frac{1}{x^2+a^2}dx$.*

## 8. Formule d'intégration par parties (IPP)

### Théorème

Soient $u, v : [a,b] \to \mathbb{R}$ de classe $C^1$ :

$$\int_a^b u(t)\,v'(t)\,dt = \left[u(t)v(t)\right]_a^b - \int_a^b u'(t)\,v(t)\,dt$$

**À quoi ça sert** : quand l'intégrande est un **produit de deux fonctions non liées** (aucune n'est la dérivée de l'autre), le changement de variable ne marche pas. L'IPP transforme l'intégrale en une autre, plus simple.

### Règle de choix (la clé de la méthode)

| Type d'intégrale | On pose $u(t) =$ | On pose $v'(t) =$ |
|---|---|---|
| $\int t\,e^{\omega t}dt$, $\int t\cos(\omega t)dt$, $\int t\sin(\omega t)dt$ | $t$ | l'autre fonction |
| $\int t^n e^{\omega t}dt$, $\int t^n\cos(\omega t)dt$, $\int t^n\sin(\omega t)dt$ | $t^n$ | l'autre fonction |

**Le principe derrière ce choix** : on met en $u$ la puissance de $t$, car en la dérivant elle **descend d'un degré** ($t \to 1$, ou $t^2 \to 2t$) et finira par disparaître. Pour $t^n$, il faut appliquer l'IPP **$n$ fois de suite**.

### Exemple guidé A — une seule IPP

**Calculer** $\displaystyle\int_0^1 t\,e^{-t}dt$

**Étape 1 — poser** : $u(t) = t$ et $v'(t) = e^{-t}$

**Étape 2 — dériver $u$, primitiver $v'$** : $u'(t) = 1$ et $v(t) = -e^{-t}$

**Étape 3 — appliquer la formule**

$$\int_0^1 t\,e^{-t}dt = \left[-t\,e^{-t}\right]_0^1 - \int_0^1 1\cdot(-e^{-t})\,dt = \left[-t\,e^{-t}\right]_0^1 + \int_0^1 e^{-t}dt$$

**Étape 4 — calculer les deux morceaux**
- $\left[-te^{-t}\right]_0^1 = -1\cdot e^{-1} - 0 = -\dfrac1e$
- $\displaystyle\int_0^1 e^{-t}dt = \left[-e^{-t}\right]_0^1 = -\frac1e + 1$

$$\int_0^1 te^{-t}dt = -\frac1e + 1 - \frac1e = 1 - \frac2e$$

### Exemple guidé B — double IPP

**Calculer** $\displaystyle\int_0^\pi t^2\sin(3t)\,dt$

**Première IPP** : $u(t) = t^2$, $v'(t) = \sin(3t)$, donc $u'(t) = 2t$ et $v(t) = -\dfrac{\cos(3t)}{3}$

$$\int_0^\pi t^2\sin(3t)dt = \left[-\frac{t^2}{3}\cos(3t)\right]_0^\pi + \int_0^\pi 2t\,\frac{\cos(3t)}{3}dt = \frac{\pi^2}{3} + \frac23\int_0^\pi t\cos(3t)\,dt$$

*(le crochet vaut $-\frac{\pi^2}{3}\cos(3\pi) - 0 = \frac{\pi^2}{3}$ car $\cos(3\pi)=-1$)*

Il reste $\int_0^\pi t\cos(3t)dt$ — toujours un produit, donc **deuxième IPP**.

**Deuxième IPP** : $u(t) = t$, $v'(t) = \cos(3t)$, donc $u'(t)=1$ et $v(t) = \dfrac{\sin(3t)}{3}$

$$\int_0^\pi t\cos(3t)dt = \left[t\,\frac{\sin(3t)}{3}\right]_0^\pi - \int_0^\pi\frac{\sin(3t)}{3}dt = 0 - \frac13\left[-\frac{\cos(3t)}{3}\right]_0^\pi = \frac19\left[\cos(3t)\right]_0^\pi = \frac{-2}{9}$$

**Conclusion — on remonte**

$$\int_0^\pi t^2\sin(3t)\,dt = \frac{\pi^2}{3} + \frac23\times\left(\frac{-2}{9}\right) = \frac{\pi^2}{3} - \frac{4}{27}$$

---

# PARTIE 2 — Fonctions polynômes et décomposition en éléments simples

## 9. Pourquoi ce chapitre

La décomposition en éléments simples sert à **calculer la primitive d'une fonction rationnelle** (une fraction de polynômes). Elle est aussi utilisée dans le calcul de la **transformée de Laplace**.

> **Le problème qu'elle résout** : il n'existe aucune formule de primitive pour un quotient $\frac{u}{v}$. La solution est donc de **découper** la grosse fraction en une somme de petites fractions dont chacune, elle, est intégrable ($\frac{1}{x-a}$ donne $\ln\lvert x-a\rvert$, $\frac{1}{x^2+1}$ donne $\arctan$, etc.).

**Ce n'est pas un changement de variable** : le changement de variable *renomme* pour simplifier, la décomposition *découpe* pour simplifier.

## 10. Définitions de base

### Fonction polynôme

$x \mapsto P(x)$ est une fonction polynôme s'il existe $(a_n, a_{n-1}, \ldots, a_0) \in \mathbb{R}^{n+1}$ tel que :

$$\forall x \in \mathbb{R},\ P(x) = a_n x^n + a_{n-1}x^{n-1} + \cdots + a_1 x + a_0$$

Si $a_n \neq 0$, le **degré** de $P$ est $n$, noté $\deg(P) = n$.

### Fonction rationnelle

$x \mapsto F(x)$ est une fonction rationnelle s'il existe deux polynômes $P$ et $B$ tels que :

$$\forall x \in D_F,\ F(x) = \frac{P(x)}{B(x)} \qquad\text{où}\qquad D_F = \{x \in \mathbb{R} \mid B(x) \neq 0\}$$

En clair : **une fraction dont le haut et le bas sont des polynômes**. Le domaine exclut les valeurs qui annulent le dénominateur.

## 11. Division euclidienne de polynômes

### Théorème

Soient $A$ et $B$ deux polynômes. Il existe un **unique** couple $(Q,R)$ de polynômes tel que :

$$\forall x \in \mathbb{R},\ A(x) = B(x)\,Q(x) + R(x) \qquad\text{avec}\qquad \deg(R) < \deg(B)$$

$Q$ est le **quotient**, $R$ est le **reste**. C'est exactement la division posée de l'école primaire, transposée aux polynômes.

> **Remarque importante du cours** : la division s'effectue en posant la division **suivant les puissances décroissantes**.

### Exemple guidé

**Diviser** $A(x) = 2x^3 - x + 3$ par $B(x) = 3x^2 - 1$

On cherche par quoi multiplier $3x^2$ pour obtenir $2x^3$ : c'est $\frac23 x$. On soustrait :

$$2x^3 - x + 3 - \frac23 x\,(3x^2-1) = 2x^3 - x + 3 - \left(2x^3 - \frac23 x\right) = -\frac{x}{3} + 3$$

Le reste $-\frac{x}{3}+3$ est de degré 1, inférieur au degré 2 de $B$ : on s'arrête.

**Conclusion** :
$$2x^3 - x + 3 = (3x^2-1)\cdot\frac23 x + \left(\frac{-x}{3}+3\right)$$

avec $Q(x) = \frac23 x$ et $R(x) = \frac{-x}{3}+3$.

## 12. Quand faut-il diviser d'abord ?

### Règle préalable à toute décomposition

Soit $F(x) = \dfrac{P(x)}{B(x)}$.

- Si $\deg(P) \geq \deg(B)$ → **on effectue d'abord la division euclidienne**. On obtient $P = BQ + R$, donc :
$$F(x) = Q(x) + \frac{R(x)}{B(x)}$$
Le premier terme $Q(x)$ est un polynôme (facile à intégrer), et le second a maintenant $\deg(R) < \deg(B)$.

- Si $\deg(P) < \deg(B)$ → **on décompose directement**, sans division.

C'est pourquoi tout le reste du chapitre suppose $\deg(P) < \deg(B)$.

## 13. Les cinq cas de décomposition

La **forme** de la décomposition dépend uniquement de la façon dont le dénominateur se factorise. On pose la forme avec des coefficients inconnus, puis on les calcule.

| Cas | Dénominateur | Forme de la décomposition |
|---|---|---|
| **1** | $(x-a)(x-b)$ | $\dfrac{\alpha}{x-a} + \dfrac{\beta}{x-b}$ |
| **2** | $(x-a)^n(x-b)$ | $\dfrac{\alpha_1}{x-a} + \dfrac{\alpha_2}{(x-a)^2} + \cdots + \dfrac{\alpha_n}{(x-a)^n} + \dfrac{\beta}{x-b}$ |
| **3** | $(x-a)^n(x-b)^m$ | une chaîne de puissances pour chaque racine |
| **4** | $ax^2+bx+c$ avec $\Delta<0$ | reste tel quel (irréductible) : $\dfrac{P(x)}{ax^2+bx+c}$ |
| **5** | $(x-x_1)^n(x-x_2)^m(ax^2+bx+c)^k$ | chaînes de puissances + termes $\dfrac{\gamma_i x + \delta_i}{(ax^2+bx+c)^i}$ |

**La logique à retenir** :
- Un facteur simple $(x-a)$ → un terme $\dfrac{\alpha}{x-a}$
- Un facteur à la puissance $n$ → **$n$ termes**, avec toutes les puissances de 1 à $n$
- Un trinôme irréductible ($\Delta<0$) → un terme au numérateur **de degré 1** : $\dfrac{\gamma x + \delta}{ax^2+bx+c}$

## 14. Les deux méthodes pour calculer les coefficients

### Méthode 1 — par identification

On remet tout sur le même dénominateur, puis on compare les numérateurs **terme par terme** (coefficient de $x^2$, de $x$, terme constant), ce qui donne un système à résoudre.

### Méthode 2 — par les limites (« très pratique » selon le cours)

**Le principe** : pour isoler un coefficient, on multiplie l'égalité par le dénominateur de ce coefficient, puis on fait tendre $x$ vers la valeur qui annule ce dénominateur — tous les autres termes s'évanouissent.

Pour la forme $F(x) = \dfrac{\alpha}{x-a} + \dfrac{\beta}{x-b}$ :

$$\alpha = \lim_{x\to a}(x-a)F(x) \qquad\qquad \beta = \lim_{x\to b}(x-b)F(x)$$

Cette méthode est plus rapide car elle donne **un coefficient à la fois**, sans système.

### Méthode 3 (complémentaire) — valeur particulière

Quand il reste un dernier coefficient inconnu, on peut **choisir une valeur simple de $x$** (souvent $x=0$ ou $x=1$) et résoudre l'équation obtenue.

## 15. Exemples guidés de décomposition

### Exemple 1 (Cas 1) — les deux méthodes comparées

**Décomposer** $F(x) = \dfrac{2x-1}{x(x+1)}$

Le dénominateur est déjà factorisé : deux facteurs simples $x$ et $(x+1)$. Le degré du haut (1) est inférieur à celui du bas (2) : pas de division. **Forme posée** :

$$\frac{2x-1}{x(x+1)} = \frac{\alpha}{x} + \frac{\beta}{x+1}$$

**Par identification**

On remet à droite sur le dénominateur commun :
$$\frac{\alpha}{x} + \frac{\beta}{x+1} = \frac{\alpha(x+1)+\beta x}{x(x+1)} = \frac{x(\alpha+\beta)+\alpha}{x(x+1)}$$

Les dénominateurs étant identiques, les numérateurs sont égaux :
$$2x - 1 = x(\alpha+\beta) + \alpha$$

On compare terme par terme :
$$\begin{cases}\alpha+\beta = 2 & \text{(coefficient de } x)\\ \alpha = -1 & \text{(terme constant)}\end{cases} \Longleftrightarrow \begin{cases}\alpha = -1\\ \beta = 3\end{cases}$$

**Par les limites**

*Calcul de $\alpha$* : on multiplie par $x$ et on simplifie → $\dfrac{2x-1}{x+1} = \alpha + \dfrac{x\beta}{x+1}$

On fait $x \to 0$ : le terme de droite s'annule, il reste $\dfrac{-1}{1} = \alpha$, donc $\alpha = -1$

*Calcul de $\beta$* : on multiplie par $(x+1)$ et on simplifie → $\dfrac{2x-1}{x} = \dfrac{(x+1)\alpha}{x} + \beta$

On fait $x \to -1$ : le terme de gauche s'annule, il reste $\dfrac{-3}{-1} = \beta$, donc $\beta = 3$

**Conclusion (identique par les deux méthodes)** :
$$\frac{2x-1}{x(x+1)} = -\frac{1}{x} + \frac{3}{x+1}$$

### Exemple 2 — avec division euclidienne préalable

**Décomposer** $F(x) = \dfrac{x^3}{x^2-x-2}$

**Étape 1** — le degré du haut (3) est supérieur à celui du bas (2) → division euclidienne obligatoire :
$$x^3 = (x^2-x-2)(x+1) + 3x+2$$

D'où : $F(x) = (x+1) + \dfrac{3x+2}{x^2-x-2}$

**Étape 2** — factoriser le dénominateur restant : $x^2-x-2 = (x+1)(x-2)$

**Étape 3** — décomposer la fraction restante :
$$\frac{3x+2}{(x+1)(x-2)} = \frac{\alpha}{x+1} + \frac{\beta}{x-2}$$

Après calcul : $\alpha = \dfrac13$ et $\beta = \dfrac83$

**Conclusion** :
$$\frac{x^3}{x^2-x-2} = x+1+\frac{1}{3(x+1)} + \frac{8}{3(x-2)}$$

### Exemple 3 (Cas 2) — facteur à une puissance

**Décomposer** $F(x) = \dfrac{2x-1}{x^3(x+1)}$

Le facteur $x$ est à la puissance 3 → il faut **trois** termes pour lui. **Forme posée** :

$$F(x) = \frac{\alpha_1}{x} + \frac{\alpha_2}{x^2} + \frac{\alpha_3}{x^3} + \frac{\beta}{x+1}$$

**Calcul de $\beta$** : $\displaystyle\lim_{x\to-1}(x+1)F(x) = \lim_{x\to-1}\frac{2x-1}{x^3} = \frac{-3}{-1} = 3$, donc $\beta = 3$

**Calcul de $\alpha_3$** : $\displaystyle\lim_{x\to0}x^3 F(x) = \lim_{x\to0}\frac{2x-1}{x+1} = \frac{-1}{1} = -1$, donc $\alpha_3 = -1$

**Calcul de $\alpha_1$** (par la limite en $+\infty$) : $\displaystyle\lim_{x\to+\infty}xF(x) = \alpha_1+\beta$. Or $\displaystyle\lim_{x\to+\infty}\frac{2x-1}{x^2(x+1)} = 0$, donc $\alpha_1+\beta = 0$, soit $\alpha_1 = -3$

**Calcul de $\alpha_2$** (par une valeur particulière, $x=1$) :
$$F(1) = \frac{2-1}{1\cdot 2} = \frac12 = \alpha_1+\alpha_2+\alpha_3+\frac{\beta}{2}$$
$$\frac12 = -3 + \alpha_2 - 1 + \frac32 \implies \alpha_2 = 3$$

**Conclusion** :
$$\frac{2x-1}{x^3(x+1)} = -\frac{3}{x} + \frac{3}{x^2} - \frac{1}{x^3} + \frac{3}{x+1}$$

### Exemple 4 — application au calcul d'une intégrale (le but final)

**Calculer** $\displaystyle I = \int_1^2 \frac{dx}{x(x+1)^2}$

**Étape 1** — décomposer (résultat donné par le cours) :
$$\frac{1}{x(x+1)^2} = \frac{1}{x} - \frac{1}{x+1} - \frac{1}{(x+1)^2}$$

**Étape 2** — intégrer chaque morceau séparément (grâce à la linéarité) :

$$I = \int_1^2\frac{dx}{x} - \int_1^2\frac{dx}{x+1} - \int_1^2\frac{dx}{(x+1)^2}$$

$$I = \left[\ln x\right]_1^2 - \left[\ln(x+1)\right]_1^2 + \left[\frac{1}{x+1}\right]_1^2$$

**Étape 3** — calculer :
- $\left[\ln x\right]_1^2 = \ln 2 - 0 = \ln 2$
- $\left[\ln(x+1)\right]_1^2 = \ln 3 - \ln 2$
- $\left[\frac{1}{x+1}\right]_1^2 = \frac13 - \frac12 = -\frac16$

$$I = \ln 2 - (\ln 3 - \ln 2) - \frac16 = 2\ln 2 - \ln 3 - \frac16$$

**C'est tout l'intérêt du chapitre** : une intégrale impossible à calculer directement devient une somme de trois intégrales élémentaires.

### Exemple 5 (Cas 3) — division + puissance

**Décomposer** $F(x) = \dfrac{x^4+3x^3+3x^2+2x-2}{x(x+1)^2}$

Après division euclidienne : $F(x) = x+1+\dfrac{x-2}{x(x+1)^2}$

On décompose $g(x) = \dfrac{x-2}{x(x+1)^2} = \dfrac{\alpha}{x} + \dfrac{\beta}{x+1} + \dfrac{\gamma}{(x+1)^2}$

- $\displaystyle\lim_{x\to0}x\,g(x) = \alpha$, d'où $\alpha = -2$
- $\displaystyle\lim_{x\to-1}(x+1)^2 g(x) = \gamma$, d'où $\gamma = 3$
- $g(1) = \dfrac{-1}{4} = \alpha + \dfrac{\beta}{2} + \dfrac{\gamma}{4}$, d'où $\beta = 2$

**Conclusion** : $F(x) = x+1-\dfrac{2}{x} + \dfrac{2}{x+1} + \dfrac{3}{(x+1)^2}$

### Exemple 6 (Cas 4) — trinôme irréductible

**Décomposer** $F(x) = \dfrac{3x^4+1}{x^2+x+1}$

Division euclidienne : $3x^4+1 = (3x^2-3x)(x^2+x+1) + 3x+1$

D'où $F(x) = 3x^2-3x + \dfrac{3x+1}{x^2+x+1}$

**Point clé** : pour $x^2+x+1$, on a $\Delta = 1-4 = -3 < 0$. Le trinôme est **irréductible** (pas de racine réelle), donc **on ne le découpe pas davantage** — il reste tel quel.

**Conclusion** : $F(x) = 3x^2-3x+\dfrac{3x+1}{x^2+x+1}$

### Exemple 8 (Cas 5) — facteur simple + trinôme irréductible

**Décomposer** $F(x) = \dfrac{2}{x^3+1}$

**Étape 1** — factoriser le dénominateur : $x^3+1 = (x+1)(x^2-x+1)$, avec $\Delta<0$ pour $x^2-x+1$.

**Forme posée** (un terme simple, un terme à numérateur de degré 1) :
$$F(x) = \frac{\alpha}{x+1} + \frac{\gamma x + \delta}{x^2-x+1}$$

**Calculs** :
- $\displaystyle\lim_{x\to-1}(x+1)F(x) = \alpha$, d'où $\alpha = \dfrac{2}{3}$
- $\displaystyle\lim_{x\to+\infty}xF(x) = \alpha+\gamma = 0$, d'où $\gamma = -\dfrac23$
- $F(0) = \alpha + \delta = 2$, d'où $\delta = 2 - \dfrac23 = \dfrac43$

**Conclusion** :
$$\frac{2}{x^3+1} = \frac{2}{3(x+1)} + \frac{-2x+4}{3(x^2-x+1)}$$

### Exemple 9 — synthèse complète

**Décomposer** $F(x) = \dfrac{x^3-x^2+x-3}{(x+1)(x^2+1)}$

Division euclidienne : $F(x) = 1 - \dfrac{2x^2+4}{(x+1)(x^2+1)}$

On décompose $g(x) = \dfrac{2x^2+4}{(x+1)(x^2+1)} = \dfrac{\alpha}{x+1} + \dfrac{\gamma x+\delta}{x^2+1}$ (avec $\Delta<0$ pour $x^2+1$)

- $\displaystyle\lim_{x\to-1}(x+1)g(x) = \alpha = 3$
- $\displaystyle\lim_{x\to+\infty}x\,g(x) = \alpha+\gamma = 2$, d'où $\gamma = -1$
- $g(0) = \alpha+\delta = 4$, d'où $\delta = 1$

Donc $g(x) = \dfrac{3}{x+1} + \dfrac{-x+1}{x^2+1}$

**Conclusion** :
$$F(x) = 1 - \frac{3}{x+1} + \frac{x-1}{x^2+1}$$

---

# Récapitulatif — quel outil pour quelle intégrale ?

| Ce que tu vois | Outil à utiliser |
|---|---|
| Une forme directe de la table ($t^n$, $e^{\omega t}$, $\sin$, $\cos$) | Primitive directe |
| Une somme de termes | Linéarité, puis primitive de chaque terme |
| $\frac{u'}{u}$ ou $u'e^u$ (dérivée présente au numérateur) | Formule composée directe |
| Une expression emboîtée dont la dérivée est présente | **Changement de variable** |
| $\cos^2$, $\sin^2$ | **Linéarisation** ($\frac{1\pm\cos 2t}{2}$) |
| Un produit de fonctions non liées ($t\,e^t$, $t\cos t$) | **Intégration par parties** |
| Une fraction de polynômes | **Décomposition en éléments simples** |
| $\frac{1}{ax^2+bx+c}$ avec $\Delta<0$ | Forme canonique + changement de variable → $\arctan$ |
| Intervalle symétrique $[-a,a]$ et fonction impaire | Résultat = 0 immédiatement |
| Intervalle symétrique $[-a,a]$ et fonction paire | $2\int_0^a$ |
| Une période complète d'une fonction $T$-périodique | Ramener à $\int_0^T$ |
| Une fonction définie par morceaux (valeur absolue) | **Relation de Chasles** |

# Pièges classiques

| Piège | Conséquence |
|---|---|
| Calculer les nouvelles bornes avec la dérivée au lieu de la relation $t=\ldots$ | Bornes fausses |
| Oublier de changer les bornes (changement de variable avec bornes) | Résultat faux |
| Oublier de revenir à $x$ (primitive sans bornes) | Réponse incorrecte |
| Oublier le $+c$ (primitive sans bornes) | Réponse incomplète |
| Oublier qu'une variable seule vaut $x^1$ | Erreur de primitive |
| Décomposer sans vérifier les degrés d'abord | Décomposition impossible |
| Vouloir découper un trinôme avec $\Delta<0$ | Il est irréductible, on le garde |
| Chercher une « règle du quotient » pour intégrer | Elle n'existe pas |

---

*Synthèse établie à partir de PASSMATHS3AFISA — Partie 1 et Partie 2, Abdelrhani DAOUDI, ESIEA.*
