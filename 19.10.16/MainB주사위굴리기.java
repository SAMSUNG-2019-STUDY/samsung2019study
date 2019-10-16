package study191016;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class MainB주사위굴리기 {

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine().trim());
		int N = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		int y = Integer.parseInt(st.nextToken());
		int K = Integer.parseInt(st.nextToken());
		int[][] arr = new int[N][M];
		int c, nx, ny, tmp;
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine().trim());
			for(int j = 0; j < M; j++) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		st = new StringTokenizer(br.readLine().trim());
		int[] dice = {0, 0, 0, 0, 0, 0};
		for(int i = 0; i < K; i++) {
			c = Integer.parseInt(st.nextToken());
			switch(c) {
			case 1:
				nx = x;
				ny = y + 1;
				if(nx >= 0 && nx < N && ny >= 0 && ny < M) {
					tmp = dice[0];
					dice[0] = dice[1];
					dice[1] = dice[5];
					dice[5] = dice[2];
					dice[2] = tmp;
					if(arr[nx][ny] == 0) {
						arr[nx][ny] = dice[5];
					} else {
						dice[5] = arr[nx][ny];
						arr[nx][ny] = 0;
					}
					System.out.println(dice[0]);
					x = nx;
					y = ny;
				}
				break;
			case 2:
				nx = x;
				ny = y - 1;
				if(nx >= 0 && nx < N && ny >= 0 && ny < M) {
					tmp = dice[0];
					dice[0] = dice[2];
					dice[2] = dice[5];
					dice[5] = dice[1];
					dice[1] = tmp;
					if(arr[nx][ny] == 0) {
						arr[nx][ny] = dice[5];
					} else {
						dice[5] = arr[nx][ny];
						arr[nx][ny] = 0;
					}
					System.out.println(dice[0]);
					x = nx;
					y = ny;
				}
				break;
			case 3:
				nx = x - 1;
				ny = y;
				if(nx >= 0 && nx < N && ny >= 0 && ny < M) {
					tmp = dice[0];
					dice[0] = dice[4];
					dice[4] = dice[5];
					dice[5] = dice[3];
					dice[3] = tmp;
					if(arr[nx][ny] == 0) {
						arr[nx][ny] = dice[5];
					} else {
						dice[5] = arr[nx][ny];
						arr[nx][ny] = 0;
					}
					System.out.println(dice[0]);
					x = nx;
					y = ny;
				}
				break;
			case 4:
				nx = x + 1;
				ny = y;
				if(nx >= 0 && nx < N && ny >= 0 && ny < M) {
					tmp = dice[0];
					dice[0] = dice[3];
					dice[3] = dice[5];
					dice[5] = dice[4];
					dice[4] = tmp;
					if(arr[nx][ny] == 0) {
						arr[nx][ny] = dice[5];
					} else {
						dice[5] = arr[nx][ny];
						arr[nx][ny] = 0;
					}
					System.out.println(dice[0]);
					x = nx;
					y = ny;
				}
				break;
			}
		}
	}

}
