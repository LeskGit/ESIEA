function [y, axe_t] = generer_sinus(Fe, duree, amplitude, frequence)
    N = round(Fe * duree);          
    axe_t = (0:N-1)/Fe;            
    y = amplitude*sin(2*%pi*frequence*axe_t);
endfunction

// --- Exo 1 a/b : Fe = 256 Hz ---
[s1, t] = generer_sinus(256, 0.5, 1, 100);
[s2, t] = generer_sinus(256, 0.5, 1, 156);
x = s1 + s2;

// Repliement : Fe < 2*fmax => 256 < 312 (Shannon non respecté)
// Le sinus à 156 Hz fait plus d'un demi-tour entre deux échantillons

// plot(t, x);

// --- Exo 1 c : Fe = 356 Hz ---
[s1, t] = generer_sinus(356, 0.5, 1, 100);
[s2, t] = generer_sinus(356, 0.5, 1, 156);
x = s1 + s2;

plot(t, x);
