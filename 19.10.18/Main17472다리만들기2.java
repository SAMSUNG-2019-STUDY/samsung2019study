package study191018;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main17472다리만들기2 {

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());
		int[][] map = new int[N][M];
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine().trim());
			for(int j = 0; j < M; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		int[][] d = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
		int[][] arr = new int[N][M];
		LinkedList<int[]> q = new LinkedList<>();
		int num = 1, r, c;
		int[] cur;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				if(map[i][j] == 1 && arr[i][j] == 0) {
					q.offer(new int[] {i, j});
					arr[i][j] = num;
					while(!q.isEmpty()) {
						cur = q.poll();
						for(int k = 0; k < 4; k++) {
							r = cur[0] + d[k][0];
							c = cur[1] + d[k][1];
							if(r >= 0 && r < N && c >= 0 && c < M && map[r][c] == 1 && arr[r][c] == 0) {
								q.offer(new int[] {r, c});
								arr[r][c] = num;
							}
						}
					}
					num++;
				}
			}
		}
		int[][] edge = new int[num][num];
		int s, si = 0;
		for(int i = 0; i < N; i++) {
			s = -1;
			for(int j = 0; j < M; j++) {
				if(arr[i][j] != 0) {
					if(s == -1) {
						s = arr[i][j];
						si = j;
					} else {
						if(j - si - 1 > 1) {
							if(edge[s][arr[i][j]] == 0) {
								edge[s][arr[i][j]] = j - si - 1;
								edge[arr[i][j]][s] = edge[s][arr[i][j]];
							} else {
								edge[s][arr[i][j]] = Math.min(edge[s][arr[i][j]], j - si - 1);
								edge[arr[i][j]][s] = edge[s][arr[i][j]];
							}
						}
						s = arr[i][j];
						si = j;
					}
				}
			}
		}
		for(int i = 0; i < M; i++) {
			s = -1;
			for(int j = 0; j < N; j++) {
				if(arr[j][i] != 0) {
					if(s == -1) {
						s = arr[j][i];
						si = j;
					} else {
						if(j - si - 1 > 1) {
							if(edge[s][arr[j][i]] == 0) {
								edge[s][arr[j][i]] = j - si - 1;
								edge[arr[j][i]][s] = edge[s][arr[j][i]];
							} else {
								edge[s][arr[j][i]] = Math.min(edge[s][arr[j][i]], j - si - 1);
								edge[arr[j][i]][s] = edge[s][arr[j][i]];
							}
						}
						s = arr[j][i];
						si = j;
					}
				}
			}
		}
		PriorityQueue<int[]> pq = new PriorityQueue<>(new Comparator<int[]>() {
			@Override
			public int compare(int[] o1, int[] o2) {
				return Integer.compare(o1[2], o2[2]);
			}
		});
		for(int i = 1; i < num; i++) {
			for(int j = i + 1; j < num; j++) {
				if(edge[i][j] != 0) {
					pq.offer(new int[] {i, j, edge[i][j]});
				}
			}
		}
		int count = 0, a, b, sum = 0;
		int[] p = new int[num];
		while(!pq.isEmpty()) {
			cur = pq.poll();
			a = cur[0];
			b = cur[1];
			while(p[a] != 0) {
				a = p[a];
			}
			while(p[b] != 0) {
				b = p[b];
			}
			if(a != b) {
				p[b] = a;
				sum += cur[2];
				count++;
				if(count == num - 2) {
					break;
				}
			}
		}
		if(count < num - 2) {
			System.out.println(-1);
		} else {
			System.out.println(sum);
		}
	}

}
