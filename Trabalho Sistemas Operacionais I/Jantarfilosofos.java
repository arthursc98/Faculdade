/*
 * Integrantes:
 * Arthur Silveira Chaves (Sistemas de InformaÃ§ão)
 * Beatriz Jonas Justino (Sistemas de InformaÃ§ão)
 * Nicholas Meirinho Perez (Sistemas de InformaÃ§ão)
 * 
 * Disciplina: Sistemas Operacionais I
 * 
 * Ultima data de modificaÃ§ão: 2020-04-06
 */
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.Scanner;

public class Jantarfilosofos {
	public static void main(String[] args) {
		Printers p = new Printers();
		Operations op = new Operations();
		p.header();

		int iAmount = 20;
	
		if(args.length > 0)
			iAmount = Integer.parseInt(args[0].trim());
			   
		//Creating tray
		Tray tray = new Tray(1, iAmount);
		
		//Creating forks
		Scanner sc = new Scanner(System.in);

		Fork[] forks = op.createForks(sc);
		
		Semaphore semaphore = new Semaphore();
		
		//Creating philosophers
		op.createAndRunPhilosophers(tray, forks, sc, p, semaphore);
	}
}

class Operations{
	public Fork[] createForks(Scanner sc){
	/*
	 * Create N forks with user input
	 */
		System.out.println("How many forks do you need? Use at least 2 for 2 participants: ");
		int nForks = sc.nextInt();

		while (nForks < 2){
			System.out.println("Incorrect amount of forks.\nPlease enter a valid amount: ");
			nForks = sc.nextInt();
		}

		Fork[] forks;
		forks = new Fork[nForks];

		for(int i = 0; i < nForks; i++){
			forks[i] = new Fork(i+1);
		}

		return forks;
	}
	
	public void createAndRunPhilosophers(Tray tray, Fork[] forks, Scanner sc, Printers p, Semaphore semaphore){
	/*
	 * Create and Run Philosophers operation
	 */
		System.out.println("How many philosophers will be participating? Use at least 2 participants");
		int nPhilosophers = sc.nextInt();

		while (nPhilosophers < 2){
			System.out.println("Invalid number of philosophers\nPlease enter a valid quantity: ");
			nPhilosophers = sc.nextInt();
		}

		Philosopher [] philosophers;
		philosophers = new Philosopher[nPhilosophers];

		p.portionsArrived();
		
		for (int i = 0; i < nPhilosophers; i++){
			if (i == 0){
				philosophers[i] = new Philosopher(i, tray, forks, i, nPhilosophers - 1, semaphore);
				philosophers[i].start();
			}
			else{
				philosophers[i] = new Philosopher(i, tray, forks, i, i-1, semaphore);
				philosophers[i].start();
			}
		}
		
		for(int i = 0; i < nPhilosophers; i++){
			try {
				philosophers[i].join();
			} catch (Exception ex) {
			}
		}
		p.summary(philosophers, nPhilosophers);
	}
}

class Printers {
	public void header(){
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
		System.out.println("|         Solve access to tray problem of philosophers        |");
		System.out.println("|                                                             |");
		System.out.println("+=============================================================+");
		System.out.println("|                                                             |");
		System.out.println("|                    Putting food on the table                |");
		System.out.println("|                                                             |");
		System.out.println("+=============================================================+");
		System.out.println();
	}

	public void portionsArrived(){
		System.out.println(); 
		System.out.println();
		System.out.println("+=============================================================+");
		System.out.println("|                                                             |");
		System.out.println("|                    Philosophers... Let's eat                |");
		System.out.println("|                                                             |");
		System.out.println("+=============================================================+");
		System.out.println("");
	}

	public void summary(Philosopher[] philosophers, int nPhilosophers){
		System.out.println("+=============================================================+");
		System.out.println("|                                                             |");
		for(int i = 0; i < nPhilosophers; i++){

			System.out.format("|\t\t%11s%4d%4s%4d%23s|\r\n","Philosopher", i+1, "ate", philosophers[i].getAmount()," ");
		}
		System.out.println("|                                                             |");
		System.out.println("+=============================================================+");
		System.out.println("|                                                             |");
		System.out.println("|        We ran out of food guys, see you all next time       |");
		System.out.println("|                                                             |");
		System.out.println("+=============================================================+");
		System.out.println();
	}

}


class Fork {
	private int iId;
	private int iBusy;
	
	public Fork(int _iId){
		this.iId = _iId;
		this.iBusy = 0;
		System.out.println("Fork " + Integer.toString(iId) + " created!");
	}
	
	public int getId(){
		return this.iId;
	}
	
	public void setBusy(int _iBusy){
		this.iBusy = _iBusy;
	}
	
	public Boolean isBusy(){
		return (this.iBusy != 0);
	}
	
}

class Tray {
	private int iId;
	private int iAmount;
	
	public Tray(int _iId, int _iAmount){
		this.iId = _iId;
		this.iAmount = _iAmount;
		System.out.println("Tray " + Integer.toString(iId) + " created! - number of portions: " 
									  + Integer.toString(iAmount));
	}
	
	public int getAmount(){
		return this.iAmount;
	}
	
	public void decreaseAmount(){
		this.iAmount--;
	}
}


class Philosopher extends Thread{
	private int iId;
	private Tray tray;
	private Fork[] forks;
	private int iLeft;
	private int iRight;
	private Boolean bCanEat;
	private int iAmount;
	private Semaphore semaphore;
	
	public Philosopher(int _iId, Tray _tray, Fork[] _forks, int _iLeft, int _iRight, Semaphore semaphore){
		this.semaphore = semaphore;
		this.iAmount = 0;
		this.iId = _iId;
		this.tray = _tray;
		this.forks = _forks;
		this.iLeft = _iLeft;
		this.iRight = _iRight;
		this.bCanEat = false;
		System.out.println("> Philosopher " + Integer.toString(iId) + " say: Hello Everyone! I've just got here");       
	}
	
	@Override
	public void run(){
		while(tray.getAmount()>0) {
			this.eat();
			this.think();
		}
		if(this.iAmount > 0)
		   System.out.println("* Philosopher " + Integer.toString(iId) + " say: Oh no, we run out of food! I just eated " 
										  + Integer.toString(this.iAmount) + " portions.");
		else
		   System.out.println("* Philosopher " + Integer.toString(iId) + " say: I couldn't get any food!");
	}
	
	private synchronized void getForks(int _iLeft, int _iRight){
	/*
	* Check if both forks of each side is available and will pick-up synchronized
	*/
		try{
			if(!forks[_iLeft].isBusy() && !forks[_iRight].isBusy()) {
				this.bCanEat = true;
				forks[_iLeft].setBusy(this.iId);
				forks[_iRight].setBusy(this.iId);
				semaphore.decrease();
				tray.decreaseAmount();
				this.iAmount++;
			}
		}catch(Exception e){
		}
	}
	
	private synchronized void releaseForks(int _iLeft, int _iRight){
	/*
	* Release both forks and make them available for other philosophers
	*/
		this.bCanEat = false;
		forks[_iLeft].setBusy(0);
		forks[_iRight].setBusy(0);
		semaphore.increment();
	}
	
	private void eat(){
	/*
	* Check if both forks of each side is available and will pick-up synchronized,
	* then check if he can access the banquet, eat his amount of food release forks to another philosopher
	*/
		System.out.println("+ Philosopher " + Integer.toString(iId) + " say: Dear god, will i eat?");
		this.getForks(iLeft, iRight);
		if(this.bCanEat) {
			System.out.println("++ Philosopher " + Integer.toString(iId) + " say: Finally!! I'm gonna eat something...");
			System.out.println("+++ Philosopher " + Integer.toString(iId) + " got the fork " 
											   + Integer.toString(forks[iLeft].getId()) 
											   + " (left) and  " 
											   + Integer.toString(forks[iRight].getId())
											   + " (right).");
			try {
				Thread.sleep(700);
			} catch (InterruptedException ex) {
				Logger.getLogger(Philosopher.class.getName()).log(Level.SEVERE, null, ex);
			}
			
			this.releaseForks(iLeft, iRight);
			System.out.println("- Philosopher " + Integer.toString(iId) + " say: I'm done, but i still want more food!");
		} 
	}
	
	private void think(){
		System.out.println("= Philosopher " + Integer.toString(iId) + " say: Right now i will just think a little bit...");
		try {
			Thread.sleep(500);
		} catch (InterruptedException ex) {
			Logger.getLogger(Philosopher.class.getName()).log(Level.SEVERE, null, ex);
		}
	}
	
	public int getAmount(){
		return this.iAmount;
	}    
}

class Semaphore{
	private int count;

	public Semaphore(){
		this.count = 1;
	}
	
	public Semaphore (int val){
		this.count = val;
	}

	public synchronized void decrease(){
		while (this.count == 0){
			try{
				wait();
			} catch(Exception e){
			}
		}

		this.count--;
	}

	public synchronized void increment(){
		this.count++;

		notify();
	}
}
