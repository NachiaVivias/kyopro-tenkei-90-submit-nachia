#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)

/////////////////////////////////////
// Time Complexity : O( N log L )

/////////////////////////////////////
// input
//
// N L
// K
// A[1] A[2] ... A[N]
//

int N,L;
int K;
vector<int> A;

// find if ans >= x
bool solve_with_x(int x){
  int lastcut=0;
  int pA=0; // seeing
  rep(k,K+1){
    while(true){ // until get a piece ( >= x )
      if(pA==A.size()) return false; // run out
      if(A[pA]-lastcut >= x) break;
      pA++;
    }
    lastcut=A[pA];
  }
  return true;
}

int main() {
  scanf("%d%d",&N,&L);
  scanf("%d",&K);
  A.resize(N);
  rep(i,N) scanf("%d",&A[i]);
  A.push_back(L);

  // Meguru-style
  int ok=0, ng=L+1;
  while(abs(ok-ng) > 1){
    int mid = (ok+ng)/2;
    (solve_with_x(mid) ? ok : ng) = mid;
  }

  printf("%d\n",ok);
  return 0;
}
