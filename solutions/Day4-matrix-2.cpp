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
// ans[y][x] =   (全体の総和)
//             - (左上の長方形の総和)
//             - (右上の長方形の総和)
//             - (左下の長方形の総和)
//             - (右下の長方形の総和)

// 各長方形の総和は、累積和を求めておけば各 O(1) 時間で求まる

int H,W;
int A[2000][2000];
int SumA[2001][2001];
int ans[2000][2000];

// SumA の情報から、長方形範囲 y=[yl,yr) , x=[xl,xr) 内の総和を求める
int RectangleSum(int yl,int yr,int xl,int xr){
  return SumA[yr][xr] - SumA[yr][xl] - SumA[yl][xr] + SumA[yl][xl];
}

int main() {
  scanf("%d%d",&H,&W);
  for(int y=0; y<H; y++) for(int x=0; x<W; x++){
    scanf("%d",&A[y][x]);
  }

  for(int y=0; y<=H; y++) for(int x=0; x<=W; x++) SumA[y][x] = 0;
  for(int y=0; y<H; y++) for(int x=0; x<W; x++) SumA[y+1][x+1] = A[y][x];
  for(int y=0; y<=H; y++) for(int x=0; x<=W-1; x++) SumA[y][x+1] += SumA[y][x];
  for(int y=0; y<=H-1; y++) for(int x=0; x<=W; x++) SumA[y+1][x] += SumA[y][x];

  for(int y=0; y<H; y++) for(int x=0; x<W; x++){
    // 今見ているマスが占める領域が y=[y,y+1), x=[x,x+1) であることに注意
    ans[y][x] = 0;
    ans[y][x] += RectangleSum(0,H,0,W); // 全体
    ans[y][x] -= RectangleSum(0,y,0,x);
    ans[y][x] -= RectangleSum(0,y,x+1,W);
    ans[y][x] -= RectangleSum(y+1,H,0,x);
    ans[y][x] -= RectangleSum(y+1,H,x+1,W);
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
