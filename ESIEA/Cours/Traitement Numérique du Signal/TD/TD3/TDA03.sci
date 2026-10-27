// ===== TDAO3 - Filtres RII en Scilab =====

// Même fonction qu'au TD2
function [y, axe_t] = generer_sinus(Fe, N, amplitude, frequence)
    axe_t = (0:N-1)/Fe;
    y = amplitude*sin(2*%pi*frequence*axe_t);
endfunction

// --- Exo 1 a : Butterworth passe-bas, ordre 4, fc = 25 Hz, fe = 100 Hz ---
fe = 100;              // fréquence d'échantillonnage (Hz)
fc = 25;               // fréquence de coupure (Hz)
fn = fc / fe;          // fréquence normalisée = 0.25 (doit être entre 0 et 0.5)

// iir(ordre, type, famille, [fc_norm 0], [ondulations])
// 'lp' = low-pass (passe-bas), 'butt' = Butterworth
// [0 0] : ondulations inutiles pour un Butterworth
hz = iir(4, 'lp', 'butt', [fn 0], [0 0]);   // hz = fonction de transfert H(z)

// Réponse en amplitude |H(f)| sur N = 512 points
N = 512;
[hzm, fr] = frmag(hz, N);   // fr est normalisée (0 -> 0.5)

scf(0); clf();              // fenêtre 0 : réponse du filtre
plot(fr*fe, hzm);           // *fe pour avoir l'axe en Hz (0 -> 50 Hz)
plot([fc fc], [0 1], "r--");        // repère fc
plot([0 fe/2], [0.707 0.707], "g--"); // repère -3 dB (1/sqrt(2))
xtitle("Butterworth passe-bas ordre 4 - fc = 25 Hz", "Fréquence (Hz)", "|H(f)|");

// --- Exo 1 b : x = somme de 3 sinus (10, 30, 40 Hz), fe = 100 Hz, N = 512 ---
// (fe et N déjà définis plus haut)
[s1, t] = generer_sinus(fe, N, 1, 10);   // va passer le filtre
[s2, t] = generer_sinus(fe, N, 1, 30);   // juste après fc : atténué
[s3, t] = generer_sinus(fe, N, 1, 40);   // loin après fc : quasi supprimé
x = s1 + s2 + s3;

// Shannon : fmax = 40 Hz < fe/2 = 50 Hz -> OK, pas de repliement
// (rien à tracer en b, on prépare juste x pour la c)

// --- Exo 1 c : spectre centré de x (comme au TD2) ---
X = fft(x);
axe_fcentre = (-N/2:N/2-1)*fe/N;   // de -50 à +50 Hz
X_centre = fftshift(abs(X));       // fréquence 0 au milieu

scf(1); clf();              // fenêtre 1 : spectre de x
plot(axe_fcentre, X_centre);
xtitle("Spectre de x (avant filtrage)", "Fréquence (Hz)", "|X(f)|");

// --- Exo 1 d : application du filtre passe-bas (ordre 4) sur x ---
y = flts(x, hz);                   // signal filtré (domaine temporel)

Y = fft(y);
Y_centre = fftshift(abs(Y));

scf(2); clf();              // fenêtre 2 : avant / après
plot(axe_fcentre, X_centre, "b");  // avant filtrage
plot(axe_fcentre, Y_centre, "r");  // après filtrage
legend(["x (avant)", "y (après filtre ordre 4)"]);
xtitle("Spectre avant / après filtrage", "Fréquence (Hz)", "|X(f)| et |Y(f)|");

// --- Exo 1 e : même filtre mais ordre 10 ---
hz10 = iir(10, 'lp', 'butt', [fn 0], [0 0]);
[hzm10, fr] = frmag(hz10, N);

// Réponse du filtre : ordre 4 vs ordre 10
scf(3); clf();
plot(fr*fe, hzm, "b");             // ordre 4
plot(fr*fe, hzm10, "r");           // ordre 10
plot([0 fe/2], [0.707 0.707], "g--"); // repère -3 dB
legend(["ordre 4", "ordre 10", "-3 dB"]);
xtitle("Réponse du filtre : ordre 4 vs ordre 10", "Fréquence (Hz)", "|H(f)|");

// Filtrage de x avec l'ordre 10
y10 = flts(x, hz10);
Y10_centre = fftshift(abs(fft(y10)));

scf(4); clf();
plot(axe_fcentre, X_centre, "b");    // avant
plot(axe_fcentre, Y_centre, "g");    // après ordre 4
plot(axe_fcentre, Y10_centre, "r");  // après ordre 10
legend(["x (avant)", "après ordre 4", "après ordre 10"]);
xtitle("Spectres : avant / ordre 4 / ordre 10", "Fréquence (Hz)", "Module");
