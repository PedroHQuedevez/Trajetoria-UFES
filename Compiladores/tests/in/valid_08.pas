program declarArrayChar;

var
  arr: array[1..10] of Integer;
  i: Integer;

begin
  arr[1] := 20;
  arr[2] := 30;
    for i := 1 to 10 do
        write(arr[i]);
    
end.