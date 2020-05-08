//Name: Tyler Roberts
//Student Number: 250922271

public class LinkedNode {
	
	//instance variables
	private int value;
	private LinkedNode next, representative;
	private int arrayRowIndex;
	private int arrayColumnIndex;
	
	//constructor 
	public LinkedNode(int v) {
		value = v;
		next = null;
		representative = null;
		arrayRowIndex = 0;
		arrayColumnIndex = 0;
	}
	
	//getter and setter methods for each instance variable
	public int getValue() {
		return value;
	}
	public LinkedNode getNext(){
		return next;
	}
	public boolean hasNext() {
		if(next == null) {
			return false;
		}
		else {
			return true;
		}
	}
	public LinkedNode getRep(){
		return representative;
	}
	public void setValue(int v) {
		value = v;
	}
	public void setNext(LinkedNode n) {
		next = n;
	}
	public void setRep(LinkedNode r) {
		representative = r;
	}
	public void setRowIndex(int i) {
		arrayRowIndex = i;
	}
	public void setColumnIndex(int i) {
		arrayColumnIndex = i;
	}
	public int getRowIndex() {
		return arrayRowIndex;
	}
	public int getColumnIndex() {
		return arrayColumnIndex;
	}
}
