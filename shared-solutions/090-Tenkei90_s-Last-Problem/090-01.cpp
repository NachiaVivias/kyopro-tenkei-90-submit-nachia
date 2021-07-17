#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

/////////////////////////////////////
// Problem : https://atcoder.jp/contests/typical90/tasks/typical90_cl
// Time Complexity : O( K log K ( log K + log N ) )

using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)


const ull MOD = 998244353;


// a^i mod M
ull powm(ull a,ull i,ull M) {
  if(i==0) return 1;
  ull r=powm(a*a%M,i/2,M);
  if(i&1) r=r*a%M;
  return r;
}


void NTT(vector<ull>& A,ull g){
  int N=1;
  while(N < A.size()) N *= 2;
  for(int i=0,j=0; j<N; j++){
    if(i<j) swap(A[i],A[j]);
    for(int k=N>>1; k>(i^=k); k>>=1);
  }
  for(int i=1; i<N; i<<=1){
    ull q=powm(g,(MOD-1)/i/2,MOD), qj=1;
    for(int j=0; j<i; j++){
      for(int k=j; k<N; k+=i*2){
        ull l = A[k];
        ull r = A[k+i] * qj % MOD;
        A[k] = l+r;
        if(A[k] >= MOD) A[k] -= MOD;
        A[k+i] = l+MOD-r;
        if(A[k+i] >= MOD) A[k+i] -= MOD;
      }
      qj = qj * q % MOD;
    }
  }
}



// find  \sum_{i=0}^\infty A^i
//         ( = 1 / (1-A) )
// n : length of result
// g : primitive root
//
// ref : https://opt-cp.com/fps-fast-algorithms/
// 
// TIME : O( n log n )
// SPACE : O( n )
vector<ull> powsumFPS(const vector<ull>& A, int n, ull g){
  assert(A[0] == 0);
  if(n == 0){ return {}; }
  if(n == 1){ return { 1 }; }
  int N = 1; while(N<n) N*=2;
  int hN = N/2;
  vector<ull> hInv = powsumFPS(A,hN,g);
  vector<ull> tgA(N,0);
  for(int i=0; i<min(N,(int)A.size()); i++) tgA[i] = A[i];
  ull ig = powm(g,MOD-2,MOD);
  NTT(tgA,g);
  vector<ull> htInv(N,0);
  for(int i=0; i<hN; i++) htInv[i] = hInv[i];
  NTT(htInv,g);
  vector<ull> R(N);
  for(int i=0; i<N; i++) R[i] = tgA[i] * htInv[i] % MOD;
  NTT(R,ig);
  for(int i=0; i<hN; i++) R[i] = R[hN+i];
  for(int i=hN; i<N; i++) R[i] = 0;
  NTT(R,g);
  ull iNN = powm((ull)N*N%MOD,MOD-2,MOD);
  for(int i=0; i<N; i++) R[i] = R[i] * htInv[i] % MOD * iNN % MOD;
  NTT(R,ig);
  hInv.resize(n,0);
  for(int i=hN; i<n; i++) hInv[i] = R[i-hN];
  return move(hInv);
}


// find  1 / A
//
// n : length of result
// g : primitive root
// 
// TIME : O( n log n )
// SPACE : O( n )
vector<ull> invFPS(const vector<ull>& A, int n, ull g){
  ull iA0 = powm(A[0],MOD-2,MOD);
  vector<ull> xA(min(n,(int)A.size()));
  for(int i=0; i<xA.size(); i++) xA[i] = (MOD - A[i]) * iA0 % MOD;
  xA[0] = 0;
  xA = powsumFPS(xA,n,g);
  for(int i=0; i<xA.size(); i++) xA[i] = xA[i] * iA0 % MOD;
  return move(xA);
}



// find  K-th term of {a_i}
//  *  n = deg(A) ( = deg(C) )
//  *  a_i = A[i]  ( 0 \leq i \lt |A| )
//  *  a_i = \sum_{j=1}^{|A|} a_{i-j} C[j-1] ( n \leq i )
//
// returns A[K]
//
// TIME : O( n log n log K )
// SPACE : O( n )
//
// ref : https://arxiv.org/abs/2008.08822
//
// I'm deeply grateful to Alin Bostan and Ryuhei Mori
ull Kth_term_of_linearly_recurrent_sequence(
  const vector<ull>& A,
  const vector<ull>& C,
  ull K,
  ull g 
){
  assert(A.size() == C.size());
  int n = A.size();

  int k = 0; while((1<<k) < 2*n+1) k++;
  int h2k = 1 << (k-1);
  ull ig = powm(g,MOD-2,MOD);
  ull w = powm(g,(MOD-1)/(1<<k),MOD);
  ull iw = powm(w,MOD-2,MOD);
  ull inv2 = powm(2,MOD-2,MOD);
  ull invk = powm(1<<k,MOD-2,MOD);

  vector<ull> P(1<<k,0);
  for(int i=0; i<n; i++) P[i] = A[i];
  vector<ull> Q(1<<k,0);
  Q[0] = 1;
  for(int i=0; i<n; i++) Q[i+1] = (MOD - C[i]) % MOD;
  
  NTT(P,g);
  NTT(Q,g);
  for(int i=0; i<1<<k; i++) P[i] = P[i] * Q[i] % MOD * invk % MOD; // * invk % MOD;
  NTT(P,ig);
  for(int i=n; i<(1<<k); i++) P[i] = 0;
  NTT(P,g);

  auto UP = [g,w](const vector<ull>& a) -> vector<ull> {
    int n = a.size();
    ull ig = powm(g,MOD-2,MOD);
    vector<ull> A = a;
    NTT(A,ig);
    ull invn = powm(n,MOD-2,MOD);
    for(int i=0; i<n; i++) A[i] = A[i] * invn % MOD;
    ull w = powm(g,(MOD-1)/(2*n),MOD);
    vector<ull> B(n);
    ull wp = 1;
    for(int i=0; i<n; i++){ B[i] = A[i] * wp % MOD; wp = wp * w % MOD; }
    NTT(B,g);
    vector<ull> res(n*2);
    for(int i=0; i<n; i++) res[i*2] = a[i];
    for(int i=0; i<n; i++) res[i*2+1] = B[i];
    return move(res);
  };

  while(K >= n){

    vector<ull> U(1<<k);
    for(int i=0; i<(1<<k); i++) U[i] = P[i] * Q[i^h2k] % MOD;

    if(K % 2 == 0){
      vector<ull> Ue(h2k);
      for(int i=0; i<h2k; i++){
        Ue[i] = (U[i] + U[i+h2k]) * inv2 % MOD;
      }
      P = UP(Ue);
    }
    else{
      vector<ull> Uo(h2k);
      ull wp = inv2;
      for(int i=0; i<h2k; i++){
        Uo[i] = (U[i] + MOD - U[i+h2k]) * wp % MOD;
        wp = wp * iw % MOD;
      }
      P = UP(Uo);
    }

    vector<ull> A(h2k);
    for(int i=0; i<h2k; i++) A[i] = Q[i] * Q[i^h2k] % MOD;
    Q = UP(A);
    K /= 2;
  }

  NTT(P,ig);
  NTT(Q,ig);

  Q = invFPS(Q,K+1,g);
  ull res = 0;
  for(int i=0; i<=K; i++) res = (res + P[i] * Q[K-i]) % MOD;
  return res;
}


const ull NTTg = 3;

int N;
int K;

vector<ull> dpStep(const vector<ull>& prev, int nxLen, ull multiplier){
  vector<ull> res(nxLen+1,0);
  ull imulti = powm(multiplier,MOD-2,MOD);
  for(int i=0; i<min(nxLen,(int)prev.size()); i++) res[i+1] = prev[i] * multiplier % MOD;
  res = powsumFPS(res,nxLen+2,NTTg);
  for(int i=0; i<=nxLen; i++) res[i] = res[i+1] * imulti % MOD;
  res.resize(nxLen+1);
  return move(res);
}


int main(){
  ll N,K; cin >> N >> K;

  vector<int> steps(K+1,0);
  for(int n=1; n<=K; n++) steps[min(N,K/n)]++;
  vector<ull> dp = {1};
  for(int l=1; l<=K; l++){
    if(steps[l] == 0) continue;
    dp = dpStep(dp,l,steps[l]);
  }

  vector<ull> recurrent_A(dp.size(),0);
  recurrent_A.back() = 1;
  cout << Kth_term_of_linearly_recurrent_sequence(recurrent_A,dp,N+dp.size(),NTTg) << "\n";
  return 0;
}



struct ios_do_not_sync{
  ios_do_not_sync(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
  }
} ios_do_not_sync_instance;


