% Nome 1: Caio Fernando Peres RA: 2000784
% Nome 2:

% SCRIPT DE TESTE E PLOTAGEM DE GRÁFICOS

clear all

clc



f=@(x,y) 10*(y-sin(x))+cos(x);

sol1 = RK2(0,1,1,0.025,f);

sol2 = RK4(0,1,1,0.025,f)

%Plota Grafico

xx = 0:0.025:1;
 
yy = e.^(10*xx)+sin(xx);
 
plot(xx, yy,'-r',sol1(:,1),sol1(:,2),'ob',sol2(:,1), sol2(:,2), '*g')

xlabel('x')
 
ylabel('y')
 
title('Metodo de HEUN x Metodo de RK4')
 
legend('Solucao','HEUN','RK4')

%figure

%plot(xx, yy,'-r',sol2(:,1),sol2(:,2),'ob',sol4(:,1), sol4(:,2),'*g')

%xlabel('x')
 
%ylabel('y')
 

%legend('Solucao','Euler','Taylor')
