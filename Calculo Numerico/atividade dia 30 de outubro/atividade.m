%NOME: 

X = [-1 -0.7 -0.4 -0.1 0.2 0.5 0.8 1]';
Y = [36.547 17.264 8.155 3.852 1.82 0.86 0.406 0.246]';

Z = log(Y);

A = [ones(length(X), 1) x];
C = (A'*A)\(A'*Z);

alpha = [exp(c(1)) - c(2)]'

%Dominio
XX = -2:0.01:2;

%Imagem
YY = alpha(1)*exp(-alpha(2)*XX);

plot(X,Y,'*r', 'LineWidth', 4, XX, YY, 'LineWidth', 2)
xlabel('X')
ylabel('y')

legend('Grafico de dispersao', 'Y=a*exp(-b*x)')

y1 = alpha(1)*exp(-alpha(2)*X);
residuo = norm(Y-y1)*2