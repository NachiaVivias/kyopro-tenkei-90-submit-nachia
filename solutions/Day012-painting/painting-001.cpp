#include <cstdio>
#include <vector>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/012.jpg
// Time Complexity : O( HW log log (HW) )

/////////////////////////////////////
// input
//
// H W
// Q
// query[1]
// query[2]
//  :
// query[Q]
//
// query syntax
//    1 x y
//    2 xa ya xb yb
//

// 赤マスのみを通って移動できる範囲を DSU で管理する。

struct DSU{
  vector<int> V;
  DSU(int n=0){ V.assign(n,-1); }
  int leader(int a){
    if(V[a]<0) return a;
    V[a] = leader(V[a]);
    return V[a];
  }
  void merge(int u,int v){
    u = leader(u);
    v = leader(v);
    if(u==v) return;
    if(V[u] > V[v]) swap(u,v);
    if(V[u] == V[v]) V[u]--;
    V[v] = u;
  }
};

const int dir[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};

int H,W;
int Q;
vector<vector<int>> Red;
DSU dsu;

int main(){
  scanf("%d%d",&H,&W);
  Red.assign(H,vector<int>(W,0));
  dsu = DSU(H*W);

  scanf("%d",&Q);

  for(int i=0; i<Q; i++){
    int t; scanf("%d",&t);
    if(t==1){
      int x,y; scanf("%d%d",&x,&y); x--; y--;
      Red[x][y] = 1;
      for(int diri=0; diri<4; diri++){
        int newx = x + dir[diri][0];
        int newy = y + dir[diri][1];
        if(!(0 <= newx && newx < H && 0 <= newy && newy < W)) continue;
        if(Red[newx][newy] == 0) continue;
        dsu.merge(x*W+y,newx*W+newy);
      }
    }
    if(t==2){
      int xa,ya,xb,yb; scanf("%d%d%d%d",&xa,&ya,&xb,&yb); xa--; ya--; xb--; yb--;
      bool ans = true;
      if(Red[xa][ya] == 0) ans = false;
      if(Red[xb][yb] == 0) ans = false;
      if(ans) ans = (dsu.leader(xa*W+ya) == dsu.leader(xb*W+yb));
      printf(ans ? "Yes" : "No"); printf("\n");
    }
  }
  return 0;
}