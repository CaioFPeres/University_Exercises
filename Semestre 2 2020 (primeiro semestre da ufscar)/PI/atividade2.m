%%% Inicializacao %%%
clear all;
close all;
clc;
pkg load image;

% Imagem de entrada
img = imread('lena.bmp');
img = rgb2gray(img);
img = im2double(img); % tratamento para aplicacao da FT

%%% Aplicacao do ruido sal e pimenta %%%
imgComRuido = imnoise(img, 'salt & pepper', 0.02);

%%% Mostra a imagem original e a imagem ruidosa %%%
figure('Name', 'Subplot 1 - Imagens de Entrada', 'NumberTitle', 'off'),
subplot(1, 2, 1), imshow(img), title('Imagem Original');
subplot(1, 2, 2), imshow(imgComRuido), title('Imagem Ruidosa');

%%% FFT2 e aplicacao dos filtros passa-baixa e alta %%%
% Definicao dos filtros
passa_alta = [-1 -1 -1;-1 8 -1;-1 -1 -1];
passa_baixa = (1/9)*[1 1 1;1 1 1;1 1 1];

% Dimensoes da imagem
s = size(img);

% Maior dimensao da imagem
DimMax = max(s);

% Calculo da menor potencia de 2 maior que dimensao maxima da imagem
M = log2(DimMax);
M = 2^ceil(M);

% Obtencao das DFTs e dos espectros de potencia
FT = fft2(img, M, M); 
FTR = fft2(imgComRuido, M, M);
FTH = fft2(passa_alta, M, M);
FTL = fft2(passa_baixa, M, M);

SPEC_img = abs(fftshift(FT));
SPEC_imgComRuido = abs(fftshift(FTR));
SPEC_h = abs(fftshift(FTH));
SPEC_l = abs(fftshift(FTL));

%%% Mostra os respectivos espectros das imagens original, ruidosa, ruidosa com %%%
%%% passa-alta e ruidosa com passa-baixa %%%
figure('Name', 'Subplot 2 - Espectros de Fourier das Imagens', 'NumberTitle', 'off'),
subplot(2, 2, 1), imshow(log(SPEC_img + 1),[]), title('Espectro de Fourier da Imagem Original:');
subplot(2, 2, 2), imshow(log(SPEC_imgComRuido + 1),[]), title('Espectro de Fourier da Imagem Ruidosa:');
subplot(2, 2, 3), imshow(log(SPEC_h + 1),[]), title('Espectro de Fourier da Imagem Ruidosa com Passa-alta:');
subplot(2, 2, 4), imshow(log(SPEC_l + 1),[]), title('Espectro de Fourier da Imagem Ruidosa com Passa-baixa:');

% Filtragem realizada pelo produto ponto-a-ponto das transformadas
IFT = ifft2(FT); % Calcula IDFT da imagem original
IFTR = ifft2(FTR); % Calcula IDFT da imagem ruidosa

Y_h = FTR.*FTH; % Calcula IDFT da imagem ruidosa com filtro passa-alta
y_h = ifft2(Y_h); 
y_h = y_h(1:s(1),1:s(2));

Y_l = FTR.*FTL; % Calcula IDFT da imagem ruidosa com filtro passa-baixa
y_l = ifft2(Y_l); 
y_l = y_l(1:s(1),1:s(2));

%Imagens resultantes
figure('Name', 'Subplot 3 - Imagens Resultantes', 'NumberTitle', 'off'),
subplot(2, 2, 1), imshow(IFT, []), title('IDFT da Imagem Original:');
subplot(2, 2, 2), imshow(IFTR, []), title('IDFT da Imagem Ruidosa:');
subplot(2, 2, 3), imshow(abs(y_h)), title('IDFT da Imagem Ruidosa com Passa-alta:');
subplot(2, 2, 4), imshow(abs(y_l)), title('IDFT da Imagem Ruidosa com Passa-baixa:');
