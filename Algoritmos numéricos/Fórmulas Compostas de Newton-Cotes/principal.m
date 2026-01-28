a = 0;
b = pi;
m = 12;

%[Integral] = regra_trapezios(a, b, m, @f);
%Integral

%[Integral] = regra_13_simpson(a, b, m, @f);
%Integral

[Integral] = regra_38_simpson(a, b, m, @f);
Integral



