//Name           : Tyler Roberts
//Student Number : 250922271

import java.util.*;
import java.io.*;

public class Graph {
	
	int vertices; //n = number of vertices passed through
	LinkedList<Edge>[] adjacencyEdgeList;//all edges
	Node[] nodes;//elements to pass into Heap
	String path="", edges=""; //strings to print for output
	
	//constructor
	public Graph(int vertices) {
		this.vertices = vertices;
		adjacencyEdgeList = new LinkedList[vertices + 1];
		
		//creates an empty linkedList to store all edges for every vertex
		for(int i=1; i <= vertices; i++) {
			adjacencyEdgeList[i] = new LinkedList<>();
		}
	}
	
	//adds an edge to the adjacency list
	public void addEdge(int start, int end, int weight) {
		Edge edge = new Edge(start, end, weight);
		adjacencyEdgeList[start].add(edge);
		
	}
	
	//computes dijkstras algorithm for the shortest path from the source to every other vertex
	public void dijkstrasAlgorithm(int sourceVertex) {
		int INFINITY = Integer.MAX_VALUE;
		LinkedList<Node> shortestPath = new LinkedList<>(); //contains the shortest path nodes
		Node[] nodes = new Node[vertices + 1]; //creates a list of nodes to pass into the heap
		
		for(int i=1; i<=vertices; i++) {
			nodes[i] = new Node(INFINITY, i);
		}
		
		nodes[sourceVertex].setCost(0);
		
		Heap heap = new Heap(nodes, vertices); 
		
		//pops the min of the heap, adds it to shortest path, the path string
		//then iterates through all of its outgoing edges, updating the costs of the nodes in the heap if necessary
		while(heap.isEmpty() != true) {
			Node currentNode = heap.delete_min();
			path = path + ("	Vertex 1 to Vertex " + currentNode.getID() + " -- Total Cost: " + currentNode.getCurrentCost() + "\n");
			shortestPath.add(currentNode);
			
			if(heap.isEmpty() == true) {
				break;
			}
			
			LinkedList<Edge> adjacentEdges = adjacencyEdgeList[currentNode.getID()];
			
			for(int i=0; i< adjacentEdges.size(); i++) {
				Edge currentEdge = adjacentEdges.get(i);
				
				if(heap.in_heap(currentEdge.getEndNode()) == true) {
					heap.decrease_key(currentEdge.getEndNode(), currentNode.getCurrentCost() + currentEdge.getWeight());
					
				}
			}
		}	
	}
	
	//to string that will print the output after dijkstra's algorithm has computed
	public void to_string() {
		for(int i=1; i<=vertices; i++) {
			edges = edges + "	Vertex " + i + " Outgoing Edges -- ";
			
			LinkedList currentList = adjacencyEdgeList[i]; 
			for(int j=0; j<currentList.size(); j++) {
				Edge currentEdge = (Edge) currentList.get(j);
				edges = edges + " (to Vertex " + currentEdge.getEndNode() + "|cost = " + currentEdge.getWeight() + "),";
			}
			edges = edges + "\n";
		}
		System.out.println("Part One: (All Edges)");
		System.out.println(edges);
		System.out.println("\nPart Two: (Dijkstra's Shortest Paths)");
		System.out.println(path);
	}
	
}
