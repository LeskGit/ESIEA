# Électronique — Notes de cours

---

## Séance 1 — Bases des circuits électriques

### Dipôle

**Dipôle** : composant électronique à deux bornes qui permet de se connecter à un circuit.
- **Passif** : ne génère pas d'énergie
- **Actif** : génère de l'énergie

### Tension et courant

- **Tension aux bornes d'une pile** : borne positive et négative (pas ou trop d'électrons).
- **Courant** : déplacement de charges électriques → a une direction.
  - Noté `i_AB` : le courant circule de A vers B
  - L'inverse : `i_BA = -i_AB`
  - **Convention** : du potentiel le plus élevé (+) vers le potentiel le moins élevé (−) → *(+ → −)*, soit l'inverse du sens de la tension.

### Conventions

| Convention | Description |
|---|---|
| **Générateur** | La flèche de tension est orientée dans le **même sens** que la flèche de courant |
| **Récepteur** | Tension et courant sont en **sens opposé** |

### Loi d'Ohm

$$U = R \times I \qquad I = \frac{U}{R} \qquad R = \frac{U}{I}$$

| Symbole | Grandeur | Unité |
|---|---|---|
| U | Tension | Volt (V) |
| I | Intensité | Ampère (A) |
| R | Résistance | Ohm (Ω) |

### Association de dipôles

**En série**
- Traversés par la **même intensité** de courant électrique.

**En parallèle**
- Deux dipôles sont en parallèle quand ils sont branchés entre les **deux mêmes nœuds** : le courant se sépare entre plusieurs chemins.
- **U** : identique avant et après, mais pas pendant la division
- **I** : s'additionne

### Réseau de Kirchhoff

Ensemble d'éléments électriques (R, I, C, générateur...) reliés entre eux par des bornes.
Chaque borne est caractérisée par deux grandeurs :
- Potentiel électrique (V)
- Intensité du courant (I)

**Vocabulaire :**
- **Branche (B)** : portion de circuit comprise entre deux nœuds, parcourue par un même courant.
- **Maille (M)** : chemin fermé constitué de plusieurs branches, parcouru en partant d'un nœud et en y revenant, sans repasser deux fois par la même branche.

### Lois de Kirchhoff

> **Loi des nœuds**
> La somme des courants entrants = la somme des courants sortants (le courant ne disparaît pas à la dispersion).

> **Loi des tensions (ou des mailles)**
> La somme des tensions dans une maille = 0.

### Règle du diviseur de tension

$$V_i = R_i \times I = V_{total} \times \frac{R_i}{\sum R}$$

→ Permet de calculer la tension aux bornes d'une résistance.

### Règle du diviseur de courant

Pour deux résistances en parallèle, le courant se répartit entre elles :

$$I_1 = I_{total} \times \frac{R_2}{R_1 + R_2} \qquad I_2 = I_{total} \times \frac{R_1}{R_1 + R_2}$$

→ Permet de calculer le courant traversant une résistance parmi plusieurs en parallèle. À noter : chaque résistance reçoit une part du courant total proportionnelle à l'**autre** résistance (inverse du diviseur de tension).

---

## Séance 2 — Théorèmes de Thévenin et Norton

### Théorème de Thévenin

Méthode pour trouver facilement le générateur de Thévenin dans un réseau compliqué.

1. **Isoler le sous-réseau** : on choisit la partie qui nous intéresse.
2. **Supprimer temporairement les sources** :
   - Source de tension → remplacée par un **court-circuit**
   - Source de courant → remplacée par un **circuit ouvert** (coupure)
3. **Calculer la résistance de Thévenin** → résistance équivalente.
4. **Recalculer la tension totale** en remettant les sources.

### Théorème de Norton

Même principe que Thévenin, mais appliqué à l'**intensité** (courant) au lieu de la tension.

### Transformation Thévenin ↔ Norton

Les deux modèles sont équivalents et on peut passer de l'un à l'autre directement :

$$R_{Norton} = R_{Thévenin} \qquad I_{Norton} = \frac{U_{Thévenin}}{R_{Thévenin}} \qquad U_{Thévenin} = R_{Norton} \times I_{Norton}$$

→ La résistance est identique dans les deux modèles ; seule la source change (tension en série pour Thévenin, courant en parallèle pour Norton).

---

## Séance 3 — Régime sinusoïdal

Cours complet disponible dans le polycopié (formules et développement des valeurs).

**Notions à connaître :**

- Impédance
- Inductance
- Fréquence
- Période
- Déphasage
	- Phase initiale
- Amplitude
- Nombres complexes liés au sinus
- Trigonométrie (cercle trigonométrique)
- Arctangente
- Cosinus / Sinus

---

## Séance 4-5-6

*(à compléter)*
