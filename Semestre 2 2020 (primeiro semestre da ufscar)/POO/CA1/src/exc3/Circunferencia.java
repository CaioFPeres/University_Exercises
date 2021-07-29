package exc3;

public class Circunferencia extends Ponto {

	final private float pi = (float) 3.14;
	
	private float x;
	
	private float y;
	
	private float r;
	
	public Circunferencia (float x, float y, float r) {
		
		super(x, y);
		
		this.r = r;
	}
	
	public float Area() {
	
		return (float) (pi*Math.pow(r, 2));
	
	}
	
	public float Comprimento() {
		
		return (float) (2*pi*r);
	
	}
	
	
	public boolean isInside(float x, float y) {
		
		if( Math.pow((x - this.x), 2) + Math.pow((y - this.y), 2) < Math.pow(r, 2) ) {
			return true;
		}
		else {
			return false;
		}
		
	}
	
	
	public boolean isOutside(float x, float y) {
		
		if( Math.pow((x - this.x), 2) + Math.pow((y - this.y), 2) > Math.pow(r, 2) ) {
			return true;
		}
		else {
			return false;
		}
		
	}
	
	
	public boolean isAtBorder(float x, float y) {
		
		if( Math.pow((x - this.x), 2) + Math.pow((y - this.y), 2) == Math.pow(r, 2) ) {
			return true;
		}
		else {
			return false;
		}
		
	}
	
	
	public void setX(float x) {
		this.x = x;
	}
	
	public void setY(float y) {
		this.y = y;
	}
	
	public void setR(float r) {
		this.r = r;
	}
	
	public float getX(float x) {
		return this.x;
	}
	
	public float getY(float y) {
		return this.y;
	}
	
	public float getR(float r) {
		return this.r;
	}
	
}
