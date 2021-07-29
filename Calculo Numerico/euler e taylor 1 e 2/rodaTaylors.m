%NOME: CAIO FERNANDO PERES  RA: 2000784
% Funcoes do PVI
f = @(x, y) (2*y/(x+1)) + (x + 1).^3;

fx = @(x, y) (-2*y/(x+1)) + 3*(x + 1).^2;

fy = @(x, y) 2/(x+1);

sol1= euler(0,1,2,0.5,f)

sol2= euler(0,1,2,0.25,f)
 
sol3= euler(0,1,2,0.05,f)

sol4 = taylor2(0,1,2,0.25,f,fx,fy)
 
% Plota solucao real
xx = 0:0.01:2;
 
yy = [(xx + 1).^4 + 5*(xx +1).^2]./2;
 
plot(xx, yy,'-r',sol1(:,1),sol1(:,2),'ob',sol2(:,1), sol2(:,2),'*g',sol3(:,1), sol3(:,2),'pc')

xlabel('x')
 
ylabel('y')
 
title('Metodo de Euler')
 
legend('Solucao','h = 0.5','h = 0.25','h = 0.01')

figure

plot(xx, yy,'-r',sol2(:,1),sol2(:,2),'ob',sol4(:,1), sol4(:,2),'*g')

xlabel('x')
 
ylabel('y')
 

legend('Solucao','Euler','Taylor')