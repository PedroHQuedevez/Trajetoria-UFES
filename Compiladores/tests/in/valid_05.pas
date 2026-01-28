program OperacoesComProcedures;

var
  num1, num2: Real;

procedure Soma(a, b: Real);
begin
  write('Soma: ');
end;

procedure Subtrai(a, b: Real);
begin
  write('Subtração: ');
end;

procedure Multiplica(a, b: Real);
begin
  write('Multiplicação: ');
end;

procedure Divide(a, b: Real);
begin
  if b <> 0 then
    write('Divisão: ')
  else
    write('Divisão por zero não é permitida.');
end;

begin

  num1 := 1.2;
  num2 := 1.5;

  Soma(num1, num2);
  Subtrai(num1, num2);
  Multiplica(num1, num2);
  Divide(num1, num2);

end.