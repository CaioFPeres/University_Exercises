% Inicialização
close all %fechar todas as janelas 
clear %limpar memoria
clc %limpa a tela
pkg load image;

A=imread('rice.png');
B=imread('mamografia.bmp');
C=imread('batatas.tif');
D=imread('solda.bmp');
E=imread('laranjas.bmp');

figure, imhist(A), title('Rice');
figure, imhist(B), title('Mamografia');
figure, imhist(C), title('Batatas');
figure, imhist(D), title('Solda');
figure, imhist(E), title('Laranjas');



