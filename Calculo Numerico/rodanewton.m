% Roda Script do metodo de Newton

clc 

clear all

f = @(x) 2.^x-3*x;

df = @(x) 2.^x * log(2)-3;

x=-6:0.01:5;
 
y = f(x);

x_sol = newtonraphson(f,df,3)


plot(x,y,'b',x_sol(:,2),x_sol(:,3),'*r-');

grid on

title('Metodo de Newton-Raphson')

legend('f(x)=x^3-x^2-1','Pontos gerados pelo Metodo')
legend('Location','southeast')
