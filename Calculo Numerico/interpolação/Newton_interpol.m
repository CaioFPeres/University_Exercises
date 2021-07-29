% NOME 1: Caio Fernando Peres RA: 2000784
% NOME 2:

% newton_interpol.m eh uma function que retorna a estimacao de um
% determinando valor por um polinomio interpolador
% Dados de Entrada: 
%                  x -> vetor de dimensão n
%                  y -> vetor de dimensão n
%                  x0  -> ponto a ser estimado por um polinomio de ordem n-1
% Dado de Saida:
%                  y0 -> ponto estimado pelo polinomio interpolador 

function y0 = Newton_interpol(x, y, x0)
     
    n = length(x); 
    
    y0 = 0;
 
 
    for j=1:n-1
      for i=n:-1:j+1
        y(i) = (y(i)-y(i-1))/(x(i)-x(i-j))
      endfor
    endfor
    y0 = y(n);
    
    for i=n-1:-1:1
      y0 = y0*(x0-x(i))+y(i);
    endfor
    
    

     

 