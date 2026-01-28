program declarArray;

var
  arr: array[1..10] of Integer;
  i: Integer;

begin
    for i := 1 to 10 do
        arr[i] := i * 2;
    write(arr[i]);
    
end.