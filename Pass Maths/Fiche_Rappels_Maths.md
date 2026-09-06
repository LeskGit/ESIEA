# Fiche de rappels — Bases mathématiques

## 1. Quantificateurs et symboles logiques

| Symbole           | Signification                          | Exemple                                |
| ----------------- | -------------------------------------- | -------------------------------------- |
| $\forall$         | Pour tout                              | $\forall x \in \mathbb{R}, x^2 \geq 0$ |
| $\exists$         | Il existe                              | $\exists x \in \mathbb{R}, x^2 = 4$    |
| $\in$             | appartient à                           | $3 \in \mathbb{N}$                     |
| $\notin$          | n'appartient pas à                     | $\sqrt{2} \notin \mathbb{Q}$           |
| $\subset$         | est inclus dans                        | $\mathbb{N} \subset \mathbb{Z}$        |
| $\mapsto$         | "est associé à" (définit une fonction) | $x \mapsto x^2$                        |
| $\Rightarrow$     | implique                               | $x=2 \Rightarrow x^2=4$                |
| $\Leftrightarrow$ | équivaut à                             | $x^2=0 \Leftrightarrow x=0$            |

## 2. Ensembles de nombres

| Lettre | Nom | Contenu | Exemple |
|---|---|---|---|
| $\mathbb{N}$ | Entiers naturels | Entiers positifs et 0 | $0, 1, 2, 3, ...$ |
| $\mathbb{Z}$ | Entiers relatifs | Entiers positifs et négatifs | $-3, -1, 0, 2, 5$ |
| $\mathbb{D}$ | Décimaux | Nombre fini de chiffres après la virgule | $0.5\ ;\ 3.25$ |
| $\mathbb{Q}$ | Rationnels | Toute fraction $\frac{a}{b}$, $a,b$ entiers, $b \neq 0$ | $\frac{1}{3}\ ;\ \frac{2}{5}$ |
| $\mathbb{R}$ | Réels | Rationnels + irrationnels ($\sqrt{}$, $\pi$, $e$...) | $\sqrt{2}\ ;\ \pi$ |
| $\mathbb{C}$ | Complexes | Réels + imaginaires ($i^2=-1$) | $3+2i\ ;\ -1-5i$ |

Inclusion : $\mathbb{N} \subset \mathbb{Z} \subset \mathbb{D} \subset \mathbb{Q} \subset \mathbb{R} \subset \mathbb{C}$

## 3. Dérivées usuelles

| Fonction $f(x)$ | Dérivée $f'(x)$ | Condition |
|---|---|---|
| $k$ (constante) | $0$ | — |
| $x$ | $1$ | — |
| $x^n$ | $n\,x^{n-1}$ | $n \in \mathbb{N}$ |
| $(\alpha x+\beta)^n$ | $n\alpha(\alpha x+\beta)^{n-1}$ | $n \in \mathbb{N}$ |
| $\frac{1}{x}$ | $-\frac{1}{x^2}$ | $x \neq 0$ |
| $\sqrt{x}$ | $\frac{1}{2\sqrt{x}}$ | $x > 0$ |
| $e^{\omega x}$ | $\omega\,e^{\omega x}$ | — |
| $\ln(x)$ | $\frac{1}{x}$ | $x > 0$ |
| $\sin(\omega x)$ | $\omega\cos(\omega x)$ | — |
| $\cos(\omega x)$ | $-\omega\sin(\omega x)$ | — |
| $u(x)+v(x)$ | $u'(x)+v'(x)$ | somme |
| $u(x)\times v(x)$ | $u'(x)v(x)+u(x)v'(x)$ | produit |
| $\frac{u(x)}{v(x)}$ | $\frac{u'(x)v(x)-u(x)v'(x)}{v(x)^2}$ | quotient, $v \neq 0$ |
| $u(v(x))$ | $v'(x)\times u'(v(x))$ | composée |

## 4. Primitives usuelles

| Fonction $f(t)$ | Primitive $\int f(t)\,dt$ | Condition |
|---|---|---|
| $t^n$ | $\frac{t^{n+1}}{n+1}$ + constante | $n \in \mathbb{N}$ |
| $(\alpha t+\beta)^n$ | $\frac{(\alpha t+\beta)^{n+1}}{\alpha(n+1)}$ + constante | $n \in \mathbb{N}$ |
| $e^{\omega t}$ | $\frac{e^{\omega t}}{\omega}$ | $\omega \neq 0$ |
| $\sin(\omega t)$ | $-\frac{\cos(\omega t)}{\omega}$ | $\omega \neq 0$ |
| $\cos(\omega t)$ | $\frac{\sin(\omega t)}{\omega}$ | $\omega \neq 0$ |
| $\frac{u'(t)}{u(t)}$ | $\ln(\lvert u(t) \rvert)$ | $u$ dérivable, ne s'annule pas |
| $u'(t)\,e^{u(t)}$ | $e^{u(t)}$ | $u$ dérivable |
| $\frac{1}{1+x^2}$ | $\arctan(x)$ + constante | — |

## 5. Intégrales — définitions et propriétés

| Notion | Formule | Remarque |
|---|---|---|
| Primitive → Intégrale | $\int_a^b f(t)\,dt = [G(t)]_a^b = G(b)-G(a)$ | $G$ primitive de $f$ sur $[a,b]$ |
| Sans bornes | $\int g(x)\,dx$ | résultat = une **fonction** |
| Avec bornes | $\int_a^b g(x)\,dx$ | résultat = un **nombre** |
| Linéarité (somme) | $\int_a^b (f+g)\,dt = \int_a^b f\,dt + \int_a^b g\,dt$ | — |
| Linéarité (facteur) | $\int_a^b \lambda f(t)\,dt = \lambda\int_a^b f(t)\,dt$ | $\lambda$ constante |
| Relation de Chasles | $\int_a^b f = \int_a^c f + \int_c^b f$ | $a<c<b$ |
| Borne identique | $\int_a^a f(t)\,dt = 0$ | — |
| Fonction périodique | $\int_a^{a+T} f = \int_0^T f$ | $f$ continue et $T$-périodique |

---

*Fiche générée à partir de PASSMATHS3AFISA – Partie 1 (ESIEA, A. Daoudi) et des rappels de dérivation usuels.*

