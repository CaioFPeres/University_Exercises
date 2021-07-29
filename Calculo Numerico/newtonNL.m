% Nome 1: Caio Fernando Peres  Ra: 2000784
% Nome 2:

% A funcao newtonNL.m para resolver sistemas de equacoes nao-lineares:
%                           F(X)=0
% onde F e um funcional F: R^n -> R^n e X pertence ao R^n.
% Entrada:
%         F: Funcao vetorial (Nx1)
%         Jac: Jacobiano de F  (NxN)
%         x: chute inicial (Nx1)
% Saida:
%         x : vetor solucao tal que F(x)  e proximo do vetor nulo
%         k:  numero de iteracoes      
             
function [x, k] = newtonNL(F,J,x)

%Num. max de iteracoes
IMAX = 50;
%Tolerancia
tol = 1e-4;

k = 1;
aux = F(x);

while norm(aux)> tol  &&  k<IMAX

    S = -J(x)\F(x);
    x = x+S;
    aux = F(x);
    k = k+1;
	
	
end
 

end

