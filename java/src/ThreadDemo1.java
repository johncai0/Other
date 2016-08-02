/**
 * Created by root on 16-5-12.
 */
class johnone implements Runnable {
    private int a=100;
    public void run() {
            while (a > 0) {
		try { Thread.sleep(1); } catch (Exception e) {}
        	synchronized (this) {
			if (a > 0) {
                		System.out.println(Thread.currentThread().getName() + " is Runing...." + a--);
			}
            	}
            }	
    }
}
public class ThreadDemo1  {
    public static void main(String[] args) {
        johnone j1 = new johnone();
        for (int i = 0; i<10 ;i++) {
            Thread t1 = new Thread(j1);
            t1.setName("TH" + i);
            t1.start();
        }
    }
}
