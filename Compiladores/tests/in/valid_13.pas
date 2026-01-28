program TesteCondicional;
var
    x, y: integer;
    resultado: boolean;
begin
    x := 10;
    y := 5;
    resultado := x > y;
    write(resultado);
    if x > y then
        write('x é maior que y')
    else
        write('x não é maior que y');
end.
