// ===== TDAO3 - Exo 3 : H(s) = 2 / (s + 1) =====

// --- Exo 3 a : numérateur NN et dénominateur DD avec poly ---
// poly(coefs, 's', 'c') : polynôme en s à partir de ses COEFFICIENTS,
// rangés par puissance croissante : [a0 a1 a2 ...] -> a0 + a1*s + a2*s^2 ...
NN = poly(2, 's', 'c');        // numérateur   : 2          (constante)
DD = poly([1 1], 's', 'c');    // dénominateur : 1 + 1*s = s + 1

disp("Numérateur NN :");   disp(NN);
disp("Dénominateur DD :"); disp(DD);

// --- Exo 3 b : création du système linéaire H avec syslin ---
// syslin(domaine, num, den)
// 'c' = continuous : système en temps continu (analogique, variable s de Laplace)
// ('d' serait un système discret, en z, comme les filtres des exos 1 et 2)
H = syslin('c', NN, DD);

disp("Fonction de transfert H(s) :"); disp(H);

// --- Exo 3 c : diagramme de Bode ---
// bode(H, fmin, fmax) : gain en dB et phase en degrés, axe des fréquences en Hz (échelle log)
scf(0); clf();
bode(H, 0.001, 100);           // de 0,001 Hz à 100 Hz pour bien voir avant/après la coupure

// --- Exo 3 d : valeur de H pour s = 0 (fréquences très faibles) ---
// Théorie : H(0) = 2 / (0 + 1) = 2  ->  20*log10(2) ≈ 6,02 dB
// Vérification : horner(H, valeur) remplace s par la valeur dans H
H0 = horner(H, 0);
disp("H(0) = " + string(H0));
disp("H(0) en dB = " + string(20*log10(abs(H0))) + " dB");

// --- Exo 3 e : fréquence de coupure ---
// Théorie : |H(jw)| = 2 / sqrt(1 + w^2)
// Coupure quand |H| = Hmax / sqrt(2)  ->  sqrt(1 + w^2) = sqrt(2)  ->  wc = 1 rad/s
wc = 1;                        // pulsation de coupure (rad/s)
fc = wc / (2*%pi);             // fréquence de coupure (Hz) ≈ 0,159 Hz
disp("fc = " + string(fc) + " Hz");

// Vérification : on remplace s par j*wc
Hc = horner(H, %i*wc);
disp("|H(fc)| = " + string(abs(Hc)) + "  (attendu 2/sqrt(2) = 1,414)");
disp("Gain en fc = " + string(20*log10(abs(Hc))) + " dB  (attendu 6 - 3 = 3 dB)");
disp("Phase en fc = " + string(atan(imag(Hc), real(Hc))*180/%pi) + " °  (attendu -45°)");
