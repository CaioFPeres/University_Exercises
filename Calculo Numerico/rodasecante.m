clc 

clear all

f = @(x) 3*x-e.^x;


x=-6:0.01:5;
 
y = f(x);


x_sol = secante(f,0.70711,2)


plot(x,y,'b',x_sol(:,1),x_sol(:,2),'*r-');

grid on

title('Metodo da Secante')

legend('f(x)=x^3-x^2-1','Pontos gerados pelo Metodo')
legend('Location','southeast')
