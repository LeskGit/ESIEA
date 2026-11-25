

### Etude du programme 

a. SAI : C'est le _Serial Audio Interface_, un périphérique série du STM32 conçu pour l'audio. Il sert à échanger les échantillons numériques avec le codec audio WM8994, qui fait la conversion analogique ↔ numérique.

b. DMA : C'est un contrôleur qui copie les données entre le SAI et la RAM sans passer par le CPU. Ici, il est en mode **circulaire** (`DMA_CIRCULAR`) : quand il arrive au bout du buffer, il recommence au début, en boucle. Pendant ce temps, le CPU est libre pour faire le traitement.

c. **Les callbacks**
- `HAL_SAI_TxHalfCpltCallback()` : interruption déclenchée quand le DMA a envoyé la **première moitié** du buffer d'émission. On peut alors réécrire cette moitié pendant que le DMA envoie la seconde.
- `HAL_SAI_TxCpltCallback()` : interruption déclenchée quand le DMA a envoyé **tout** le buffer. On réécrit alors la seconde moitié pendant que le DMA repart sur la première.
d. `audio_init(AUDIO_FREQUENCY_22K)` dans `main.c`, donc **Fe = 22 050 Hz**. La valeur est définie dans `sai.h`.

e. **Les buffers**

- `saiDMAReceiveBuffer` : le DMA y écrit en continu les échantillons venant de l'ADC du codec (entrée LINE IN).
- `saiDMATransmitBuffer` : le DMA y lit les échantillons à envoyer au DAC du codec (sortie LINE OUT).

f. Il vaut **1024**, c'est le nombre d'échantillons (de trames audio) contenus dans un buffer DMA

g. Le buffer est découpé en deux moitiés : pendant que le DMA lit ou remplit une moitié, le CPU traite l'autre. Ils ne travaillent donc jamais sur la même zone en même temps, ce qui évite d'écraser des données en cours d'utilisation. Avantage pour le temps réel : le flux audio est continu, sans coupure, et le CPU dispose du temps d'une demi-trame (512 / 22 050 ≈ 23 ms) pour faire son traitement.

h. 1. ils lisent la moitié du buffer de réception qui vient d'être remplie (`LowerHalf_Input_Samples` / `UpperHalf_Input_Samples`), en ne prenant que le canal gauche ;
2. ils écrivent ces mêmes échantillons, **sans modification**, dans la moitié correspondante du buffer d'émission, sur les canaux gauche **et** droit (`LowerHalf_Output_Samples` / `UpperHalf_Output_Samples`).

C'est donc une recopie entrée

### Travail pratique 

![[Pasted image 20261124142721.png|577]]

d): **Fonctionnement du programme :**
1. Le codec WM8994 numérise le signal de LINE IN (ADC) à Fe = 22 050 Hz.
2. Le SAI reçoit les échantillons, et le DMA les copie automatiquement dans `saiDMAReceiveBuffer`, sans intervention du CPU.
3. À chaque demi-buffer transféré, une interruption (`HAL_SAI_TxHalfCpltCallback` ou `HAL_SAI_TxCpltCallback`) se déclenche. Le CPU recopie alors les échantillons reçus dans la moitié libre de `saiDMATransmitBuffer`.
4. Le DMA envoie ces échantillons au SAI, puis le codec les reconvertit en analogique (DAC) vers LINE OUT.

![[IMG_2875.jpeg]]


Le programme réalise donc une **recopie entrée → sortie, sans traitement**

e): En augmentant la fréquence d'entrée, la sortie suit l'entrée jusqu'à environ **10,6 kHz**. Au-delà, le signal de sortie s'atténue et se déphase par rapport à l'entrée.

**Conclusion :** cette limite vient du **théorème de Shannon** : un signal échantillonné à Fe ne peut être restitué correctement que si sa fréquence est inférieure à **Fe/2**. Ici, Fe = 22 050 Hz, donc Fe/2 ≈ 11 kHz. Les filtres du codec coupent un peu avant, d'où la limite observée vers 10,6 kHz. Pour transmettre des fréquences plus hautes, il faut augmenter Fe.

48khz
![[Pasted image 20261124151714.png]]


16 khz
![[Pasted image 20261124152013.png]]


f. À 2 kHz, le signal est correctement restitué pour toutes les fréquences d'échantillonnage, car 2 kHz < Fe/2 dans tous les cas. En revanche, la fréquence maximale restituable dépend de Fe : elle vaut environ Fe/2 (théorème de Shannon). Plus Fe est élevée, plus la bande passante est large, mais plus il y a d'échantillons à traiter.

### Application audio

a): Avec Fe = 44,1 kHz, on relie la sortie casque du PC à l'entrée LINE IN de la carte, et le casque à la sortie LINE OUT. La musique jouée sur le PC est restituée dans le casque avec une bonne qualité. La bande passante (Fe/2 ≈ 22 kHz) couvre tout le spectre audible (20 Hz à 20 kHz), donc aucune perte n'est perceptible.

b): En réduisant la fréquence d'échantillonnage (22 kHz, 16 kHz, 8 kHz), le son devient de plus en plus étouffé, avec un rendu proche d'un téléphone. D'après le théorème de Shannon, seules les fréquences inférieures à Fe/2 sont restituées, donc les aigus sont supprimés. À 8 kHz, on ne garde que les fréquences sous 4 kHz : la voix reste compréhensible, mais la musique perd beaucoup de qualité. Plus Fe est basse, plus la bande passante est réduite et plus la qualité audio se dégrade.

![[IMG_2880.jpeg]]