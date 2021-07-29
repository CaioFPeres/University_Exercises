clc 

clear all

f = @(x) 2.^x-3*x; %mudar isso para a função desejada


tei=0:0.01:3; %mudar os valores da esquerda e direita para estarem em volta do zero da função
 
tau = f(tei);

x0 = 0.7;
x1 = 2; 


iteracoes = 1000;
  difMinima = 0.001;
  aprox_min = 0.001;
  
  diferenca = 1;
  
  i = 2;
  x(1) = x0;
  y(1) = f(x0);
  x(2) = x1;
  y(2) = f(x1);
  
  while ((i<(iteracoes-2)) && (abs(diferenca)>=difMinima) && (abs(y(i))>aprox_min))
    diferenca = y(i) - y(i-1);
    x(i+1) = (x(i-1)*f(x(i))-x(i)*f(x(i-1)))/diferenca;
    y(i+1) = f(x(i+1));
    i++;
  endwhile
  
  guiaIndice = 1:i;
  x_sol=[guiaIndice' x' y'];
  
  for j = 1:i;
  
  printf("%d | %f | %f\n",j,x(j),y(j));
  
endfor
  

plot(tei,tau,'b',x_sol(:,2),x_sol(:,3),'*r-');

grid on

title('Metodo da Secante')

legend('f(x)=x^3-x^2-1','Pontos gerados pelo Metodo') %mudar a função para a desejada
legend('Location','southeast')
