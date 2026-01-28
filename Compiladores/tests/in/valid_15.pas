program ClassificacaoNota;

var
  nota: Real;

begin
  nota := 6;

  if (nota >= 0) and (nota <= 10) then
  begin
    if nota >= 7 then
    begin
      if nota >= 9 then
        WriteLn('Excelente!')
      else
        WriteLn('Aprovado com bom desempenho.');
    end
    else
    begin
      if nota >= 5 then
        WriteLn('Recuperação.')
      else
        WriteLn('Reprovado.');
    end;
  end
  else
    WriteLn('Nota inválida. Digite um valor entre 0 e 10.');


end.
