% Nome 1: Caio Fernando Peres RA: 2000784
% Nome 2:

% RK4.m: function que resolve um PVI na forma padrao
%               y' = f(x,y)    y(x0) = x0
% utilizando o metodo numerico de Euler
% Entrada: x0: x inicial
%          y0: y inicial
%          xf: x final
%           h: tamanho do passo para discretizar o intervalo [x0, xf]
%           f: derivada de y dada pelo PVI          
% Saida: [x, y]:  x é o vetor contendo o intervalo [x0, xf] discretizado
% com o passo de tamanho h
%                 y é o vetor com as aproximacoes de y(x(i)) para cada 
% elemento do vetor x 

function sol2 = RK4(x0, y0, xf, h, f)

x = x0:h:xf;
y(1) = y0;
for k = 2:length(x)
    M1=f(x(k-1), y(k-1));
    M2=f(x(k-1) + (h/2), y(k-1)+((h/2)*(M1)));
    M3=f(x(k-1) + (h/2), y(k-1)+((h/2)*(M2)));
    M4=f(x(k), y(k-1)+(h*M3));
    y(k) = y(k-1) + ((h/6)*(M1+2*M2+2*M3+M4));
endfor

sol2 = [x' y'];
