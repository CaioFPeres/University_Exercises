
clc
clear all
fun = @(x)[x(1)+x(2)-3; x(1)^2+x(2)^2-9];
%Jac = @(x) [1 1; 2*x(1) 2*x(2)];
x0 = ones(2, 1);
B0 = eye(2);
%x0=[1:5]
%B0=[1 1; 2 10];
[x1, k1] = secanteNL(fun, x0, B0)
%[x2, k2] = newtonNL(fun, Jac, x0)
fun(x1)