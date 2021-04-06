#include <stdio.h>
#include <set>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/007.jpg
// Time Complexity : O( (N + Q) log N )

/////////////////////////////////////
// input
//
// N
// A[1] A[2] ... A[K]
// Q
// B[1]
// B[2]
//  :
// B[Q]
//

/////////////////////////////////////
// output
//
// separated by line break
//

// A を昇順ソートしたとして、
// B[i] より大きい A[i] のうち最小のものと、その 1 個手前しか見なくてよい。

int N;
set<ll> A;
int Q;

int main(){
  scanf("%d",&N);
  for(int i=0; i<N; i++){
    int a; scanf("%d",&a);
    A.insert(a);
  }

  // B[i] が どの A[i] より大きい時などを考慮
  A.insert(-11001001001);
  A.insert(11001001001);

  scanf("%d",&Q);
  for(int i=0; i<Q; i++){
    int b; scanf("%d",&b);
    auto r_itr = A.upper_bound(b); // 大きいもののうち最小
    auto l_itr = r_itr; l_itr--; // その 1 個手前
    ll ans = min(b-*l_itr,*r_itr-b);
    printf("%lld\n",ans);
  }
  return 0;
}
