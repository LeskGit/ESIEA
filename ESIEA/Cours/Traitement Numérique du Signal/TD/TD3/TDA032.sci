// ===== TDAO3 - Exo 2 : filtrage d'un signal sonore bruité =====

// Dossier du script (pour trouver affreux.wav sans changer de répertoire)
chemin = get_absolute_file_path("TDA032.sci");

// --- Exo 2 a : lecture du fichier son ---
[y, fe, bits] = wavread(chemin + "affreux.wav");
// y    : les échantillons (valeurs entre -1 et 1)
// fe   : fréquence d'échantillonnage (Hz)
// bits : nombre de bits par échantillon (quantification)

N = length(y);                     // nombre d'échantillons
duree = N / fe;                    // durée du son (s)

disp("fe = " + string(fe) + " Hz");
disp("bits = " + string(bits));
disp("N = " + string(N) + " échantillons");
disp("durée = " + string(duree) + " s");

playsnd(y, fe);                    // écouter le son

// --- Exo 2 b : TFD et spectre centré du son (comme en 1c) ---
Y = fft(y);
axe_fcentre = (-N/2:N/2-1)*fe/N;   // de -fe/2 à +fe/2 (≈ -8,9 à +8,9 kHz)
Y_centre = fftshift(abs(Y));

scf(0); clf();              // fenêtre 0 : spectre du son original
plot(axe_fcentre, Y_centre);
xtitle("Spectre centré du son original", "Fréquence (Hz)", "|Y(f)|");

// --- Exo 2 c : bruit blanc gaussien, moyenne 0, même variance que le son ---
// rand(..., "n") : loi normale de moyenne 0 et d'écart-type 1
// * stdev(y)     : on étire pour avoir l'écart-type (donc la variance) du son
// size(y,1), size(y,2) : même forme que y (ligne ou colonne), pour pouvoir additionner en d
b=stdev(y)*rand(1,length(y),"n");

// Vérification
disp("moyenne du bruit = " + string(mean(b)));
disp("variance du son   = " + string(variance(y)));
disp("variance du bruit = " + string(variance(b)));

// --- Exo 2 d : son bruité + enregistrement ---
yb = y + b;                        // le bruit s'ajoute échantillon par échantillon

// Même fe que l'original, sinon le son serait lu trop vite ou trop lentement
wavwrite(yb, fe, chemin + "affreuxB.wav");

playsnd(yb, fe);                   // écouter le son bruité

// --- Exo 2 e : spectre centré du son bruité ---
YB = fft(yb);
YB_centre = fftshift(abs(YB));

scf(1); clf();              // fenêtre 1 : original vs bruité
plot(axe_fcentre, YB_centre, "r");  // bruité (en premier pour qu'il soit derrière)
plot(axe_fcentre, Y_centre, "b");   // original
legend(["son bruité", "son original"]);
xtitle("Spectre centré : original vs bruité", "Fréquence (Hz)", "Module");

// --- Exo 2 f : filtre RII passe-bas pour atténuer le bruit ---
// Choix de fc : 95 % de l'énergie de la voix est sous ~3,4 kHz (cf. 2b)
// -> on garde la voix, on coupe la zone > 4 kHz où il n'y a que du bruit
fc = 4000;                 // fréquence de coupure (Hz)
fn = fc / fe;              // normalisée par fe = 17857 Hz -> ≈ 0,19

// ===== Essais : décommenter UNE seule ligne =====
hf = iir(4,  'lp', 'butt', [fn 0], [0 0]);    // Essai 1 : Butterworth ordre 4
// hf = iir(10, 'lp', 'butt', [fn 0], [0 0]); // Essai 2 : Butterworth ordre 10
// hf = iir(4,  'lp', 'cheb1', [fn 0], [0.1 0]); // Essai 3 : Tchebychev I ordre 4 (ondulation 0.1)

// --- Exo 2 g : réponse fréquentielle du filtre proposé ---
[hfm, fr] = frmag(hf, 1024);       // |H(f)|, fr normalisée (0 -> 0.5)

scf(2); clf();              // fenêtre 2 : filtre + spectre bruité
// Spectre bruité (partie f >= 0), ramené entre 0 et 1 pour être comparable au gain
idx = find(axe_fcentre >= 0);
plot(axe_fcentre(idx), YB_centre(idx) / max(YB_centre), "c");
plot(fr*fe, hfm, "b");                       // gain du filtre, axe en Hz
plot([fc fc], [0 1], "r--");                 // repère fc
plot([0 fe/2], [0.707 0.707], "g--");        // repère -3 dB
legend(["spectre son bruité (normalisé)", "|H(f)| du filtre", "fc", "-3 dB"]);
xtitle("Réponse du filtre passe-bas, fc = 3400 Hz", "Fréquence (Hz)", "Gain");

// --- Exo 2 h : application du filtre sur le son bruité ---
// flts attend un signal en ligne -> matrix(..., 1, -1) le met en ligne quoi qu'il arrive
yf = flts(matrix(yb, 1, -1), hf);  // son filtré

YF = fft(yf);
YF_centre = fftshift(abs(YF));

scf(3); clf();              // fenêtre 3 : bruité vs filtré
plot(axe_fcentre, YB_centre, "r");  // bruité
plot(axe_fcentre, YF_centre, "b");  // filtré
legend(["son bruité", "son filtré"]);
xtitle("Spectre centré : bruité vs filtré", "Fréquence (Hz)", "Module");

// Mesure de l'amélioration (le filtre est linéaire : on peut filtrer voix et bruit séparément)
yv = flts(matrix(y, 1, -1), hf);   // ce qu'il reste de la voix
bv = flts(matrix(b, 1, -1), hf);   // ce qu'il reste du bruit
RSB_avant = 10*log10(sum(y.^2) / sum(b.^2));
RSB_apres = 10*log10(sum(yv.^2) / sum(bv.^2));
disp("RSB avant filtrage = " + string(RSB_avant) + " dB");
disp("RSB après filtrage = " + string(RSB_apres) + " dB");
disp("Voix conservée  = " + string(100*sum(yv.^2)/sum(y.^2)) + " %");
disp("Bruit conservé  = " + string(100*sum(bv.^2)/sum(b.^2)) + " %");

wavwrite(yf, fe, chemin + "affreuxF.wav");   // on garde le résultat
playsnd(yb, fe);                   // bruité...
sleep(2500);                       // pause (ms) le temps que le premier son finisse
playsnd(yf, fe);                   // ...puis filtré
