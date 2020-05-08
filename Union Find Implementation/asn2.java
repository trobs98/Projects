//Name: Tyler Roberts
//Student Number: 250922271

import java.util.Scanner;
import java.io.*;

public class asn2 {
	public static void main(String [] args) throws Exception {
		
		File file = new File(args[0]);//change to args
		Scanner scanner = new Scanner(file);
		char[][] imageArray = new char[71][71];
		
	//part 1
		System.out.println("Part 1 \n  Binary Image: " + "\n");
		int arrayIndex = 0;
		while(scanner.hasNextLine()) {
			String lineCurrent = scanner.nextLine();
			char[] currentArray = lineCurrent.toCharArray();
			
			for(int i=0; i<71; i++) {
				
				if(currentArray[i] == '+') {
					System.out.print("1");
					imageArray[arrayIndex][i] = '1';
				}
				else {
					System.out.print("0");
					imageArray[arrayIndex][i] = '0';
				}
			}
			
			arrayIndex++;
			System.out.print("\n");
		}
		scanner.close();
		
		
	//part2
		System.out.println("\n\n" + "Part 2 \n  Connected Components Image: " + "\n");

		char currentChar = 'a';
		int rowsIndex = 0, columnsIndex = 0;
		
		for(rowsIndex = 0; rowsIndex<71; rowsIndex++) {
			for(columnsIndex = 0; columnsIndex<71; columnsIndex++) {
				if(imageArray[rowsIndex][columnsIndex] == '1') {
					updateNear(imageArray, currentChar, rowsIndex, columnsIndex);
					currentChar++;
				}
				else if(imageArray[rowsIndex][columnsIndex] == '0') {
					imageArray[rowsIndex][columnsIndex] = ' ';
				}
			}
		}
		
		//prints picture
		for(int i=0; i<71; i++) {
			for(int j=0; j<71; j++) {
				System.out.print(imageArray[i][j]);
			}
			System.out.print("\n");
		}
		
	//part 3
		System.out.println("\n\nPart 3 \n  Sorted Collection + it's size and component label:\n");
		uandf collection = new uandf(71*71);
		int rowIndex = 0, collectionInt = 1;
		
		while(rowIndex < 71) {
			for(int columnIndex=0; columnIndex<71; columnIndex++) {
				
					LinkedList currentList = collection.find_set(collectionInt);
					LinkedList possibleList = collection.find_set((int) (imageArray[rowIndex][columnIndex]) + 5041); //use a 5041 offset so that the values are unique (different from char ASCII values)
					
					currentList.getHead().setRowIndex(rowIndex);
					currentList.getHead().setColumnIndex(columnIndex);
					
					if(possibleList != null) {
						collection.union_sets(possibleList.getHead().getValue(), currentList.getHead().getValue());
						
					}
					else {
						currentList.getHead().setValue(imageArray[rowIndex][columnIndex] + 5041); //use a 5041 offset so that the values are unique (different from char ASCII values)
					}
					collectionInt++;
				}
			rowIndex++;
		}
		
		collection.removeSet((char)(' ' + 5041)); //removes the blank set 
		collection.final_sets();
		collection.sortArray();
		
		
		for(int i=1; i< collection.numberOfSets()+ 1; i++) {
			System.out.println("Set " + i + ") \nsize = " + collection.unionFind[i-1].getSize() + "\ncomponent = " + (char) (collection.unionFind[i-1].getHead().getValue() + 96)); //96 is ASCII offset created from using final set
			System.out.println("");
		}
		
	//part 4
		System.out.println("\n\nPart4\n  Connected component image minus components of size 2 or less: \n");
		char[] badComponents = new char[collection.numberOfSets()];
		int badCompIndex = 0;
		
		for(int i=0; i<collection.numberOfSets(); i++) {
			if(collection.unionFind[i].getSize() <= 2) {
				badComponents[badCompIndex] = ((char)(collection.unionFind[i].getHead().getValue() +96));
				badCompIndex++;
			}
		}
		for(int i=0; i<badCompIndex; i++) {
			LinkedList list = collection.find_set(badComponents[i]-96);
			LinkedNode node = list.getHead();
			while(node != null) {
				imageArray[node.getRowIndex()][node.getColumnIndex()] = ' ';
				node = node.getNext();
			}
		}
		
		//prints picture
		for(int i=0; i<71; i++) {
			for(int j=0; j<71; j++) {
				System.out.print(imageArray[i][j]);
			}
			System.out.print("\n");
		}
		
	}
	
	//recursive function used to update the image so that connected components are the same character 
	//from potentially a-z
	public static void updateNear(char[][] array,char i, int row, int column) {
		if(array[row][column] != '1') { //base case
			return;
		}
		else {
			array[row][column] = i;
			if(row == 0 && column == 0) { //top left corner
					updateNear(array, i, (row+1), column);
					updateNear(array, i, row, (column+1));
			}
			else if(row == 0 && column < 70) { //first row - (top left and top right corner) 
					updateNear(array, i, (row+1), column);
	
					updateNear(array, i, row, (column+1));
				
					updateNear(array, i, row, (column-1));
			}
			else if(column == 0 && row < 70) { //first column - (top left and bottom left corner)
					updateNear(array, i, (row+1), column);
				
					updateNear(array, i, row, (column+1));
				
					updateNear(array, i, (row-1), column);
				
			}
			
			else if(column == 70 && row == 70) { //bottom right corner 
					updateNear(array, i, (row-1), column);
			
					updateNear(array, i, row, (column-1));
			}
			
			else if(row == 0 && column == 70 ) { //top right corner
					updateNear(array, i, row, (column-1));
				
					updateNear(array, i, (row+1), column);

			}
			
			else if(row == 70 && column == 0) { //bottom left corner

					updateNear(array, i, (row-1), column);

					updateNear(array, i, row, (column+1));

			}
			
			else if(row == 70) { //last row - (bottom left and bottom right corner) 
			
					updateNear(array, i, row, (column-1));
				
					updateNear(array, i, row, (column+1));
			
					updateNear(array, i, (row-1), column);

			}
			
			else if(column == 70) { //last column - (top right and bottom right corner)
					updateNear(array, i, (row+1), column);
			
					updateNear(array, i, (row+1), column);
				
					updateNear(array, i, row, (column-1));
				
			}
			
			else {
					updateNear(array, i, (row+1), column);
				
					updateNear(array, i, row, (column+1));
				
					updateNear(array, i, (row-1), column);
				
					updateNear(array, i, row, (column-1));
				
			}
		}
	}
}
