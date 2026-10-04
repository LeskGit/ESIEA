// ===== Exercice 4 : détection d'un signal connu par intercorrélation =====

// --- Paramètres ---
N     = 1024;                 // nombre d'échantillons
n     = -N/2 : N/2-1;         // axe des échantillons centré en 0 (-512 à 511)
A     = 2;                    // amplitude du rectangle
L     = 50;                   // largeur du rectangle (échantillons)
d     = 100;                  // décalage
sigma = 0.25;                 // écart-type du bruit

// --- Rectangle x centré en 0 ---
x = A*bool2s(n >= -L/2 & n < L/2);

// --- Version décalée xd centrée en d = 100 ---
xd = A*bool2s(n >= d-L/2 & n < d+L/2);

scf(0); clf();
plot(n, x, "b-");
plot(n, xd, "r-");
a = gca(); a.data_bounds = [-600, -0.5; 600, 2.5];

// --- Ajout du bruit blanc gaussien ---
bruit = 0 + sigma*rand(1, N, "normal");   // moyenne 0, écart-type 0.25
y = xd + bruit;

// --- x et y sur la même figure ---
scf(1); clf();
plot(n, x, "b-");
plot(n, y, "r-");
a = gca(); a.data_bounds = [-600, -1; 600, 3];

// --- Intercorrélation entre y et x ---
[C, lag] = xcorr(y, x);

scf(2); clf();
plot(lag, C);
// --- Position du maximum ---
[Cmax, imax] = max(C);
disp("Maximum de l''intercorrélation = " + string(Cmax));
disp("Position du maximum (décalage) = " + string(lag(imax)) + " échantillons");
