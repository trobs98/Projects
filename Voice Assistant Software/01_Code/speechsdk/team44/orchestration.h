#ifndef ORCHESTRATION_H
#define ORCHESTRATIONN_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "GetTime.h"
#include "GetDate.h"
#include "todo.h"
#include "Alarm.h"
#include "math3307.h"
#include <speechapi_cxx.h>


class orchestration{
	public:
		//constructor
		orchestration();
		//public function
		void addCommand(std::string text);
	
	private:
		//instance variables and class variables
		std::string toParse;
		todo *myList;
		std::string output;
		std::vector<std::string> libraryNumbers {"1","one","2","two","3","three","4","four","5","five","6","six","7","seven","8","eight","9","nine"};
		
		//private functions
		std::vector<std::string> parseText(std::string text);
};

#endif
