#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)

/////////////////////////////////////
// Problem : https://atcoder.jp/contests/typical90/tasks/typical90_bp
// Time Complexity : O( Q log log N )

/////////////////////////////////////
// input
//
// N
// Q
// T[1] X[1] Y[1] V[1]
// T[2] X[2] Y[2] V[2]
//  :
// T[Q] X[Q] Y[Q] V[Q]
//

struct DSU{
  vector<int> P;
  vector<ll> D;
  DSU(int n){
    P.assign(n,-1);
    D.assign(n,0);
  }
  int root(int a){
    if(P[a] < 0) return a;
    root(P[a]);
    D[a] = D[a] + D[P[a]];
    P[a] = root(P[a]);
    return P[a];
  }
  ll diff(int a){ root(a); return D[a]; }
  void merge(int r, int c, ll c_minus_r){
    c_minus_r -= diff(c); c = root(c);
    c_minus_r += diff(r); r = root(r);
    if(r == c){
      if(c_minus_r != 0){
        cout << "ERROR\n";
        exit(0);
      }
    }
    else{
      if(-P[c] > -P[r]){
        c_minus_r *= -1;
        swap(r,c);
      }
      D[c] = c_minus_r;
      P[r] += P[c];
      P[c] = r;
    }
  }
};

int main(){
  int N,Q; cin >> N >> Q;
  DSU G(N*2);
  rep(i,Q){
    int t,x,y,v;
    cin >> t >> x >> y >> v;
    x--; y--;
    if(t == 0){
      G.merge(x+N,y,v);
      G.merge(y+N,x,v);
    }
    if(t == 1){
      if(G.root(y) == G.root(y+N)){
        ll ans = (G.diff(y) - G.diff(y+N)) / 2;
        cout << ans << "\n";
      }
      else if(G.root(y) == G.root(x)){
        ll ans = v - G.diff(x) + G.diff(y);
        cout << ans << "\n";
      }
      else if(G.root(y) == G.root(x+N)){
        ll ans = -v - G.diff(x+N) + G.diff(y);
        cout << ans << "\n";
      }
      else{
        cout << "Ambiguous\n";
      }
    }
  }
  return 0;
}



struct ios_do_not_sync{
  ios_do_not_sync(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
  }
} ios_do_not_sync_instance;
