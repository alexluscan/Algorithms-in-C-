{$A+,B-,D+,E+,F+,G+,I+,L+,N+,O+,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
const in_file='carti.in';
      out_file='carti.out';
      maxN=13;
      kartya:array[1..13] of string[2]=(
      'A','2','3','4','5','6','7','8','9','10','J','Q','K');
type str2=string[2];
var win:array[0..(1 shl maxN)-1] of byte;{0-lose,1-win,2-not known}
    fin,fout:text;
    n,k,test,q:byte;
    s,aux:string;
    state:word;
    auxx,qq,ww,ll:word;
    nnn:byte;
    losing:array[0..13] of word;
function value(card:str2):byte;
var code:integer;
    ans:byte;
begin
     val(card,ans,code);
     if code=0
     then value:=ans
     else
         case card[1] of
              'A':value:=1;
              'J':value:=11;
              'Q':value:=12;
              'K':value:=13;
         end;
end;
function DoesWin(state:word):boolean;
var i,j:byte;
    mask:word;
begin
     if win[state]<>2
     then DoesWin:=win[state]=1
     else
     begin
          win[state]:=0;
          for i:=1 to k do
          begin
               mask:=0;
               for j:=0 to i-1 do mask:=mask or (1 shl j);
               for j:=0 to 13-i do
                   if (state and (mask shl j))=(mask shl j)
                   then
                       if not DoesWin(state-(mask shl j))
                       then
                       begin
                            win[state]:=1;
                            break;
                       end;
               if win[state]=1
               then break;
          end;
          DoesWin:=win[state]=1;
     end;
end;
begin
     assign(fout,'carti.in');
     rewrite(fout);
     writeln;
     for k:=1 to 10 do
     begin
          fillchar(win,sizeof(win),2);
          win[0]:=0;
          ww:=0;
          ll:=0;
          fillchar(losing,sizeof(losing),false);
          for qq:=0 to 8191 do
          begin
               if DoesWin(qq)
               then inc(ww)
               else
               begin
                    inc(ll);
                    nnn:=0;
                    auxx:=qq;
                    while (auxx>0) do
                    begin
                         auxx:=auxx and (auxx-1);
                         inc(nnn);
                    end;
                    inc(losing[nnn]);
                    if (nnn>=12) and (k>2)
                    then
                    begin
                         writeln(fout,nnn,' ',k);
                         for auxx:=0 to 12 do
                             if (qq and (1 shl auxx))<>0
                             then write(fout,kartya[auxx+1],' ');
                         writeln(fout);
                    end;
               end;
               if (odd(k)) and (qq=8012)
               then
               begin
                    writeln(fout,nnn,' ',k);
                    for auxx:=0 to 12 do
                        if (qq and (1 shl auxx))<>0
                        then write(fout,kartya[auxx+1],' ');
                    writeln(fout);
               end;
          end;
          writeln(k,' ',ww,' ',ll);
          write('Losing: ');
          for qq:=1 to 13 do
              if losing[qq]>0
              then write(qq,':',losing[qq],' ');
          writeln;
     end;
     close(fout);
end.
