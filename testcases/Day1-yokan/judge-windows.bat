g++ main.cpp -o contestant.exe -m64 -O2 -static
g++ judge.cpp -o judge.exe -m64 -O2 -static
g++ generator.cpp -o generator.exe -m64 -O2 -static
del in /Q
del out /Q
generator.exe
copy nul result.txt 1> nul
for %%i in (in/*.txt) do (
  contestant.exe <in/%%i 1>out-contestant.txt
  judge.exe in/%%i out/%%i out-contestant.txt %%i 2>>result.txt
)
del out-contestant.txt
