%m = 2;
m = 3;
x = [1.0 1.3 1.7 2.0];
y = [0.8415 1.2526 1.6858 1.8186];
%z = 1.1;
z = 1.2;

m
x
y
z

[Pz] = polinomio_lagrange(m, x, y, z);
Pz

