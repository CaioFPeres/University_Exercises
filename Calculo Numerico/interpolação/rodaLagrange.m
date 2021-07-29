% roda Lagrange 

clear all
clc

x = [-2 0 3 5];

y = [3 -2 4 2];

c = polyfit(x,y,3)

res= polyval(c,2)

y0 = Lagrange(x, y, 2)