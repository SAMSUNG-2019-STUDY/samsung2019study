package study191015;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class MainA경사로 {

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine().trim());
		int N = Integer.parseInt(st.nextToken());
		int L = Integer.parseInt(st.nextToken());
		int[][] arr = new int[N][N];
		boolean chkh, down;
		boolean[] chkv = new boolean[N], downv = new boolean[N];
		int count, road = 0;
		int[] countv = new int[N];
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine().trim());
			chkh = true;
			count = 1;
			down = false;
			for(int j = 0; j < N; j++) {
				if(i == 0) {
					chkv[j] = true;
					countv[j] = 1;
				}
				arr[i][j] = Integer.parseInt(st.nextToken());
				if(i > 0 && chkv[j]) {
					if(Math.abs(arr[i - 1][j] - arr[i][j]) > 1) {
						chkv[j] = false;
					} else if(arr[i][j] > arr[i - 1][j]) {
						if(downv[j]) {
							chkv[j] = false;
						} else {
							if(countv[j] >= L) {
								countv[j] = 1;
							} else {
								chkv[j] = false;
							}
						}
					} else if(arr[i][j] < arr[i - 1][j]) {
						if(downv[j]) {
							chkv[j] = false;
						} else {
							if(L == 1) {
								countv[j] = 0;
							} else {
								if(i == N - 1) {
									chkv[j] = false;
								} else {
									downv[j] = true;
									countv[j] = 1;
								}
							}
						}
					} else {
						countv[j]++;
						if(downv[j] && countv[j] == L) {
							countv[j] = 0;
							downv[j] = false;
						} else if(downv[j] && i == N - 1) {
							chkv[j] = false;
						}
					}
					if(i == N - 1) {
						if(chkv[j]) {
							road++;
						}
					}
				}
				
				if(j > 0 && chkh) {
					if(Math.abs(arr[i][j - 1] - arr[i][j]) > 1) {
						chkh = false;
					} else if(arr[i][j] > arr[i][j - 1]) {
						if(down) {
							chkh = false;
						} else {
							if(count >= L) {
								count = 1;
							} else {
								chkh = false;
							}
						}
					} else if(arr[i][j] < arr[i][j - 1]) {
						if(down) {
							chkh = false;
						} else {
							if(L == 1) {
								count = 0;
							} else {
								if(j == N - 1) {
									chkh = false;
								} else {
									down = true;
									count = 1;
								}
							}
						}
					} else {
						count++;
						if(down && count == L) {
							count = 0;
							down = false;
						} else if(down && j == N - 1) {
							chkh = false;
						}
					}
				}
			}
			if(chkh) {
				road++;
			}
		}
		System.out.println(road);
	}

}
