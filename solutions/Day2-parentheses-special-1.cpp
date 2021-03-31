#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)

/////////////////////////////////////
// Problem : https://twitter.com/e869120/status/1377043092369330176
//           Original : https://github.com/E869120/kyopro_educational_90/blob/main/problem/002.jpg
// Time Complexity : ある K に対して N が十分大きいとき O( N log K )

/////////////////////////////////////
// input
//
// N K
//

const ll INF = 1001001001001001001;

int N;
ll K;

// 辞書順なので前から決める
// 前から x 文字を決めたときにあり得るものの数を求めたいが、
// '(' と ')' それぞれの数が決まれば実は数えるものは変わらない。
// 後ろ部分の数え上げを K 番目が出るまで前計算して K 番目を復元。

// x (後述) を固定したときに N が十分大きければ、
// 初めの ')' の後ろに '(' が x 個あるもので Θ(N)^x 個以上の正しい文字列があるので、
// 下の方法では( K に対して N が十分大きいとき )答えを O( N log K ) で求められる。
// N が小さいときは O( N^2 ) なので十分高速。

// dp[i][j] = 以下を満たす文字列の数
//     ・ i 個の '(' と j 個の ')' からなる
//     ・ 正しいカッコ文字列の接尾辞としてあり得る
vector<vector<ll>> dp;

int main() {
  scanf("%d%lld",&N,&K);
  if(N%2==1){ printf("NOT EXIST\n"); return 0; }
  dp.push_back(vector<ll>(N/2+1,1));
  while(dp.back().back()<K){
    if(dp.size()>=N/2+1){ printf("NOT EXIST\n"); return 0; }
    int i=dp.size();
    dp.push_back(vector<ll>(N/2+1,0));
    for(int j=i; j<=N/2; j++) dp[i][j] = min(INF, dp[i][j-1]+dp[i-1][j]);
  }

  rep(i,N/2-(dp.size()-1)) printf("(");
  int pi=dp.size()-1, pj=dp[pi].size()-1;
  while(pi!=0 || pj!=0){
    bool next_is_open = true;
    if(pi==0) next_is_open = false;
    else if(pj==0) next_is_open = true;
    else if(dp[pi-1][pj] >= K) next_is_open = true; // できるだけ '(' を使いたい
    else next_is_open = false;
    if(next_is_open){
      printf("("); pi--;
    }
    else{
      K -= dp[pi][pj]-dp[pi][pj-1];
      printf(")"); pj--;
    }
  }

  printf("\n");

  return 0;
}
