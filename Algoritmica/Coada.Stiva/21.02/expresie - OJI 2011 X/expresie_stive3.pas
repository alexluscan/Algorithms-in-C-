(*
     Constantin Galatan (translatare in pascal)
     Stive
     Complexitate O(n)
*)

const nmax = 100002;
type Stiva = 	array[0..nmax] of longint;
var st : Stiva;
	f, g : text;
	ex : array[0..nmax] of char;
	r, d : array[0..nmax div 2] of longint;
	L, i, k, x, y, j, kd, kr, S, sm, Max, nr : longint;
	sol : longint;

	 	
procedure swap(var a, b : longint);
var temp : integer;
begin
		temp := a; a := b; b := temp; 
end;

Function quickselect(var a : Stiva; st, dr, k : longint) : longint;
var i, j, ir, l, mid, p: integer;
	ok : boolean;
begin
	l := st;
	ir := dr;
	while ( ok) do
	begin
		if ir <= l+1 then 
			begin
				if (ir = l + 1) and (a[ir] < a[l]) then
					swap(a[l], a[ir]);
            
				quickselect:= a[k];
				ok := false;
			end
		else 
			begin
				mid := trunc((l+ir) div 2);
				swap(a[mid], a[l+1]);
				if a[l] > a[ir] then
					swap(a[l],a[ir]);
			
				if (a[l+1] > a[ir]) then
					swap(a[l+1],a[ir]);
          
				if (a[l] > a[l+1]) then
					swap(a[l],a[l+1]);
          
				i := l + 1;
				j := ir;
				p := a[l+1];
				while (true) do
				begin
					repeat inc(i); until (a[i] >= p);
					repeat dec(j); until (a[j] <= p);
					if (j < i) then break;
					swap(a[i],a[j]);
				end;
				a[l+1] := a[j];
				a[j] := p;
				if (j >= k) then ir := j - 1;
				if (j <= k) then l := i;
			end
		end
end;


begin {PP}
	assign(f, 'expresie.in'); reset(f);
	assign(g, 'expresie.out'); rewrite(g);
	L := 0;
	while ( not eoln(f) ) do
	begin
		read(f, ex[L]);
		inc(L);
	end;

	i := 0; k := 0; kd := 0; kr := 0;
	while i < L do
	begin
		if ex[i] = '(' then
		begin
			inc(i); inc(kr); r[kr] := k + 1;
		end;
		if ex[i] ='[' then
		begin
			inc(i); inc(kd); d[kd] := k + 1;
		end;
		if ((('0' <= ex[i]) and (ex[i] <= '9')) or (ex[i] = '-')) then
			begin
				if (ex[i] ='-') then
					begin
						sm := -1; inc(i);
					end
                else sm := 1;
				
				x := 0;
				while ('0' <= ex[i]) and (ex[i] <= '9') and (i < L) do
					begin
							x := x * 10 + ord(ex[i]) - ord('0');
							inc(i);
					end;
				inc(k);
				st[k] := sm * x;
				if (ex[i] = ',') then begin inc(i); inc(nr); end;
			end;
		if ex[i] = ')' then
			begin
				//secventa de suma maxima
				x := r[kr];
				S := st[x]; Max := S;
				j := x + 1;
				while (j <= k ) do
				begin          
                    if (S + st[j] < st[j]) then 
						S := st[j]
                    else 
						inc(S, st[j]);
                    if (S > Max) then Max := S;
                    
                    inc(j);
                end;
				k := x; dec(kr);
				st[k] := Max;
				inc(i);
			end;
		if (ex[i] =']') then
            begin
                 //determinam mediana
                 x := d[kd];
                 y := quickselect(st, x, k, trunc((k+x)div 2));
                 k := x; dec(kd);
                 st[k] := y;
                 inc(i);
             end;
		if (ex[i] = ',') then begin inc(i); inc(nr); end;
	end;
	sol := 0;
	for i := 1 to k do	
		inc(sol, st[i]);
	
	writeln(g, nr + 1);
	writeln(g, sol);	
	
	close(f); close(g);
end.
