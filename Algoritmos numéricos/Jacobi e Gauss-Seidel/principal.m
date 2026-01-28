%A = [10 2 -3 5; 1 8 -1 2; 2 -1 -5 1; -1 2 3 20];
%b = [48; 4; -11; 150];

%A = [1 2 -2; 1 1 1; 2 2 1];
%b= [-1; 6; 9];

A = [1 -0.5 0.5; 1 1 1; -0.5 -0.5 1];
b = [3; 12; 3];

n = size(A)(1);
Toler = 10^-3;
IterMax = 10;

n
A
b
Toler
IterMax

printf("Solução de sistema linear pelo método de Jacobi\n");
[x, Iter, Info] = jacobi(n, A, b, Toler, IterMax);

%printf("Solução de sistema linear pelo método de Gauss-Seidel\n");
%[x, Iter, Info] = gauss_seidel(n, A, b, Toler, IterMax);

x
Iter
Info

r = b - A * transpose(x);
r
