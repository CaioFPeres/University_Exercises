%% Nome 1: Caio Fernando Peres 
%% Nome 2: Pedro Cathcart Duarte Loureiro
%% Grupo 4

clear;clc
format compact

A = [-7 2 1 2 1;3 11 -4 1 0;-1 1 8 2 1;2 -4 1 9 1;2 0 1 3 10]
C = [3;4;-2;12;1]
n = length(C)
X = zeros(n,1)
erro = ones(n,1)

for i = 1:n
    j = 1:n;
    j(i) = [];
    B = abs(A(i,j));
    Check(i) = abs(A(i,i)) - sum(B);
    if Check(i) < 1
        fprintf('A matriz nao eh estritamente diagonal dominante na linha %2i\n\n',i)
    end
end

iter = 0;
while max(erro) > 0.001
    iter = iter + 1;
    Z = X;
    for i = 1:n
        j = 1:n;
        j(i) = [];
        Xtemp = X;
        Xtemp(i) = [];
        X(i) = (C(i) - sum(A(i,j) * Xtemp)) / A(i,i);
    end
    X2(:,iter) = X;
    erro = sqrt((X - Z).^2);
end

GaussSeidel = [1:iter;X2]'
X = [X]
