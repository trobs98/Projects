//Name           : Tyler Roberts
//Student Number : 250922271

import java.util.*;
import java.io.*;

public class asn3 {

	public static void main(String args[]) throws Exception {
		
		//scanner to read in the file
		File file = new File(args[0]);
		Scanner scanner = new Scanner(file);
		
		int vertices = Character.getNumericValue(scanner.nextLine().charAt(0)); //number of vertices from text file

		Graph graph = new Graph(vertices);//initialize the graph
		
		//iterate through the lines of the text file
		while(scanner.hasNextLine()) {
			String currentLine = scanner.nextLine();
			
			int currentStart = Character.getNumericValue(currentLine.charAt(0));//start node of current edge
			int currentEnd = Character.getNumericValue(currentLine.charAt(2));//end node of current edge
			int currentDistance = Integer.parseInt(currentLine.substring(5, currentLine.length()));//the cost to get from start to end of current edge
			
			graph.addEdge(currentStart, currentEnd, currentDistance);//add the edge to the graph
		}
		
		//perform dijkstra's algorithm on the edges of the graph with the source node's id = 1 and then prints the results
		graph.dijkstrasAlgorithm(1);
		graph.to_string();
	}
}
