package study191011;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main1배열돌리기4 {
	
	public static int N, M, K, min = Integer.MAX_VALUE, tmp, r, c, s;
	public static int[][] A, rot, tmpA;
	public static int[] p;
	public static boolean[] visit;

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine().trim());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		A = new int[N + 1][M + 1];
		tmpA = new int[N + 1][];
		rot = new int[K][3];
		p = new int[K];
		visit = new boolean[K];
		for(int i = 1; i <= N; i++) {
			st = new StringTokenizer(br.readLine().trim());
			for(int j = 1; j <= M; j++) {
				A[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		for(int i = 0; i < K; i++) {
			st = new StringTokenizer(br.readLine().trim());
			r = Integer.parseInt(st.nextToken());
			c = Integer.parseInt(st.nextToken());
			s = Integer.parseInt(st.nextToken());
			rot[i][0] = r;
			rot[i][1] = c;
			rot[i][2] = s;
		}
		go(0);
		System.out.println(min);
	}
	
	public static void go(int index) {
		if(index == K) {
			for(int i = 1; i <= N; i++) {
				tmpA[i] = A[i].clone();
			}
			for(int i = 0; i < K; i++) {
				r = rot[p[i]][0];
				c = rot[p[i]][1];
				s = rot[p[i]][2];
				for(int j = 1; j <= s; j++) {
					tmp = tmpA[r - j][c - j];
					for(int k = r - j; k < r + j; k++) {
						tmpA[k][c - j] = tmpA[k + 1][c - j];
					}
					for(int k = c - j; k < c + j; k++) {
						tmpA[r + j][k] = tmpA[r + j][k + 1];
					}
					for(int k = r + j; k > r - j; k--) {
						tmpA[k][c + j] = tmpA[k - 1][c + j];
					}
					for(int k = c + j; k > c - j; k--) {
						tmpA[r - j][k] = tmpA[r - j][k - 1];
					}
					tmpA[r - j][c - j + 1] = tmp;
				}
			}
			for(int i = 1; i <= N; i++) {
				tmp = 0;
				for(int j = 1; j <= M; j++) {
					tmp += tmpA[i][j];
				}
				min = Math.min(min, tmp);
			}
			return;
		}
		for(int i = 0; i < K; i++) {
			if(!visit[i]) {
				p[index] = i;
				visit[i] = true;
				go(index + 1);
				visit[i] = false;
			}
		}
	}

}
