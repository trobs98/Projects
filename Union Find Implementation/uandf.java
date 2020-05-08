//Name: Tyler Roberts
//Student Number: 250922271

import java.util.*; 
import java.lang.*; 
import java.io.*; 

public class uandf<T>{
	public LinkedList<T>[] unionFind;
	private int currentSize;
	private int state;
	
	//constructor
	public uandf(int n) {
		
		state = 1;
		currentSize = n;
		unionFind = new LinkedList[n];
		
		for(int i=0; i<n; i++) {
			LinkedNode node = new LinkedNode(i+1);
			LinkedList<T> list = new LinkedList<T>(node, node);
			unionFind[i] = list;
		}
	}
	
	//private functions to make life easier
	
	//increases the size of the array by 1
	private void increaseSize() {
		LinkedList<T>[] temp = new LinkedList[currentSize + 1];
		
		for(int i=0; i<currentSize; i++) {
			temp[i] = unionFind[i];
		}
		
		currentSize++;
		unionFind = temp;
		
	}
	
	//decreases the size of the array by 1
	private void decreaseSize() {
		LinkedList<T>[] temp = new LinkedList[currentSize - 1];
		int tempIndex = 0;
		
		for(int i=0; i<currentSize; i++) {
			if(unionFind[i] != null) {
				temp[tempIndex] = unionFind[i];
				tempIndex++;
			}
		}
		
		currentSize--;
		unionFind = temp;
		
	}
	
	//finds the location of the list in the array
	private int findLocation(LinkedList<T> list) {
		int location = 0;
		for(int i=0; i<currentSize; i++) {
			if(list == unionFind[i]) {
				location = i;
			}
		}
		return location;
	}
	
	public LinkedList<T> make_set(int i) {
		LinkedNode node = new LinkedNode(i);
		LinkedList<T> list = new LinkedList<T>(node,node);
		
		if(state == 1) {
			increaseSize();
			unionFind[currentSize-1] = list;
		}
		
		return list;
	}
	
	
	
	public void union_sets(int i,int j) {
		LinkedList<T> list_i = null;
		LinkedList<T> list_j = null;
		
		if(state == 1) {	
			list_i = find_set(i);
			list_j = find_set(j);
			
			if(list_i.getSize() >= list_j.getSize()) {
				LinkedNode currentNode = list_j.getHead(); 
		
				for(int k=0; k<list_j.getSize(); k++) {
					currentNode.setRep(list_i.getHead());
					currentNode = currentNode.getNext();
				}
				
				list_i.getTail().setNext(list_j.getHead());
				list_i.setTail(list_j.getTail());
				unionFind[findLocation(list_j)] = null;
				list_j.removeList();
			}
			else {
				LinkedNode currentNode = list_i.getHead(); 
				for(int k=0; k<list_i.getSize(); k++) {
					currentNode.setRep(list_j.getHead());
					currentNode = currentNode.getNext();
				}
				
				list_j.getTail().setNext(list_i.getHead());
				list_j.setTail(list_i.getTail());
				unionFind[findLocation(list_i)] = null;
				list_i.removeList();
			}
			decreaseSize();
		}
	}
	
	public LinkedList<T> find_set(int i) {
		LinkedList<T> set = null;
		for(int j=0; j<currentSize; j++) {
			if(unionFind[j].getHead().getValue() == i) {
				set = unionFind[j];
			}
		}
		return set;
	}
	
	public int final_sets() {

		for(int i=0; i<currentSize; i++) {
		
			if(unionFind[i].getHead().getValue() == (i+1)) {
				continue;
			}
			else {
				unionFind[i].getHead().setValue(i+1);
			}
		}
		state = 0;
		return currentSize;
	}
	
	//additional function to remove the set that represents the blank space so that the unionFind collection only
	//contains the sets that represents characters from potentially a-z
	public void removeSet(char character) {
		if(state == 1) {
			LinkedList<T> blankSet = find_set(character);
			int blankSetLoc = findLocation(blankSet);
			
			LinkedList<T>[] temp = new LinkedList[currentSize-1];
			int tempIndex = 0;
			for(int i=0; i<currentSize; i++) {
				if(i == blankSetLoc) {
					continue;
				}
				else {
					temp[tempIndex] = unionFind[i];
					tempIndex++;
				}
			}
			unionFind = temp;
			currentSize--;
		}
	}
	
	//additional function that returns the number of sets in the array 
	public int numberOfSets() {
		return currentSize;
	}
	
	//additional function to sort the array by the sets representative values
	public void sortArray(){
		Arrays.sort(unionFind, new sortByRep());
	}
}
