% PROJETO FINAL
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
% ------------



% possíveis de encontrar com PI :

% - quebra cabeça
% - marca dagua
% - fio de segurança
% - numero escondido



  binarizacao('100_frente.JPG', 180) % foto inteira binarizada
  binarizacao('100_CL_frente.JPG', 185) % foto contra a luz inteira binarizad

  binarizacaoCL('100_CL_frente.JPG', 185) % processamento da imagem contra a luz para encontrar o desenho, o numero e o quebra cabeça.
  binarizacaoCL('50_CL_frente.JPG', 180) % mesmo caso para a nota de 50.

  binarizacaoFaixa('100_CL_frente.JPG', 140) % processamento da imagem contra a luz para encontrar a faixa de segurança. O quebra cabeça e a faixa só da para identificar com a imagem contra a luz.
  binarizacaoFaixa('50_CL_frente.JPG', 140) % mesmo caso para a nota de 50.

  binarizacaoNormal('100_frente.JPG', 180) % processamento da imagem normal para encontrar o desenho e o numero, que foram feitos para serem vistos contra a luz.
  binarizacaoNormal('50_frente.JPG', 185)  % mesmo caso para a nota de 50.

  binarizacaoHorizontal('100_frente.JPG', 110) % processamento da imagem normal para identificacao do numero escondido
  binarizacaoHorizontal('50_frente.JPG', 110) % mesmo caso para a nota de 50.



endfunction


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Implementação das técnicas
% ------------



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
  
  figure
  imshow(B);

  t = title (['\fontsize{15} Binarizacao com limiar ', num2str(limiar)]);

endfunction



function binarizacaoNormal(arquivo, limiar)
  
  A=imread(arquivo); % Ler o arquivo
  if isrgb(A) % Se a imagem for RGB, faz a conversão para escala de cinza
    A = rgb2gray(A);
  endif
  
  limiar=limiar;

  count = 0;

  B=A( end/6: end , end/(4/1.2) : end/2);   % corta a imagem
    
  [lin col]=size(B); % obtém dimensões da imagem




  for i=1:lin
    for j=1:col
      if B(i,j)>=limiar
        B(i,j)=255;
      else
        B(i,j)=0;
      end
    end
  end
  


  for i=1:lin
    for j=1:col
      if B(i,j) == 0   % procura preto
        count++;
      end
    end
  end


  p = (count/(lin*col))*100;



  figure
  imshow(B);

  t = title (['\fontsize{15} Binarizacao - Porcentagem de preto encontrado na regiao: ', num2str(p), '%'; 'Maior que 30% e verdadeira']);

endfunction



function binarizacaoCL(arquivo, limiar)
  
  A=imread(arquivo); % Ler o arquivo
  if isrgb(A) % Se a imagem for RGB, faz a conversão para escala de cinza
    A = rgb2gray(A);
  endif
  
  limiar=limiar;

  count = 0;

  B=A( : , end/(5) : end/2);   % corta a imagem

  C = B( end/(3): end/(4/2.8) , 1 : end); % corta de novo, isolando o desenho

  D = B( end/(6) : end/(2.7) , 1 : end/(4/2)); % corta de novo, isolando o quebra cabeca

  E = B( end/1.4 : end/1.15 , end/(1.8) : end/(1)); % corta de novo, isolando o numero
  
  [lin col]=size(C); % obtém dimensões da imagem




  for i=1:lin
    for j=1:col
      if C(i,j)>=limiar
        C(i,j)=255;
      else
        C(i,j)=0;
      end
    end
  end



  for i=1:lin
    for j=1:col
      if C(i,j) == 0   % procura preto
        count++;
      end
    end
  end


  p = (count/(lin*col))*100;

  figure
  imshow(C);

  t = title (['\fontsize{15} Binarizacao - Porcentagem de preto encontrado na regiao: ', num2str(p), '%'; 'Maior que 68% e verdadeira para notas de 100 e 85% para notas de 50']);




  [lin col]=size(D); % obtém dimensões da imagem


  for i=1:lin
    for j=1:col
      if D(i,j)>=limiar
        D(i,j)=255;
      else
        D(i,j)=0;
      end
    end
  end

  count = 0;

  for i=1:lin
    for j=1:col
      if D(i,j) == 0   % procura preto
        count++;
      end
    end
  end


  p = (count/(lin*col))*100;

  figure
  imshow(D);

  t = title (['\fontsize{15} Binarizacao - Porcentagem de preto encontrado na regiao: ', num2str(p), '%'; 'Maior que 58% e verdadeira para notas de 100 e 75% para notas de 50']);



  [lin col]=size(E); % obtém dimensões da imagem


  for i=1:lin
    for j=1:col
      if E(i,j)>=limiar
        E(i,j)=255;
      else
        E(i,j)=0;
      end
    end
  end

  count = 0;

  for i=1:lin
    for j=1:col
      if E(i,j) == 255   % procura branco
        count++;
      end
    end
  end


  p = (count/(lin*col))*100;

  figure
  imshow(E);

  t = title (['\fontsize{15} Binarizacao - Porcentagem de branco encontrado na regiao: ', num2str(p), '%'; 'Maior que 6% e verdadeira']);



endfunction




function binarizacaoHorizontal(arquivo, limiar)
  
  A=imread(arquivo); % Ler o arquivo
  if isrgb(A) % Se a imagem for RGB, faz a conversão para escala de cinza
    A = rgb2gray(A);
  endif

  count = 0;
  
  limiar=limiar;

  B=A(end/5 : end/(4/3), end/(4/3) : end);   % corta a imagem em 4 partes e pega a da extrema direita ( corta em cima tambem)


  [lin col]=size(B); % pega as dimensoes



  for i=1:lin
    for j=1:col-7
      if B(i,j) >= limiar && B(i,j+1) >= limiar && B(i,j+2) >= limiar && B(i,j+3) >= limiar && B(i,j+4) >= limiar && B(i,j+5) >= limiar && B(i,j+6) >= limiar && B(i,j+7) >= limiar
        B(i,j)=255;
        B(i,j+1)=255;
        B(i,j+2)=255;
        B(i,j+3)=255;
        B(i,j+4)=255;
        B(i,j+5)=255;
        B(i,j+6)=255;
        B(i,j+7)=255;
      else
        B(i,j)=0;
      end
    end
  end


  for i=1:lin
    for j=1:col
      if B(i,j) == 255   % procura branco
        count++;
      end
    end
  end


  p = (count/(lin*col))*100;
  
  figure
  imshow(B);
  t = title (['\fontsize{15} Binarizacao - Porcentagem de branco encontrado na regiao: ', num2str(p), '%'; 'Maior que 41% e verdadeira para notas de 100 e 36% para notas de 50.']);

endfunction




% Binarizacao
function binarizacaoFaixa(arquivo, limiar)
  
  A=imread(arquivo); % Ler o arquivo
  if isrgb(A) % Se a imagem for RGB, faz a conversão para escala de cinza
    A = rgb2gray(A);
  endif

  count = 0;
  
  limiar=limiar;

  B=A( : , end/(2) : end/(7/4)); % corta a imagem em 4 partes e pega a da extrema direita
    
  [lin col]=size(B); % obtém dimensões da imagem
  

  for i=1:lin
    for j=1:col
      if B(i,j)>=limiar
        B(i,j)=255;
      else
        B(i,j)=0;
      end
    end
  end



  for j=1:col
    for i=1:lin
      if B(i,j) == 0    % procura preto
        count++;
      end
    end
  end

  p = (count/(lin*col))*100;

  figure
  imshow(B); 
  t = title (['\fontsize{15} Binarizacao - Porcentagem de preto encontrado na regiao: ', num2str(p), '%'; 'Maior que 32% e verdadeira para notas de 100 e 44% para notas de 50']);

 

endfunction
