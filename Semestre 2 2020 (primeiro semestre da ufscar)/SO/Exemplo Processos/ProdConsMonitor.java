import java.util.Random;

public class ProdConsMonitor {

    private static final int N_ITENS = 10;

    private int[] buffer;
    private int inicio;
    private int fim;
    private int cont;
    
    public ProdConsMonitor() {
        buffer = new int[N_ITENS];
        inicio = fim = cont = 0;
    }
    
    public synchronized void produz(int item) throws InterruptedException {
        if (cont == N_ITENS) {
            wait();
        }
        System.out.println("Produtor, item = " + item
			   + ", posição = " + fim);     
        fim = (fim + 1) % N_ITENS;
        buffer[fim] = item;
	cont++;
        System.out.println("Produtor total = " + cont);
        if (cont == 1) {
            notify();
        }
    }

    public synchronized int consome() throws InterruptedException {
        if (cont == 0) {
            wait();
        }
        System.out.println("Consumidor consumiu");
        inicio = (inicio + 1) % N_ITENS;
        int aux = buffer[inicio];
        System.out.println("Consumidor, item = " + aux
			   + ", posição = " + inicio);     
	cont--;
        System.out.println("Consumidor total = " + cont);
        if (cont == N_ITENS - 1) {
            notify();
        }
        return aux;
    }

    public static void main(String[] args) {
        final ProdConsMonitor monitor = new ProdConsMonitor();
        
        (new Thread() {public void run() {
            for (int i = 0; i < 3 * ProdConsMonitor.N_ITENS; i++) {
                try {
                    monitor.produz(i);
                    sleep(new Random().nextInt(3000));
                } catch (InterruptedException e) {
                }
            }
        } } ).start();

        (new Thread() {public void run() {
            for (int i = 0; i < 3 * ProdConsMonitor.N_ITENS; i++) {
                try {
                    monitor.consome();
                    sleep(new Random().nextInt(3000));
                } catch (InterruptedException e) {
                }
            }
        } } ).start();
    }
}
