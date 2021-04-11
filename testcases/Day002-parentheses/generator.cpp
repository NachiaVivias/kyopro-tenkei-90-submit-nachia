#include "../Lib/generator_lib.hpp"

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<memory>
#include<sstream>
#include<stack>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)

/////////////////////////////////////
// Reference
//   problem statememt,
//   constraints : https://github.com/E869120/kyopro_educational_90/blob/main/problem/002.jpg
//   sample : https://github.com/E869120/kyopro_educational_90/blob/main/sample/002.txt

/////////////////////////////////////
// input
//
// N
//


namespace generatorNS{

  class OutputOptionHandle{
  public:
    virtual ~OutputOptionHandle() = default;
    virtual ostream& getStream() = 0;
  };

  class OutputOptionHandle_stdout
    : public OutputOptionHandle
  {
  public:
    OutputOptionHandle_stdout() = default;
    virtual ostream& getStream(){ return cout; }
  };

  class OutputOptionHandle_stderr
    : public OutputOptionHandle
  {
  public:
    OutputOptionHandle_stderr() = default;
    virtual ostream& getStream(){ return cerr; }
  };

  class OutputOptionHandle_void
    : public OutputOptionHandle
  {
  private:
    ofstream ofs;
  public:
    OutputOptionHandle_void() = default;
    virtual ostream& getStream(){ return ofs; }
  };

  class OutputOptionHandle_file
    : public OutputOptionHandle
  {
  private:
    ofstream ofs;
  public:
    OutputOptionHandle_file(const string& fName) : ofs(fName) {}
    virtual ostream& getStream(){ return ofs; }
  };

}

namespace Solver{

  struct SearchNode{
    int searchBit;
    int depth;
    char nextChar;
  };

  int N;

  void solve(
    istream& ifs,
    ostream& ofs
  ) {

    ifs >> N;

    stack<SearchNode> Q;
    string buf(N,'(');
    Q.push({N-1,0,'('});
    Q.push({N-1,0,')'});
    while(Q.size()){
      auto p = Q.top(); Q.pop();
      if(p.depth < 0) continue;
      buf[N-1-p.searchBit] = p.nextChar;
      int nextDepth = p.depth;
      if(p.nextChar=='(') nextDepth++;
      if(p.nextChar==')') nextDepth--;
      if(nextDepth > p.searchBit) continue;
      if(p.searchBit==0){
        if(nextDepth==0){
          ofs << buf << "\n";
        }
      }
      else{
        Q.push({p.searchBit-1,nextDepth,')'});
        Q.push({p.searchBit-1,nextDepth,'('});
      }
    }
  }

}


class Input{
private:

  int N,L;
  int K;
  vector<int> A;

  string mCaseName = {};

  string mInputBuffer;

  unique_ptr<generatorNS::OutputOptionHandle> ofsh_input;
  unique_ptr<generatorNS::OutputOptionHandle> ofsh_output;
  unique_ptr<generatorNS::OutputOptionHandle> ofsh_casename;
  unique_ptr<generatorNS::OutputOptionHandle> ofsh_log;

  static vector<void (*)(Input*)> mGenerateById;

public:

  ostream& get_ostream_input(){
    return ofsh_input->getStream();
  }
  ostream& get_ostream_output(){
    return ofsh_output->getStream();
  }
  ostream& get_ostream_casename(){
    return ofsh_casename->getStream();
  }
  ostream& get_ostream_log(){
    return ofsh_log->getStream();
  }
  Input* set_ostream_input(unique_ptr<generatorNS::OutputOptionHandle> ofsh){
    ofsh_input = move(ofsh);
    return this;
  }
  Input* set_ostream_output(unique_ptr<generatorNS::OutputOptionHandle> ofsh){
    ofsh_output = move(ofsh);
    return this;
  }
  Input* set_ostream_casename(unique_ptr<generatorNS::OutputOptionHandle> ofsh){
    ofsh_casename = move(ofsh);
    return this;
  }
  Input* set_ostream_log(unique_ptr<generatorNS::OutputOptionHandle> ofsh){
    ofsh_log = move(ofsh);
    return this;
  }

  Input* clear(){
    N=0; L=0;
    K=0;
    A.clear();
    return this;
  }

  Input* rename(const string& caseName){
    mCaseName = caseName;
    return this;
  }

  Input(){
    ofsh_input = make_unique<generatorNS::OutputOptionHandle_stdout>();
    ofsh_output = make_unique<generatorNS::OutputOptionHandle_void>();
    ofsh_casename = make_unique<generatorNS::OutputOptionHandle_stderr>();
    ofsh_log = make_unique<generatorNS::OutputOptionHandle_void>();
    clear();
  }

  Input* validate(){
    assert(1 <= N && N <= 20);
    
    return this;
  }

  Input* output_to_file(){
    ostream& ostr_file = get_ostream_input();
    {
      auto ostr = ostringstream();
      get_ostream_casename() << mCaseName;

      // begin main
      ostr<< N <<"\n";
      // end main

      mInputBuffer = move(ostr).str(); // copy... (move since C++20)
    } // ostr dies
    ostr_file << mInputBuffer;
    return this;
  }

  Input* solve(){
    get_ostream_log() << mCaseName << " : started solving" << endl << flush;
    auto istr = istringstream(mInputBuffer);
    Solver::solve(
      istr,
      get_ostream_output()
    );
    get_ostream_log() << mCaseName << " : finished solving" << endl << flush;
    return this;
  }

  Input* generate_sample1(){
    N=2;
    return this;
  }

  Input* generate_sample2(){
    N=3;
    return this;
  }

  Input* generate_sample3(){
    N=4;
    return this;
  }

  Input* generate_sample4(){
    N=10;
    return this;
  }

  Input* generate_fixed(
    int givenN
  ){
    N=givenN;
    return this;
  }

  int getCaseCount(){
    return (int)mGenerateById.size();
  }

  Input* generate_by_id(int id){
    assert(0 <= id);
    assert(id < getCaseCount());
    mGenerateById[id](this);
    return this;
  }

};


vector<void (*)(Input*)> Input::mGenerateById = {
  [](Input* inputManager)->void{
    inputManager -> rename("01_sample01.txt")
                 -> generate_sample1();
  },
  [](Input* inputManager)->void{
    inputManager -> rename("01_sample02.txt")
                 -> generate_sample2();
  },
  [](Input* inputManager)->void{
    inputManager -> rename("01_sample03.txt")
                 -> generate_sample3();
  },
  [](Input* inputManager)->void{
    inputManager -> rename("01_sample04.txt")
                 -> generate_sample4();
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all01.txt")
                 -> generate_fixed(1);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all02.txt")
                 -> generate_fixed(5);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all03.txt")
                 -> generate_fixed(6);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all04.txt")
                 -> generate_fixed(7);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all05.txt")
                 -> generate_fixed(8);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all06.txt")
                 -> generate_fixed(9);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all07.txt")
                 -> generate_fixed(11);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all08.txt")
                 -> generate_fixed(12);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all09.txt")
                 -> generate_fixed(13);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all10.txt")
                 -> generate_fixed(14);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all11.txt")
                 -> generate_fixed(15);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all12.txt")
                 -> generate_fixed(16);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all13.txt")
                 -> generate_fixed(17);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all14.txt")
                 -> generate_fixed(18);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all15.txt")
                 -> generate_fixed(19);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_all16.txt")
                 -> generate_fixed(20);
  }
};


/////////////////////////////////////////////////////////////
// # generator
//
// ## options
//
// - `--casecount`
//    Outputs the number of testcases to stdout instead of generating any testcase.
// - `-input <stdout|stderr|file|void> <filename>`
//    Destination of the testcase's input file.
// - `-output <stdout|stderr|file|void> <filename>`
//    Destination of the testcase's output file.
// - `-casename <stdout|stderr|file|void> <filename>`
//    Destination of the testcase's name.
// - `-input <stdout|stderr|file|void> <filename>`
//    Destination of the log.
//
// ## stdin
//    Input an integer `idx` representing the id (1-indexed) of the testcase.
//    This is not necessary when calling with `--casecount` option.
//
// ## error
//    Errors will be output to stderr.
int main(int narg, char** varg) {
  auto inputManeger = make_unique<Input>();

  bool mode_casecount = false;

  vector<string> args;
  for(int i=1; i<narg; i++) args.push_back(varg[i]);
  string ofName_input = "";
  string ofName_output = "";
  string ofName_casename = "";
  string ofName_log = "";
  int argp = 0;

  // lambda
  // prepares output destination following the option
  auto read_argument_for_output_dest = [&argp,&args](const string& optionName)->unique_ptr<generatorNS::OutputOptionHandle>{
    if(args.size() == argp){
      cerr << "generator : missing value : " << optionName << " <fileName>" << endl << flush;
      exit(1);
    }
    string arg1 = args[argp++];
    if(arg1 == "stdout"){
      return make_unique<generatorNS::OutputOptionHandle_stdout>();
    }
    else if(arg1 == "stderr"){
      return make_unique<generatorNS::OutputOptionHandle_stderr>();
    }
    else if(arg1 == "file"){
      if(args.size() == argp){
        cerr << "generator : missing value : " << optionName << " file <fileName>" << endl << flush;
        exit(1);
      }
      string arg2 = args[argp++];
      return make_unique<generatorNS::OutputOptionHandle_file>(arg2);
    }
    else if(arg1 == "void"){
      return make_unique<generatorNS::OutputOptionHandle_void>();
    }
    else{
      cerr << "generator : invalid value : " << optionName << " <stdout|stderr|file|void>" << endl << flush;
      exit(1);
    }
  };

  while(argp < args.size()){
    string arg0 = args[argp++];
    if(arg0=="") continue;
    if(arg0[0]!='-'){
      cerr << "generator : invalid argument \"" << arg0 << "\"" << endl << flush;
      exit(1);
    }
    else if(arg0=="-input"){
      inputManeger->set_ostream_input(read_argument_for_output_dest("-input"));
    }
    else if(arg0=="-output"){
      inputManeger->set_ostream_output(read_argument_for_output_dest("-output"));
    }
    else if(arg0=="-casename"){
      inputManeger->set_ostream_casename(read_argument_for_output_dest("-casename"));
    }
    else if(arg0=="-log"){
      inputManeger->set_ostream_log(read_argument_for_output_dest("-log"));
    }
    else if(arg0=="--casecount"){
      mode_casecount = true;
    }
    else{
      cerr << "generator : undefined option \"" << arg0 << "\"" << endl << flush;
      exit(1);
    }
  }


  if(mode_casecount){
    cout << inputManeger->getCaseCount() << flush;
  }
  else{
    int id; cin >> id;
    inputManeger -> generate_by_id(id-1);
    inputManeger -> validate() -> output_to_file() -> solve() -> clear();
  }
  return 0;
}
