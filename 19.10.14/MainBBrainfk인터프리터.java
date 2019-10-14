package study191014;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class MainBBrainfk인터프리터 {

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(br.readLine().trim());
		StringTokenizer st;
		int Sm, Sc, Si, pointer, pc, count, loopS = 0, ipointer;
		int[] memory, pair;
		char[] code, input;
		boolean[] endable;
		Stack<Integer> stack = new Stack<>();
		for(int testcase = 1; testcase <= t; testcase++) {
			st = new StringTokenizer(br.readLine().trim());
			Sm = Integer.parseInt(st.nextToken());
			Sc = Integer.parseInt(st.nextToken());
			Si = Integer.parseInt(st.nextToken());
			memory = new int[Sm];
			code = br.readLine().trim().toCharArray();
			input = br.readLine().trim().toCharArray();
			pair = new int[Sc];
			endable = new boolean[Sc];
			stack.clear();
			for(int i = 0; i < Sc; i++) {
				if(code[i] == '[') {
					stack.push(i);
				} else if(code[i] == ']') {
					pair[i] = stack.peek();
					pair[stack.pop()] = i;
				}
			}
			pointer = 0;
			ipointer = 0;
			pc = 0;
			count = 0;
			stack.clear();
			while(count < 50000000 && pc != Sc) {
				switch(code[pc]) {
				case '-':
					memory[pointer] = (memory[pointer] - 1 + (1 << 8)) % (1 << 8);
					break;
				case '+':
					memory[pointer] = (memory[pointer] + 1) % (1 << 8);
					break;
				case '<':
					pointer = (pointer - 1 + Sm) % Sm;
					break;
				case '>':
					pointer = (pointer + 1) % Sm;
					break;
				case '[':
					stack.push(pc);
					if(memory[pointer] == 0) {
						pc = pair[pc] - 1;
					}
					break;
				case ']':
					if(memory[pointer] != 0) {
						pc = pair[pc] - 1;
					} else {
						endable[stack.peek()] = true;
					}
					stack.pop();
					break;
				case ',':
					if(ipointer == Si) {
						memory[pointer] = 255;
					} else {
						memory[pointer] = input[ipointer++];
					}
					break;
				}
				pc++;
				count++;
			}
			if(pc == Sc) {
				System.out.println("Terminates");
			} else {
				while(!stack.isEmpty()) {
					loopS = stack.pop();
					if(!endable[loopS]) {
						System.out.println("Loops " + loopS + " " + pair[loopS]);
						break;
					}
				}
			}
		}
	}

}
