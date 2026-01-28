program FatorialRecursivo;

var
  numero: Integer;

function Fatorial(n: Integer): Integer;
begin
  if n <= 1 then
    Fatorial := 1
  else
    Fatorial := n * Fatorial(n - 1);
end;


begin
  
  numero := 5;
  
  if numero < 0 then
    WriteLn('Fatorial não definido para números negativos.')
  else
    WriteLn('Fatorial de ', numero, ' é: ', Fatorial(numero));
  
end.
