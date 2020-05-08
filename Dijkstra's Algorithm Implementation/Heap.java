//Name           : Tyler Roberts
//Student Number : 250922271

public class Heap {
	 //current number of elements in heap
	 //max possible size of heap
	//heap array
	private Node[] originalArray; //original array of nodes passed into heap constructor
    private Node[] Heap; //heap array 
    private int size; //number of node in heap
    private int maxsize; //total number of possible nodes (the n that is passed into heap constructor)
    
    //returns the parent's array index of id in heap
    private int parent(int id) {
    	return id/2;
    }
    //returns the left child's array index of id in heap
    private int left(int id) {
    	return 2*id;
    }
    //returns the right child's array index of id in heap
    private int right(int id) {
    	return 2*id + 1;
    }
    //checks to see if a given array index is a leaf node in the heap 
    private boolean isLeaf(int id) {
    	if(id >= (size/2) && id <= size) {
    		return true;
    	}
    	return false;
    }
    
    //swaps two elements in the heap given the array indices id1 and id2
    private void swap(int id1,int id2) {
    	Node temp = Heap[id1];
    	Heap[id1] = Heap[id2];
    	Heap[id2] =  temp;
    }
    
    //heapify (used after deleting the min to restructure the heap)
    private void heapify(int id) {
    	if(!isLeaf(id)) {
    		
    		if(Heap[id].getCurrentCost() > Heap[left(id)].getCurrentCost() || Heap[id].getCurrentCost() > Heap[right(id)].getCurrentCost()) {
    			
    			if(Heap[left(id)].getCurrentCost() < Heap[right(id)].getCurrentCost()) {
    				swap(id, left(id));
    				heapify(left(id));
    			}
    			
    			else {
    				swap(id, right(id));
    				heapify(right(id));
    			}
    		}
    	}
    }
    
    //inserts the node into the heap and readjusts the nodes to maintain heap order
    private void insert(Node node) {
    	size++;
    	Heap[size] = node;
    	int current = size;
    	
    	while(current != 1 && Heap[parent(current)].getCurrentCost() > Heap[current].getCurrentCost()) {
    		swap(current, parent(current));
    		current = parent(current);
    	}
    	
    }
    
    //used for when the node is in the incorrect place in the heap (after adjusting the key of a node)
    private void bubbleUp(int id) {
    	if(id != 1) {
    		int parentIndex = parent(id);
    		int currentIndex = id;
    		
    		while(currentIndex > 1 && Heap[currentIndex].getCurrentCost() < Heap[parentIndex].getCurrentCost()) {
    			swap(currentIndex, parentIndex);
    			currentIndex = parentIndex;
    			parentIndex = parent(parentIndex);
    		}
    	}
    }
    
    //checks to see if the heap is empty
    public boolean isEmpty() {
    	if(Heap[1] == null) {
    		return true;
    	}
    	return false;
    }
    
    //heap constructor
    public Heap(Node[] keys, int n){
    	originalArray = keys;
    	maxsize = n;
    	size = 0;
    	Heap = new Node[n+1];
    	
    	//inserts all the original nodes into the heap (leaving index 0 to be empty)
    	for(int i=1; i<=maxsize; i++) {
    		insert(originalArray[i]);
    	}
    }
    
    //sees if a given id is in the heap by looping through the heap array
    public boolean in_heap(int id) {
   
    	for(int i=1; i<=size; i++) {
    		if(Heap[i].getID() == id) {
    			return true;
    		}
    	}
    	return false;
    }
    
    //returns the minimum key (node's key at index 1 of heap)
    public int min_key() {
    	return Heap[1].getCurrentCost();
    }
    
    //returns the minimum ID (node's ID at index 1 of heap)
    public int min_id() {
    	return Heap[1].getID();
    }
    
    //returns the key of an ID that is in the heap, otherwise it returns -1 as default if the ID does not exist in the heap
    public int key(int id) {
    	int key = -1;
    	if(in_heap(id) == true) {
    		for(int i=1; i<=size; i++) {
    			if(Heap[i].getID() == id) {
    				key = Heap[i].getCurrentCost();
    			}
    		}
    	}
    	return key;
    }
    
    //removes the minimum node of heap, replaces it with last element in the heap array, 
    //and then heapifiys, if the size of the heap is greater then 1, in order to maintain heap order
    public Node delete_min() { 
    	Node node = Heap[1];
    	Heap[1] = Heap[size];
    	Heap[size] = null;
    	size--;
    	
    	if(size > 1) {
    		heapify(1);
    	}
    	return node;
    	
    }
    
    //sets the key of a node with the ID id, to new_key, if the new_key is smaller then the nodes original key
    //then it bubblesUp to maintain the heap order
    public void decrease_key(int id, int new_key) {
    	if(in_heap(id) == true) {
    		for(int i=1; i<=size; i++) {
    			if(Heap[i].getID() == id) {
    				if(Heap[i].getCurrentCost() > new_key) {
    					Heap[i].setCost(new_key);
    					bubbleUp(i);
    				}
    				break;
    			}
    		}
    	}
    }
    
    //prints the heap by looping through the indices of the heap (mainly used for testing my code)
    public void printHeap() {
    	for(int i=1; i<size+1; i++) {
    		System.out.println("Index: " + i + " Node: "+ Heap[i].getID() + " Cost: " + Heap[i].getCurrentCost());
    	}
    }  
}