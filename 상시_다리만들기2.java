package Samsung;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
/*
 * 시작 1225
 * 다리의 길 2이상
 * 넘버링 안된 섬은 7
 * 길은 8로 표시
 * 
 */
class RC17472{
	int row;
	int col;
		public RC17472(int r, int c) {
			row = r;
			col = c;
		}
}
public class 상시_다리만들기2 {
	static int N,M;
	static int[][] nation;
	static boolean[][][] visitAndDir;
	static boolean[] visit;
	static int min;
	static int islandSize;
	static int[] dr = {-1,0,1,0};
	static int[] dc = {0,1,0,-1};//상우하좌
	static Queue<RC17472> q = new LinkedList<RC17472>();
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		nation = new int[N][M];
		visitAndDir = new boolean[N][M][4];
		for(int row=0;row<N;row++) {
			for(int col=0;col<M;col++) {
				nation[row][col] = sc.nextInt();
				if(nation[row][col]==1) nation[row][col] = 7;//넘버링 안된 섬
			}
		}
		setIsland();
		view();
		//완탐시작
	}
	private static void view() {
		for(int row=0;row<N;row++) {
			for(int col=0;col<M;col++) {
				System.out.print(nation[row][col]+" ");
			}
			System.out.println();
		}
		System.out.println();
	}
	private static void setIsland() {
		int island = 1;
		//맵에 섬 넘버링
		for(int row=0;row<N;row++) {
			for(int col=0;col<M;col++){
				if(nation[row][col]==7){
					nation[row][col] = island;
					q.add(new RC17472(row, col));
					BFS(island);//BFS로 섬 마킹
					island++;
				
				}
			}
		}
		islandSize = island;
		visit = new boolean[islandSize];
	}
	private static void BFS(int island) {
		while(!q.isEmpty()){
			int size = q.size();
			for(int i=0;i<size;i++){
				RC17472 curRC = q.poll();
				for(int dir=0;dir<4;dir++){
					int nr = curRC.row+dr[dir];
					int nc = curRC.col+dc[dir];
					if(rangeCheck(nr,nc)){
						if(nation[nr][nc]==7) {
							nation[nr][nc] = island;
							q.add(new RC17472(nr,nc));	
						}
					}
				}
			}
		}
	}
	private static boolean rangeCheck(int nr, int nc) {
		if(nr>=0 && nr<N && nc>=0 && nc<M) return true;
		return false;
	}
	
}
