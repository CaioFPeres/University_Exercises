% PROJETO PARCIAL 1
% Grupo 11
% ------------
%
% Integrantes: 
% ------------
% 769298: Caio Fernando Peres
% 743545: Guilherme Madureira Engler
% 726598: Vitoria Rodrigues Silva
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% main
% ------------
function main

% Inicialização
% ------------
  close all %fechar todas as janelas 
  clear %limpar memoria
  clc %limpa a tela
  pkg load image;

% Imagem 1 - rice 
% ------------
  
  figure
  original('rice.png')
  autoescala('rice.png')
  quantizacao('rice.png')
  splitting('rice.png')
  equalizacao('rice.png')
  binarizacao('rice.png', 110)
  
% Imagem 2 - mamografia
% ------------
  
  figure
  original('mamografia.bmp')
  autoescala('mamografia.bmp')
  quantizacao('mamografia.bmp')
  splitting('mamografia.bmp')
  equalizacao('mamografia.bmp')
  binarizacao('mamografia.bmp', 40)

% Imagem 3 - batatas
% ------------
  figure
  original('batatas.tif')
  autoescala('batatas.tif')
  quantizacao('batatas.tif')
  splitting('batatas.tif')
  equalizacao('batatas.tif')
  binarizacao('batatas.tif', 75)

% Imagem 4 - solda
% ------------
  figure
  original('solda.bmp')
  autoescala('solda.bmp')
  quantizacao('solda.bmp')
  splitting('solda.bmp')
  equalizacao('solda.bmp')
  binarizacao('solda.bmp', 190)

% Imagem 5 - laranjas
% ------------
  figure
  original('laranjas.bmp')
  autoescala('laranjas.bmp')
  quantizacao('laranjas.bmp')
  splitting('laranjas.bmp')
  equalizacao('laranjas.bmp')
  binarizacao('laranjas.bmp', 130)
endfunction
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Original
function original(arquivo)

  A=imread(arquivo);
  if isrgb(A) % Se a imagem for RGB, faz a conversão para escala de cinza
    A = rgb2gray(A);
  endif
  subplot(1, 6, 1), subimage(A), title('Original')

endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Implementação das técnicas
% ------------
% Autoescala
function autoescala(arquivo)
  
  A=imread(arquivo); % Ler o arquivo
  if isrgb(A) % Se a imagem for RGB, faz a conversão para escala de cinza
    A = rgb2gray(A);
  endif
  
  [lin col] = size(A); % define as dimensões da imagem
  f_max = max(max(A));
  f_min = min(min(A));
  
  for i=1:lin
    for j=1:col
      B(i,j) = (255/(f_max - f_min)) * (A(i,j) - f_min);
      if B(i,j) > 255
        B(i,j) = 255;
      else
        if B(i,j) < 0
          B(i, j) = 0;
        endif
      endif    
    endfor
  endfor
  
  subplot(1, 6, 2), subimage(B), title('Autoescala')
  
endfunction

% Quantizacao
function quantizacao(arquivo)

  A=imread(arquivo); % Ler o arquivo
  if isrgb(A) % Se a imagem for RGB, faz a conversão para escala de cinza
    A = rgb2gray(A);
  endif

  maior_cinza=max(max(A));
  qtd_niveis=4;
  passo=round(maior_cinza/qtd_niveis);
  [lin col]=size(A); % obtém dimensões da imagem
  
  for i=1:lin
    for j=1:col
      B(i,j)=round(A(i,j)/passo)*passo;
      if B(i,j)>255
        B(i,j)=255;
      else
        if B(i,j)<0
          B(i,j)=0;
        end
      end
    end
  end
  
  subplot(1, 6, 3), subimage(B), title('Quantizacao')

endfunction


% Splitting
function splitting(arquivo)

  A=imread(arquivo); % Ler o arquivo
  if isrgb(A) % Se a imagem for RGB, faz a conversão para escala de cinza
    A = rgb2gray(A);
  endif
  
  limiar=45;
  split=15;
  [lin col]=size(A); % obtém dimensões da imagem
  
  for i=1:lin
    for j=1:col
      if A(i,j) <= limiar
        B(i,j)=A(i,j)-split;
      else
        B(i,j)=A(i,j)+split;
      end
      if B(i,j)>255
        B(i,j)=255;
      else
        if B(i,j)<0
          B(i,j)=0;
        end
      end
    end
  end

  subplot(1, 6, 4), subimage(B), title('Splitting')

endfunction


% Equalizacao
function equalizacao(arquivo)

  A=imread(arquivo); % Ler o arquivo
  if isrgb(A) % Se a imagem for RGB, faz a conversão para escala de cinza
    A = rgb2gray(A);
  endif
  
  B=histeq(A); % equalizar o histograma
  subplot(1, 6, 5), subimage(B), title('Equalizacao')

endfunction


% Binarizacao
function binarizacao(arquivo, limiar)
  
  A=imread(arquivo); % Ler o arquivo
  if isrgb(A) % Se a imagem for RGB, faz a conversão para escala de cinza
    A = rgb2gray(A);
  endif
  
  limiar=limiar;
    
  [lin col]=size(A); % obtém dimensões da imagem
  B=A;

  for i=1:lin
    for j=1:col
      if B(i,j)>=limiar
        B(i,j)=255;
      else
        B(i,j)=0;
      end
    end
  end
  
  subplot(1, 6, 6), subimage(B), title('Binarizacao')

endfunction

