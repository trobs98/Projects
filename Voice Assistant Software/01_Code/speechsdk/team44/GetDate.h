#ifndef GETDATE_H
#define GETDATEE_H

//libraries
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <ctime>
#include <iostream>
#include <cmath>



class GetDate{

    public://structs
    struct month{
        int days;
        std::string name;
    };

        //global arrays
        month months[12] = {{31, "January"},{28, "February"}, {31, "March"}, {30, "April"}, {31, "May"}, {30, "June"},
                    {31, "July"}, {31, "August"}, {30, "September"}, {31, "October"}, {30, "November"}, {31, "December"}};

        std::string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

        std::vector<std::string> tokenSixAllowable = {"week", "weeks", "day", "days", "year", "years", "week?", "weeks?", "day?", "days?", "year?", "years?"};

        //constructor
        GetDate(std::string input);

        //destructor
        ~GetDate();

        std::string getOutput();
    
    private:
        //instance variables
        std::string myInput;
        std::string myOutput;

        bool is_number(const std::string& s);
        std::string setError();
        std::string getPreviousDate(int num, std::string type);
        std::string getFutureDate(int num, std::string type);
};

#endif
