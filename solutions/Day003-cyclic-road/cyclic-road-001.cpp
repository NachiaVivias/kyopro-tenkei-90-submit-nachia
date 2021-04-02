#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/003.jpg
// Time Complexity : O( N )

/////////////////////////////////////
// input
//
// N
// A[1] B[1]
// A[2] B[2]
//  :
// A[N-1] B[N-1]
//

// スペシャル : 標準エラー出力に、新設する道の両端の都市の番号を出力

int N;
vector<vector<int>> E;
vector<int> P; // bfs木での親
vector<int> I; // bfsの探索順に並べたもの

vector<int> D, Didx; // 最も遠いbfs木の末端までの距離と、その末端の番号


// この関数は bfs するだけ
// 要するにこれ : https://twitter.com/maspy_stars/status/1367811754575556611
void bfs(int root){
  P.assign(N,-1);
  queue<int> Q;
  Q.push(root);
  while(Q.size()){
    int p=Q.front(); Q.pop();
    I.push_back(p);
    for(int e:E[p]) if(P[p]!=e){
      P[e]=p;
      Q.push(e);
    }
  }
}

int main() {
  scanf("%d",&N);
  E.resize(N);
  for(int i=0; i<N-1; i++){
    int u,v; scanf("%d%d",&u,&v); u--; v--;
    E[u].push_back(v);
    E[v].push_back(u);
  }
  bfs(0);

  int ans=0;
  pair<int,int> ans_idx = {-1,-1}; // 新設する道の両端

  D.assign(N,0);
  Didx.resize(N); for(int i=0; i<N; i++) Didx[i]=i;
  for(int i=N-1; i>=1; i--){
    int p=I[i];
    if(ans < D[P[p]]+D[p]+1){
      ans = D[P[p]]+D[p]+1;
      ans_idx = {Didx[P[p]],Didx[p]};
    }
    if(D[P[p]] < D[p]+1){
      D[P[p]] = D[p]+1;
      Didx[P[p]] = Didx[p];
    }
  }

  printf("%d\n",ans+1);

  if(ans_idx.first > ans_idx.second) swap(ans_idx.first,ans_idx.second);
  fprintf(stderr,"%d %d\n",ans_idx.first+1,ans_idx.second+1);
  return 0;
}
