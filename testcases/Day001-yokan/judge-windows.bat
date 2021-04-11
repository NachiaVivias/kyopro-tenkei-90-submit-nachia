
@echo off

g++ generator.cpp -o generator.exe -std=gnu++17 -O2 -static
mkdir in
mkdir out
del in /Q
del out /Q

for /f "usebackq" %%j in (`generator.exe --casecount`) do set CASECOUNT=%%j

for /l %%i in (1,1,%CASECOUNT%) do (
  echo %%i | generator.exe -input file gen-in.txt -output file gen-out.txt -log file gen-log.txt -casename file gen-name.txt
  for /f "usebackq" %%j in (`type gen-name.txt`) do set CASENAME=%%j
  call move gen-in.txt "in/"%%CASENAME%%
  call move gen-out.txt "out/"%%CASENAME%%
)

del generator.exe

del gen-log.txt
del gen-name.txt

g++ main.cpp -o contestant.exe -std=gnu++17 -O2 -static
g++ judge.cpp -o judge.exe -std=gnu++17 -O2 -static

copy nul result.txt 1> nul
for %%i in (in/*.txt) do (
  contestant.exe <in/%%i 1>out-contestant.txt
  judge.exe in/%%i out/%%i out-contestant.txt %%i 2>>result.txt
)
del out-contestant.txt

del contestant.exe
del judge.exe
del in /Q
del out /Q
rmdir in
rmdir out
