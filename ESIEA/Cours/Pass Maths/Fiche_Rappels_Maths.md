# Fiche de rappels — Bases mathématiques

## 1. Quantificateurs et symboles logiques

| Symbole           | Signification                              | Exemple                                         |
| ----------------- | ------------------------------------------ | ----------------------------------------------- |
| $\forall$         | Pour tout                                  | $\forall x \in \mathbb{R},\ x^2 \geq 0$         |
| $\exists$         | Il existe                                  | $\exists x \in \mathbb{R},\ x^2 = 4$            |
| $\exists !$       | Il existe un unique                        | $\exists !\, x \in \mathbb{R},\ x^3 = 8$        |
| $\in$             | appartient à                               | $3 \in \mathbb{N}$                              |
| $\notin$          | n'appartient pas à                         | $\sqrt{2} \notin \mathbb{Q}$                    |
| $\subset$         | est inclus dans                            | $\mathbb{N} \subset \mathbb{Z}$                 |
| $\cup$            | union (réunion)                            | $[0,1] \cup [2,3]$                              |
| $\cap$            | intersection                               | $[0,2] \cap [1,3] = [1,2]$                      |
| $\emptyset$       | ensemble vide                              | $\mathbb{R}^- \cap \mathbb{R}^{+*} = \emptyset$ |
| $\mapsto$         | « est associé à » (définit une fonction)   | $x \mapsto x^2$                                 |
| $\to$             | « va vers » (ensemble de départ → arrivée) | $f : \mathbb{R} \to \mathbb{R}$                 |
| $\Rightarrow$     | implique                                   | $x=2 \Rightarrow x^2=4$                         |
| $\Leftrightarrow$ | équivaut à                                 | $x^2=0 \Leftrightarrow x=0$                     |

**Notations d'intervalles**

| Notation | Signification |
|---|---|
| $[a,b]$ | $a$ et $b$ **inclus** (fermé) |
| $]a,b[$ | $a$ et $b$ **exclus** (ouvert) |
| $[a,b[$ | $a$ inclus, $b$ exclu |
| $\mathbb{R}^*$ | l'ensemble privé de zéro |
| $\mathbb{R}^+$ | uniquement les positifs (et 0) |

## 2. Ensembles de nombres

| Lettre | Nom | Contenu | Exemple |
|---|---|---|---|
| $\mathbb{N}$ | Entiers naturels | Entiers positifs et 0 | $0, 1, 2, 3, \ldots$ |
| $\mathbb{Z}$ | Entiers relatifs | Entiers positifs et négatifs | $-3, -1, 0, 2, 5$ |
| $\mathbb{D}$ | Décimaux | Nombre fini de chiffres après la virgule | $0{,}5\ ;\ 3{,}25$ |
| $\mathbb{Q}$ | Rationnels | Toute fraction $\frac{a}{b}$, $a,b$ entiers, $b \neq 0$ | $\frac{1}{3}\ ;\ \frac{2}{5}$ |
| $\mathbb{R}$ | Réels | Rationnels + irrationnels ($\sqrt{\ }$, $\pi$, $e$…) | $\sqrt{2}\ ;\ \pi$ |
| $\mathbb{C}$ | Complexes | Réels + imaginaires ($i^2=-1$) | $3+2i\ ;\ -1-5i$ |

> Inclusion : $\mathbb{N} \subset \mathbb{Z} \subset \mathbb{D} \subset \mathbb{Q} \subset \mathbb{R} \subset \mathbb{C}$

## 3. Dérivées

### 3.1 Fonctions usuelles

| Fonction $f(x)$ | Dérivée $f'(x)$ | Condition |
|---|---|---|
| $k$ (constante) | $0$ | — |
| $x$ | $1$ | — |
| $x^n$ | $n\,x^{n-1}$ | $n \in \mathbb{N}$ |
| $(\alpha x+\beta)^n$ | $n\alpha(\alpha x+\beta)^{n-1}$ | $n \in \mathbb{N}$ |
| $\frac{1}{x}$ | $-\frac{1}{x^2}$ | $x \neq 0$ |
| $\frac{1}{x^n}$ | $-\frac{n}{x^{n+1}}$ | $x \neq 0$ |
| $\sqrt{x}$ | $\frac{1}{2\sqrt{x}}$ | $x > 0$ |
| $e^{\omega x}$ | $\omega\,e^{\omega x}$ | — |
| $\ln(x)$ | $\frac{1}{x}$ | $x > 0$ |
| $\sin(\omega x)$ | $\omega\cos(\omega x)$ | — |
| $\cos(\omega x)$ | $-\omega\sin(\omega x)$ | — |
| $\tan(x)$ | $1+\tan^2(x) = \frac{1}{\cos^2(x)}$ | $x \neq \frac{\pi}{2}+k\pi$ |
| $\arctan(x)$ | $\frac{1}{1+x^2}$ | — |

### 3.2 Règles d'opération

| Forme | Dérivée | Nom |
|---|---|---|
| $u + v$ | $u' + v'$ | somme |
| $k \cdot u$ | $k \cdot u'$ | multiple par une constante |
| $u \times v$ | $u'v + uv'$ | produit |
| $\frac{1}{v}$ | $-\frac{v'}{v^2}$ | inverse ($v \neq 0$) |
| $\frac{u}{v}$ | $\frac{u'v - uv'}{v^2}$ | **quotient** ($v \neq 0$) |
| $u(v(x))$ | $v'(x) \times u'(v(x))$ | composée (« chaîne ») |

### 3.3 Dérivées de fonctions composées (les formes en $u$)

| Forme | Dérivée |
|---|---|
| $u^n$ | $n\,u'\,u^{n-1}$ |
| $\sqrt{u}$ | $\frac{u'}{2\sqrt{u}}$ |
| $e^{u}$ | $u'\,e^{u}$ |
| $\ln(u)$ | $\frac{u'}{u}$ |
| $\sin(u)$ | $u'\cos(u)$ |
| $\cos(u)$ | $-u'\sin(u)$ |

## 4. Primitives

### 4.1 Fonctions usuelles

| Fonction $f(t)$ | Primitive $\int f(t)\,dt$ | Condition |
|---|---|---|
| $k$ (constante) | $k\,t$ + constante | — |
| $t^n$ | $\frac{t^{n+1}}{n+1}$ + constante | $n \in \mathbb{N}$ |
| $(\alpha t+\beta)^n$ | $\frac{(\alpha t+\beta)^{n+1}}{\alpha(n+1)}$ + constante | $n \in \mathbb{N}$ |
| $\frac{1}{t}$ | $\ln(\lvert t \rvert)$ + constante | $t \neq 0$ |
| $\frac{1}{t^n}$ | $\frac{-1}{(n-1)\,t^{n-1}}$ + constante | $n \geq 2$, $t \neq 0$ |
| $\frac{1}{\sqrt{t}}$ | $2\sqrt{t}$ + constante | $t > 0$ |
| $\sqrt{t}$ | $\frac{2}{3}t^{3/2}$ + constante | $t \geq 0$ |
| $e^{\omega t}$ | $\frac{e^{\omega t}}{\omega}$ | $\omega \neq 0$ |
| $\ln(t)$ | $t\ln(t) - t$ + constante | $t > 0$ |
| $\sin(\omega t)$ | $-\frac{\cos(\omega t)}{\omega}$ | $\omega \neq 0$ |
| $\cos(\omega t)$ | $\frac{\sin(\omega t)}{\omega}$ | $\omega \neq 0$ |
| $\frac{1}{1+t^2}$ | $\arctan(t)$ + constante | — |
| $\frac{1}{\cos^2(t)}$ | $\tan(t)$ + constante | $t \neq \frac{\pi}{2}+k\pi$ |

### 4.2 Formes composées (à reconnaître dans les exercices)

Ce sont les lignes du tableau des dérivées **lues à l'envers**. Ce sont elles qui servent le plus souvent.

| Fonction $f(t)$ | Primitive | Condition |
|---|---|---|
| $u'\,u^n$ | $\frac{u^{n+1}}{n+1}$ | $n \neq -1$ |
| $\frac{u'}{u}$ | $\ln(\lvert u \rvert)$ | $u$ ne s'annule pas |
| $u'\,e^{u}$ | $e^{u}$ | — |
| $\frac{u'}{\sqrt{u}}$ | $2\sqrt{u}$ | $u > 0$ |
| $\frac{u'}{u^2}$ | $-\frac{1}{u}$ | $u \neq 0$ |
| $u'\cos(u)$ | $\sin(u)$ | — |
| $u'\sin(u)$ | $-\cos(u)$ | — |
| $u' + v'$ | $u + v$ | linéarité |
| $k \cdot u'$ | $k \cdot u$ | linéarité |

> **Point de vigilance — le quotient $\frac{u}{v}$**
> Il n'existe **aucune formule générale** pour la primitive de $\frac{u}{v}$, contrairement à la dérivée qui a sa formule $\frac{u'v-uv'}{v^2}$. L'intégration n'a pas de « règle du quotient ».
> Pour intégrer une fraction, il faut la ramener à l'une des formes reconnaissables ci-dessus :
> - si le numérateur est la dérivée du dénominateur → forme $\frac{u'}{u}$, primitive $\ln\lvert u\rvert$
> - si le dénominateur est du type $1+t^2$ → forme $\arctan$
> - sinon → **décomposition en éléments simples** (voir PASSMATHS Partie 2) ou changement de variable

### 4.3 Techniques d'intégration

| Technique | Formule | Quand l'utiliser |
|---|---|---|
| Changement de variable | $\int_{\phi(a)}^{\phi(b)} f(x)\,dx = \int_a^b f(\phi(t))\,\phi'(t)\,dt$ | expression emboîtée dont la dérivée est présente |
| Intégration par parties | $\int_a^b u'v = [uv]_a^b - \int_a^b uv'$ | produit de deux fonctions « non liées » (ex. $t\cos(t)$, $t\,e^t$) |
| Décomposition en éléments simples | — | fraction rationnelle $\frac{P(x)}{Q(x)}$ |

## 5. Intégrales — définitions et propriétés

| Notion | Formule | Remarque |
|---|---|---|
| Définition d'une primitive | $G$ primitive de $f$ sur $I$ si $G' = f$ | $G$ est une **fonction** |
| Primitive → Intégrale | $\int_a^b f(t)\,dt = [G(t)]_a^b = G(b)-G(a)$ | $G$ primitive de $f$ sur $[a,b]$ |
| Sans bornes | $\int g(x)\,dx$ | résultat = une **fonction** |
| Avec bornes | $\int_a^b g(x)\,dx$ | résultat = un **nombre** |
| Lettres muettes | $\int_a^b g(x)dx = \int_a^b g(t)dt = \int_a^b g(u)du$ | le nom de la variable n'a pas d'importance |
| Linéarité (somme) | $\int_a^b (f+g)\,dt = \int_a^b f\,dt + \int_a^b g\,dt$ | — |
| Linéarité (facteur) | $\int_a^b \lambda f(t)\,dt = \lambda\int_a^b f(t)\,dt$ | $\lambda$ constante |
| Relation de Chasles | $\int_a^b f = \int_a^c f + \int_c^b f$ | $a<c<b$ |
| Borne identique | $\int_a^a f(t)\,dt = 0$ | — |
| Inversion des bornes | $\int_a^b f = -\int_b^a f$ | — |
| Fonction périodique | $\int_a^{a+T} f = \int_0^T f$ | $f$ continue et $T$-périodique |
| Fonction paire | $\int_{-a}^{a} f = 2\int_0^a f$ | $f(-x) = f(x)$ |
| Fonction impaire | $\int_{-a}^{a} f = 0$ | $f(-x) = -f(x)$ |

## 6. Méthode de calcul — procédures pas à pas

### CAS A — Intégrale directe (sans changement de variable)

**Quand ?** La fonction correspond directement à une ligne de la table des primitives (une puissance, une exponentielle simple, un sinus/cosinus, une somme de ces éléments).

1. **Séparer les termes** s'il y a une somme (linéarité), et sortir les coefficients devant chaque terme
2. **Trouver la primitive** de chaque terme avec la table
3. **Écrire entre crochets** $[\ \ ]$ avec les bornes de départ, sans les changer
4. **Appliquer $G(b) - G(a)$** : substituer la borne du haut, puis la borne du bas, puis soustraire
5. **Calculer** le résultat numérique

*Vérification optionnelle : dériver la primitive doit redonner la fonction de départ.*

### CAS B — Avec changement de variable (avec bornes)

**Quand ?** Il y a une expression emboîtée (dans une puissance, une exponentielle, une racine, un log) ou une fraction, et la dérivée de cette expression est présente ailleurs dans l'intégrale.

1. **Repérer et poser** $t = (\text{l'expression compliquée})$
   *Réflexes : ce qui est dans la parenthèse / en exposant / sous la racine / au dénominateur*
2. **Dériver la relation** pour obtenir $dt = (\ldots)\,dx$
   → **Cette étape sert UNIQUEMENT à convertir le $dx$ en $dt$**
3. **Valider le choix (test)** : l'expression trouvée à l'étape 2 est-elle bien présente dans l'intégrale ?
   - Oui → continuer
   - Non → mauvais choix de $t$, revenir à l'étape 1
4. **Convertir les bornes** — avec la relation $t = \ldots$ de l'étape 1, **JAMAIS avec la dérivée**
   - Substituer la borne du bas : $x = a \rightarrow t = ?$
   - Substituer la borne du haut : $x = b \rightarrow t = ?$
5. **Réécrire l'intégrale entièrement en $t$** : remplacer l'expression compliquée par $t$, remplacer le groupe $(\ldots)dx$ par $dt$, et mettre les nouvelles bornes
6. **Vérifier qu'il ne reste plus aucun $x$** dans l'intégrale — s'il en reste, le changement de variable ne s'applique pas correctement
7. **Calculer l'intégrale simple** en $t$ avec la table des primitives
8. **Appliquer $G(b') - G(a')$** avec les **nouvelles** bornes
9. **Ne pas revenir à $x$** — c'est inutile, le résultat est déjà un nombre

### Variante — Primitive sans bornes avec changement de variable

Si l'intégrale n'a **pas de bornes** (le résultat doit être une fonction) :

1. **Étapes 1 à 3 identiques au cas B** (poser $t$, dériver, valider)
2. **Pas de bornes à changer** (il n'y en a pas)
3. **Réécrire** en $t$
4. **Calculer** la primitive en $t$
5. **Revenir à la variable $x$** : remplacer $t$ par son expression en $x$
6. **Ajouter $+\,c$** (la constante)

### Tableau des pièges à éviter

| Piège | Conséquence |
|---|---|
| Calculer les bornes avec la dérivée au lieu de $t = \ldots$ | Bornes fausses → résultat faux |
| Oublier de changer les bornes | Résultat faux |
| Oublier de revenir à $x$ (cas sans bornes) | Réponse incomplète / incorrecte |
| Oublier le $+\,c$ (cas sans bornes) | Réponse incomplète |
| Oublier qu'une variable seule vaut $x^1$ | Erreur sur la primitive |
| Laisser un $x$ traîner après conversion | Le calcul est bloqué ou faux |
| Chercher une « règle du quotient » pour intégrer $\frac{u}{v}$ | Elle n'existe pas (voir §4.2) |

## 7. Fonctions périodiques — rappel

$f$ est **$T$-périodique** si :

$$\forall x \in \mathbb{R},\ f(x+T) = f(x)$$

Plus généralement : $\forall x \in \mathbb{R},\ \forall n \in \mathbb{Z},\ f(x + nT) = f(x)$

**Méthode pour calculer $f$ en un point hors de l'intervalle de définition** : ajouter ou retrancher des multiples de $T$ pour ramener le point dans l'intervalle de référence, puis lire la valeur.

*Exemple* : $f$ est $2\pi$-périodique définie sur $[0,2\pi[$. Alors $f(3\pi) = f(\pi + 2\pi) = f(\pi)$, et $\pi$ est bien dans l'intervalle connu.

---

*Fiche compilée à partir de PASSMATHS3AFISA — Partie 1 (ESIEA, A. Daoudi) et des tables de dérivation / primitives usuelles.*
