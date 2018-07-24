/*
Chef Goes to the Cinema Problem Code: CO92SUBW
All submissions for this problem are available.
Read problems statements in Mandarin chinese, Russian and Vietnamese as well.

Chef lives in Chefcity. Chefcity can be represented as a straight line with Chef's house at point 0 on this line. There is an infinite number of subway stations in Chefcity, numbered by positive integers. The first station is located at point 1 and for each i ≥ 1, the distance between stations i and i+1 is equal to i+1. (Station i+1 is always located at a higher coordinate than station i, i.e., the subway stations are located at points 1, 3, 6, 10, 15 etc.)

Subway trains in Chefcity allow Chef to move between any pair of adjacent stations in one minute, regardless of the distance between them. Chef can also move by walking; his walking speed is one unit of distance in one minute. Chef can enter or exit the subway at any station.

Chef has decided to go to the cinema. The only cinema in Chefcity is located at point X. (Note that the cinema can be placed at the same point as a subway station.) Help Chef determine the minimum possible time required to get to the cinema from his house.
Input

    The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
    The first and only line of each test case contains a single integer X.

Output

For each test case, print a single line containing one integer - the minimum possible travel time.
Constraints

    1 ≤ T ≤ 200
    1 ≤ X ≤ 109

Example

Input:

4
1
2
3
9

Output:

1
2
2
5

Explanation

Example case 4: Chef will walk from x = 0 to x = 1 in one minute, then he will enter the subway and move from station 1 (at x = 1) to station 2 (at x = 3) in one minute, then from station 2 to station 3 (at x = 6) in one minute, from station 3 to station 4 (at x = 10) in one minute, and finally, he will walk from x = 10 to x = 9 in one minute, which makes the total travel time 5 minutes.
*/

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.InputMismatchException;

class CIN {
	InputStream is;
	PrintWriter out;
	String INPUT = "";

	void solve() {
		for(int T = ni(); T > 0; T--) {
			int x = ni();
			long min = Long.MAX_VALUE;
			for(int i = 1; i <= 45000; i++) {
				long s = i + Math.abs(i * (i+1)/2-x);
				min = Math.min(min, s);
			}
			out.println(min);
		}
	}

	void run() throws Exception {
		is = INPUT.isEmpty() ? System.in : new ByteArrayInputStream(INPUT.getBytes());
		out = new PrintWriter(System.out);

		long s = System.currentTimeMillis();
		solve();
		out.flush();
		if(!INPUT.isEmpty()) 
			tr(System.currentTimeMillis()-s+"ms");
	}

	public static void main(String args[]) throws Exception {
		new CIN().run();
	}

	private byte[] inbuf = new byte[1024];
	public int lenbuf = 0, ptrbuf = 0;

	private int readByte() {
		if(lenbuf == -1)
			throw new InputMismatchException();
		if(ptrbuf >= lenbuf) {
			ptrbuf = 0;
			try {
				lenbuf = is.read(inbuf);
			} catch (IOException e) {
				throw new InputMismatchException();
			}
			if(lenbuf <= 0) 
				return -1;
		}
		return inbuf[ptrbuf++];
	}

	private boolean isSpaceChar(int c) {
		return !(c >= 33 && c <= 126);
	}
	private int skip() {
		int b;
		while((b = readByte()) != -1 && isSpaceChar(b));
		return b;
	}
	private double nd() {
		return Double.parseDouble (ns());
	}
	private char nc() {
		return (char) skip();
	}
	private String ns() {
		int b = skip();
		StringBuilder sb = new StringBuilder();
		while(!(isSpaceChar(b))) {
			sb.appendCodePoint(b);
			b = readByte();
		}
		return sb.toString();
	}
	private char[] ns(int n) {
		char[] buf = new char[n];
		int b = skip(), p = 0;
		while(p < n && !(isSpaceChar(b))) {
			buf[p++] = (char)b;
			b = readByte();
		}
		return n == p ? buf: Arrays.copyOf(buf, p);
	}
	private char[][] nm(int n, int m) {
		char[][] map = new char[n][];
		for(int i = 0; i < n; i++)
			map[i] = ns(m);
		return map;
	}
	private int[] na(int n) {
		int[] a = new int[n];
		for(int i = 0; i < n; i++) 
			a[i] = ni();
		return a;
	}
	private int ni() {
		int num = 0, b;
		boolean minus = false;
		while((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-'));
		if(b == '-') {
			minus = true;
			b = readByte();
		}	
		while(true) {
			if(b >= '0' && b <= '9') {
				num = num * 10 + (b - '0');
			} else {
				return minus ? -num : num;
			}
			b = readByte();
		}
	}
	private long nl() {
		long num = 0;
		int b; 
		boolean minus = false;
		while((b = readByte()) != -1 && ((b >= '0' && b <= '9')|| b == '-'));
		if(b == '-') {
			minus = true;
			b = readByte();
		}
		while(true) {
			if(b >= '0' && b <= '9') {
				num = num * 10 + (b - '0');
			} else {
				return minus ? -num : num;
			}
			b = readByte();
		}
	}

	private void tr(Object... o) {
		if(INPUT.length() > 0) 
			System.out.println(Arrays.deepToString(o));
	}
}