#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)

/////////////////////////////////////
// Problem : https://atcoder.jp/contests/typical90/tasks/typical90_bn
// Divide and Conquer
// Time Complexity : O( N log N )

/////////////////////////////////////
// input
//
// N
// L[1] R[1]
// L[2] R[2]
//  :
// L[N] R[N]
//

using Val = double;

struct Event{ int t; Val slope; };

vector<Event> mergeEvents(const vector<Event>& A, const vector<Event>& B, Val& ans){
  int iA=0, iB=0;
  Val slopeA = Val(0), slopeB = Val(0);
  Val sumA = Val(0), sumB = Val(0);
  Val tmpans = Val(0);
  int t = 0;
  vector<Event> res;
  while(iA+iB < A.size()+B.size()){
    bool chooseA = false;
    if(iA == A.size()) chooseA = false;
    else if(iB == B.size()) chooseA = true;
    else if(A[iA].t < B[iB].t) chooseA = true;
    else chooseA = false;
    auto a = (chooseA ? A[iA++] : B[iB++]);
    int dt = a.t - t;
    tmpans += slopeA * slopeB * Val(dt*(dt-1)/2);
    tmpans += sumB * slopeA * Val(dt);
    sumA += slopeA * Val(dt);
    sumB += slopeB * Val(dt);
    (chooseA ? slopeA : slopeB) += a.slope;
    t = a.t;
    res.push_back(a);
  }
  ans += tmpans;
  return move(res);
}


int N;
vector<int> L;
vector<int> R;
vector<vector<Event>> segtree;


int main(){
  cin >> N;
  L.resize(N);
  R.resize(N);
  for(int i=0; i<N; i++) cin >> L[i] >> R[i];
  
  int segtree_N = 1;
  while(segtree_N < N) segtree_N *= 2;
  segtree.resize(segtree_N*2);
  for(int i=0; i<N; i++){
    segtree[segtree_N+i].push_back(Event{ L[i]-1, Val(1)/Val(R[i]-L[i]+1) });
    segtree[segtree_N+i].push_back(Event{ R[i], -(Val(1)/Val(R[i]-L[i]+1)) });
  }

  Val ans = 0;
  for(int i=segtree_N-1; i>=1; i--){
    segtree[i] = mergeEvents(segtree[i*2],segtree[i*2+1],ans);
  }

  cout << setprecision(10) << ans << "\n";
  return 0;
}
