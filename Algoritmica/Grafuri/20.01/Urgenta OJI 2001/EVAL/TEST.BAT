@echo off
echo Testul %2
echo _________
copy teste\%2.in urgenta.in
copy teste\%2.ok urgenta.ok
timer %1 1
verif.exe
echo S-a obtinut urmatorul procent din punctajul de 10 puncte acordate pe acest test
type urgenta.rez
echo .
pause
del urgenta.in
del urgenta.out
del urgenta.ok
del urgenta.rez