
## A. Introduction aux signaux

### A.1. Définition

Un **signal** est la manifestation physique d'une grandeur mesurable, porteuse d'une information à transmettre.

> **Exemple** : une onde acoustique (la voix) est captée par un microphone qui la convertit en signal électrique — une tension qui varie dans le temps et reproduit la forme de l'onde sonore.

Le **bruit** est tout phénomène perturbateur qui gêne la perception ou l'interprétation d'un signal (ex. friture sur une ligne téléphonique, grain sur une image).

### A.2. À quoi sert le traitement du signal

Le traitement du signal regroupe quatre grandes familles d'opérations :

- **Analyse** des caractéristiques du signal (temporelle ou fréquentielle) ;
- **Modification** du signal : élimination du bruit et des dégradations (filtrage) ;
- **Mise en forme** du signal : numérisation, modulation, etc. ;
- **Extraction** du maximum d'information utile pour une application donnée.

> **Champs d'application concrets** (donnés en cours) : acoustique (parole, musique), biomédical (ECG, EEG), mécanique (vibrations), télécommunications, météorologie (relevés de température), économie (indices boursiers). Le point commun : dans tous ces domaines on mesure une grandeur physique variable dans le temps et on veut en extraire de l'information utile malgré le bruit.

### A.3. Rapport signal sur bruit (S/B, RSB, SNR)

$$RSB_{dB} = 10 \log_{10}\left(\frac{P_s}{P_B}\right)$$

avec $P_s$ la puissance du signal et $P_B$ la puissance du bruit.

| Cas | Signification |
|---|---|
| $RSB > 0$ | $P_s > P_B$ : le signal domine le bruit (bonne qualité) |
| $RSB = 0$ | $P_s = P_B$ : signal et bruit ont la même puissance |
| $RSB < 0$ | $P_s < P_B$ : le bruit domine, le signal est « noyé » dans le bruit (mauvaise qualité) |

Le décibel étant une échelle logarithmique, chaque tranche de +10 dB correspond à un rapport de puissance ×10 en faveur du signal (et inversement pour le bruit).

> **Exemple** : un signal audio enregistré avec $P_s = 100$ et $P_B = 1$ donne $RSB = 10\log_{10}(100) = 20\ dB$ — très bonne qualité. Si le bruit augmente jusqu'à $P_B = P_s$, $RSB = 0\ dB$ : on entend autant de bruit que de signal utile.

## B. Classification des signaux

Les signaux se classent selon quatre critères indépendants : leur **dimension**, leur **évolution**, leur **morphologie**, et leur **énergie/puissance**.

### B.1. Classification dimensionnelle

| Type | Définition | Exemple |
|---|---|---|
| **Monodimensionnel (1-D)** | fonction d'**une seule variable indépendante** | tension électrique $x(t)$ mesurée dans le temps aux bornes d'une source alternative |
| **Bidimensionnel (2-D)** | fonction de **deux variables**, $x(n_1, n_2)$ | image numérique — les deux variables sont les coordonnées spatiales (ligne/colonne) d'un pixel, pas un axe temporel |
| **Multidimensionnel (M-D)** | fonction de **plusieurs variables** | vidéo (3-D) : $x(n_1, n_2, t)$ — deux coordonnées spatiales + le temps |

> Correction par rapport à tes notes : le monodimensionnel n'est **pas** défini par « une fréquence » mais par **une seule variable indépendante** (le plus souvent le temps). La fréquence est une caractéristique du *contenu* du signal (voir partie D), pas de sa dimension. De même le bidimensionnel n'est pas « bidirectionnel » — c'est bien deux **variables**, pas deux sens/directions.

### B.2. Classification selon l'évolution : déterministe / aléatoire

**Signaux déterministes** : évolution **parfaitement prévisible**, décrite par un modèle mathématique.

- **Périodiques** : se répètent à l'identique à intervalles réguliers → $x(t) = x(t+T)$, $T$ = période.
  > **Exemple** : le secteur électrique domestique, $x(t) = 230\sqrt{2}\sin(2\pi \cdot 50 \cdot t)$, période $T = 20$ ms.
- **Non périodiques (apériodiques)** :
  - **transitoires** : montée rapide suivie d'une décroissance, liée à un changement d'état d'un système, durée limitée. *Exemple : la décharge d'un condensateur, un choc mécanique.*
  - **pseudo-périodiques** : somme de sinusoïdes de périodes différentes, sans période commune exacte. *Exemple : un accord de plusieurs notes de musique dont les fréquences ne sont pas multiples les unes des autres.*

**Signaux aléatoires (probabilistes)** : comportement temporel **imprévisible**, seules des observations statistiques sont possibles (moyenne, écart-type, histogramme). *Exemple : le bruit, le signal de parole.*

- **Stationnaires** : les caractéristiques statistiques ne varient pas dans le temps. *Exemple : un bruit de fond électronique constant.*
- **Non stationnaires** : les caractéristiques statistiques varient dans le temps. *Exemple : le signal de parole, dont l'énergie et le spectre changent constamment selon ce qui est prononcé.*

> Remarque : « aléatoire » et « probabiliste » désignent la même famille — ce n'est pas une troisième catégorie séparée de déterministe/aléatoire, juste un synonyme utilisé dans le cours.

### B.3. Signal réel / complexe — module et phase

**Rappel maths** : un nombre imaginaire repose sur $j$ (noté $i$ en maths pures, $j$ en électronique pour ne pas confondre avec l'intensité), défini par $j^2 = -1$. Un nombre complexe combine une partie réelle et une partie imaginaire : $z = a + jb$. On le représente comme un point dans un plan (axe horizontal = partie réelle, axe vertical = partie imaginaire).

- **Signal réel** : toutes ses valeurs sont réelles. *Exemple : $x(t) = A\sin(2\pi t)$.*
- **Signal complexe** : $x(t) = \text{Re}(x(t)) + j\,\text{Im}(x(t)) = |x(t)|\,e^{j\phi(t)}$.

**Module** $|x(t)|$ : distance entre l'origine et le point représentant $x(t)$ dans le plan complexe.
$$|x(t)| = \sqrt{\text{Re}(x(t))^2 + \text{Im}(x(t))^2}$$

**Phase / argument** $\phi(t)$ (la lettre grecque **phi**) : angle entre l'axe des réels et le vecteur $x(t)$.
$$\phi(t) = \arctan\!\left(\frac{\text{Im}(x(t))}{\text{Re}(x(t))}\right)$$

> **Exemple du cours** : $x(t) = A e^{j3\pi t} = A\cos(3\pi t) + jA\sin(3\pi t)$
> → $\text{Re}(x(t)) = A\cos(3\pi t)$, $\text{Im}(x(t)) = A\sin(3\pi t)$
> → $|x(t)| = A$ (constant), $\phi(t) = 3\pi t$ (la phase croît linéairement avec le temps — le vecteur tourne dans le plan complexe).
>
> **Pourquoi c'est utile en traitement du signal** : les signaux complexes ne sont pas juste une curiosité mathématique — la transformée de Fourier (partie D) transforme un signal réel en une fonction à valeurs *complexes*, où le module donne l'amplitude de chaque fréquence et la phase son décalage temporel.

### B.4. Signaux pairs / impairs

- **Pair** : symétrique par rapport à l'axe des ordonnées → $x(-t) = x(t)$. *Exemple : $x(t) = \cos(t)$, ou $x(t) = |t|$.*
- **Impair** : symétrique par rapport à l'origine → $x(-t) = -x(t)$. *Exemple : $x(t) = \sin(t)$, ou $x(t) = t$.*

### B.5. Signal causal *(notion du PDF absente de tes notes)*

Un signal $x(t)$ est dit **causal** si $x(t) = 0$ pour $t < 0$ — c'est-à-dire qu'il n'existe pas avant l'instant zéro (avant que la « cause » ne se produise). Pour rendre un signal quelconque causal, on le multiplie simplement par l'échelon unité $u(t)$ (voir partie C).

> **Exemple** : $f(t) = \sin(\omega t)\cdot u(t)$ décrit une sinusoïde qui ne « démarre » qu'à $t = 0$ — avant, elle vaut 0. Concept important en pratique : un système physique (un filtre, un capteur) ne peut réagir qu'*après* avoir reçu une entrée, jamais avant — tout système réel est donc causal.

### B.6. Classification morphologique : continu / discret

| | Définition | Notation |
|---|---|---|
| **Signal continu** (temps continu) | Défini pour **toute** valeur réelle du temps | $x(t)$, $t \in \mathbb{R}$ |
| **Signal discret** (temps discret) | Défini seulement à des instants précis, sur une grille de points | $x(n)$, $n \in \mathbb{Z}$ |

L'origine d'un signal discret peut être **naturelle** (ex. relevé économique mensuel) ou issue d'un **échantillonnage** : on prélève les valeurs d'un signal continu à intervalles réguliers (voir C.7 et D.4).

### B.7. Lien avec l'entrée analogique Arduino

Application directe du point précédent. Le monde physique (une tension délivrée par un capteur, un potentiomètre) est un **signal continu**. Le convertisseur analogique-numérique (ADC) de l'Arduino fait deux opérations pour le rendre numérique :

1. **Échantillonnage** (dans le temps) : une mesure toutes les X millisecondes → $x(t) \to x(n)$.
2. **Quantification** (en amplitude) : chaque valeur mesurée est arrondie à l'un des niveaux discrets disponibles — sur un Arduino Uno, l'ADC a une résolution de 10 bits, soit $2^{10} = 1024$ niveaux (0 à 1023) au lieu d'une tension continue de 0 à 5 V.

**Échantillonnage + quantification = numérisation** (voir D.5) : c'est exactement ce que fait `analogRead()` en interne.

> **Exemple chiffré** : sur un Uno, une résolution de $5\text{V}/1024 \approx 4{,}9\ \text{mV}$ par niveau. Une tension mesurée de 2,50 V est donc arrondie au niveau discret le plus proche, avec une erreur de quantification d'au plus ±2,4 mV.

### B.8. Énergie et puissance d'un signal

| | Temps continu | Temps discret |
|---|---|---|
| **Énergie totale** | $E_{tot} = \int_{-\infty}^{+\infty} \lvert x(t) \rvert^2\, dt$ | $E_{tot} = \sum_{n=-\infty}^{+\infty} \lvert x(n) \rvert^2$ |
| **Puissance moyenne** | $P_{moy} = \lim_{T \to \infty} \frac{1}{T}\int_{-T/2}^{T/2} \lvert x(t) \rvert^2\, dt$ | $P = \lim_{k \to \infty} \frac{1}{2k+1}\sum_{n=-k}^{k} \lvert x(n) \rvert^2$ |

On calcule la puissance moyenne quand l'énergie totale diverge — c'est une façon de mesurer la « quantité de signal » par unité de temps plutôt que sur une durée infinie.

**Classement des signaux** :
- **Énergie finie** ($0 < E_{tot} < +\infty$) → puissance moyenne **nulle**. Signaux non périodiques / transitoires, à support temporel borné. *Exemple : une impulsion isolée, un choc mécanique amorti.*
- **Puissance moyenne finie** ($0 < P_{moy} < +\infty$) → énergie **infinie**. Signaux périodiques et permanents (aléatoires ou non). *Exemple : une sinusoïde qui dure indéfiniment — son énergie totale diverge, mais sa puissance moyenne est finie et vaut $A^2/2$.*

## C. Signaux élémentaires *(section du PDF absente de tes notes)*

Ce sont les « briques de base » utilisées pour construire ou décrire des signaux plus complexes.

**Exemple** : La fonction signe, l'échelon unité (Heaviside), le signal porte (une fenêtre rectangulaire), l'impulsion de Dirac, le peigne de Dirac (une succession périodique d'impulsions de Dirac), le signal sinusoïdal, et le sinus cardinal.

Pourquoi on les étudie à part : ils servent d'outils pratiques. Par exemple l'échelon unité sert à "couper" un signal pour le rendre causal (rien avant t=0), le signal porte sert à modéliser une fenêtre d'observation limitée dans le temps, et le peigne de Dirac sert justement à modéliser mathématiquement l'échantillonnage — chaque impulsion du peigne "prélève" une valeur du signal continu à un instant précis, exactement ce que fait l'ADC de l'Arduino.

### C.1. Translation temporelle

Décaler un signal $x(t)$ dans le temps :
- $x(t - t_0)$, $t_0 > 0$ : décalage vers la **droite**, le signal est **retardé** de $t_0$.
- $x(t - t_0)$, $t_0 < 0$ : décalage vers la **gauche**, le signal est **avancé** de $t_0$.

> **Exemple** : un signal reçu par un radar est une version retardée du signal émis, $t_0$ étant le temps de trajet aller-retour de l'onde jusqu'à l'obstacle (voir E.3).

### C.2. Fonction signe

$$\text{sgn}(t) = \begin{cases} 1 & \text{si } t > 0 \\ 0 & \text{si } t = 0 \\ -1 & \text{si } t < 0 \end{cases}$$

### C.3. Échelon unité (fonction de Heaviside)

$$u(t) = \begin{cases} 1 & \text{si } t \geq 0 \\ 0 & \text{si } t < 0 \end{cases}$$

C'est cette fonction qui sert à « rendre causal » un signal (voir B.5) : $x(t)\cdot u(t)$ annule tout ce qui précède $t=0$.

### C.4. Signal porte (fenêtre rectangulaire)

$$rect_T(t) = P(t) = \begin{cases} \dfrac{1}{T} & \text{si } -\dfrac{T}{2} \leq t \leq \dfrac{T}{2} \\ 0 & \text{sinon} \end{cases}$$

de surface $S = \int_{-\infty}^{+\infty} P(t)\,dt = 1$.

> **Exemple d'usage** : le signal porte sert à modéliser une « fenêtre d'observation » — par exemple, mesurer un signal pendant une durée limitée $T$ revient à multiplier ce signal par une porte de largeur $T$.

### C.5. Impulsion de Dirac $\delta(t)$

Impulsion idéale, infiniment fine et infiniment haute, d'aire unité — limite du signal porte quand sa largeur tend vers 0 :

$$\delta(t) = \lim_{T \to 0} P(t), \quad \delta(t) = 0 \text{ pour } t \neq 0, \quad \int_{-\infty}^{+\infty}\delta(t)\,dt = 1$$

**Propriétés utiles** :
- Multiplication par une fonction : $f(t)\cdot\delta(t-t_0) = f(t_0)\cdot\delta(t-t_0)$ — l'impulsion de Dirac « échantillonne » la fonction à l'instant $t_0$.
- Intégrale : $\int_{-\infty}^{+\infty} f(t)\cdot\delta(t-t_0)\,dt = f(t_0)$.

> **Exemple d'usage** : ces deux propriétés sont la base mathématique de l'échantillonnage (C.6) — multiplier un signal continu par une impulsion de Dirac à l'instant $t_0$ revient à « prélever » exactement la valeur du signal à cet instant.

### C.6. Peigne de Dirac — modèle de l'échantillonnage

$$\delta_T(t) = \sum_{k=-\infty}^{+\infty}\delta(t-kT)$$

Succession périodique d'impulsions de Dirac espacées de $T$ (période du peigne), aussi appelée **train d'impulsions** ou **fonction d'échantillonnage**. Multiplier un signal continu par un peigne de Dirac de période $T$ revient exactement à l'échantillonner à intervalles réguliers $T$ : c'est le modèle mathématique de ce que fait un ADC (voir B.7).

### C.7. Signal sinusoïdal

$$x(t) = A\sin(\omega_0 t + \varphi)$$

| Symbole | Nom | Relation |
|---|---|---|
| $A$ | amplitude | — |
| $\omega_0$ | pulsation (rad/s) | $\omega_0 = 2\pi f_0$ |
| $T_0$ | période (s) | — |
| $f_0$ | fréquence (Hz) | $f_0 = 1/T_0$ |
| $\varphi$ | phase à l'origine | décalage du signal à $t=0$ |

Pour rendre une sinusoïde **causale**, on la multiplie par l'échelon unité : $f(t) = \sin(\omega t)\cdot u(t)$ (nulle pour $t<0$, sinusoïdale pour $t \geq 0$).

> C'est cette forme sinusoïdale qui est la brique de base de toute la partie D : un signal périodique quelconque se décompose en une **somme** de signaux de cette forme (série de Fourier).

### C.8. Sinus cardinal

$$\text{sinc}(x) = \frac{\sin(x)}{x}, \qquad \lim_{x \to 0}\text{sinc}(x) = 1$$

S'annule aux points $x = k\pi$ ($k = \pm1, \pm2, \dots$). Cette fonction réapparaît en filtrage numérique et en échantillonnage (elle est la transformée de Fourier d'un signal porte) — le cours y reviendra dans la partie filtres/numérisation.

## D. Analyse fréquentielle

### D.1. Analyse temporelle vs analyse fréquentielle

- **Analyse temporelle** : étude du signal en fonction du **temps** — à quoi il ressemble seconde par seconde.
- **Analyse fréquentielle** : étude du signal en fonction de la **fréquence** — quelles composantes fréquentielles il contient (son spectre).

Les deux sont complémentaires : un signal difficile à interpréter en temporel peut être très lisible en fréquentiel, et inversement.

### D.2. Transformée de Fourier

Outil mathématique qui fait passer un signal du domaine temporel au domaine fréquentiel — il donne l'amplitude (et la phase) de chacune des fréquences qui composent le signal.

> **Exemple** : un accord de piano semble complexe en temporel (une courbe qui oscille de façon irrégulière), mais son spectre de Fourier montre clairement des pics nets aux fréquences des notes jouées.

### D.3. Série de Fourier

**N'importe quel signal périodique** peut se décomposer en une somme (potentiellement infinie) de sinusoïdes, dont les fréquences sont des multiples entiers de la fréquence fondamentale $f_0$ (fondamentale + harmoniques $2f_0, 3f_0, \dots$). La transformée de Fourier généralise cette idée aux signaux non périodiques.

> **Exemple** : un signal carré périodique se décompose en une fondamentale sinusoïdale plus une somme infinie d'harmoniques impairs d'amplitude décroissante ($f_0, 3f_0, 5f_0, \dots$) — c'est pour ça qu'un son « carré » de synthé sonne plus riche/agressif qu'une sinusoïde pure : il contient beaucoup plus de fréquences.

### D.4. Hautes / basses fréquences — lissage

- **Basses fréquences** : variations lentes du signal, sa tendance générale.
- **Hautes fréquences** : variations rapides, détails fins — mais aussi souvent le bruit.

**Lisser** un signal = atténuer ses hautes fréquences pour ne garder que l'évolution lente. *Exemple : une moyenne glissante sur des mesures de température bruitées fait disparaître les petites fluctuations rapides et ne garde que la tendance générale.*

### D.5. Filtre / numérisation des signaux

Un **filtre** modifie le contenu fréquentiel d'un signal de façon sélective :

| Type de filtre | Effet | Exemple d'usage |
|---|---|---|
| Passe-bas | garde les basses fréquences, coupe les hautes → lissage | enlever le souffle/bruit haute fréquence d'un enregistrement audio |
| Passe-haut | garde les hautes fréquences, coupe les basses | enlever le ronflement 50 Hz du secteur, ou une dérive lente de capteur |
| Passe-bande | ne garde qu'une plage de fréquences | isoler la voix (environ 300 Hz – 3400 Hz) dans un enregistrement |
| Coupe-bande (réjecteur) | élimine une plage précise | supprimer un sifflement à une fréquence donnée |

Pour choisir passe-bas ou passe-haut afin d'enlever du bruit, **ça dépend du signal** : on choisit le filtre qui laisse passer la bande où se trouve le signal utile et qui coupe la bande où se trouve le bruit. Le bruit est le plus souvent en haute fréquence (bruit électronique) → passe-bas ; mais une dérive lente ou un 50 Hz secteur sont en basse fréquence → passe-haut.

**Numériser un signal**, étapes :
1. **Échantillonnage** : prélever les valeurs à intervalles de temps réguliers (modélisé par le peigne de Dirac, C.6) → $x(t) \to x(n)$.
2. **Quantification** : arrondir chaque valeur prélevée à un niveau discret parmi un nombre fini de niveaux (dépend de la résolution en bits du convertisseur — voir exemple Arduino en B.7).
3. (Éventuellement) **Codage** : représenter chaque niveau quantifié en binaire pour le stockage/la transmission.

## E. Analyse corrélative des signaux *(section du PDF absente de tes notes)*

L'analyse corrélative mesure la **ressemblance** entre deux signaux (ou entre un signal et lui-même décalé dans le temps).

### E.1. Inter-corrélation

Compare un signal de référence $x(t)$ à un signal $y(t)$ retardé :

$$R_{xy}(\tau) = \int_{-\infty}^{+\infty} x(t)\cdot y(t+\tau)\,dt \quad \text{(signaux à énergie finie)}$$

Pour des signaux à énergie infinie / puissance moyenne finie :
$$R_{xy}(\tau) = \lim_{T \to \infty}\frac{1}{T}\int_{-T/2}^{T/2} x(t)\cdot y(t+\tau)\,dt$$

et pour des signaux périodiques de période $T$, la moyenne se calcule directement sur une période (sans passer à la limite).

$R_{xy}$ est une fonction du **décalage** $\tau$ : son maximum indique le décalage temporel pour lequel les deux signaux se ressemblent le plus.

### E.2. Autocorrélation

Cas particulier où $y(t) = x(t)$ : on compare un signal à ses propres copies retardées (mesure de ressemblance du signal avec lui-même au cours du temps).

$$R_{xx}(\tau) = \int_{-\infty}^{+\infty} x(t)\cdot x(t+\tau)\,dt$$

**Propriétés** :
- $R_{xx}(\tau) \leq R_{xx}(0)$ : le maximum est toujours atteint en $\tau = 0$ (un signal ressemble le plus à lui-même sans décalage).
- $R_{xx}(\tau)$ est **paire** pour les signaux réels.
- $R_{xx}(0) = E_{tot}$ (signal à énergie finie) ou $R_{xx}(0) = P_{moy}$ (signal à puissance moyenne finie) — l'autocorrélation à l'origine redonne l'énergie ou la puissance du signal (voir B.8).

### E.3. Exemple d'application : le radar

Le radar émet un signal, puis reçoit le même signal réfléchi par un obstacle (un avion), retardé d'un temps $\tau_0$ correspondant au trajet aller-retour de l'onde. En calculant l'inter-corrélation (ou l'autocorrélation si on compare le signal reçu à l'émis) entre les deux, on obtient un pic marqué exactement à $\tau = \tau_0$ : le retard mesuré permet de **calculer la distance de l'obstacle**, puisque distance $= \dfrac{c \cdot \tau_0}{2}$ avec $c$ la vitesse de l'onde.

### E.4. Bruit blanc

Le **bruit blanc** (par analogie avec la lumière blanche, qui contient toutes les fréquences lumineuses) est un processus aléatoire qui a la **même puissance à toutes les fréquences**. Il varie si rapidement que sa valeur à un instant donné est indépendante de ses valeurs précédentes — d'où une autocorrélation qui est une impulsion de Dirac :

$$R_{xx}(\tau) = \sigma^2\,\delta(\tau)$$

où $\sigma^2$ est la variance du signal aléatoire (= sa puissance).

> **Pourquoi c'est utile** : l'autocorrélation d'un signal périodique noyé dans du bruit blanc fait ressortir un pic net à la période du signal (le bruit blanc, lui, ne contribue qu'à un pic étroit en $\tau=0$ et reste plat ailleurs) — c'est un moyen de **détecter un signal périodique caché dans du bruit**, exactement comme pour le radar en E.3.

---

## Notions ajoutées par rapport à ta version précédente

Ces points viennent directement du support de cours (`cours120262027FISA.pdf`) mais n'étaient pas dans tes notes de séance : objectifs/champs d'application du traitement du signal (A.2), signal causal (B.5), toute la section des signaux élémentaires — translation temporelle, fonction signe, échelon unité, signal porte, impulsion et peigne de Dirac, signal sinusoïdal détaillé, sinus cardinal (partie C), et toute l'analyse corrélative — inter-corrélation, autocorrélation, exemple radar, bruit blanc (partie E). Je les ai intégrées à leur place logique dans le plan plutôt qu'à la fin, pour que ça suive l'ordre du cours.

Si tu veux, je peux aussi :
- faire un **schéma** du plan complexe (module/phase) et un pour le principe d'échantillonnage (peigne de Dirac appliqué à un signal continu) ;
- vérifier plus précisément la formule de distance radar en E.3 (je l'ai ajoutée à partir du principe physique standard, pas du texte exact du PDF — je peux la comparer avec ce que dit précisément ton cours si tu as ce passage).
