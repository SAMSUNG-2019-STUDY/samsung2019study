package study191016;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class MainA낚시왕 {

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine().trim());
		int R = Integer.parseInt(st.nextToken());
		int C = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());
		int r, c, s, d, z, sum, dd, rr, cc, ss;
		int[][][] arr = new int[R + 1][C + 1][2];
		int[][] shark = new int[M][6];
		int[][] nd = {{}, {-1, 0}, {1, 0}, {0, 1}, {0, -1}};
		for(int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine().trim());
			r = Integer.parseInt(st.nextToken());
			c = Integer.parseInt(st.nextToken());
			s = Integer.parseInt(st.nextToken());
			d = Integer.parseInt(st.nextToken());
			z = Integer.parseInt(st.nextToken());
			arr[r][c][1] = i;
			shark[i][1] = r;
			shark[i][2] = c;
			shark[i][3] = s;
			shark[i][4] = d;
			shark[i][5] = z;
		}
		sum = 0;
		for(int i = 1; i <= C; i++) {
			for(int j = 1; j <= R; j++) {
				if(arr[j][i][0] == i - 1 && arr[j][i][1] < M) {
					shark[arr[j][i][1]][0] = -1;
					sum += shark[arr[j][i][1]][5];
					break;
				}
			}
			for(int j = 0; j < M; j++) {
				if(shark[j][0] != -1) {
					ss = shark[j][3];
					dd = shark[j][4];
					rr = shark[j][1] + ss * nd[dd][0];
					cc = shark[j][2] + ss * nd[dd][1];
					while(rr < 1 || rr > R || cc < 1 || cc > C) {
						if(shark[j][4] == 1) {
							shark[j][4] = 2;
						} else if(shark[j][4] == 2) {
							shark[j][4] = 1;
						} else if(shark[j][4] == 3) {
							shark[j][4] = 4;
						} else if(shark[j][4] == 4) {
							shark[j][4] = 3;
						}
						if(rr < 1) {
							rr = -rr + 2;
						} else if(rr > R) {
							rr = R + R - rr;
						} else if(cc < 1) {
							cc = -cc + 2;
						} else if(cc > C) {
							cc = C + C - cc;
						}
					}
					shark[j][1] = rr;
					shark[j][2] = cc;
					if(arr[rr][cc][0] == i) {
						if(shark[j][5] > shark[arr[rr][cc][1]][5]) {
							shark[arr[rr][cc][1]][0] = -1;
							arr[rr][cc][1] = j;
						}
					} else {
						arr[rr][cc][0] = i;
						arr[rr][cc][1] = j;
					}
				}
			}
		}
		System.out.println(sum);
	}

}
