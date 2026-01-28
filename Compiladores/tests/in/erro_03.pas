program ArgumentosErrados;

function H(a, b: Integer): Integer;
begin
  H := a + b;
end;

begin
  writeln(H(1)); // Faltando argumento
end.