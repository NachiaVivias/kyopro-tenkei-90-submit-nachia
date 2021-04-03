
#include<direct.h>
#include<dirent.h>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<memory>

/////////////////////////////////////
// Reference
//   problem statememt,
//   constraints : https://github.com/E869120/kyopro_educational_90/blob/main/problem/001.jpg
//   sample : https://github.com/E869120/kyopro_educational_90/blob/main/sample/001.txt


namespace JudgeNS{

  enum Verdict{
    Verdict_AC,
    Verdict_WA
  };

  Verdict Judge(std::istream& case_in, std::istream& case_out, std::istream& user_out){
    using ll = long long;
    using ull =  unsigned long long;

    while(true){
      std::string ans0, ans1;
      case_out >> ans0;
      user_out >> ans1;
      if(case_out.eof() && user_out.eof()) break;
      if(case_out.eof() || user_out.eof()) return Verdict_WA;
      if(ans0 != ans1) return Verdict_WA;
    }
    
    return Verdict_AC;
  }

}


int main(int argc, char** argv){

  if(argc != 5){
    std::cerr << "judge <testcase input> <testcase output> <contestant output> <testcase name>" << std::endl << std::flush;
    exit(0);
  }

  FILE* fileTest = nullptr;
  fopen_s(&fileTest,argv[1],"r");
  if(fileTest==nullptr){
    std::cerr << "error : " << argv[1] << " (for [testcase input]) does not exist" << std::endl << std::flush;
    exit(1);
  }
  else{
    fclose(fileTest);
    fileTest = nullptr;
  }
  
  fopen_s(&fileTest,argv[2],"r");
  if(fileTest==nullptr){
    std::cerr << "error : " << argv[2] << " (for [testcase output]) does not exist" << std::endl << std::flush;
    exit(1);
  }
  else{
    fclose(fileTest);
    fileTest = nullptr;
  }

  fopen_s(&fileTest,argv[3],"r");
  if(fileTest==nullptr){
    std::cerr << "error : " << argv[3] << " (for [contestant output]) does not exist" << std::endl << std::flush;
    exit(1);
  }
  else{
    fclose(fileTest);
    fileTest = nullptr;
  }

  std::ifstream case_in(argv[1]);
  std::ifstream case_out(argv[2]);
  std::ifstream user_out(argv[3]);

  auto verdict = JudgeNS::Judge(case_in,case_out,user_out);

  std::cerr << argv[4] << " : ";

  if(verdict==JudgeNS::Verdict_AC){
    std::cerr << "AC" << std::endl << std::flush;
  }
  else if(verdict==JudgeNS::Verdict_WA){
    std::cerr << "WA" << std::endl << std::flush;
  }

  return 0;
}
