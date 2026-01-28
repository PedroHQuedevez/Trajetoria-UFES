program FuncaoSemParametros;

var
  dez : Integer;

function GetDez: Integer;
begin
  GetDez := 10;
end;

begin
  dez := GetDez();
  write(dez);
end.
