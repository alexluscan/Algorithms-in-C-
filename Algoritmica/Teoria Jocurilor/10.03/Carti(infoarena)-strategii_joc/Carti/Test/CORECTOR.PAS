var q:byte;
    s,qs:string;
    fin,fout:text;
begin
     for q:=0 to 9 do
     begin
          str(q,qs);
          assign(fin,'carti'+qs+'.in');
          assign(fout,'carti'+qs+'.in2');
          reset(fin);
          rewrite(fout);
          while not seekeof(fin) do
          begin
               readln(fin,s);
               while s[length(s)]=' ' do delete(s,length(s),1);
               writeln(fout,s);
          end;
          close(fout);
          close(fin);
     end;
end.