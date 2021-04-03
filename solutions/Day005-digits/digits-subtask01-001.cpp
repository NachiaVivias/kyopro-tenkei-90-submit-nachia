#include <stdio.h>
#include <vector>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/005.jpg
// Subtask 1
// Time Complexity : O( N B^2 )

/////////////////////////////////////
// input
//
// N B K
// c[1] c[2] ... c[K]
//

const ull MOD = 1000000007;

ll N;
int B, K;
vector<int> C;

// dp[i][j] : 数字 c[1],c[2] ... c[k] のみを用いて作れる
//            i 桁の正の整数で、 B で割った余りが j であるものの数
ull dp[10001][30];

int main() {
  scanf("%lld%d%d",&N,&B,&K);
  if(!(N<=10000)) return 0; // 小課題 1 以外は TLE または RE するので
  if(!(B<=30)) return 0;
  C.resize(K);
  for(int i=0; i<K; i++) scanf("%d",&C[i]);

  for(int i=0; i<=N; i++) for(int d=0; d<B; d++) dp[i][d] = 0;
  dp[0][0] = 1;

  for(int i=0; i<N; i++){
    for(int pre=0; pre<B; pre++){
      for(int c : C){
        int to = (pre*10+c)%B;
        dp[i+1][to] += dp[i][pre];
        if(dp[i+1][to] >= MOD) dp[i+1][to] -= MOD;
      }
    }
  }

  printf("%llu\n",dp[N][0]);
  return 0;
}
