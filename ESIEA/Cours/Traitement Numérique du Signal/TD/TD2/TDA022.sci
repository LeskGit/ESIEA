
function [y, axe_t] = generer_sinus(Fe, N, amplitude, frequence)
    axe_t = (0:N-1)/Fe;            
    y = amplitude*sin(2*%pi*frequence*axe_t);
endfunction


N  = 512;
Fe = 100;

// --- Exo 2 a ---
[s1, t] = generer_sinus(Fe, N, 1, 10);

// plot(t, s1);

// --- Exo 2 b ---
E_temps = sum(abs(s1).^2);
disp("Energie (domaine temporel) : " + string(E_temps));

// --- Exo 2 c ---
X1 = fft(s1);

// --- Exo 2 d ---
axe_f = (0:N-1)*Fe/N;    

// plot(axe_f, abs(X1));

// --- Exo 2 e ---
axe_fcentre = (-N/2:N/2-1)*Fe/N;   // axe centré : de -50 à +50 Hz
X1_centre = fftshift(abs(X1));     // on remet la fréquence 0 au milieu

// plot(axe_fcentre, X1_centre);

// --- Exo 2 f ---
E_freq = sum(abs(X1).^2) / N;
disp("Energie (domaine fréquentiel) : " + string(E_freq));

// L'énergie ne dépend pas de la façon dont on regarde le signal. Dans le temps, elle est répartie sur les 512 instants. Donc c'est égal et heureusement

// --- Exo 2 g ---
[s2, t] = generer_sinus(Fe, N, 1, 5);  
x = s1 + s2;                        

// --- Exo 2 h ---
X = fft(x);
X_centre = fftshift(abs(X));

plot(axe_fcentre, X_centre);
