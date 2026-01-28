program FuncoesComVariaveisIguais;

var
  x, y, a, z: Real;



function Multiplicar(a, b: Real): Real;
var
  resultado: Real;
begin
  resultado := a * b;
  Multiplicar := resultado;
end;

function Dividir(a, b: Real): Real;
var
  resultado: Real;
begin
  if b <> 0 then
    resultado := a / b
  else
  begin
    writeln('Erro: Divisão por zero!');
    resultado := 0;
  end;
  Dividir := resultado;
end;


begin
  x := 2;
  y := 3;
  a := Multiplicar(x, y);
  write(a);
end.