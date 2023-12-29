const test=15;
      n=6;
      k=3;
      kartya:array[1..13] of string[2]=(
      'A','2','3','4','5','6','7','8','9','10','J','Q','K');
var q,w,nn,kk,next:byte;
    was:array[1..13] of boolean;
begin
     randomize;
     assign(output,'carti.in');
     rewrite(output);
     writeln(test);
     for q:=1 to test do
     begin
          fillchar(was,sizeof(was),false);
          nn:=n;
          kk:=k;
          writeln(nn,' ',kk);
          for w:=1 to nn do
          begin
               repeat
                     next:=random(13)+1;
               until not was[next];
               was[next]:=true;
               write(kartya[next],' ');
          end;
          writeln;
     end;
     close(output);
end.