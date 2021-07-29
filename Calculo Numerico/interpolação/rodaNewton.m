% roda newton_interpol

clear all
clc

xi = [-2 0 3 5];
yi = [3 -2 4 2];
x = 5;

y0 = Newton_interpol(xi, yi, x)

%c = polyfit(xi,yi,3)

%yy = polyval(c,7)


%5xx = -5:0.01:6;

%for i=1:length(xx);
%    yy(i) =  newton_interpol(xi, yi, xx(i));
%end

%plot(xi,yi,'*r',xx,yy)


%legend('Pontos tabelados','Polinomio Interpolador');
    
    
