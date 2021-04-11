#include "../Lib/generator_lib.hpp"

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<memory>
#include<sstream>
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
    istream& ifs,
    ostream& ofs
  ) {
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
    assert(1 <= K && K < N && N <= 100000);
    assert(N == (int)A.size());

    assert(0 < A[0]);
    for(int i=0; i<N-1; i++) assert(A[i] < A[i+1]);
    assert(A.back() < L);
    return this;
  }

  Input* output_to_file(){
    ostream& ostr_file = get_ostream_input();
    {
      auto ostr = ostringstream();
      get_ostream_casename() << mCaseName;
      ostr<< N <<" "<< L <<"\n";
      ostr<< K <<"\n";
      for(int i=0; i<N; i++){
        if(i!=0) ostr<<" ";
        ostr<< A[i];
      }
      ostr<<"\n";
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

  Input* generate_fixed1(){
    N=3; L=1000000000;
    K=1;
    A={499999999,500000000,500000001};
    return this;
  }

  Input* generate_fixed2(){
    N=100000; L=1000000000;
    K=50000;
    A.resize(N);
    for(int i=0; i<N; i++) A[i]=i+1;
    return this;
  }

  Input* generate_fixed3(){
    N=100000; L=1000000000;
    K=20000;
    A.resize(N);
    for(int i=0; i<N; i++) A[i]=L-(N-i);
    return this;
  }

  Input* generate_K_sensitive(
    int givenK,
    bool reverseA,
    ull seed
  ){
    generatorNS::mt_seed(seed);
    N=29; L=1000000000;
    K=givenK;
    int p = generatorNS::random_signed(500'000'000,650'000'000);
    for(int i=0; i<N; i++){
      A.push_back(p);
      p = (p+1)/2;
    }
    if(reverseA){
      for(int i=0; i<N; i++) A[i] = (L-A[i]);
    }
    sort(A.begin(),A.end());
    return this;
  }

  Input* generate_randomComb(
    int minN, int maxN,
    int minL, int maxL,
    int minK, int maxK,
    ull seed
  ){
    assert(maxK < minN);
    generatorNS::mt_seed(seed);
    N = generatorNS::random_signed(minN,maxN);
    L = generatorNS::random_signed(minL,maxL);
    K = generatorNS::random_signed(minK,maxK);
    vector<ll> comb = generatorNS::random_nPr(1,L,N);
    sort(comb.begin(),comb.end());
    A.resize(N);
    for(int i=0; i<N; i++) A[i]=comb[i];
    return this;
  }

  // bias_func(distSize) returns x : 0 <= x < distSize
  Input* generate_randombias(
    int givenN,
    int givenL,
    int givenK,
    int (*bias_func)(int distSize),
    ull seed
  ){
    generatorNS::mt_seed(seed);
    N = givenN;
    L = givenL;
    K = givenK;
    vector<int> comb(N);
    int distributionSize = L-N-1;
    for(int i=0; i<N; i++){
      comb[i]=bias_func(distributionSize);
    }
    for(int i=0; i<N; i++) assert(0<=comb[i] && comb[i]<distributionSize);
    sort(comb.begin(),comb.end());
    A.resize(N);
    for(int i=0; i<N; i++) A[i] = comb[i] + i+1;
    return this;
  }

  Input* generate_equally(
    int givenN,
    int givenL,
    int givenK
  ){
    N = givenN;
    L = givenL;
    K = givenK;
    A.resize(N);
    for(int i=0; i<N; i++) A[i]=(ll)L*(i+1)/(N+1);
    return this;
  }

  Input* generate_max(
    int givenN,
    int givenL,
    int givenK
  ){
    N = givenN;
    L = givenL;
    K = givenK;
    A.resize(N);
    for(int i=0; i<N; i++) A[i]=L-(N-i);
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
    inputManager -> rename("02_fixed01.txt")
                 -> generate_fixed1();
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_fixed02.txt")
                 -> generate_fixed2();
  },
  [](Input* inputManager)->void{
    inputManager -> rename("02_fixed03.txt")
                 -> generate_fixed3();
  },
  [](Input* inputManager)->void{
    inputManager -> rename("03_k_sensitive01.txt")
                 -> generate_K_sensitive(2,false,0xE2A6936FB37E5384);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("03_k_sensitive02.txt")
                 -> generate_K_sensitive(24,false,0xABEC18BD450BD832);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("03_k_sensitive03.txt")
                 -> generate_K_sensitive(3,true,0x6F6C29C6DDEADBD4);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("03_k_sensitive04.txt")
                 -> generate_K_sensitive(26,true,0xC50132DEF5D88057);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("04_random_small01.txt")
                 -> generate_randomComb(50,150,100'000,1'000'000,10,49,0x094D4E40D0FED7CC);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("04_random_small02.txt")
                 -> generate_randomComb(50,150,100'000,1'000'000,10,49,0xAE4099E189429F8A);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("04_random_small03.txt")
                 -> generate_randomComb(50,150,100'000,1'000'000,10,49,0x094D4E40D0FED7CC);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("05_random_bias01.txt")
                 -> generate_randombias(100000,1'000'000'000,794,
                    [](int distSize)->int{
                      if(generatorNS::random_signed(1,1000)==1) return generatorNS::random_signed(0,distSize-1);
                      return generatorNS::random_signed((ll)0,(ll)distSize/1000-1);
                    },
                    0x9BA4BB84977CDDB1);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("05_random_bias02.txt")
                 -> generate_randombias(100000,1'000'000'000,819,
                    [](int distSize)->int{
                      if(generatorNS::random_signed(1,1000)==1) return generatorNS::random_signed(0,distSize-1);
                      return generatorNS::random_signed((ll)distSize*999/1000,(ll)distSize-1);
                    },
                    0xFA11AE9A1243D02F);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("05_random_bias03.txt")
                 -> generate_randombias(100000,1'000'000'000,1022,
                    [](int distSize)->int{
                      if(generatorNS::random_signed(1,1000)==1) return generatorNS::random_signed(0,distSize-1);
                      return generatorNS::random_signed((ll)distSize*385/1000,(ll)distSize*386/1000-1);
                    },
                    0x7D0BB7C20DC641BF);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("06_random01.txt")
                 -> generate_randomComb(90001,99999,1'000'000'000,1'000'000'000,5,5,0x37BA8F22B990EBD7);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("06_random02.txt")
                 -> generate_randomComb(90001,99999,1'000'000,10'000'000,5,5,0x81C25C89090349DF);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("06_random03.txt")
                 -> generate_randomComb(90001,99999,400'000'000,999'999'999,1000,3000,0x99E1A8DC2AF7A25D);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("06_random04.txt")
                 -> generate_randomComb(90001,99999,400'000'000,999'999'999,30000,40000,0xB173266D1F063991);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("07_random_max01.txt")
                -> generate_randomComb(100000,100000,1'000'000'000,1'000'000'000,1,1,0xBBA992A70AE2B7EE);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("07_random_max02.txt")
                 -> generate_randomComb(100000,100000,1'000'000'000,1'000'000'000,50000,50000,0x5FC1661BE8838FC1);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("07_random_max03.txt")
                 -> generate_randomComb(100000,100000,1'000'000'000,1'000'000'000,99999,99999,0x95DB4BD35BAED305);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("08_equally01.txt")
                 -> generate_equally(99999,1'000'000'000,26);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("08_equally02.txt")
                 -> generate_equally(100000,100001,48130);
  },
  [](Input* inputManager)->void{
    inputManager -> rename("09_max01.txt")
                 -> generate_max(100000,1'000'000'000,99999);
  }
};


/////////////////////////////////////////////////////////////
// # generator
//
// ## options
//
// - `--casecount`
//    Outputs the number of testcase to stdout instead of generating any testcase.
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
