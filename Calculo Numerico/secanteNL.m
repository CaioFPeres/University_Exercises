% Nome 1: CAIO FERNANDO PERES
% Nome 2: Gabriel Rodrigues Shiota

% A função secanteNL.m resolve sistemas de equacoeses nao-lineares:
% F(X)=0
% onde F e um funcional F:R^n -> R^n e X pertence ao R^n.
% Entrada:
% F: Funcao vetorial (Nx1)
% x0: chute inicial (Nx1)
% B0: matriz inicial (NXN)
% Saida:
% x0 : vetor solucao tal que F(x) e proximo do vetor nulo
% k: numero de iteracoes

function [x0, k] = secanteNL(FF,x0,B0)
  MAX = 5000;
  tol = 1e-4;
  k=1;
  F = FF(x0);
  while (norm(F) > tol) && (k < MAX)
    
    s = - B0\FF(x0);
    x0 = x0 + s;
     F = FF(x0);
    
    B0 = B0 + (F*s')/(s'*s);
    k = k+1;
    
endwhile