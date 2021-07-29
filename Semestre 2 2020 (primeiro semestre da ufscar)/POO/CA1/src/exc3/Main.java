package exc3;
import java.util.Scanner;

// NOME : CAIO FERNANDO PERES 			RA: 769298


public class Main {

	public static void main(String[] args) {
	
	
	Scanner leitor = new Scanner(System.in);
	
	System.out.print("Insira X, Y e raio do circulo: \n");
	
	float x = leitor.nextFloat();
	float y = leitor.nextFloat();
	float r = leitor.nextFloat();
	
	Circunferencia circulo = new Circunferencia(x, y, r);
	
	System.out.print("Insira X e Y do ponto: \n");
	x = leitor.nextFloat();
	y = leitor.nextFloat();
	
	leitor.close();
	
	Ponto ponto = new Ponto(x,y);
	
	
	System.out.printf("Area: %f\n", circulo.Area());
	
	System.out.printf("Comprimento: %f\n", circulo.Comprimento());
	
	if( circulo.isInside(ponto.getX(), ponto.getY()) ) {
		System.out.printf("Ponto interno.");
		
	}
	
	if( circulo.isOutside(ponto.getX(), ponto.getY()) ) {
		System.out.printf("Ponto externo.");
		
	}
	
	if( circulo.isAtBorder(ponto.getX(), ponto.getY()) ) {
		System.out.printf("Ponto pertence ao circulo.");
		
	}
	
	
	}
}
