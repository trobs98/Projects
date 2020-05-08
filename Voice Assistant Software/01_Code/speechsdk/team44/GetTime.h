#ifndef GETIME_H
#define GETTIME_H

//libraries
#include <ctime>
#include <string>
#include <iostream>
#include <algorithm> 
#include <sstream>
#include <iterator>
#include <vector>


class GetTime{
    
    public:
        //constructor
        GetTime(std::string input);
        //destructor
        ~GetTime();
        std::string GetOutput();
    
    private:
        std::string myInput;
        std::string myOutput;
        


        std::string getFutureTime(int num, std::string type);
        std::string getCurrentTime();
        bool is_number(const std::string& s);
        std::string setError();


};

#endif
