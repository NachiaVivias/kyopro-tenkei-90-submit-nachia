#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/002.jpg
// Time Complexity : O( N 2^N )

/////////////////////////////////////
// input
//
// N
//

int N;

int main() {
  scanf("%d",&N);

  // bit 全探索
  // 0 -> '('   1 -> ')'
  // 00110101 -> "(())()()"
  // bit d (1<<d) が (N-1-d)番目の文字に対応 (0-indexed)
  rep(i,1<<N){
    bool valid = true;
    int depth=0;
    for(int d=N-1; d>=0; d--){
      if((i>>d)&1) depth--;
      else depth++;
      if(depth<0) valid = false;
    }
    if(depth!=0) valid = false;

    if(valid){
      string ans(N,'(');
      rep(d,N) if((i>>d)&1) ans[d]=')';
      reverse(ans.begin(),ans.end());
      printf(ans.c_str());
      printf("\n");
    }
  }

  return 0;
}
