#include "../Lib/generator_lib.hpp"

#include<direct.h>

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<memory>
#include<stack>
using namespace std;
using ll = long long;
using ull = unsigned long long;

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



void make_base_dir(string path){
  auto p = min(path.find("/"),path.find("\\"));
  while(p != string::npos){
    string nextDir = path.substr(0,p);
    _mkdir(nextDir.c_str());
    p = min(path.find("/",p+1),path.find("\\",p+1));
  }
}


namespace Solver{

  struct SearchNode{
    int searchBit;
    int depth;
    char nextChar;
  };

  int N;

  void solve(
    const string& fName_in,
    const string& fName_out
  ) {
    make_base_dir(fName_out);

    ifstream ifs(fName_in);
    ofstream ofs(fName_out);

    ifs >> N;

    // bit 全探索 -> 深さ優先探索
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
        // 後に入れたほうが先に探索される
        Q.push({p.searchBit-1,nextDepth,')'});
        Q.push({p.searchBit-1,nextDepth,'('});
      }
    }
  }

}


class Input{
private:

  int N;

  string mCaseName = {};

public:

  string get_input_file_name(){
    if(mCaseName=="") return "";
    return "in/"+mCaseName+".txt";
  }
  string get_output_file_name(){
    if(mCaseName=="") return "";
    return "out/"+mCaseName+".txt";
  }

  Input* clear(){
    N=0;
    return this;
  }

  Input* rename(const string& caseName){
    mCaseName = caseName;
    return this;
  }

  Input(){ clear(); }

  Input* validate(){
    cerr << "validating ... "<<endl<<flush;
    assert(1 <= N && N <= 20);
    
    return this;
  }

  Input* output_to_file(){
    if(mCaseName==""){
      cerr << "skipped output_to_file by empty caseName" << endl << flush;
    }
    string fileName = get_input_file_name();
    make_base_dir(fileName);
    cerr << "output INPUT to file " << fileName << endl << flush;
    ofstream ofs(fileName);

    ofs<< N <<"\n";
    return this;
  }

  Input* solve(){
    cerr << "solving ... " << endl << flush;
    Solver::solve(
      get_input_file_name(),
      get_output_file_name()
    );
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

};



int main() {
  auto inputManeger = make_unique<Input>();
  inputManeger -> rename("01_sample1")
               -> generate_sample1()
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("01_sample2")
               -> generate_sample2()
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("01_sample3")
               -> generate_sample3()
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("01_sample4")
               -> generate_sample4()
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all1")
               -> generate_fixed(1)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all2")
               -> generate_fixed(5)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all3")
               -> generate_fixed(6)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all4")
               -> generate_fixed(7)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all5")
               -> generate_fixed(8)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all6")
               -> generate_fixed(9)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all7")
               -> generate_fixed(11)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all8")
               -> generate_fixed(12)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all9")
               -> generate_fixed(13)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all10")
               -> generate_fixed(14)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all11")
               -> generate_fixed(15)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all12")
               -> generate_fixed(16)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all13")
               -> generate_fixed(17)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all14")
               -> generate_fixed(18)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all15")
               -> generate_fixed(19)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_all16")
               -> generate_fixed(20)
               -> validate() -> output_to_file() -> solve() -> clear();
  cerr << "finished" << endl << flush;
  return 0;
}
