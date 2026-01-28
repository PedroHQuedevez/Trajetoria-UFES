function [Integral] = regra_13_simpson(a, b, m, f)

  h = (b - a) / m;

  printf("i \t xi \t yi \t ci\n");
  printf("%d \t %f \t %f \t %i\n", 0, a, f(a), 1);

  Soma = f(a);

  for i=1:2:m-2

    printf("%d \t %f \t %f \t %i\n", i, a + i * h, f(a + i * h), 4);
    printf("%d \t %f \t %f \t %i\n", i + 1, a + (i + 1) * h, f(a + (i + 1) * h), 2);

    Soma = Soma + 4 * f(a + i * h) + 2 * f(a + (i + 1) * h);

  endfor

  printf("%d \t %f \t %f \t %i\n", m - 1, a + (m - 1) * h, f(a + (m - 1) * h), 4);
  printf("%d \t %f \t %f \t %i\n", m, a + m * h, f(a + m * h), 1);

  Soma = Soma + 4 * f(a + (m - 1) * h) + 1 * f(a + m * h);

  Integral = h * Soma / 3;

endfunction
