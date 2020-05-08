//Name           : Tyler Roberts
//Student Number : 250922271


public class Edge {
	private int start, end, weight; //instance variables 
	
	//constructor
	public Edge(int start, int end, int weight) {
		this.start = start; //start vertex 
		this.end = end; //end vertex
		this.weight = weight; //cost to go from start to end
	}
	
	//getter methods
	public int getStartNode() {
		return this.start;
	}
	public int getEndNode() {
		return this.end;
	}
	public int getWeight() {
		return this.weight;
	}
}
