program VariaveisGlobaisLocais;

var
  x: Integer;

function IncX: Integer;
var
  y: Integer;
begin
  y := x + 1;
  IncX := y;
end;

begin
  x := IncX();
  write(x);
end.