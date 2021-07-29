% NOME 1: Caio Fernando Peres
% NOME 2:

% A funcao newtonraphson.m funcaoo utiliza o metodo de newton-raphson para encontar
% uma raiz real de uma funcao f continua no intervalo [a,b]
% Entrada:
%         f:  funco de uma variavel
%         df: derivada de f  
%         x0: chute inicial
% SaÃ­da:
%         sol : vetor onde as colunas correspondem a:
%               coluna 1: iteracoes
%               coluna 2: sequencia de (xk's) 
%               coluna 3: valores da funcao f em cada xk's


function sol = newtonraphson(f,df,x0)
  
y = 0;
% criterio de parada
tol = 1e-3;

% definição de 0
zero = 1e-50;

% numero maximo de iteracões
n = 10;

% diferença
dif=1;

k=1;

fprintf('A = ');
while abs(f(x0))>=tol && abs(dif)>=tol && k<=n
    
    x1 = x0 - f(x0)/(df(x0));
    dif = x1 - x0;
    x0 = x1;
    k = k+1;
    y = y +1;
    fprintf('\t%d \t%f \t%f\n', y, x0, f(x0));
   
end

sol = x0;
