program FuncaoComString;

var
  msg : String;

function Mensagem: String;
begin
  Mensagem := 'Olá, mundo!';
end;

begin
  msg := Mensagem();
  write(msg);
end.