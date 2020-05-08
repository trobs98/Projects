//Name: Tyler Roberts
//Student Number: 250922271

import java.util.*;
import java.lang.*;
import java.io.*;

public class LinkedList<T> {
	//instance variables
	private LinkedNode head, tail; 
	
	//constructor
	public LinkedList(LinkedNode h, LinkedNode t){
		head = h;
		tail = t;
		head.setRep(head);
		tail.setRep(head);
		
	}
	
	//getter and setters for instance variables
	public LinkedNode getHead() {
		return head;
	}
	public LinkedNode getTail(){
		return tail;
	}
	public void setHead(LinkedNode h) {
		head = h;
	}
	public void setTail(LinkedNode t) {
		tail = t;
	}
	
	//allows you to add a new node to the tail end of the LinkedList
	public void addNewNode(LinkedNode node) {
		tail.setNext(node);
		tail = node;
		node.setRep(head);
	}
	
	//gets the size of the LinkedList
	public int getSize() {
		int size = 1;
		LinkedNode node = head;
		if(head == tail) {
			size = 1;
		}
		else {
			while(node.hasNext() != false) {
				node = node.getNext();
				size++;
			}
		}
		return size;
	}
	
	//removes the list
	public void removeList() {
		head = null;
		tail = null;
	}
}

//Comparator to make it easier for when i'm sorting the uandf
class sortByRep implements Comparator<LinkedList>{
	public int compare(LinkedList a, LinkedList b) {
		return b.getSize() - a.getSize(); //results in ascending order
	}
}

