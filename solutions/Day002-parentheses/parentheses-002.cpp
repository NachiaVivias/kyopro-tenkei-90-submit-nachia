#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i,n) for(int i=0; i<(n); i++)

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/002.jpg
// Time Complexity : O( 2^N + N * #ans )

/////////////////////////////////////
// input
//
// N
//

// O(N 2^N) -> O(2^N) の常套手段
// O(N) 時間かけていた判定を、前からちょっとずつやる

struct SearchNode{
  int searchBit;
  int depth;
  char nextChar;
};

int N;

int main() {
  scanf("%d",&N);

  // bit 全探索 -> 深さ優先探索
  stack<SearchNode> Q;
  string buf(N,'(');
  Q.push({N-1,0,'('});
  Q.push({N-1,0,')'});
  while(Q.size()){
    auto p = Q.top(); Q.pop();
    if(p.depth < 0) continue;
    buf[N-1-p.searchBit] = p.nextChar;
    int nextDepth = p.depth;
    if(p.nextChar=='(') nextDepth++;
    if(p.nextChar==')') nextDepth--;
    if(nextDepth > p.searchBit) continue;
    if(p.searchBit==0){
      if(nextDepth==0){
        printf(buf.c_str());
        printf("\n");
      }
    }
    else{
      // 後に入れたほうが先に探索される
      Q.push({p.searchBit-1,nextDepth,')'});
      Q.push({p.searchBit-1,nextDepth,'('});
    }
  }

  return 0;
}
