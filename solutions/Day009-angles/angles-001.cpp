#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/////////////////////////////////////
// Problem : https://github.com/E869120/kyopro_educational_90/blob/main/problem/009.jpg
// Time Complexity : O( N^2 log N )

/////////////////////////////////////
// input
//
// N
// X[1] Y[1]
// X[2] Y[2]
//  :
// X[N} Y[N]
//

struct Vec2D{
  ll x,y;
  static ll dot(Vec2D l, Vec2D r);
  static ll cross(Vec2D l, Vec2D r);
  static double cos2(Vec2D x, Vec2D p);
  static double atan2(Vec2D x);
};

Vec2D operator-(Vec2D l, Vec2D r){ return { l.x-r.x, l.y-r.y }; }
ll Vec2D::dot(Vec2D l, Vec2D r){ return l.x*r.x + l.y*r.y; }
ll Vec2D::cross(Vec2D l, Vec2D r){ return l.x*r.y - l.y*r.x; }
double Vec2D::cos2(Vec2D l, Vec2D r){
  double absl = dot(l,l);
  double absr = dot(r,r);
  double crs = cross(l,r);
  return crs / (absl * absr);
}
double Vec2D::atan2(Vec2D x){
  return std::atan2(x.x,x.y);
}

int N;
vector<Vec2D> P;

const double PI = acos(-1.0);

int main() {
  scanf("%d",&N);
  P.resize(N);
  for(int i=0; i<N; i++){
    int x,y; scanf("%d%d",&x,&y);
    P[i] = {x,y};
  }

  double ans = 0.0;

  for(int s=0; s<N; s++){
    vector<Vec2D> difs;
    vector<double> args;
    for(int i=0; i<N; i++){
      if(i!=s) difs.push_back(P[i]-P[s]);
    }
    auto sort_Vec2D_by_args = [](Vec2D l,Vec2D r)->bool{
      return Vec2D::atan2(l) < Vec2D::atan2(r);
    };
    sort(difs.begin(),difs.end(),sort_Vec2D_by_args);
    args.resize(N-1);
    
    for(int i=0; i<N-1; i++){
      args[i] = Vec2D::atan2(difs[i]) / PI * 180.0;
    }

    // 1 周した後扱いの点
    for(int i=0; i<N; i++){
      difs.push_back(difs[i]);
      args.push_back(args[i]+360.0);
    }

    int rp=0;
    for(int lp=0; lp<N-1; lp++){
      while(args[rp]-args[lp] < 180.0) rp++;
      ans = max(ans, args[rp-1]-args[lp]);
      ans = max(ans, -(args[rp]-args[lp]-180.0)+180.0);
    }
  }

  printf("%.10f\n",ans);
  return 0;
}
