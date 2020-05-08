//Name           : Tyler Roberts
//Student Number : 250922271

public class Node {

	private int id;//id
	private int cost; //key
	
	//constructor
	public Node(int cost, int id) {
		this.cost = cost;
		this.id = id;
	}
	
	//getter and setter methods for instance variables
	public int getCurrentCost() {
		return this.cost;
	}
	public int getID() {
		return this.id;
	}
	public void setCost(int cost) {
		this.cost = cost;
	}
	public void setID(int id) {
		this.id = id;
	}

}
