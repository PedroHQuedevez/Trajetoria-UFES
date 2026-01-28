function [U, d] = eliminacao_gauss_com_pivotacao(n, A, b)
    U = A;
    d = b;
    det = 1;
    info = 0;

    for j=1:1:n-1
      p=j ;Amax = abs(U(j,j));
      for k=(j+1):1:n
        if abs(U(k,j)) > Amax
          Amax = abs(U(k,j));
          p = k;
          endif
        endfor
        if p != j
          for k=1:1:n
            t = U(j,k);U(j,k) = U(p,k);U(p,k)=t;
          endfor
          t = d(j);d(j) = d(p); d(p) = t; det = -det;
        endif
        det = det*U(j,j);
        if abs(U(j,j)) != 0
          r = 1/U(j,j);
          for i = j+1:1:n
            Mult = U(i,j)*r;U(i,j) = 0;
            for k = j+1:1:n
              U(i,k) = U(i,k) - (Mult*U(j,k));
            endfor
            d(i) = d(i) - (Mult*d(j));
          endfor
        elseif info == 0
          info = j;
        endif
    endfor

    det = det*U(n,n);
    if info == 0 && abs(U(n,n)) == 0
      info = n;
    endif

endfunction
