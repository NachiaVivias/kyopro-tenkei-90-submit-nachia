#include <stdio.h>
#include <vector>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/005.jpg
// Subtask 2
// Time Complexity : O( B^3 log N )

/////////////////////////////////////
// input
//
// N B K
// c[1] c[2] ... c[K]
//


// 小課題 1 でやった dp は行列の累乗で表せるので、繰り返し 2 乗法で高速化できる

const ull MOD = 1000000007;

const int matSize = 30;

// 30 x 30 行列どうしの掛け算をする
struct Matrix{
  ull G[matSize][matSize] = {}; // G[i][j] は i 行 j 列
  
  ull* operator[](int i){ return G[i]; } // 便利
  Matrix pow(ull i);
};

Matrix operator*(Matrix l, Matrix r){
  Matrix res;
  // i,j,k の 3 重ループ
  for(int i=0; i<matSize; i++){
    for(int j=0; j<matSize; j++){
      for(int k=0; k<matSize; k++){
        res[i][j] = (res[i][j] + l[i][k] * r[k][j]) % MOD;
      }
    }
  }
  return res;
}

// i 乗
Matrix Matrix::pow(ull i){
  if(i==0){
    Matrix res;
    for(int i=0; i<matSize; i++) res[i][i] = 1;
    return res;
  }
  Matrix res = pow(i/2);
  res = res * res;
  if(i%2==1) res = res * *this;
  return res;
}

ull N;
int B, K;
vector<int> C;

Matrix G;

int main() {
  scanf("%llu%d%d",&N,&B,&K);
  if(!(N<=1'000'000'000'000'000'000)) return 0; // 小課題 1,2 以外は TLE または RE するので
  if(!(B<=30)) return 0;
  C.resize(K);
  for(int i=0; i<K; i++) scanf("%d",&C[i]);

  // 遷移を行列に書く
  for(int pre=0; pre<B; pre++) for(int c : C){
    int to = (pre*10+c)%B;
    G[pre][to] += 1;
  }

  // N 桁分やったことにする
  // N 桁分の遷移が求まる
  G = G.pow(N);

  // 元々 0 で、遷移後も 0
  printf("%llu\n",G[0][0]);
  return 0;
}
