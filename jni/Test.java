import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Scanner;
import java.util.Random;
import java.util.Date;

public class Test {
	public static int DIM_NUM = 128;
	public static int TEST_NUM = 10000;
	public static int DFT_NUM = 10000;

	public static void main(String[] args) {
		int num = DFT_NUM;
		if (args[0] != null) {
			num = Integer.parseInt(args[0]);
		}
		int alg = 0;
		if (args[1] != null) {
			alg = Integer.parseInt(args[1]);
		}
		
		JNIFind jf = new JNIFind();
		System.out.println("readdata...");
		float[] data = readData(num);
		long pool = jf.create_search_pool(data, DIM_NUM, num);
		float[] target = genOne();
		System.out.println("testing...");
		long begin = new Date().getTime();
		switch (alg) {
		case 0:
			test0(jf, target, pool);
			break;

		case 1:
			test1(jf, target, pool);
			break;

		case 2:
			test2(jf, target, pool);
			break;
			
		case 3:
			test3(jf, target, pool);
			break;
		}
		long end = new Date().getTime();
		System.out.println("totaltime: " + (end - begin) + "ms");
		System.out.println("throughput: " + (float)TEST_NUM/ (float)(end - begin) * 1000 + "cps");
	}

	private static void test0(JNIFind jf, float[] target, long pool) {
		for (int i = 0; i < TEST_NUM; i++) {
			int idx = jf.find_0(target, pool);
		}
	}

	private static void test1(JNIFind jf, float[] target, long pool) {
		for (int i = 0; i < TEST_NUM; i++) {
			int idx = jf.find_1(target, pool);
		}
	}

	private static void test2(JNIFind jf, float[] target, long pool) {
		for (int i = 0; i < TEST_NUM; i++) {
			int idx = jf.find_2(target, pool);
		}
	}

	private static void test3(JNIFind jf, float[] target, long pool) {
		for (int i = 0; i < TEST_NUM; i++) {
			int idx = jf.find_3(target, pool);
		}
	}

	private static float[] readData(int num) {
		try {
			float[] data = new float[DIM_NUM * num];
			BufferedReader br = new BufferedReader(new FileReader( num + ".txt"));
			String line = br.readLine();
			int lineCnt = 0;
			
			while (line != null) {
				readLine(line, data, lineCnt * DIM_NUM);
				line = br.readLine();
				lineCnt++;
			}
			return data;
		} catch (Exception e) {
			System.out.println("error in readData" + e);
			return null;
		}
	}

	private static void readLine(String line, float[] data, int base) {
		Scanner scanner = new Scanner(line);
		int i = 0;
		scanner.useDelimiter(" ");
		while (scanner.hasNext()) {
			String dStr = scanner.next();
			data[base + i] = Float.parseFloat(dStr);
			i++;
		}
	}

	private static float[] genOne() {
		float[] target = new float[DIM_NUM];
		for (int i = 0; i < target.length; i++) {
			target[i] = (float)(Math.random() * 1000);
		}
		return target;
	}
}
