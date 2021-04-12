#include <vector>
#include <random>
#include <cassert>
#include <unordered_map>

namespace generatorNS{

  std::mt19937_64 mt;

  // generate x : l <= x <= r
  unsigned long long random_unsigned(unsigned long long l,unsigned long long r){
    assert(l<=r);
    r-=l;
    auto res = mt();
    if(res<=r) return res+l;
    unsigned long long d = r+1;
    unsigned long long max_valid = 0xffffffffffffffff/d*d;
    while(true){
      auto res = mt();
      if(res<=max_valid) break;
    }
    return res%d+l;
  }

  // generate x : l <= x <= r
  long long random_signed(long long l,long long r){
    assert(l<=r);
    unsigned long long unsigned_l = (unsigned long long)l ^ (1ull<<63);
    unsigned long long unsigned_r = (unsigned long long)r ^ (1ull<<63);
    unsigned long long unsigned_res = random_unsigned(unsigned_l,unsigned_r) ^ (1ull<<63);
    return (long long)unsigned_res;
  }

#ifdef GENERATOR_LEGACY_FLOAT

  double random_real(double l,double r){
    static const double scale = pow(0.5,64);
    auto randint = random_unsigned(0,0xffffffffffffffff);
    auto rand01 = (double)randint * scale;
    return l + rand01*(r-l);
  }

#endif

  unsigned long long mt_seed(unsigned long long seed){
    mt.seed(seed);
    return seed;
  }


  // permute x : n_left <= x <= n_right
  // output r from the front
  std::vector<long long> random_nPr(long long n_left,long long n_right,long long r){
    long long n = n_right-n_left;

    assert(n>=0);
    assert(r<=(1ll<<27));
    if(r==0) return {};  
    assert(n>=r-1);

    if(n==0) return {};
    std::vector<long long> V;
    std::unordered_map<long long,long long> G;
    for(int i=0; i<r; i++){
      long long p = random_signed(i,n);
      long long x = p - G[p];
      V.push_back(x);
      G[p] = p - (i - G[i]);
    }

    for(long long& v : V) v+=n_left;
    return move(V);
  }



  // V[i] := V[perm[i]]
  // using swap
  template<class E,class PermInt_t>
  void permute_inplace(std::vector<E>& V,std::vector<PermInt_t> perm){
    assert(V.size() == perm.size());
    int N=V.size();
    for(int i=0; i<N; i++){
      int p=i;
      while(perm[p]!=i){
        assert(0 <= perm[p] && perm[p] < N);
        assert(perm[p] != perm[perm[p]]);
        std::swap(V[p],V[perm[p]]);
        /* std::swap(p,perm[p]); */ { int pbuf = p; p = perm[p]; perm[p] = pbuf; }
      }
    }
  }

  template<class E>
  std::vector<E> shuffle(const std::vector<E>& V){
    int N=V.size();
    auto P = random_nPr(0,N-1,N);
    std::vector<E> res;
    res.reserve(N);
    for(int i=0; i<N; i++) res.push_back(V[P[i]]);
  }

  // shuffle using swap
  template<class E>
  void shuffle_inplace(std::vector<E>& V){
    int N=V.size();
    permute_inplace(V,random_nPr(0,N-1,N));
  }

}
