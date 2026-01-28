program TabuadaCompleta;

var
  i, j: Integer;

begin

  for i := 1 to 10 do
  begin
    WriteLn('Tabuada do ', i, ':');
    
    for j := 1 to 10 do
    begin
      WriteLn(i, ' x ', j, ' = ', i * j);
    end;

  end;

end.