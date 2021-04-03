#include "../Lib/generator_lib.hpp"

#include<direct.h>

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<memory>
#include<queue>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Reference
//   problem statememt,
//   constraints : https://github.com/E869120/kyopro_educational_90/blob/main/problem/005.jpg
//   sample : https://github.com/E869120/kyopro_educational_90/blob/main/sample/005.txt

/////////////////////////////////////
// input
//
// N B K
// c[1] c[2] ... c[K]
//



void make_base_dir(string path){
  auto p = min(path.find("/"),path.find("\\"));
  while(p != string::npos){
    string nextDir = path.substr(0,p);
    _mkdir(nextDir.c_str());
    p = min(path.find("/",p+1),path.find("\\",p+1));
  }
}


class Solver{

  static const ull MOD = 1000000007;

  static const int matSize = 1000;

  ull N;
  int B, K;
  vector<int> C;
  
  struct MergeNode{
    vector<ull> G = vector<ull>(matSize);
    ull multi = 10;
  };

  vector<ull> convolution(const vector<ull>& l, const vector<ull>& r){
    vector<ull> res(matSize);
    for(int i=0; i<matSize; i++){
      for(int j=0; j<matSize; j++){
        int to=i+j; if(to>=matSize) to-=matSize;
        res[to] = (res[to] + l[i] * r[j]) % MOD;
      }
    }
    return move(res);
  }

  MergeNode multiplyMergeNodes(const MergeNode& l, const MergeNode& r){
    MergeNode res;
    for(int i=0; i<matSize; i++){
      for(int j=0; j<matSize; j++){
        int to = (i * r.multi + j) % B;
        res.G[to] = (res.G[to] + l.G[i] * r.G[j]) % MOD;
      }
    }
    res.multi = (l.multi * r.multi) % B;
    return move(res);
  }

  // i 乗
  MergeNode powMergeNode(const MergeNode& a,ull i){
    if(i==0){
      MergeNode res;
      res.G[0] = 1;
      res.multi = 1;
      return res;
    }
    MergeNode res = powMergeNode(a,i/2);
    res = multiplyMergeNodes(res,res);
    if(i%2==1) res = multiplyMergeNodes(res,a);
    return res;
  }

  MergeNode G;

public:

  void operator()(
    istream& ifs,
    ostream& ofs
  ){
    ifs >> N >> B >> K;
    C.resize(K);
    for(int i=0; i<K; i++) ifs >> C[i];

    for(int c : C) G.G[c%B] += 1;
    G.multi = 10 % B;

    G = powMergeNode(G,N);
    
    ofs << G.G[0] << "\n";
  }

  static void solve(
    const string& fName_in,
    const string& fName_out
  ) {
    make_base_dir(fName_out);

    ifstream ifs(fName_in);
    ofstream ofs(fName_out);

    Solver()(ifs,ofs);
  }

};


class Input{
private:

  ull N;
  int B, K;
  vector<int> C;

  string mCaseName = {};
  vector<int> mPreparingSubTasks;
  vector<int> mValidatedSubTasks;

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
    B=0; K=0;
    C.clear();
    return this;
  }

  Input* rename(const string& caseName){
    mCaseName = caseName;
    return this;
  }

  Input* prepareToSubTask(vector<int> subtaskIds){
    mPreparingSubTasks = subtaskIds;
    return this;
  }

  Input(){ clear(); }

  Input* validate(vector<int> subtaskIds){
    cerr << "validating ... "<<endl<<flush;
    assert(1 <= N && N <= 1'000'000'000'000'000'000);
    assert(2 <= B && B <= 1'000);
    assert(1 <= K && K <= 9);
    assert(K == (int)C.size());
    for(int i=0; i<K; i++) assert(1 <= C[i] && C[i] <= 9);
    for(int i=0; i<K-1; i++) assert(C[i] < C[i+1]);

    for(int subtaskId : subtaskIds){
      switch(subtaskId){
        case 1:
          assert(1 <= N && N <= 10'000);
          assert(2 <= B && B <= 30);
          break;
        case 2:
          assert(2 <= B && B <= 30);
          break;
        case 3:
          break;
        default :
          cerr << "invalid subtaskId" << endl << flush;
          assert(false);
      }
    }

    mValidatedSubTasks = subtaskIds;
    
    return this;
  }

  Input* output_to_file(){
    if(mCaseName==""){
      cerr << "skipped output_to_file by empty caseName" << endl << flush;
      return this;
    }

    bool matchSubtask = false;
    for(int preparingSubTask : mPreparingSubTasks){
      for(int validatedSubTask : mValidatedSubTasks){
        if(preparingSubTask == validatedSubTask) matchSubtask = true;
      }
    }
    if(!matchSubtask){
      cerr << "skipped output_to_file because it\'s not match for required subtasks" << endl << flush;
      return this;
    }

    string fileName = get_input_file_name();
    make_base_dir(fileName);
    cerr << "output INPUT to file " << fileName << endl << flush;
    ofstream ofs(fileName);

    ofs<< N <<" "<< B <<" "<< K <<"\n";
    for(int i=0; i<K; i++){
      if(i!=0) ofs<<" ";
      ofs << C[i];
    }
    ofs<<"\n";
    return this;
  }

  Input* solve(){
    bool matchSubtask = false;
    for(int preparingSubTask : mPreparingSubTasks){
      for(int validatedSubTask : mValidatedSubTasks){
        if(preparingSubTask == validatedSubTask) matchSubtask = true;
      }
    }
    if(!matchSubtask){
      cerr << "skipped solve because it\'s not match for required subtasks" << endl << flush;
      return this;
    }

    cerr << "solving ... " << endl << flush;
    Solver::solve(
      get_input_file_name(),
      get_output_file_name()
    );
    return this;
  }

  Input* generate_sample1(){
    N=3; B=7; K=3;
    C={1,4,9};
    return this;
  }

  Input* generate_sample2(){
    N=5; B=2; K=3;
    C={1,4,9};
    return this;
  }

  Input* generate_sample3(){
    N=10000; B=27; K=7;
    C={1,3,4,6,7,8,9};
    return this;
  }

  Input* generate_sample4(){
    N=1'000'000'000'000'000'000; B=29; K=6;
    C={1,2,4,5,7,9};
    return this;
  }

  Input* generate_sample5(){
    N=1'000'000'000'000'000'000; B=957; K=7;
    C={1,2,3,5,6,7,9};
    return this;
  }

  Input* generate_hand1(){
    N=1; B=3; K=1;
    C={9};
    return this;
  }

  Input* generate_hand2(){
    N=1; B=3; K=1;
    C={8};
    return this;
  }

  Input* generate_hand3(){
    N=1; B=2; K=1;
    C={8};
    return this;
  }

  Input* generate_hand4(){
    N=5328; B=10; K=7;
    C={1,2,5,6,7,8,9};
    return this;
  }

  Input* generate_hand5(){
    N=9318; B=2; K=5;
    C={1,3,5,7,9};
    return this;
  }

  Input* generate_hand6(){
    N=8189; B=3; K=2;
    C={1,7};
    return this;
  }

  Input* generate_hand7(){
    N=8280; B=9; K=2;
    C={1,7};
    return this;
  }

  Input* generate_hand8(){
    N=1; B=4; K=5;
    C={1,4,5,6,8};
    return this;
  }

  Input* generate_random(
    ull minN, ull maxN,
    int minB, int maxB,
    int minK, int maxK,
    ull seed
  ){
    generatorNS::mt_seed(seed);
    N = generatorNS::random_unsigned(minN,maxN);
    B = generatorNS::random_signed(minB,maxB);
    K = generatorNS::random_signed(minK,maxK);
    vector<ll> Cbuf = generatorNS::random_nPr(1,9,K);
    sort(Cbuf.begin(),Cbuf.end());
    C.resize(K);
    for(int i=0; i<K; i++) C[i] = Cbuf[i];
    return this;
  }
};



int main() {
  cout << "please enter the list of subtasks" << endl;
  cout << "    separated by whitespace or new line" << endl;
  cout << "    ends with 0" << endl;
  cout << flush;

  vector<int> subtaskList;
  while(true){
    string S; cin >> S;
    int valS;
    try{ valS = stoi(S); }
    catch(const invalid_argument& e){
      cerr << e.what() << endl;
      cout << "it\'s not a number -> to be skipped" << endl << flush;
    }
    catch(const out_of_range& e){
      cerr << e.what() << endl;
      cout << "the value is out of range -> to be skipped" << endl << flush;
    }

    if(valS == 0) break;
    subtaskList.push_back(valS);
  }

  auto inputManeger = make_unique<Input>();
  inputManeger->prepareToSubTask(subtaskList);

  inputManeger -> rename("01_sample_01")
               -> generate_sample1()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("01_sample_02")
               -> generate_sample2()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("01_sample_03")
               -> generate_sample3()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("01_sample_04")
               -> generate_sample4()
               -> validate({2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("01_sample_05")
               -> generate_sample5()
               -> validate({3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_hand_01")
               -> generate_hand1()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_hand_02")
               -> generate_hand2()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_hand_03")
               -> generate_hand3()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_hand_04")
               -> generate_hand4()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_hand_05")
               -> generate_hand5()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_hand_06")
               -> generate_hand6()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_hand_07")
               -> generate_hand7()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("02_hand_08")
               -> generate_hand8()
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();

  inputManeger -> rename("03_random_subtask1_01")
               -> generate_random(1,10000, 2,29, 1,9, 0x54619C21131FC353)
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("03_random_subtask1_02")
               -> generate_random(1,10000, 2,29, 1,9, 0xE973DB236D77293D)
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("03_random_subtask1_03")
               -> generate_random(1,10000, 2,29, 1,9, 0x438F9E564609F708)
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("03_random_subtask1_04")
               -> generate_random(9000,9999, 25,29, 1,1, 0x120634EDA6B06E8E)
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("03_random_subtask1_05")
               -> generate_random(9000,9999, 25,29, 6,8, 0x046A617728A89126)
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("03_random_subtask1_06")
               -> generate_random(10000,10000, 29,29, 9,9, 0xC1D64A625177C04E)
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("03_random_subtask1_07")
               -> generate_random(10000,10000, 29,29, 8,8, 0x7102AB2C2720E9FB)
               -> validate({1,2,3}) -> output_to_file() -> solve() -> clear();
               
  inputManeger -> rename("04_random_subtask1_01")
               -> generate_random(1,1'000'000'000'000'000'000, 2,29, 1,9, 0x40C7ADD7F81650FA)
               -> validate({2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("04_random_subtask1_02")
               -> generate_random(1,1'000'000'000'000'000'000, 2,29, 1,9, 0xB5289F03B1B8ED4B)
               -> validate({2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("04_random_subtask1_03")
               -> generate_random(1,1'000'000'000'000'000'000, 2,29, 1,9, 0x2007F7803C3D3E63)
               -> validate({2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("04_random_subtask1_04")
               -> generate_random(900'000'000'000'000'000,999'999'999'999'999'999, 25,29, 1,1, 0x92E22700A4735869)
               -> validate({2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("04_random_subtask1_05")
               -> generate_random(900'000'000'000'000'000,999'999'999'999'999'999, 25,29, 6,8, 0x4FF2C320FFCDD451)
               -> validate({2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("04_random_subtask1_06")
               -> generate_random(1'000'000'000'000'000'000,1'000'000'000'000'000'000, 29,29, 9,9, 0x17C9BEF32620063A)
               -> validate({2,3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("04_random_subtask1_07")
               -> generate_random(1'000'000'000'000'000'000,1'000'000'000'000'000'000, 29,29, 8,8, 0x83CD28B4CD81B61C)
               -> validate({2,3}) -> output_to_file() -> solve() -> clear();
               
  inputManeger -> rename("05_random_regular_01")
               -> generate_random(1,1'000'000'000'000'000'000, 2,999, 1,9, 0xC02E33A021C79771)
               -> validate({3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("05_random_regular_02")
               -> generate_random(1,1'000'000'000'000'000'000, 2,999, 1,9, 0x00D8CA08C26EADB1)
               -> validate({3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("05_random_regular_03")
               -> generate_random(1,1'000'000'000'000'000'000, 2,999, 1,9, 0x3B257B93E56158AC)
               -> validate({3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("05_random_regular_04")
               -> generate_random(900'000'000'000'000'000,999'999'999'999'999'999, 900,999, 1,1, 0x512D86D5AE24EC56)
               -> validate({3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("05_random_regular_05")
               -> generate_random(900'000'000'000'000'000,999'999'999'999'999'999, 900,999, 6,8, 0x6C7C9DB3489747F9)
               -> validate({3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("05_random_regular_06")
               -> generate_random(1'000'000'000'000'000'000,1'000'000'000'000'000'000, 999,999, 9,9, 0x6CEE65FEA70F6157)
               -> validate({3}) -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("05_random_regular_07")
               -> generate_random(1'000'000'000'000'000'000,1'000'000'000'000'000'000, 999,999, 8,8, 0x52A0F8E57104EE4C)
               -> validate({3}) -> output_to_file() -> solve() -> clear();
  cerr << "finished" << endl << flush;
  return 0;
}
