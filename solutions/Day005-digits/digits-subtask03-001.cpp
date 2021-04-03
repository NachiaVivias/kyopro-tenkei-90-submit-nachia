#include <stdio.h>
#include <vector>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/005.jpg
// Subtask 3
// Time Complexity : O( B^2 log N )

/////////////////////////////////////
// input
//
// N B K
// c[1] c[2] ... c[K]
//


// 小課題 1 でやった dp は畳み込みを用いた合成で表せるので、これを繰り返し 2 乗法で高速化する
// 小課題 2 で行列の掛け算 (O( B^3 )) にあたるものが畳み込み (O( B^2 )) になる

const ull MOD = 1000000007;

const int matSize = 1000;

ull N;
int B, K;
vector<int> C;

struct MergeNode{
  vector<ull> G = vector<ull>(matSize);
  ull multi = 10; // 桁数によって左の数字の重みが変わる
  MergeNode pow(ull i);
};

MergeNode operator*(MergeNode l, MergeNode r){
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
MergeNode MergeNode::pow(ull i){
  if(i==0){
    MergeNode res;
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
  scanf("%llu%d%d",&N,&B,&K);
  C.resize(K);
  for(int i=0; i<K; i++) scanf("%d",&C[i]);

  // 遷移を MergeNode に表す
  for(int c : C) G.G[c] = 1;
  G.multi = 10 % B;

  // N 桁分やったことにする
  // N 桁分の遷移が求まる
  G = G.pow(N);

  // 元々 0 で、遷移後も 0 となる遷移の部分
  printf("%llu\n",G.G[0]);
  return 0;
}
