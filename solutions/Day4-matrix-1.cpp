#include<stdio.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/004.jpg
// Time Complexity : O( H W )

/////////////////////////////////////
// input
//
// H W
// A[1][1] A[1][2] ... A[1][W]
// A[2][1] A[2][2] ... A[2][W]
//  :
// A[H][1] A[H][2] ... A[H][W]
//

/////////////////////////////////////
// output
//
// ans[1][1] ans[1][2] ... ans[1][W]
// ans[2][1] ans[2][2] ... ans[2][W]
//  :
// ans[H][1] ans[H][2] ... ans[H][W]
//


// 考察
// ans[y][x] = (行 y の和) + (列 x の和) - A[y][x]

int H,W;
int A[2000][2000];
int RowSum[2000]; // 行 i の和
int ColSum[2000]; // 列 i の和
int ans[2000][2000];

int main() {
  scanf("%d%d",&H,&W);
  for(int y=0; y<H; y++) for(int x=0; x<W; x++){
    scanf("%d",&A[y][x]);
  }

  for(int y=0; y<H; y++){
    RowSum[y]=0;
    for(int x=0; x<W; x++) RowSum[y] += A[y][x];
  }
  for(int x=0; x<W; x++){
    ColSum[x]=0;
    for(int y=0; y<H; y++) ColSum[x] += A[y][x];
  }

  for(int y=0; y<H; y++) for(int x=0; x<W; x++){
    // ans[y][x] = (行 y の和) + (列 x の和) - A[y][x]
    ans[y][x] = RowSum[y] + ColSum[x] - A[y][x];
  }

  for(int y=0; y<H; y++){
    for(int x=0; x<W; x++){
      if(x!=0) printf(" ");
      printf("%d",ans[y][x]);
    }
    printf("\n");
  }
  return 0;
}
