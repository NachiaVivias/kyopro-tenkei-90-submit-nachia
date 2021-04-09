#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/011.jpg
// Subtask 2
// Time Complexity : O( 2^N N )

/////////////////////////////////////
// input
//
// N
// D[1] C[1] S[1]
// D[2] C[2] S[2]
//  :
// D[N] C[N] S[N]
//

// 取る依頼の集合を決め打ち、可能かどうか判定するのは、
// 締め切りが早い順に時系列順に取れるだけ取る貪欲が成り立つ。

struct Query{ int d,c; ll s; };
bool cmp_Query_by_d(const Query& l,const Query& r){ return l.d<r.d; }

int N;
vector<Query> Q;

int main(){
  scanf("%d",&N);
  Q.resize(N);
  for(int i=0; i<N; i++){
    int c,d,s; scanf("%d%d%d",&d,&c,&s);
    Q[i] = {d,c,s};
  }

  // 締め切りの早い順に
  sort(Q.begin(),Q.end(),cmp_Query_by_d);

  ll ans = 0;
  // bit 全探索
  for(int i=0; i<(1<<N); i++){
    int t = 0;
    ll partans = 0;
    bool ok = true;
    for(int j=0; j<N; j++){
      if(i&(1<<j)){
        if(t + Q[j].c > Q[j].d) ok = false;
        partans += Q[j].s;
        t += Q[j].c;
      }
    }
    if(ok) ans = max(ans,partans);
  };

  printf("%lld\n",ans);
  return 0;
}