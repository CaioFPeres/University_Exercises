clc 
clear all

f = @(x) 2.^x-3*x; %mudar isso para a função desejada

x =-1:0.01:1; %mudar os valores da esquerda e direita para estarem em volta do zero da função
 
 
fy = f(x);

a = -2; %mudar valor para estar à esquerda da função
b = 4; %mudar valor para estar à direita da função
indice = 0;
f_p = 100;
diferenca = 1;

while((f_p != 0) && (diferenca > 0.001) && (abs(f_p)>0.001))

  p = ((a*f(b)) - (b*f(a))) / (f(b) - f(a));
  diferenca = abs(f_p - f(p));
  f_p = f(p);
  indice++;
  x(indice) = p;
  y(indice) = f_p;
  
  if(f_p > 0)
    a = p;
else
    b = p;
endif
endwhile


%guiaIndice = 1:indice;
%sol=[guiaIndice' x' y'];

for j = 1:indice;
  
  printf("%d | %f | %f\n",j,x(j),y(j));
  
endfor


plot(x,fy,'b',sol(:,2),sol(:,3),'*r-');
grid on


legend('(3*x)-cos(x)+1','Pontos gerados pelo Metodo'); %mudar a função para a desejada
legend('Location','southeast');