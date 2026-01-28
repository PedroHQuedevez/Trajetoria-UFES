program VerificaPar;

var
numero: Boolean;
numero2: Real;

begin
numero := True;
numero2 := 2;
if (False = numero) then
	Write('O numero ', numero, ' é False.')
	else
		Write('O numero ', numero, ' é impar.');

end.
