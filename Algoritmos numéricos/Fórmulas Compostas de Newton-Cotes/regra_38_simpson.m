function [Integral] = regra_38_simpson(a, b, m, f)
 h = (b - a) / m;
    Soma = f(a);

    printf("i \t xi \t yi \t ci\n");
    printf("%d \t %f \t %f \t %i\n", 0, a, f(a), 1);


    for i = 1:3:m-3
        printf("%d \t %f \t %f \t %i\n", i, a + i * h, f(a + i * h), 3);
        printf("%d \t %f \t %f \t %i\n", i + 1, a + (i + 1) * h, f(a + (i + 1) * h), 3);
        printf("%d \t %f \t %f \t %i\n", i + 2, a + (i + 2) * h, f(a + (i + 2) * h), 2);

        Soma = Soma + 3 * f(a + i * h) + 3 * f(a + (i + 1) * h) + 2 * f(a + (i + 2) * h);
    end

    printf("%d \t %f \t %f \t %i\n", m - 2, a + (m - 2) * h, f(a + (m - 2) * h), 3);
    printf("%d \t %f \t %f \t %i\n", m - 1, a + (m - 1) * h, f(a + (m - 1) * h), 3);
    printf("%d \t %f \t %f \t %i\n", m, a + m * h, f(a + m * h), 1);

    Soma = Soma + 3 * f(a + (m - 2) * h) + 3 * f(a + (m - 1) * h) + 1 * f(a + m * h);

    Integral = 3 * h * Soma / 8;
endfunction
