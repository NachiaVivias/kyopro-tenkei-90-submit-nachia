#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

/////////////////////////////////////
// Problem : https://atcoder.jp/contests/typical90/tasks/typical90_ac
// Full Score
// Time Complexity : O( (N + Q) log N )

/////////////////////////////////////
// input
//
// W N
// L[1] R[1]
// L[2] R[2]
//  :
// L[N] R[N]
//


/////////////////////////////////////
// すごいセグ木
//
// - vector<int> query(int l,int r,int id)
//   以下を順に行う。
//     (1) 列 A の区間 [l,r] に書かれている値の種類を列挙
//     (2) 列 A の区間 [l,r] を id で置き換える
//     (3) (1) で列挙したものを返す
//   計算量 ならし O(log N) : 列 A の、値が変化する部分の数をポテンシャルとする
//
// std::map でもできるよ
// 例題：https://atcoder.jp/contests/past202104-open/tasks/past202104_m
//
struct interval_overlap_segtree{
  int N;
  vector<int> V;
  vector<int> Fin;

  interval_overlap_segtree(int n = 0){
    N = 1; while(N<n) N*=2;
    V.assign(N*2,-1);
    Fin.assign(N*2,1);
  }
  vector<int> query(int l,int r,int id){
    struct QueryNode{ int a,b,i; };
    vector<QueryNode> Q;
    vector<int> ans;
    Q.push_back({0,N,1});
    while(Q.size()){
      QueryNode q = Q.back(); Q.pop_back();
      if(q.b <= l || r <= q.a) continue;
      if(Fin[q.i]){
        if(V[q.i] != -1) ans.push_back(V[q.i]);
        continue;
      }
      Q.push_back({q.a,(q.a+q.b)/2,q.i*2});
      Q.push_back({(q.a+q.b)/2,q.b,q.i*2+1});
    }
    Q.push_back({0,N,1});
    while(Q.size()){
      QueryNode q = Q.back(); Q.pop_back();
      if(q.b <= l || r <= q.a) continue;
      if(l <= q.a && q.b <= r){
        V[q.i] = id; Fin[q.i] = 1;
        continue;
      }
      if(Fin[q.i]){
        V[q.i*2] = V[q.i*2+1] = V[q.i];
        Fin[q.i*2] = Fin[q.i*2+1] = 1;
        V[q.i] = -1;
        Fin[q.i] = 0;
      }
      Q.push_back({q.a,(q.a+q.b)/2,q.i*2});
      Q.push_back({(q.a+q.b)/2,q.b,q.i*2+1});
    }
    sort(ans.begin(),ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    return move(ans);
  }
};





vector<vector<int>> construct_dag(
  int W,
  int N,
  vector<int> L,
  vector<int> R
){
  vector<vector<int>> ans(N);
  interval_overlap_segtree G(W);
  for(int i=0; i<N; i++){
    ans[i] = G.query(L[i]-1,R[i],i);
  }
  return move(ans);
}

int main(){
  int W,N; scanf("%d%d",&W,&N);
  vector<int> L(N), R(N);
  for(int i=0; i<N; i++) scanf("%d%d",&L[i],&R[i]);
  vector<vector<int>> G = construct_dag(W,N,L,R);
  vector<int> D(N,1);
  for(int i=0; i<N; i++){
    for(int e : G[i]) D[i] = max(D[i],D[e]+1);
    printf("%d\n",D[i]);
  }
  return 0;
}
