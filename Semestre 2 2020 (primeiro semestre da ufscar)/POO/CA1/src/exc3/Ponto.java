package exc3;

public class Ponto {

	private float x;
	private float y;
	
	public Ponto(float x, float y) {
		
		this.x = x;
		this.y = y;
		
	}
	
	public float getX() {
		return this.x;
	}
	
	public float getY() {
		return this.y;
	}
        
        public void imprimir(){
            System.out.println(this.x);
            System.out.println(this.y);
        }


}
