#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://atcoder.jp/contests/typical90/tasks/typical90_w
// Full Score
// Time Complexity : O( 1.57^W H W )

/////////////////////////////////////
// input
//
// H W
// c[1][1] ... c[1][W]
//  :
// c[H][1] ... c[H][W]
//


// 1 行分の情報を持ってメモ化再帰 ... は間に合わないので、遷移を前計算して配列で DP

// キングを新しく置けない場所を 1 、置ける場所を 0 としてビット列で表す。
// 改行は、各行の後ろに "#" を 1 つ置くことと同じ。
// あり得る状態と遷移に限定した配列で DP を行う。

const ull MOD = 1000000007;

int H, W;
string C;

vector<int> dp_nodes; // あり得る状態
map<int,int> dp_nodeid; // dp配列インデックス から 状態のビット列 へ
vector<int> dp_edges[2]; // 各状態からの遷移 ( 高々 2 通り )

void init_dp(){
  int dp_node_mask = (1 << (W+1)) - 1;
  dp_nodeid.clear();
  dp_nodeid[0] = 0;
  dp_nodes.clear();
  dp_nodes.push_back(0);
  for(int d = 0; d < dp_nodes.size(); d++){
    int pre = dp_nodes[d];
    int to = ((pre << 2) | 0b111) & dp_node_mask;
    if((pre & (1 << W)) == 0){
      if(dp_nodeid.count(to) == 0){
        dp_nodeid[to] = (int)dp_nodes.size();
        dp_nodes.push_back(to);
      }
    }
    to = (pre << 1) & dp_node_mask;
    if(dp_nodeid.count(to) == 0){
      dp_nodeid[to] = (int)dp_nodes.size();
      dp_nodes.push_back(to);
    }
  }

  for(int t=0; t<2; t++) dp_edges[t].resize(dp_nodes.size(), -1);
  for(int nodeid = 0; nodeid < dp_nodes.size(); nodeid++){
    int pre = dp_nodes[nodeid];
    dp_edges[0][nodeid] = dp_nodeid[(pre << 1) & dp_node_mask];
    if((pre & (1 << W)) != 0) continue;
    dp_edges[1][nodeid] = dp_nodeid[((pre << 2) | 0b111) & dp_node_mask];
  }
}

int main() {
  cin >> H >> W;
  for(int i=0; i<H; i++){
    string buf; cin >> buf;
    C += buf;
    C += "#";
  }

  init_dp();
  
  vector<vector<ull>> dp(3,vector<ull>(dp_nodes.size(),0));
  dp[0][0] = 1;
  for(char c : C){
    for(int p=0; p<dp[0].size(); p++){
      ull& to1 = dp[1][dp_edges[0][p]];
      to1 += dp[0][p]; if(to1 >= MOD) to1 -= MOD;
      if(c == '#') continue;
      if(dp_edges[1][p] == -1) continue;
      ull& to2 = dp[2][dp_edges[1][p]];
      to2 += dp[0][p]; if(to2 >= MOD) to2 -= MOD;
    }
    dp[0] = move(dp[1]);
    dp[1] = move(dp[2]);
    dp[2] = vector<ull>(dp_nodes.size(),0);
  }

  ull ans = 0;
  for(ull a : dp[0]) ans += a;
  ans %= MOD;
  printf("%llu\n",ans);
  return 0;
}
