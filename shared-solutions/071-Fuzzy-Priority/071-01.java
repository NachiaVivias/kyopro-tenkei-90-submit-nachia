import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

	class StackNode{
		int i;
		int r;
		StackNode(int new_i, int new_r){
			i = new_i;
			r = new_r;
		}
	}

	int N;
	int M;
	int K;
	int A[];
	int B[];
	int E[][];
	int inIdx[];

	void solve() {
		Scanner sc = new Scanner(System.in);
		PrintWriter wt = new PrintWriter(System.out);

		N = sc.nextInt();
		M = sc.nextInt();
		K = sc.nextInt();
		A = new int[M];
		B = new int[M];
		for(int i=0; i<M; i++) {
			A[i] = sc.nextInt(); A[i]--;
			B[i] = sc.nextInt(); B[i]--;
		}

		inIdx = new int[N];
		E = new int[N][];
		{
			ArrayList<ArrayList<Integer>> Ebuf = new ArrayList<>(N);
			for(int i=0; i<N; i++) Ebuf.add(new ArrayList<>(0));
			for(int i=0; i<M; i++) {
				Ebuf.get(A[i]).add(B[i]);
				inIdx[B[i]]++;
			}
			for(int i=0; i<N; i++) {
				E[i] = new int[Ebuf.get(i).size()];
				for(int j=0; j<Ebuf.get(i).size(); j++) {
					E[i][j] = Ebuf.get(i).get(j);
				}
			}
		}

		ArrayList<Integer> topological_que = new ArrayList<>(0);
		ArrayList<StackNode> recursive_stack = new ArrayList<>(0);
		ArrayList<ArrayList<Integer>> ans = new ArrayList<>(0);
		for(int i=0; i<N; i++) {
			if(inIdx[i] == 0) topological_que.add(i);
		}
		recursive_stack.add(new StackNode(0,topological_que.size()));
		while(topological_que.size() < N) topological_que.add(0);

		while(recursive_stack.size() != 0) {
			int i = recursive_stack.size() - 1;
			StackNode st = recursive_stack.get(i);
			if(i == N) {
				ans.add(new ArrayList<>(topological_que));
				recursive_stack.remove(recursive_stack.size()-1);
				if(!recursive_stack.isEmpty()) {
					int prei = i-1;
					StackNode pres = recursive_stack.get(prei);
					for(int e : E[topological_que.get(prei)]) inIdx[e]++;
					int swapbuf = topological_que.get(prei);
					topological_que.set(prei,topological_que.get(pres.i));
					topological_que.set(pres.i,swapbuf);
					pres.i++;
				}
				continue;
			}
			if(st.r == i) {
				// no valid answer
				break;
			}
			if(st.i >= st.r) {
				recursive_stack.remove(recursive_stack.size()-1);
				if(!recursive_stack.isEmpty()) {
					int prei = i-1;
					StackNode pres = recursive_stack.get(prei);
					for(int e : E[topological_que.get(prei)]) inIdx[e]++;
					int swapbuf = topological_que.get(prei);
					topological_que.set(prei,topological_que.get(pres.i));
					topological_que.set(pres.i,swapbuf);
					pres.i++;
				}
				continue;
			}
			if(ans.size() == K) {
				break;
			}

			StackNode pres = recursive_stack.get(recursive_stack.size()-1);
			int que_back = pres.r;
			int swapbuf = topological_que.get(i);
			topological_que.set(i,topological_que.get(pres.i));
			topological_que.set(pres.i,swapbuf);
			int p = topological_que.get(i);
			for(int e : E[p]) if(--inIdx[e] == 0) {
				topological_que.set(que_back++,e);
			}
			recursive_stack.add(new StackNode(i+1,que_back));
		}

		if(ans.size() < K) {
			wt.println(-1);
		}
		else {
			for(int k=0; k<K; k++) {
				for(int i=0; i<N; i++) {
					if(i != 0) wt.print(' ');
					wt.print(ans.get(k).get(i)+1);
				}
				wt.println();
			}
		}
		wt.flush();

		sc.close();
	}

	public static void main(String[] args) {
		Main solver = new Main();
		solver.solve();
	}
}
