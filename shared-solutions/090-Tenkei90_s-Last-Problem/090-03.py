

# Problem : https://atcoder.jp/contests/typical90/tasks/typical90_cl
# Time Complexity : O( K log K ( log K + log N ) )


MOD = 998244353
ntt_perm = [[0]]

def ntt(A,g):
  logN = 0
  while (1 << logN) < len(A) : logN += 1
  N = 1 << logN
  A += [0] * (N-len(A))
  while len(ntt_perm) < logN + 1: ntt_perm.append([2*x for x in ntt_perm[-1]] + [2*x+1 for x in ntt_perm[-1]])
  X = ntt_perm[logN]
  for i in range(N):
    if i < X[i]: A[i],A[X[i]] = A[X[i]],A[i]
  i = 1
  while i < N:
    q = pow(g,(MOD-1)//i//2,MOD)
    qj = 1
    for j in range(i):
      for k in range(j,N+j,i*2):
        A[k], A[k+i] = (A[k] + A[k+i] * qj) % MOD , (A[k] - A[k+i] * qj) % MOD
      qj = qj * q % MOD
    i *= 2


# find  \sum_{i=0}^\infty A^i
#         ( = 1 / (1-A) )
# n : length of result
# g : primitive root
#
# ref : https://opt-cp.com/fps-fast-algorithms/
# 
# TIME : O( n log n )
# SPACE : O( n )
def powsumFPS(A,n,g):
  if n == 0: return []
  if n == 1: return [1]
  N = 1
  while N<n: N *= 2
  hN = N//2
  hInv = powsumFPS(A,hN,g)
  tgA = [0] * N
  for i in range(min(N,len(A))): tgA[i] = A[i]
  ig = pow(g,MOD-2,MOD)
  ntt(tgA,g)
  htInv = [x for x in hInv] + [0] * hN
  ntt(htInv,g)
  R = [tgA[i] * htInv[i] % MOD for i in range(N)]
  ntt(R,ig)
  R = R[hN:N] + [0] * hN
  ntt(R,g)
  iNN = pow(N*N%MOD,MOD-2,MOD)
  R = [R[i] * htInv[i] % MOD * iNN % MOD for i in range(N)]
  ntt(R,ig)
  return hInv + R[:(n-hN)]


# find  1 / A
#
# n : length of result
# g : primitive root
# 
# TIME : O( n log n )
# SPACE : O( n )
def invFPS(A,n,g):
  A0 = A[0]
  iA0 = pow(A0,MOD-2,MOD)
  xA = [(MOD - A[i]) * iA0 % MOD for i in range(min(n,len(A)))]
  xA[0] = 0
  xA = powsumFPS(xA,n,g)
  for i in range(len(xA)): xA[i] = xA[i] * iA0 % MOD
  return xA


# find  K-th term of {a_i}
#  *  n = deg(A) ( = deg(C) )
#  *  a_i = A[i]  ( 0 \leq i \lt |A| )
#  *  a_i = \sum_{j=1}^{|A|} a_{i-j} C[j-1] ( n \leq i )
#
# returns A[K]
#
# faster with fft setting!
#
# TIME : O( n log n log K )
# SPACE : O( n )
#
# ref : https://arxiv.org/abs/2008.08822
#
# I'm deeply grateful to Alin Bostan and Ryuhei Mori
def Bostan_Mori(A,C,K,g):
  n = len(A)
  k = 1
  while k < 2*n+1: k *= 2
  hk = k // 2
  ig = pow(g,MOD-2,MOD)
  w = pow(g,(MOD-1)//k,MOD)
  iw = pow(w,MOD-2,MOD)
  inv2 = pow(2,MOD-2,MOD)
  
  P = [0] * k
  for i in range(n): P[i] = A[i]
  Q = [0] * k
  Q[0] = 1
  for i in range(n): Q[i+1] = (MOD - C[i]) % MOD

  ntt(P,g)
  ntt(Q,g)

  def UP(a):
    n = len(a)
    A = [x for x in a]
    ntt(A,ig)
    invn = pow(n,MOD-2,MOD)
    for i in range(n): A[i] = A[i] * invn % MOD
    w = pow(g,(MOD-1)//(2*n),MOD)
    B = [0] * n
    wp = 1
    for i in range(n):
      B[i] = A[i] * wp % MOD
      wp = wp * w % MOD
    ntt(B,g)
    res = [0] * (n*2)
    for i in range(n): res[i*2] = a[i]
    for i in range(n): res[i*2+1] = B[i]
    return res

  while K >= n:

    U = [P[i] * Q[i^hk] % MOD for i in range(k)]
    
    if K % 2 == 0:
      Ue = [(U[i]+U[i+hk]) * inv2 % MOD for i in range(hk)]
      P = UP(Ue)
    else:
      Uo = [0] * hk
      wp = inv2
      for i in range(hk):
        Uo[i] = (U[i] + MOD - U[i+hk]) * wp % MOD
        wp = wp * iw % MOD
      P = UP(Uo)
    
    A = [Q[i] * Q[i^hk] % MOD for i in range(hk)]
    Q = UP(A)
    K //= 2

  ntt(P,ig)
  ntt(Q,ig)
  
  Q = invFPS(Q,K+1,g)
  res = sum([P[i] * Q[K-i] % MOD for i in range(K+1)]) % MOD
  return res

NTTg = 3


def dpStep(prev,nxLen,multiplier):
  res = [0] * (nxLen+1)
  imulti = pow(multiplier,MOD-2,MOD)
  for i in range(min(nxLen,len(prev))): res[i+1] = prev[i] * multiplier % MOD
  res = [x * imulti % MOD for x in powsumFPS(res,nxLen+2,NTTg)]
  return res[1:]


N,K = map(int,input().split())
steps = [0] * (K+1)
for k in range(1,K+1): steps[min(N,K//k)] += 1
dp = [1]
for l in range(1,K+1):
  if steps[l] == 0: continue
  dp = dpStep(dp,l,steps[l])

recurrent_A = [0] * (len(dp)-1) + [1]
res = Bostan_Mori(recurrent_A,dp,N+len(dp),NTTg)
print(res)
