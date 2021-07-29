% NOME 1: Caio Fernando Peres
% NOME 2:


% A função newtonraphson.m função utiliza o método de newton-raphson para encontar
% uma raiz real de uma função f contínua no intervalo [a,b]
% Entrada:
%         f:  função de uma variável
%         df: derivada de f  
%         x0: chute inicial
% Saída:
%         sol : vetor onde as colunas correspondem a:
%               coluna 1: iterações
%               coluna 2: sequência de (xk's) 
%               coluna 3: valores da função f em cada ak's



function sol = secante(f,x0,x1)

%tolerancia
tol=1e-3;
%iteracao
c=2;
%max numero de iteracoes
max=50;

while abs(f(x0))>tol % && c<=max
  p=x0-f(x1)*(x1-x0)/(f(x1)-f(x0));
  x0=p;
  c=c+1;
  fprintf('\t%d \t%f \t%f\n', c, x0, f(x0));
  
end
