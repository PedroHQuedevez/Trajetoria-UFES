

function [Integral] = regra_trapezios (a, b, m, f)
 % Passo do intervalo
    h = (b - a) / m;
   printf("i \t xi \t yi\n");
    soma = 0;
    interacao = 0;
   for i=a:h:b
    valor_funcao = f(i);
    soma = soma +( 2* valor_funcao);
    printf("%i \t %f \t %f\n", interacao, i, valor_funcao);
    interacao = interacao + 1;
   endfor
    % Aplica a regra dos trapézios
    Integral = (h/2) * (soma - f(a) - f(b));

endfunction
