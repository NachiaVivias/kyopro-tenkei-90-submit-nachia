#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/011.jpg
// Subtask 1
// Time Complexity : O( N! N )

/////////////////////////////////////
// input
//
// N
// D[1] C[1] S[1]
// D[2] C[2] S[2]
//  :
// D[N] C[N] S[N]
//

// 依頼を完遂する順番が決まれば、時系列順に取れるだけ取る貪欲が成り立つ

struct Query{ int d,c; ll s; };

int N;
vector<Query> Q;

int main(){
  scanf("%d",&N);
  Q.resize(N);
  for(int i=0; i<N; i++){
    int c,d,s; scanf("%d%d%d",&d,&c,&s);
    Q[i] = {d,c,s};
  }

  vector<int> perm(N);
  for(int i=0; i<N; i++) perm[i] = i;

  ll ans = 0;
  // perm が全順列を通るループ
  do{
    int t = 0;
    ll partans = 0;
    for(int i=0; i<N; i++){
      int qi = perm[i];
      if(t + Q[qi].c <= Q[qi].d){
        partans += Q[qi].s;
        t += Q[qi].c;
      }
    }
    ans = max(ans,partans);
  } while(next_permutation(perm.begin(),perm.end()));

  printf("%lld\n",ans);
  return 0;
}