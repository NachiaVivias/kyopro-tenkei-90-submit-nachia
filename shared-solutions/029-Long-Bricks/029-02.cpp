#include<vector>
#include<iostream>
#include<algorithm>
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


int main(){
  int W,N; scanf("%d%d",&W,&N);

  vector<int> H(W,0);
  for(int i=0; i<N; i++){
    int l,r; scanf("%d%d",&l,&r); l--;
    int h = 0;
    for(int j=l; j<r; j++) h = max(h,H[j]);
    h += 1;
    for(int j=l; j<r; j++) H[j] = h;
    printf("%d\n",h);
  }
  return 0;
}
