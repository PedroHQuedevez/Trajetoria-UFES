function [U, d] = eliminacao_gauss_sem_pivotacao(n, A, b)
    U = A;
    d = b;

    for j = 1:1:n-1
        for i = j+1:1:n
            Mult = U(i,j) / U(j,j);
            U(i, j:1:n) = U(i, j:1:n) - Mult * U(j, j:1:n);
            d(i) = d(i) - Mult * d(j);
        end
    end
end

