
#include <stdio.h>
#include <vector>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/005.jpg
// Subtask 3
// Time Complexity : O( B log B log N ) with large constant factor

/////////////////////////////////////
// input
//
// N B K
// c[1] c[2] ... c[K]
//

const ull MOD = 1000000007;

const ull NTT_Mods[4] = { 998244353, 1107296257, 2113929217, 1000000007 };
const ull NTT_gs[3] = { 3, 10, 5 };

ull powm(ull a, ull i, ull m){
  if(i==0) return 1;
  ull r = powm(a*a%m,i/2,m);
  if(i%2==1) r = r*a%m;
  return r;
}

void NTT(vector<ull>& A, ull m, ull g){
	int N = A.size();
  for(int i=0, j=0; j<N; j++){
    if(i<j) swap(A[i],A[j]);
    for(int k=N>>1; k>(i^=k); k>>=1);
  }
  for(int i=1; i<N; i<<=1){
    ull q = powm(g,(m-1)/i/2,m);
    ull qj = 1;
    for(int j=0; j<i; j++){
      for(int k=j; k<N; k+=i*2){
        ull l = A[k], r = A[k+i]*qj%m;
        A[k] = l+r; if(A[k]>=m) A[k]-=m;
        A[k+i] = l+m-r; if(A[k+i]>=m) A[k+i]-=m;
      }
      qj = qj*q%m;
    }
  }
}

vector<ull> convolution(const vector<ull>& A,const vector<ull>& B){
	int Z=1; while(Z < A.size() + B.size()) Z *= 2;
  vector<ull> fA(Z), fB(Z);
  vector<ull> resM[3];
  for(int modi=0; modi<3; modi++){
    for(int i=0; i<Z; i++) fA[i]=0;
    for(int i=0; i<A.size(); i++) fA[i]=A[i];
    NTT(fA,NTT_Mods[modi],NTT_gs[modi]);
    for(int i=0; i<Z; i++) fB[i]=0;
    for(int i=0; i<B.size(); i++) fB[i]=B[i];
    NTT(fB,NTT_Mods[modi],NTT_gs[modi]);
    resM[modi].resize(Z);
    for(int i=0; i<Z; i++) resM[modi][i] = fA[i]*fB[i]%NTT_Mods[modi];
    ull invg = powm(NTT_gs[modi],NTT_Mods[modi]-2,NTT_Mods[modi]);
    ull invZ = powm(Z,NTT_Mods[modi]-2,NTT_Mods[modi]);
    NTT(resM[modi],NTT_Mods[modi],invg);
    for(int i=0; i<Z; i++) resM[modi][i] = resM[modi][i] * invZ % NTT_Mods[modi];
  }

  vector<ull> res(Z);
  vector<ull> gerner_coeff, gerner_const;
  for(int i=0; i<Z; i++){
    gerner_coeff.assign(4,1);
    gerner_const.assign(4,0);
    for(int j=0; j<4; j++){
      ull inv_coeff = powm(gerner_coeff[j],NTT_Mods[j]-2,NTT_Mods[j]);
      ull t = resM[j][i] + (NTT_Mods[j]-gerner_const[j]);
      t = t * inv_coeff % NTT_Mods[j];
      for(int k=j+1; k<4; k++){
				gerner_const[k] = (gerner_const[k] + gerner_coeff[k] * t) % NTT_Mods[k];
				gerner_coeff[k] = gerner_coeff[k] * NTT_Mods[j] % NTT_Mods[k];
      }
    }
    res[i] = gerner_const[3];
  }

  res.resize(A.size() + B.size() - 1);
  return move(res);
}


ull N;
int B, K;
vector<int> C;

struct MergeNode{
  vector<ull> G;
  ull multi = 10; // 桁数によって左の数字の重みが変わる
  MergeNode pow(ull i);
};

MergeNode operator*(MergeNode l, MergeNode r){
  MergeNode res;
  vector<ull> buf(B);
  for(int i=0; i<B; i++) buf[i * r.multi % B] += l.G[i];
  for(int i=0; i<B; i++) buf[i] %= MOD;
  buf = convolution(buf,r.G);
  for(int i=buf.size()-1; i>=B; i--){
    buf[i-B] += buf[i];
    if(buf[i-B] >= MOD) buf[i-B] -= MOD;
  }
  buf.resize(B);
  res.G = move(buf);
  res.multi = (l.multi * r.multi) % B;
  return move(res);
}

// i 乗
MergeNode MergeNode::pow(ull i){
  if(i==0){
    MergeNode res;
    res.G.resize(B);
    res.G[0] = 1;
    res.multi = 1;
    return res;
  }
  MergeNode res = pow(i/2);
  res = res * res;
  if(i%2==1) res = res * *this;
  return res;
}

MergeNode G;


int main() {
  scanf("%lld%d%d",&N,&B,&K);
  C.resize(K);
  for(int i=0; i<K; i++) scanf("%d",&C[i]);

  // 遷移を MergeNode に表す
  G.G.resize(B);
  for(int c : C) G.G[c%B] += 1;
  G.multi = 10 % B;

  // N 桁分やったことにする
  // N 桁分の遷移が求まる
  G = G.pow(N);

  // 元々 0 で、遷移後も 0 となる遷移の部分
  printf("%llu\n",G.G[0]);
  return 0;
}
