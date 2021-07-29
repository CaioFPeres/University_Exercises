%NOME: CAIO FERNANDO PERES  RA: 2000784

% taylor2.m: function que resolve um PVI na forma padrao
%               y' = f(x,y)    y(x0) = x0
% utilizando o metodo numerico de Taylor Ordem 2
% Entrada: x0: x inicial
%          y0: y inicial
%          xf: x final
%           h: tamanho do passo para discretizar o intervalo [x0, xf]
%           f: derivada de y dada pelo PVI
%          fx: derivada de f em relacao a variavel x
%          fy: derivada de f em relacao a variavel y
% Saida: [x, y]:  x é o vetor contendo o intervalo [x0, xf] discretizado
% com o passo de tamanho h
%                 y é o vetor com as aproximacoes de y(x(i)) para cada 
% elemento do vetor x 


function sol = taylor2(x0,y0,xf,h,f,fx,fy)
x = x0:h:xf;
y(1) = y0;
for k = 2:length(x)
  aux = f(x(k-1), y(k-1))
  y(k) = y(k-1) + h*aux + 0.5*(h^2)*(fx(x(k-1), y(k-1)) + aux * fy(x(k-1), y(k-1)))
  k = k+1;
endfor

sol = [x' y'];