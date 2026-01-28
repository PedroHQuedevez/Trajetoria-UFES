program ContarAteN;

var
  N: Integer;

procedure Contar(x: Integer);
begin
  if x > 0 then
  begin
    Contar(x - 1);
    Write(x, ' ');
  end;
end;

begin

  N := 5;
  if N < 1 then
    WriteLn('Numero invalido. Digite um valor maior ou igual a 1.')
  else
  begin
    WriteLn('Contando de 1 ate ', N, ':');
    Contar(N);
  end;

end.
