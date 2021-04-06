#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/008.jpg
// Time Complexity : O( |S| |T| ) ( T : picked string ("atcoder") )

/////////////////////////////////////
// input
//
// S
//

// dp[i][j] = S[[0,i)] から T[[0,j)] を取り出す方法の数
// これの更新には i 軸において直前しか使用せず、メモリは j 軸だけでよい

const ull MOD = 1000000007;

string S;
string T = "atcoder";

int main() {
  cin >> S;

  vector<int> dp(T.size()+1,0);
  dp[0] = 1;

  for(int i=0; i<S.size(); i++){
    // for(int j=0; j<T.size(); j++) は T に同じ文字が連続する部分があると WA
    for(int j=T.size()-1; j>=0; j--){
      if(S[i] == T[j]){
        dp[j+1] += dp[j];
        if(dp[j+1] >= MOD) dp[j+1] -= MOD;
      }
    }
  }

  printf("%d\n",dp[7]);
  return 0;
}
