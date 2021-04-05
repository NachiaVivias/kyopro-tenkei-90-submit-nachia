
#include <iostream>
#include <string>
#include <queue>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/006.jpg
// Time Complexity : O( |S| + C ) ( C は文字の種類数 )

/////////////////////////////////////
// input
//
// S
// K
//

// 貪欲法における優先度は優先度キューで管理できる
// この問題なら、優先度キューの代わりに配列に持っても、
// その時点で最小の値より小さい値の挿入を高々 1 回にできる

string S;
int K;

int lenS;

// Q[i] は文字種 i が S 中にある位置が、昇順に並ぶ
vector<queue<int>> Q;
string ans;

int main() {
  cin >> S;
  cin >> K;
  lenS = S.size();
  int l = -1;
  int r = lenS - K;
  Q.resize(256);
  for(int i=0; i<r; i++){
    Q[S[i]].push(i);
  }
  int p = 0; // 取れる文字に p より小さい文字はない
  for(int k=0; k<K; k++){
    // 1 文字とると取れる範囲が 1 文字伸びる
    if(S[r] < p){
      // ぎりぎりの位置の文字を取りたい -> その後ろは全部取る
      ans += S.substr(r);
      break;
    }
    Q[S[r]].push(r);
    r++;
    while(true){
      while(Q[p].empty() ? false : (Q[p].front() <= l)) Q[p].pop();
      if(Q[p].empty()){ p++; continue; }
      ans.push_back(S[Q[p].front()]);
      l = Q[p].front();
      break;
    }
  }
  cout << ans << "\n";
  return 0;
}
