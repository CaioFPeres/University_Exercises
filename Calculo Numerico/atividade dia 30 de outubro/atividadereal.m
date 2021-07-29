%NOME: Caio Fernando Peres  RA: 2000784

X = [0.0 	0.5 	1 	1.5 	2 	2.5 	3]';
Y = [2.8 	0.9 	0.67 	0.55 	0.48 	0.43 	0.4]';

Z = 1./(Y.^2);

A = [ones(length(X), 1) X];

c = (A'*A)\(A'*Z);

alpha = [c(1) c(2)]'

XX = -0.03:0.01:4;

YY = sqrt(1./((c(1)+c(2))*XX));

plot(X,Y,'*r', 'LineWidth', 4, XX, YY, 'LineWidth', 2)
xlabel('X');
ylabel('Y');

y1 = sqrt(1./(c(1)+c(2)*X));
residuo = norm(Y-y1)*2