
#include <iostream>
#include <string>
#include <queue>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/006.jpg
// Time Complexity : O( |S| log |S| )

/////////////////////////////////////
// input
//
// S
// K
//

// 貪欲法における優先度を優先度キューで管理

struct PriorityNode{
  char c;
  int i;
};

bool operator<(PriorityNode l, PriorityNode r){
  if(l.c != r.c) return l.c > r.c;
  return l.i > r.i;
}

string S;
int K;

int lenS;

priority_queue<PriorityNode> Q;
string ans;

int main() {
  cin >> S;
  cin >> K;
  lenS = S.size();
  int l = -1;
  int r = lenS - K;
  for(int k=0; k<K; k++){
    // 1 文字とると取れる範囲が 1 文字伸びる
    r++;
    for(int i=0; i<r; i++) Q.push({S[i],i});
    while(Q.size()){
      auto q = Q.top(); Q.pop();
      if(q.i <= l) continue; // 前に取った文字と同じかそれより前
      ans.push_back(S[q.i]);
      l = q.i + 1;
      break;
    }
  }
  cout << ans << "\n";
  return 0;
}
