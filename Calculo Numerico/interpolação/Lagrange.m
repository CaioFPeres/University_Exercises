% NOME 1: Caio Fernando Peres   RA: 2000784
% NOME 2:

% Lagrange.m eh uma function que retorna a estimacao de um
% determinando valor por um polinomio interpolador
% Dados de Entrada: 
%                  x -> vetor de dimensão n
%                  y -> vetor de dimensão n
%                  x0  -> ponto a ser estimado por um polinomio de ordem n-1
% Dado de Saida:
%                  y0 -> ponto estimado pelo polinomio interpolador  

function y0 = Lagrange(x, y, x0)
  
  n = length(x);
  y0 = 0;
  
  for k=1:n
    L = 1;
    
    for i=1:n
      if(i!=k)
        L = L*(x0 - x(i))/(x(k)-x(i));
      endif
    endfor
    
  y0 = y0 +y(k)*L;
  endfor
      
  
  