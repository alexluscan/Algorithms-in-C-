

const MAXN=200100;

var S:string;
    A,B:array[0..MAXN]of longint;
    N, K, i, Left, Right, Mid, Sol, Poz, sign, aux, j:longint;

function Check(Rez:longint):boolean;
	var Last, Nr, i:longint;
begin
	Last := -2000000000;
	Nr := 0;
	for i := 1 to N do begin
		if (A[i] <= Last) then
			continue;
		Last := A[i] + Rez;
		inc(Nr);
		if (Nr > K) then break;
	end;
	Check:= (Nr <= K);
end;

procedure interc(Left, Mid, Right:longint);
var i, j, t, k:longint;
begin
       for i:=left to Right do B[i]:=A[i];
       i := Left; j := Mid + 1;  k := Left;
       while(i<=Mid) and (j<=Right) do
        if B[i]>B[j] then begin
         A[k]:=B[j]; inc(j); inc(k)
        end
        else begin
         A[k]:=B[i]; inc(i); inc(k)
        end;
       for t := i to Mid do begin
         A[k] := B[t];
         inc(k)
        end;
       for t := j to Right do begin
         A[k] := B[t];
         inc(k)
        end;
end;

procedure mergesort(Left, Right:longint);
var Mid: longint;
begin
      if Left <> Right then begin
          Mid:=(left + Right) div 2;
          mergesort(left, Mid);
          mergesort(Mid + 1, Right);
          interc(left, Mid, Right)
      end;
end;

begin
	assign(input,'2d.in'); reset(input);
	assign(output,'2d.out'); rewrite(output);

	readln( N, K);
	for  i := 1 to N do begin
		readln(S);
		Poz := 1;
		if (S[1] = '-')then begin
			sign := -1;
			inc(Poz);
		end
		else
			sign := 1;
		A[i] := 0;
		while (S[Poz] <> ' ')  do begin
			if (S[Poz] = '.') then
				inc(Poz);
			A[i] := A[i] * 10 + ord(S[Poz]) - 48;
			inc(Poz);
		end;
		A[i] := A[i] * sign;
	end;

        mergesort(1, N);

	Left := 1000; Right := 2000000000; Sol := 1000;
        while (Left <= Right) do begin
		Mid := (Left + Right) div 2;
		if (Check(Mid)) then begin
			Sol := Mid;
			Right := Mid - 1;
		end
		else
			Left := Mid + 1;
	end;
       str(Sol,S);
       writeln(Sol div 1000 ,'.', copy(S,length(S)-2,3));
       close(output);
end.
