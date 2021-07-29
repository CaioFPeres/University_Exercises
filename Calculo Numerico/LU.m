%% Nome 1: Caio Fernando Peres 
%% Nome 2: Pedro Cathcart Duarte Loureiro
%% Grupo 4

clear;clc
format compact

A = [-6 2 1 2 1;3 8 -4 1 0;-1 1 4 10 1;3 -4 1 9 2;2 0 1 3 10]
function [L,A]=LU(A) 
    n=size(A,1)
    L=eye(n,n)
 
 for j=1:n-1 
        for i=j+1:n 
            L(i,j)=A(i,j)/A(j,j)
            A(i,j+1:n)=A(i,j+1:n)-L(i,j)*A(j,j+1:n)
            A(i,j)=0 
       end 
    end 
    
endfunction