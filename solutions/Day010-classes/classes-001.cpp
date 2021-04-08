#include <cstdio>
#include <vector>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/010.jpg
// Time Complexity : O( N + Q )

/////////////////////////////////////
// input
//
// N
// C[1] P[1]
// C[2] P[2]
//  :
// C[N} P[N]
// Q
// L[1] R[1]
// L[2] R[2]
//  :
// L[N} R[N]
//

/////////////////////////////////////
// output
//
// ans[1][1] ans[1][2]
// ans[2][1] ans[2][2]
//  :
// ans[Q][1] ans[Q][2]
//

// 各クラスで累積和をとると、各クラス O(1) で区間和が求まる。
// ない部分は 0 として扱えばよい。

int N;
vector<vector<int>> sum;
int Q;

int main(){
  scanf("%d",&N);
  sum.assign(2,vector<int>(N+1,0));
  for(int i=0; i<N; i++){
    int c,a; scanf("%d%d",&c,&a);
    sum[c-1][i+1] = a;
    for(int j=0; j<2; j++) sum[j][i+1] += sum[j][i];
  }

  scanf("%d",&Q);
  for(int i=0; i<Q; i++){
    int l,r; scanf("%d%d",&l,&r); l--; // 0-indexed の半開区間 [l,r) にする
    for(int j=0; j<2; j++){
      if(j!=0) printf(" ");
      printf("%d",sum[j][r]-sum[j][l]);
    }
    printf("\n");
  }
  return 0;
}