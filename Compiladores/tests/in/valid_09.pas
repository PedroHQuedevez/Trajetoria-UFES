program TesteAritmetica;
var
    x, y, z: integer;
    resultado: real;
begin
    x := 20;
    y := 3;
    z := x - y;
    resultado := x / y;
    write(z);
    write(resultado);
    if x > y then
        write('verdadeiro')
    else
        write('falso');
end.
