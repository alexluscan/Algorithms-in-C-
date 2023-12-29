{$A+,B-,D+,E+,F-,G-,I-,L+,N-,O-,P-,Q-,R-,S-,T-,V+,X+,Y+}
{$M 65500,0,655360}

{ Time Complexity : O(N) }

Program _color_;

const filein = 'color.in';
      fileout = 'color.out';
      MAXN = 16000;

type bytearray = array [1..MAXN] of byte;
     intarray = array [1..MAXN] of integer;
     pintarray = ^intarray;

var i, j, k, n, m : integer;
    winup, windown : bytearray;
    nfii, tata, frate : pintarray;
    fiu : array [1..2] of pintarray;
    ok : boolean;

procedure dfdown(nod : integer);
begin
if (nfii^[nod] = 0) then
  windown[nod] := 1
else
  begin
    dfdown(fiu[1]^[nod]);
    dfdown(fiu[2]^[nod]);

    windown[nod] := (1 - windown[fiu[1]^[nod]]) and
                    (1 - windown[fiu[2]^[nod]]);
  end;
end;

procedure dfup(nod : integer);
begin
if (nod = 1) then
  winup[1] := 1
else
  winup[nod] := windown[frate^[nod]] or
                (1 - winup[tata^[nod]]);

if (nfii^[nod] > 0) then
  begin
    dfup(fiu[1]^[nod]);
    dfup(fiu[2]^[nod]);
  end;
end;

begin
assign(input, filein);
reset(input);
read(n);

new(nfii);
new(tata);
new(frate);
new(fiu[1]);
new(fiu[2]);

fillchar(nfii^, sizeof(intarray), 0);
fillchar(tata^, sizeof(intarray), 0);

for k := 1 to n-1 do
  begin
    read(i, j);

    tata^[j] := i;
    inc(nfii^[i]);
    fiu[nfii^[i]]^[i] := j;
  end;

close(input);

for i := 1 to n do
  if (nfii^[i] = 2) then
    begin
      frate^[fiu[1]^[i]] := fiu[2]^[i];
      frate^[fiu[2]^[i]] := fiu[1]^[i];
    end;

dfdown(1);
dfup(1);

m := 0;
for i := 1 to n do
  if (winup[i] and windown[i] = 1) then
    inc(m);


ok := false;
for i := 2 to n do
  if (winup[i] and windown[i] = 1) and (nfii^[i] > 0) then
    ok := true;

if (ok) then
  writeln('OK')
else
  writeln('not OK');

assign(output, fileout);
rewrite(output);
writeln(m);
for i := 1 to n do
  if (winup[i] and windown[i] = 1) then
    write(i, ' ');
writeln;
close(output);
end.