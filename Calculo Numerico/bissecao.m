clc 
clear all

f = @(x) 2.^x-3*x; %mudar isso para a função desejada

tei =1:0.01:1.5; %mudar os valores da esquerda e direita para estarem em volta do zero da função
 
tau = f(tei);

a = 0.9; %mudar valor para estar à esquerda da função
b = 1.6; %mudar valor para estar à direita da função
indice = 0;
f_p = 100;
diferenca = 1;

while((f_p != 0) && (diferenca > 0.001) && (abs(f_p)>0.001))

  p = (a+b)/2;
  diferenca = abs(f_p - f(p));
  f_p = f(p);
  indice++;
  x(indice) = p;
  y(indice) = f_p;
  
  if(!(((f(a) > 0) && (f_p > 0)) || ((f(a) < 0) && (f_p < 0))))
    b = p;
endif


  if(!(((f(b) > 0) && (f_p > 0)) || ((f(b) < 0) && (f_p < 0))))
    a = p;
endif

endwhile


guiaIndice = 1:indice;
sol=[guiaIndice' x' y'];

for j = 1:indice
  
  printf("%d | %f | %f\n",j,x(j),y(j));
  
endfor


plot(tei,tau,'b',sol(:,2),sol(:,3),'*r-');
grid on;

title('Metodo da Bissecao');
legend('sqrt(x.^2+1) - x.^2','Pontos gerados pelo Metodo'); %mudar a função para a desejada
legend('Location','southeast');