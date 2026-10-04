

function [x, axe_t] = generer_sinus(periode, duree, echantillon, phase)
    frequence = 1/periode;
    Fe = echantillon/duree;       
    axe_t = (0:echantillon-1)/Fe;            
    x = sin(2*%pi*frequence*axe_t+phase);
endfunction

// --- Exo 3.a

[x1, t1] = generer_sinus(1, 5, 256, 0); 
[x2, t2] = generer_sinus(1, 10, 512, 0);  

subplot(2,1,1);
// plot(t1, x1);
xtitle("x1 : T=1 s, d=5 s, N=256", "t (s)", "Amplitude (V)");

subplot(2,1,2);
// plot(t2, x2);
xtitle("x2 : T=1 s, d=10 s, N=512", "t (s)", "Amplitude (V)");

// --- Exo 3.b

// --- Exo 3 c ---
[C1, lag1] = xcorr(x1);   // autocorrélation de x1
[C2, lag2] = xcorr(x2);   // autocorrélation de x2

disp(C1, lag1);
disp(C2, lag2);

subplot(2,1,1);
// plot(lag1, C1);
xtitle("Autocorrélation de x1", "Décalage (échantillons)", "Cxx");

subplot(2,1,2);
// plot(lag2, C2);
xtitle("Autocorrélation de x2", "Décalage (échantillons)", "Cxx");

// --- Exo 3 d ---
moy   = 0;
sigma = 2;
b1 = moy + sigma*rand(1, length(x1), "normal");   // bruit de même longueur que x1 (256)
S1 = x1 + b1;

// --- Exo 3 e ---
b2 = moy + sigma*rand(1, length(x2), "normal");   // mêmes caractéristiques, longueur de x2 (512)
S2 = x2 + b2;


subplot(2,1,1);
// plot(t1, S1);
xtitle("S1 = x1 + b1", "t (s)", "Amplitude (V)");

subplot(2,1,2);
// plot(t2, S2);
xtitle("S2 = x2 + b2", "t (s)", "Amplitude (V)");

// --- Exo 3 f ---
[CS1, lagS1] = xcorr(S1);   // autocorrélation de S1 (bruité)
[CS2, lagS2] = xcorr(S2);   // autocorrélation de S2 (bruité)

subplot(2,1,1);
// plot(lagS1, CS1);
xtitle("Autocorrélation de S1", "Décalage (échantillons)", "C");

subplot(2,1,2);
// plot(lagS2, CS2);
xtitle("Autocorrélation de S2", "Décalage (échantillons)", "C");

// --- Exo 3 g ---
P_signal = mean(x1.^2);        // puissance du sinus (signal déterministe)
P_bruit  = stdev(b1)^2;        // puissance du bruit = variance
RSB      = P_signal / P_bruit;
RSB_dB   = 10*log10(RSB);

disp("P_signal = " + string(P_signal));
disp("P_bruit  = " + string(P_bruit));
disp("RSB = " + string(RSB) + "  soit  " + string(RSB_dB) + " dB");


// --- Exo 3 h ---
sigma = 0.5;                                        // nouvel écart-type
b1 = moy + sigma*rand(1, length(x1), "normal");     // on régénère le bruit
S1 = x1 + b1;                                       // nouveau signal bruité (pour tracer si besoin)

P_signal = mean(x1.^2);
P_bruit  = stdev(b1)^2;
RSB      = P_signal / P_bruit;
RSB_dB   = 10*log10(RSB);

disp("Avec sigma = 0.5 :");
disp("P_bruit = " + string(P_bruit));
disp("RSB = " + string(RSB) + "  soit  " + string(RSB_dB) + " dB");
