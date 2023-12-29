{Description: O(nlogc) - O(logc) brush (full binary tree, range 0..30000)}
{Tomasz Walen, walen@mimuw.edu.pl}
{2001.05.07}
{$I+,$R+,$O+}
program mar;
const
   f_in	    = 'mar10.in';
   f_out    = 'mar.out';
   maxn	    = 10000;
   max_edge = 70001;
   miny	    = 0;
   maxy	    = 30000;
var
   f	 : text;
   edge	 : array[0..max_edge] of integer;
   sum	 : array[0..max_edge] of integer;
   e	 : array[0..2*maxn,1..4] of integer; {(x,y0,y1,delta=+-1)}
   en	 : longint;	
   n	 : integer;
   area	 : longint;

procedure error(msg : string);
begin
   Writeln(msg);
   readln;
   halt(1);
end;
	
{*****}

procedure qsort(l,r : longint);
var
   i,j	 : longint;
   tmp	 : integer;
   m1,m4 : integer;
   ii	 : integer;
   m	 : longint;
begin
   if (l<r) then begin
      m:=(l+r) div 2;
      m1:=e[m,1];m4:=e[m,4];
      i:=l;j:=r;
      repeat                        { sortarea punctelor dupa x si la acelasi x, dupa y }
	 while (e[i,1]<m1) or ((e[i,1]=m1) and (e[i,4]<m4)) do inc(i);
	 while (m1<e[j,1]) or ((e[j,1]=m1) and (m4<e[j,4])) do dec(j);
	 if (i<=j) then begin
	    for ii:=1 to 4 do begin
	       tmp:=e[i,ii];e[i,ii]:=e[j,ii];e[j,ii]:=tmp;
	    end;
	    inc(i);
	    dec(j);
	 end;
      until i>j;
      if (l<j) then qsort(l,j);
      if (i<r) then qsort(i,r);
   end;
end; { qsort }

procedure correct(v,L,R	: longint);
begin
   if (edge[v]=0) and (L<R) then begin     { ma asigur ca exista fii }
      sum[v]:=sum[2*v]+sum[2*v+1];
   end;
end;

procedure add(v			 : longint;           { nodul }
	     L ,R : integer;       { intervalul atasat lui }
	     y0,y1		 : integer;               { intervalul care trebuie obtinut }
	     delta		 : integer);              { +1 segm vertical de stanga, -1 dreapta }
var
   m : integer;
begin
{   Writeln('add v=',v,' (',L,',',R,') y=(',y0,',',y1,') delta=',delta);}
   if (y0 <= L) and (R <= y1) then
   begin
      if (delta > 0) then
      begin
	     edge[v]:=edge[v]+delta; { cate segmente acopera perfect intervalalul [L, R]}
	     sum[v] := (R + 1 - L) * delta;  { l - r + 1 };            { lungimea acoperita pe intervalul [min_valeu, R   }
      end
      else
      begin
	     edge[v]:=edge[v] + delta; { delta < 0 }
	     if (edge[v]=0) then
         begin
	        sum[v]:=0;
	        correct(v,L,R);
	        end;
      end;
{      Writeln('v=',v,' (',L,',',R,') delta=',delta,' edge=',edge[v],' sum=',sum[v]);      }
   end
      else
       if (L<R) then
       begin
            m:=(L + R) div 2;
            {res: = 0; }
            if (y0 <= m) then add(2*v, L, m, y0, y1, delta);
            if (m < y1) and (m < R)
	              then add(2*v+1, m+1, R, y0, y1, delta);
            correct(v, L, R);
       end;
end;

procedure new_edge(y0,y1,delta : integer);
begin
{   Writeln('new_edge y0=',y0,' y1=',y1,' delta=',delta);}
   add(1, miny, maxy, y0, y1-1, delta);
{   Writeln('e_len=',edge[1]);}
end;

{*****}

procedure read_data;
var
   x1,x2,y1,y2 : integer;
   i	       : integer;
begin
   assign(f,f_in);
   reset(f);
   readln(f,n);

   if (n<1) or (n>maxn) then error('wrong n value');

   en:=0;
   for i:=1 to n do begin
      readln(f,x1,y1,x2,y2);

      if (x1<miny) or (x1>maxy) then error('wrong x1 value');
      if (y1<miny) or (y1>maxy) then error('wrong y1 value');
      if (x2<miny) or (x2>maxy) then error('wrong x2 value');
      if (y2<miny) or (y2>maxy) then error('wrong y2 value');

      if (x1>=x2) or (y1>=y2) then error('wrong rectangle');

      inc(en);       { primul segment vertical al dreptunghiului }
      e[en,1]:=x1;
      e[en,2]:=y1;
      e[en,3]:=y2;
      e[en,4]:=1;

      inc(en);      { al doilea segment vertical al dreptunghiului }
      e[en,1]:=x2;
      e[en,2]:=y1;
      e[en,3]:=y2;
      e[en,4]:=-1;
   end;

   close(f);
end; { read_data }

procedure solve;
var
   i : integer;
begin
   fillchar(edge,sizeof(edge),0);
   fillchar(sum,sizeof(sum),0);
   area:=0;

   qsort(1,en);

   e[0,1]:=0;
   for i:=1 to en do
   begin
      if (i>1) and (e[i,1]<>e[i-1,1]) then
      begin
           { Writeln('area+=',sum[1],'*',(e[i,1]-e[i-1,1]),'=',(sum[1]*(e[i,1]-e[i-1,1])));}
	     area:=area+(sum[1]*(e[i,1]-e[i-1,1]));
      end;
      new_edge(e[i,2],e[i,3],e[i,4]);
{     Writeln('e_len=',sum[1]);}
   end;
end; { solve }

procedure write_answer;
begin
   assign(f,f_out);
   rewrite(f);
   Writeln(f,area);
   close(f);
end; { write_answer }

begin
   read_data;
   solve;
   write_answer;
end.
