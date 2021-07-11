import java.io.PrintWriter;
import java.util.Scanner;


/////////////////////////////////////
// Problem : https://atcoder.jp/contests/typical90/tasks/typical90_cl
// Time Complexity : O( K log K ( log K + log N ) )

public class Main {

	static final int MOD = 998244353;
	static final int NTTg = 3;

	long powm(long a, long i, long M) {
		if(i == 0) return 1;
		long r = powm(a*a%M,i/2,M);
		if(i%2 == 1) r=r*a%M;
		return r;
	}

	void NTT(long[] A, long g) {
		int N = A.length;
		for(int i=0, j=0; j<N; j++) {
			if(i < j) {
				long b = A[i];
				A[i] = A[j];
				A[j] = b;
			}
			for(int k=N>>1; k>(i^=k); k>>=1);
		}
		for(int i=1; i<N; i<<=1) {
			long q = powm(g,(MOD-1)/i/2,MOD), qj = 1;
			for(int j=0; j<i; j++) {
				for(int k=j; k<N; k+=i*2) {
					long l = A[k];
					long r = A[k+i] * qj % MOD;
					A[k] = l+r;
					if(A[k] >= MOD) A[k] -= MOD;
					A[k+i] = l+MOD-r;
					if(A[k+i] >= MOD) A[k+i] -= MOD;
				}
				qj = qj * q % MOD;
			}
		}
	}

	// find  \sum_{i=0}^\infty A^i
	//	         ( = 1 / (1-A) )
	// n : length of result
	// g : primitive root
	//
	// ref : https://opt-cp.com/fps-fast-algorithms/
	//
	// TIME : O( n log n )
	// SPACE : O( n )
	long[] powsumFPS(long[] A, int n, long g){
		if(n == 0){ return new long[] {}; }
		if(n == 1){ return new long[] {1}; }
		int N = 1; while(N<n) N*=2;
		int hN = N/2;
		long hInv[] = powsumFPS(A,hN,g);
		long tgA[] = new long[N];
		for(int i=0; i<Math.min(N,A.length); i++) tgA[i] = A[i];
		long ig = powm(g,MOD-2,MOD);
		NTT(tgA,g);
		long[] htInv = new long[N];
		for(int i=0; i<hN; i++) htInv[i] = hInv[i];
		NTT(htInv,g);
		long[] R = new long[N];
		for(int i=0; i<N; i++) R[i] = tgA[i] * htInv[i] % MOD;
		NTT(R,ig);
		for(int i=0; i<hN; i++) R[i] = R[hN+i];
		for(int i=hN; i<N; i++) R[i] = 0;
		NTT(R,g);
		long iNN = powm((long)N*N%MOD,MOD-2,MOD);
		for(int i=0; i<N; i++) R[i] = R[i] * htInv[i] % MOD * iNN % MOD;
		NTT(R,ig);
		long[] res = new long[n];
		for(int i=0; i<hN; i++) res[i] = hInv[i];
		for(int i=hN; i<n; i++) res[i] = R[i-hN];
		return res;
	}

	// find  1 / A
	//
	// n : length of result
	// g : primitive root
	//
	// TIME : O( n log n )
	// SPACE : O( n )
	long[] invFPS(long[] A, int n, long g) {
		long iA0 = powm(A[0],MOD-2,MOD);
		long[] xA = new long[Math.min(n, A.length)];
		for(int i=0; i<xA.length; i++) xA[i] = (MOD - A[i]) * iA0 % MOD;
		xA[0] = 0;
		xA = powsumFPS(xA,n,g);
		for(int i=0; i<xA.length; i++) xA[i] = xA[i] * iA0 % MOD;
		return xA;
	}

	long[] UP_BostanMori(long[] a, long g) {
		int n = a.length;
		long ig = powm(g,MOD-2,MOD);
		long[] A = new long[n];
		for(int i=0; i<n; i++) A[i] = a[i];
		NTT(A,ig);
		long invn = powm(n,MOD-2,MOD);
		for(int i=0; i<n; i++) A[i] = A[i] * invn % MOD;
		long w = powm(g,(MOD-1)/(2*n),MOD);
		long[] B = new long[n];
		long wp = 1;
		for(int i=0; i<n; i++) { B[i] = A[i] * wp % MOD; wp = wp * w % MOD; }
		NTT(B,g);
		long[] res = new long[n*2];
		for(int i=0; i<n; i++) res[i*2] = a[i];
		for(int i=0; i<n; i++) res[i*2+1] = B[i];
		return res;
	}

	// find  K-th term of {a_i}
	//  *  n = deg(A) ( = deg(C) )
	//  *  a_i = A[i]  ( 0 \leq i \lt |A| )
	//  *  a_i = \sum_{j=1}^{|A|} a_{i-j} C[j-1] ( n \leq i )
	//
	// returns A[K]
	//
	// faster with fft setting!
	//
	// TIME : O( n log n log K )
	// SPACE : O( n )
	//
	// ref : https://arxiv.org/abs/2008.08822
	//
	// I'm deeply grateful to Alin Bostan and Ryuhei Mori
	long Kth_term_of_linearly_recurrent_sequence_faster(
			long[] A,
			long[] C,
			long K,
			long g
	) {
		int n = A.length;
		int k = 0; while((1<<k) < 2*n+1) k++;
		int h2k = 1 << (k-1);
		long ig = powm(g,MOD-2,MOD);
		long w = powm(g,(MOD-1)/(1<<k),MOD);
		long iw = powm(w,MOD-2,MOD);
		long inv2 = powm(2,MOD-2,MOD);

		long[] P = new long[1<<k];
		for(int i=0; i<n; i++) P[i] = A[i];
		long[] Q = new long[1<<k];
		Q[0] = 1;
		for(int i=0; i<n; i++) Q[i+1] = (MOD - C[i]) % MOD;

		NTT(P,g);
		NTT(Q,g);

		while(K >= n) {

			long[] U = new long[1<<k];
			for(int i=0; i<(1<<k); i++) U[i] = P[i] * Q[i^h2k] % MOD;

			if(K % 2 == 0) {
				long[] Ue = new long[h2k];
				for(int i=0; i<h2k; i++) {
					Ue[i] = (U[i] + U[i+h2k]) * inv2 % MOD;
				}
				P = UP_BostanMori(Ue,g);
			}
			else {
				long[] Uo = new long[h2k];
				long wp = inv2;
				for(int i=0; i<h2k; i++) {
					Uo[i] = (U[i] + MOD - U[i+h2k]) * wp % MOD;
					wp = wp * iw % MOD;
				}
				P = UP_BostanMori(Uo,g);
			}

			long[] Qh = new long[h2k];
			for(int i=0; i<h2k; i++) Qh[i] = Q[i] * Q[i^h2k] % MOD;
			Q = UP_BostanMori(Qh,g);
			K /= 2;
		}

		NTT(P,ig);
		NTT(Q,ig);

		Q = invFPS(Q,(int)K+1,g);
		long res = 0;
		for(int i=0; i<=K; i++) res = (res + P[i] * Q[(int)K-i]) % MOD;
		return res;
	}

	long N;
	int K;

	long[] dpStep(long[] prev, int nxLen, long multiplier){
		long[] res = new long[nxLen+1];
		long imulti = powm(multiplier,MOD-2,MOD);
		for(int i=0; i<Math.min(nxLen,prev.length); i++) res[i+1] = prev[i] * multiplier % MOD;
		long[] buf = powsumFPS(res,nxLen+2,NTTg);
		for(int i=0; i<=nxLen; i++) res[i] = buf[i+1] * imulti % MOD;
		return res;
	}

	void solve() {
		Scanner sc = new Scanner(System.in);
		PrintWriter wt = new PrintWriter(System.out);

		N = sc.nextLong();
		K = sc.nextInt();

		int[] steps = new int[K+1];
		for(int n=1; n<=K; n++) steps[K/n]++;
		long[] dp = {1};
		for(int l=1; l<=K; l++){
			if(steps[l] == 0) continue;
			dp = dpStep(dp,l,steps[l]);
		}

		long[] recurrent_A = new long[dp.length];
		recurrent_A[dp.length-1] = 1;
		long ans = Kth_term_of_linearly_recurrent_sequence_faster(recurrent_A,dp,N+dp.length,NTTg);
		wt.println(ans);

		wt.flush();
		sc.close();
	}

	public static void main(String[] args) {
		Main solver = new Main();
		solver.solve();
	}
}
