clc
close all

a = 0;
b = 1;
h = 0.05;
x = a : h : b; % ascisse equispaziate 
y = 0.1 + x + (10^(-1)) * rand(size(x)) ; % ordinate

% valutazione coeff . dell ’ approssimante ai minimi quadrati 
coeff = polyfit( x, y, 1);

% valore ”p 1” nelle ascisse ”x”
z = polyval(coeff, x);

% errore ||f−p 1|| 2
err2 = norm( z-y, 2);

fprintf('\n \t Errore regressione norma2: %1.2e', err2);

% grafico del polinomio ai minimi quadrati di grado ”1”
ht = 1/10000;
u = a : ht : b ;
v = polyval( coeff, u);
clf;

% plot punti
plot(x, y, 'go', 'LineWidth' , 1, ... 
    'MarkerEdgeColor', 'k', ...
    'MarkerFaceColor', 'g' ,...
    'MarkerSize', 10);
hold on;

% plot retta regressione
plot( u, v); 

% titoli e legenda
title('Regressione lineare');
legend('Dati', 'Retta di regressione')
legend();
hold off;


fprintf('\n \n');