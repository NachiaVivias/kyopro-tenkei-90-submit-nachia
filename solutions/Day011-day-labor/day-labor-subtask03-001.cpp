#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/011.jpg
// Subtask 3
// Time Complexity : O( N (max D) )

/////////////////////////////////////
// input
//
// N
// D[1] C[1] S[1]
// D[2] C[2] S[2]
//  :
// D[N] C[N] S[N]
//

// 締め切りが早い順にして前から見ると、
// 後ろを考える際にはこれまででかかる時間以外を無視できる。

const ll INF = 1001001001001001001;

struct Query{ int d,c; ll s; };
bool cmp_Query_by_d(const Query& l,const Query& r){ return l.d<r.d; }

int N;
vector<Query> Q;
vector<ll> dp; // dp[i][t] : 時刻 t までに達成できる報酬

int main(){
  scanf("%d",&N);
  Q.resize(N);
  for(int i=0; i<N; i++){
    int c,d,s; scanf("%d%d%d",&d,&c,&s);
    Q[i] = {d,c,s};
  }

  // 締め切りの早い順に
  sort(Q.begin(),Q.end(),cmp_Query_by_d);
  
  dp.assign(5001,-INF);
  dp[0] = 0;
  for(int i=0; i<N; i++){
    // 同じ依頼を複数回受けないように、後ろから回す
    for(int t=Q[i].d; t>=Q[i].c; t--){
      dp[t] = max(dp[t],dp[t-Q[i].c]+Q[i].s);
    }
  }

  ll ans = 0;
  for(int t=0; t<=5000; t++) ans = max(ans,dp[t]);
  printf("%lld\n",ans);
  return 0;
}