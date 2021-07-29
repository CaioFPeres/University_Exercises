%Caio Fernando Peres	      		RA: 769298
%Isabelle Tomazela Barizon		RA: 759507 
%Rafael Tofoli Sereicikas	  	RA: 760934
%Thaina de Almeida Santana		RA: 761067
%Vitor Pacheco de Carvalho		RA: 760941 

function trabalho_2
  
%--------------- Inicialização ---------------

close all %fecha todas as janelas
clear %limpa memoria
clc %limpa a tela

%---------------------------------------------

 is_0('0.png');
 is_1('1.png');
 is_2('2.png');
 is_3('3.png');
 is_4('4.png');
 is_5('5.png');
 is_6('6.png');
 is_7('7.png');
 is_8('8.png');
 is_9('9.png');

endfunction



%---------------- Identifica o zero -----------
function is_0(img)

A = imread(img);
A = im2bw(A);

B = bwmorph(A,'skel',Inf);

[h,w] = size(B);



% aqui é para encontrar a borda da esqueletização

for i= 1 : w
	if(B(h/2, i) == 1)
		break;
	endif
endfor


for j = 1 : h
	if(B(j, w/2) == 1)
		break;
	endif 
endfor




% aqui é para encontrar as pontas do esqueleto do zero
% o + 50 é uma margem para sair da possibilidade de encontrar a borda do esqueleto exterior 

achou = 0;


for ai = i+50 : w - i - 50
	for aj = j+50 : h - j - 50
		if(B(aj, ai) == 1)
			achou = 1;
			break;
		endif
	endfor
	if(achou == 1)
		break;
	endif
endfor


achou = 0;


for bj = j+50 : h - j - 50
	for bi = i+50 : w - i - 50
		if(B(bj, bi) == 1)
			achou = 1;
			break;
		endif
	endfor
	if(achou == 1)
		break;
	endif
endfor


achou = 0;


for cj = h - j - 50 : -1 : j+50
	for ci = w - i - 50 : -1 : i+50
		if(B(cj, ci) == 1)
			achou = 1;
			break;
		endif
	endfor
	if(achou == 1)
		break;
	endif
endfor

% aqui é para verificar se o valor é simétrico com uma certa margem de erro


achou = 0;

distanciaCentro = aj - bj + aj;


if(distanciaCentro - 5 < cj && distanciaCentro + 5 > cj)
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Esqueletizacao',; 'Resultado: Identificou o numero zero']);
else
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Esqueletizacao',; 'Resultado: Nao identificou corretamente']);
endif

endfunction



%---------------- Identifica o um -----------
function is_1(img)

  A = imread(img);
  A = im2bw(A);

  B = bwmorph(~A,'thin',Inf);

  contx = 0;
  conty = 0;


  for i = 1: 500
      for j = 1: 500
          if(B(i, j) == 1)
              conty++;
              break;
          endif
      endfor
  endfor

  for j = 1: 500
      for i = 1: 500
          if(B(i, j) == 1)
              contx++;
              break;
          endif
      endfor
  endfor


  relacao = conty/contx;


if(relacao > 3 && relacao < 3.5)
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Afinamento',; 'Resultado: Identificou o numero um']);
else
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Afinamento',; 'Resultado: Nao identificou corretamente']);
endif

endfunction

%---------------- Identifica o dois -----------
function is_2(img)

pkg load image

A = imread(img);
A = rgb2gray(A);

%corta o 2
A = A(290:360,205:500);


l = bwlabel(A);
p = regionprops(l, 'Orientation');

resul = p.Orientation;

if(resul > 44 && resul < 46)
    figure, imshow(img);
    t = title (['\fontsize{15} Descritor usado: Orientation: ', num2str(resul); 'Resultado: Identificou o numero dois']);
else
    figure, imshow(img);
    t = title (['\fontsize{15} Descritor usado: Orientation: ', num2str(resul); 'Resultado: Nao identificou corretamente']);
endif

endfunction

%---------------- Identifica o três -----------
function is_3(img)

pkg load image

A = imread(img);
BW = im2bw(A);
BW = ~BW;
s = regionprops(BW,'Eccentricity');
Eccentricity = s.Eccentricity;

if ( Eccentricity > 0.85 && Eccentricity < 0.88)
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Excentricidade',; 'Resultado: Identificou o numero tres']);
else
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Excentricidade',; 'Resultado: Nao identificou corretamente']);
endif

endfunction

%---------------- Identifica o quatro -----------
function is_4(img)


A = imread(img);
A = im2bw(A);


stats = regionprops(A,'Area');

% tem q usar try catch pq dependendo da imagem a funcao nao retorna 2 areas distintas

try
    [areaExterna, areaInterna] = stats.Area;
catch
    figure, imshow(img);
    t = title (['\fontsize{15} Descritor usado: Area e Bounding box',; 'Resultado: Não identificou corretamente']);
    return;
end_try_catch

box = regionprops(A,'BoundingBox');

[first, second] = box.BoundingBox;

% pega as medidas do triangulo dentro do 4

base = second(3);
altura = second(4);

% encontramos a base e altura dentro do numero 4, agora temos que ver se é mesmo um triangulo retangulo
% area do triangulo retangulo:  base x altura / 2

if( (base*altura)/2 - areaInterna < 350 && (base*altura)/2 - areaInterna >= -350)
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Area e Bounding box',; 'Resultado: Identificou o numero quatro']);
else
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Area e Bounding box',; 'Resultado: Não identificou corretamente']);
endif


endfunction

%---------------- Identifica o cinco -----------
function is_5(img)

pkg load image

A = imread(img);
A = im2bw(A);

%corta o 5
A = A(166:173,214:220);

A = imrotate(A, 0);

l = bwlabel(A);

p = regionprops(l, 'Orientation');

resul = p.Orientation;

if(resul > 89 && resul < 91)
    figure, imshow(img);
    t = title (['\fontsize{15} Descritor usado: Orientation: ', num2str(resul); 'Resultado: Identificou o numero cinco']);
else
    figure, imshow(img);
    t = title (['\fontsize{15} Descritor usado: Orientation: ', num2str(resul); 'Resultado: Nao identificou corretamente']);
endif


endfunction


%---------------- Identifica o seis -----------
function is_6(img)

  img_num = imread(img);
  img_num = im2bw(img_num);

  primeiro_corte = img_num(1:290,1:500);
  segundo_corte = img_num(250:500,1:500,:);

  euler_primeiro = bweuler(~primeiro_corte);
  euler_segundo = bweuler(~segundo_corte);


  if(euler_primeiro == 1 && euler_segundo == 0)
    figure, imshow(img);
    t = title (['\fontsize{15} Descritor usado: Numero de Euler',; 'Resultado: Identificou o numero seis']);
  else
    figure, imshow(img);
    t = title (['\fontsize{15} Descritor usado: Numero de Euler',; 'Resultado: Nao identificou corretamente']);
  endif

endfunction


%---------------- Identifica o sete -----------
function is_7(img)

I = imread(img);
I = rgb2gray(I);
I = bwmorph(~I, 'thin', Inf);
I = mat2gray(~I);

Edges = edge(I, 'Sobel');

b = bwboundaries(I);
[boundarycount, asdf] = size(b);
grid = 10;

for k=2:boundarycount
    j=0;
    array = [];
    [rows, columns] = size(b{k,1});
    for i=1:rows-1
        y = round(b{k,1}(i,1)/grid);
        x = round(b{k,1}(i,2)/grid);
        y2 = round(b{k,1}(i+1,1)/grid);
        x2 = round(b{k,1}(i+1,2)/grid);

        dx = x2 - x;
        dy = y2 - y;
        if not(dx == 0 && dy==0)
            j = j+1;
            if (dx == 1 && dy ==0)
               array(j) = 0;
            end
            if (dx == 1 && dy ==1)
               array(j) = 1;
            end
            if (dx == 0 && dy ==1)
               array(j) = 2;
            end
            if (dx == -1 && dy ==1)
               array(j) = 3;
            end
            if (dx == -1 && dy ==0)
               array(j) = 4;
            end
            if (dx == -1 && dy ==-1)
               array(j) = 5;
            end
            if (dx == 0 && dy ==-1)
               array(j) = 6; 
            end
            if (dx == 1 && dy ==-1)
               array(j) = 7; 
            end
        end
    end;
end;

%----------------- identificando se é 7 ou não ------------------------%
array_comparacao = [0 0 0];
if(array(1) == array_comparacao(1) && array(2) == array_comparacao(2) && array(3) == array_comparacao(3)) %Verifica as primeiras 3 posicoes da cadeia, pois o 7 e o unico que mantem uma sequencia de zeros
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Afinamento + Cadeia',; 'Resultado: Identificou o numero sete']);
else
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Afinamento + Cadeia',; 'Resultado: Nao identificou corretamente']);
end
%-----------------------------------------------------------------------%

endfunction

%---------------- Identifica o oito -----------
function is_8(img)

A = imread(img);
A = im2bw(A);
euler = bweuler(~A);


if(euler == -1)
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Numero de Euler',; 'Resultado: Identificou o numero oito']);
else
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Numero de Euler',; 'Resultado: Nao identificou corretamente']);
end


endfunction

%---------------- Identifica o nove -----------

function is_9(img)

img_num = imread(img);
img_num = im2bw(img_num);

primeiro_corte = img_num(1:290,1:500);
segundo_corte = img_num(260:500,1:500,:);

euler_primeiro = bweuler(~primeiro_corte);
euler_segundo = bweuler(~segundo_corte);


if(euler_primeiro == 0 && euler_segundo == 1)
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Numero de Euler',; 'Resultado: Identificou o numero nove']);
else
  figure, imshow(img);
  t = title (['\fontsize{15} Descritor usado: Numero de Euler',; 'Resultado: Nao identificou corretamente']);
endif

endfunction

