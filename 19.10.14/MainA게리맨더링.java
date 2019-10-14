package study191014;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class MainA게리맨더링 {

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine().trim());
		int[] arr = new int[N];
		StringTokenizer st = new StringTokenizer(br.readLine().trim());
		for(int i = 0; i < N; i++) {
			arr[i] = Integer.parseInt(st.nextToken());
		}
		ArrayList<Integer>[] adj = (ArrayList<Integer>[])new ArrayList[N];
		for(int i = 0; i < N; i++) {
			adj[i] = new ArrayList<>();
			st = new StringTokenizer(br.readLine().trim());
			for(int j = 0, size = Integer.parseInt(st.nextToken()); j < size; j++) {
				adj[i].add(Integer.parseInt(st.nextToken()) - 1);
			}
		}
		int visit = 0, cur, min = Integer.MAX_VALUE;
		int[] sum = new int[2];
		boolean[] chk = new boolean[2];
		LinkedList<Integer> q = new LinkedList<>();
		for(int i = 1, size = (1 << N) - 1; i < size; i++) {
			visit = 0;
			q.clear();
			sum[0] = 0;
			sum[1] = 0;
			chk[0] = false;
			chk[1] = false;
			for(int j = 0; j < N; j++) {
				if(((1 << j) & i) == 0 && !chk[0]) {
					q.offer(j);
					visit |= (1 << j);
					sum[0] += arr[j];
					while(!q.isEmpty()) {
						cur = q.poll();
						for(int next : adj[cur]) {
							if(((1 << next) & i) == 0 && ((1 << next) & visit) == 0) {
								q.offer(next);
								visit |= (1 << next);
								sum[0] += arr[next];
							}
						}
					}
					chk[0] = true;
					if(chk[1]) {
						break;
					}
				} else if(((1 << j) & i) != 0 && !chk[1]) {
					q.offer(j);
					visit |= (1 << j);
					sum[1] += arr[j];
					while(!q.isEmpty()) {
						cur = q.poll();
						for(int next : adj[cur]) {
							if(((1 << next) & i) != 0 && ((1 << next) & visit) == 0) {
								q.offer(next);
								visit |= (1 << next);
								sum[1] += arr[next];
							}
						}
					}
					chk[1] = true;
					if(chk[0]) {
						break;
					}
				}
			}
			if(visit == ((1 << N) - 1)) {
				min = Math.min(min, Math.abs(sum[0] - sum[1]));
			}
		}
		if(min == Integer.MAX_VALUE) {
			System.out.println(-1);
		} else {
			System.out.println(min);
		}
	}

}
