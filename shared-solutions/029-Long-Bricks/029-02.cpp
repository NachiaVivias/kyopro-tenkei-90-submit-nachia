#include <vector>
#include <iostream>
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;

/////////////////////////////////////
// Problem : https://atcoder.jp/contests/typical90/tasks/typical90_ac
// Subtask 1
// Time Complexity : O( N W )

/////////////////////////////////////
// input
//
// W N
// L[1] R[1]
// L[2] R[2]
//  :
// L[N] R[N]
//

int W,N;
int H[500000];

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);
  cin >> W >> N;
  for(int i=0; i<N; i++){
    int l,r; cin >> l >> r; l--;
    int h = 0;
    for(int j=l; j<r; j++) h = max(h,H[j]);
    h += 1;
    for(int j=l; j<r; j++) H[j] = h;
    cout << h << "\n";
  }
  return 0;
}
