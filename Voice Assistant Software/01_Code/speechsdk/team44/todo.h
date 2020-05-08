#ifndef TODO_H
#define TOODO_H

#include <utility>
#include <string>
#include <iostream>

class todo{ 
	
	public:
		todo();
		int addToList(std::string description, std::string date);
		void getMyToDo(); 
		int markCompleted(std::string task);
		std::string getOutput();
		int getSize();
	private:
		struct item {

			std::string description; //struct to hold items for list
			std::string date;
			bool complete;
		};
		
		//instance & global variables
		item list[20]; //max list size is 20
		int size;
		bool complete = false;
		std::string output;
};

#endif
