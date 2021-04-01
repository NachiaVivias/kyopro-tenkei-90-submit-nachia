#include "../Lib/generator_lib.hpp"

#include<direct.h>

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<memory>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)

/////////////////////////////////////
// Reference
//   problem statememt,
//   constraints : https://github.com/E869120/kyopro_educational_90/blob/main/problem/001.jpg
//   sample : https://github.com/E869120/kyopro_educational_90/blob/main/sample/001.txt

/////////////////////////////////////
// input
//
// N L
// K
// A[1] A[2] ... A[N]
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

  int N,L;
  int K;
  vector<int> A;

  // find if ans >= x
  bool solve_with_x(int x){
    int lastcut=0;
    int pA=0; // seeing
    rep(k,K+1){
      while(true){ // until get a piece ( >= x )
        if(pA==A.size()) return false; // run out
        if(A[pA]-lastcut >= x) break;
        pA++;
      }
      lastcut=A[pA];
    }
    return true;
  }

  void solve(
    const string& fName_in,
    const string& fName_out
  ) {
    make_base_dir(fName_out);

    ifstream ifs(fName_in);
    ofstream ofs(fName_out);

    ifs >> N >> L;
    ifs >> K;
    A.resize(N);
    rep(i,N) ifs >> A[i];
    A.push_back(L);

    // Meguru-style
    int ok=0, ng=L+1;
    while(abs(ok-ng) > 1){
      int mid = (ok+ng)/2;
      (solve_with_x(mid) ? ok : ng) = mid;
    }

    ofs << ok << "\n";
  }

}


class Input{
private:

  int N,L;
  int K;
  vector<int> A;

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
    N=0; L=0;
    K=0;
    A.clear();
    return this;
  }

  Input* rename(const string& caseName){
    mCaseName = caseName;
    return this;
  }

  Input(){ clear(); }

  Input* validate(){
    cerr << "validating ... "<<endl<<flush;
    assert(1 <= K && K < N && N <= 100000);
    assert(N == (int)A.size());

    assert(0 < A[0]);
    for(int i=0; i<N-1; i++) assert(A[i] < A[i+1]);
    assert(A.back() < L);
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
    ofs<< N <<" "<< L <<"\n";
    ofs<< K <<"\n";
    for(int i=0; i<N; i++){
      if(i!=0) ofs<<" ";
      ofs<< A[i];
    }
    ofs<<"\n";
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
    N=7; L=45;
    K=2;
    A={7,11,16,20,28,34,38};
    return this;
  }

  Input* generate_sample2(){
    N=3; L=100;
    K=1;
    A={28,54,81};
    return this;
  }

  Input* generate_sample3(){
    N=3; L=100;
    K=2;
    A={28,54,81};
    return this;
  }

  Input* generate_sample4(){
    N=20; L=1000;
    K=4;
    A={51,69,102,127,233,295,350,388,417,466,469,523,553,587,720,739,801,855,926,954};
    return this;
  }

  Input* generate_randomComb(
    int givenN,
    int givenL,
    int givenK,
    ull seed
  ){
    generatorNS::mt_seed(seed);
    N = givenN;
    L = givenL;
    K = givenK;
    vector<ll> comb = generatorNS::random_nPr(1,L,N);
    sort(comb.begin(),comb.end());
    A.resize(N);
    for(int i=0; i<N; i++) A[i]=comb[i];
    return this;
  }

  Input* generate_randombias(
    int givenN,
    int givenL,
    int givenK,
    double (*bias_func)(double x),
    ull seed
  ){
    generatorNS::mt_seed(seed);
    N = givenN;
    L = givenL;
    K = givenK;
    vector<double> comb(N);
    for(int i=0; i<N; i++) comb[i]=bias_func(generatorNS::random_real(0.0,1.0));
    for(int i=0; i<N; i++) assert(0.0<=comb[i] && comb[i]<=1.0);
    sort(comb.begin(),comb.end());
    A.resize(N);
    for(int i=0; i<N; i++) A[i] = min(L-N-2,(int)(comb[i]*(L-N-1)))+i+1;
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
  inputManeger -> rename("02_random_small1")
               -> generate_randomComb(100,1000000,41,0x094D4E40D0FED7CC)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("03_random_bias1")
               -> generate_randombias(65,1000000000,9,
                  [](double x)->double{ return pow(x,7); },
                  0xA70294E52DFA93B0)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("03_random_bias2")
               -> generate_randombias(100000,1000000000,794,
                  [](double x)->double{ return x>=0.001 ? x/1000.0 : min(1.0,x*1000.0); },
                  0x9BA4BB84977CDDB1)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("03_random_bias3")
               -> generate_randombias(100000,1000000000,819,
                  [](double x)->double{ return x>=0.001 ? (x+999.0)/1000.0 : min(1.0,x*1000.0); },
                  0xFA11AE9A1243D02F)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("03_random_bias4")
               -> generate_randombias(100000,1000000000,1022,
                  [](double x)->double{ return x>=0.001 ? (x+385.0)/1000.0 : min(1.0,x*1000.0); },
                  0x7D0BB7C20DC641BF)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("04_random1")
               -> generate_randomComb(98381,1000000000,5,0x37BA8F22B990EBD7)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("04_random2")
               -> generate_randomComb(98381,441003,5,0x81C25C89090349DF)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("04_random3")
               -> generate_randomComb(99999,424061994,2319,0x99E1A8DC2AF7A25D)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("04_random4")
               -> generate_randomComb(99214,913851643,38155,0xB173266D1F063991)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("05_random_max1")
               -> generate_randomComb(100000,1000000000,1,0xBBA992A70AE2B7EE)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("05_random_max2")
               -> generate_randomComb(100000,1000000000,50000,0x5FC1661BE8838FC1)
               -> validate() -> output_to_file() -> solve() -> clear();
  inputManeger -> rename("05_random_max3")
               -> generate_randomComb(100000,1000000000,99999,0x95DB4BD35BAED305)
               -> validate() -> output_to_file() -> solve() -> clear();
  cerr << "finished" << endl << flush;
  return 0;
}
