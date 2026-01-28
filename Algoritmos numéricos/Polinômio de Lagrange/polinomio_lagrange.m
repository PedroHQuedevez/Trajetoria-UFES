function [Pz] = polinomio_lagrange(m, x, y,z)
    Pz = 0;

    for i = 1:m
      c = 1;
      d = 1;
        for j = 1:m
          if i != j
            c = c*(z-x(j));
            d = d * (x(i)-x(j));
          endif
        endfor
        Pz = Pz + y(i) * (c/d);
    endfor
endfunction

