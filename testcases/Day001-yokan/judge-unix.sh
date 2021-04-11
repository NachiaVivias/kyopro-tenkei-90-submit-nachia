
g++ generator.cpp -o generator.exe -std=gnu++17 -O2 -static
mkdir in
mkdir out
rm in/*
rm out/*

CASECOUNT=$(./generator.exe --casecount)

for((i=1; i<=$CASECOUNT; i++)) do
  echo $i | ./generator.exe -input file gen-in.txt -output file gen-out.txt -log file gen-log.txt -casename file gen-name.txt
  CASENAME=$(cat gen-name.txt)
  mv gen-in.txt "in/"$CASENAME
  mv gen-out.txt "out/"$CASENAME
done

rm generator.exe

rm gen-log.txt
rm gen-name.txt

g++ main.cpp -o contestant.exe -std=gnu++17 -O2 -static
g++ judge.cpp -o judge.exe -std=gnu++17 -O2 -static

echo -n 1> result.txt
cd in
CASELIST=$(find ./ -maxdepth 1 -name "*.txt" | sort)
cd ../
for i in $CASELIST
do
  eval './contestant.exe <in/'${i}' 1>out-contestant.txt'
  eval './judge.exe in/'${i}' out/'${i}' out-contestant.txt $i 2>>result.txt'
done
rm out-contestant.txt

rm contestant.exe
rm judge.exe
rm -r in
rm -r out
