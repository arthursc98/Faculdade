/*
 * Integrantes:
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
 * 
 * Disciplina: Sistemas Operacionais I
 * 
 * Ultima data de modificação: 2020-04-05
 */

import java.io.PrintWriter;
import java.lang.Math;
import java.nio.file.Paths;
import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;
import java.util.Scanner;
import java.util.Random;


public class MatrixMultiplication{

	public static long[][] a;
	public static long[][] b;
	public static long[][] c;
	public static double STD = (500/3);
	public static int MEAN = 500;
	public static int cores  = Runtime.getRuntime().availableProcessors();
	public static final String filename = "MatMul.txt";
	public static final String curDir = Paths.get(".").toAbsolutePath().normalize().toString();

	public static long[][] createSquaredMatrix(int N, PrintWriter pw) throws Exception {
	/*
	* Create and display a Squared Matrix with N rows and N columns.
	*/
		Random r = new Random();
		long mat[][] = new long[N][N];
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++) {
				mat[i][j] = (long) Math.round((MEAN + (r.nextGaussian() * STD)));
			pw.print(mat[i][j] + (j!=N-1? "\t" : ""));
			}
	  pw.print("\r\n");
	}
	pw.println();
		return mat;
	}

	public static void saveMatMul(PrintWriter pw, int n){
	/*
	 * Save current result matrix at MatMul.txt
	 */
	pw.println("Result Matrix:");
		for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++) {
			pw.print(c[i][j] + (j!=n-1? "\t" : ""));
		}
		pw.print("\r\n");
		}
	}

  // public static long karatsuba(long num1, long num2) {
  // /*
  // * Algorithmn developed by Anatolii Alexeevitch Karatsuba to multiply numbers using * the approach divide and conquer.
  // */
  //     int n = Math.max(
  //             String.valueOf(num1).length(),
  //             String.valueOf(num2).length()
  //     );

  //     if (n < 2)
  //         return num1 * num2;

  //     n = (n / 2) + (n % 2);

  //     long m = (long) Math.pow(10, n);

  //     long b = num1 / m;
  //     long a = num1 - (b * m);
  //     long d = num2 / m;
  //     long c = num2 - (d * n);

  //     long ac = karatsuba(a, c);
  //     long bd = karatsuba(b, d);
  //     long abcd = karatsuba(a + b, c + d);

  //     return ac + ((abcd - ac - bd) * m) + (bd * (long)(Math.pow(10,2 * n)));
  // }

	public static class Thread2 extends Thread {
	/*
	* Iteration per core
	*/
		public int rows_per_thread;
		public int rows_to_matrix;
		public int n;

		public Thread2(int rows_per_thread, int rows_to_matrix, int n){
		this.rows_per_thread = rows_per_thread;
		this.rows_to_matrix = rows_to_matrix;
		this.n = n;
		}

		@Override
		public synchronized void run(){
		for (int i = rows_per_thread; i < rows_to_matrix + rows_per_thread && i < n; i++){
			for (int j = 0; j < n; j++) {
				c[i][j] = 0;
				for(int k =0 ; k < n; k++){
					c[i][j] += (a[i][k] * b[k][j]);
				}
			}
		}
		}
	}

	public static void runMatMul() {
	/*
	* Store result of every multiplication into a matrix with N rows and N columns.
	* Mechanic: Create an ArrayList of Threads and start all processes then join all
	* after processing
	*/
		int n = b.length;

		int rows_per_thread = n/cores;

		Thread[] ThreadsList;
		ThreadsList = new Thread [cores];

		for (int i = 0; i < cores; i++){
			int rows_to_matrix = rows_per_thread;

			if (i == cores -1)
				rows_to_matrix += n%cores;

			ThreadsList[i] = new Thread2(rows_per_thread * i, rows_to_matrix, n);
			ThreadsList[i].start();
		}
		for (int i = 0; i < cores; i++){
		try{
			ThreadsList[i].join();
		}catch(Exception e){
		}
		}
	}	
	public static void header(){
		System.out.println("+=============================================================+");
		System.out.println("|              Catholic University of Santos                  |");
		System.out.println("|                                                             |");
		System.out.println("|                     University Assigment                    |");
		System.out.println("|              Class/Subject: Operating Systems               |");
		System.out.println("|                        Semester: 5                          |");
		System.out.println("|                                                             |");
		System.out.println("|                        Developed by:                        |");
		System.out.println("|                  Arthur Silveira Chaves                     |");
		System.out.println("|                   Beatriz Jonas Justino                     |");
		System.out.println("|                  Nicholas Meirinho Perez                    |");
		System.out.println("|                                                             |");
		System.out.println("+=============================================================+");
		System.out.println("|                                                             |");
		System.out.println("|                      Application goal:                      |");
		System.out.println("|  Generate a Square Matrix of N with random Gaussian numbers |");
		System.out.println("|             Random Numbers between 0-1000                   |");
		System.out.println("|                                                             |");
		System.out.println("+=============================================================+");
	}

	public static void main(String[] args) throws Exception {
		header();
		System.out.println("Enter N to generate the Squared Matrix: ");
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();

		System.out.println("You have "+cores+" cores, how much do you want to use?");
		cores = sc.nextInt();

		sc.close();

		PrintWriter pw = new PrintWriter(filename);

		DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss.SSSSSSSS");  
		LocalDateTime t1 = LocalDateTime.now();
		pw.println("Init Matrix Multiplication:" + dtf.format(t1));

		pw.println("Matrix A:");
		a = createSquaredMatrix(N, pw);

		pw.println("Matrix B:");
		b = createSquaredMatrix(N, pw);
	
		c = new long [N][N];

		runMatMul();

		saveMatMul(pw, N);

		System.out.println("Your Matrix Multiplication are located at "+curDir+"/"+filename);

		LocalDateTime t2 = LocalDateTime.now();
		pw.print("Finish Matrix Multiplication:" + dtf.format(t2));
		pw.close();
	}
}
