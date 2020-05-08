/**
*
* @brief Get the date.
* @author : Tyler Roberts
* The user can ask a variety of questions (as specified by the commandList) to 
* 	return different values regarding the date (ex. past, present, future)
*
*/          

using namespace std;
#include "GetDate.h"


//PUBLIC FUNCTIONS

	/**
	*  @brief Constructor.
	*
	*  The constructor for the GetDate class that will take in a command and parse
	*  it to send it to it's corresponding function. 
	*
	*  @param input string input which is the user command
	*/
GetDate::GetDate(string input){
    myInput = input;//input command
    vector<string> tokens;

    //converts the input string into its individual words
    istringstream iss(myInput);
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(tokens));
    
    //check to see that the input command is formatted correctly and check to see what they are asking for 
    if(tokens[0] == "What" && tokens[1] == "day" && tokens[3] == "it"){
        if(tokens[2] == "is"){
            
            if(tokens[4] == "today?" && tokens.size() == 5){
                myOutput = getFutureDate(0,"days");
            }
            else if(tokens[4] == "tomorrow?" && tokens.size() == 5){
                myOutput = getFutureDate(1, "days");
            }
            else if(tokens[4] == "in" && 
                    find(tokenSixAllowable.begin(), tokenSixAllowable.end(), tokens[6]) != tokenSixAllowable.end()
                    && tokens.size() == 7){
                        
                if(tokens[5] == "one"){
                    myOutput = getFutureDate(1, tokens[6].substr(0,tokens[6].size()-1));
                }
                else if(is_number(tokens[5]) == true){
                    myOutput = getFutureDate(stoi(tokens[5]), tokens[6].substr(0,tokens[6].size()-1));
                }
                else{
                    myOutput = setError();
                }
            }
            else{
                myOutput = setError();
            }
        }

        else if(tokens[2] == "was"){
            
            if(tokens[4] == "yesterday?" && tokens.size() == 5){
                myOutput = getPreviousDate(1, "day");
            }
            else if( 
                    find(tokenSixAllowable.begin(), tokenSixAllowable.end(), tokens[5]) != tokenSixAllowable.end() && 
                    tokens[6] == "ago?" && tokens.size() == 7){
                
                if(tokens[4] == "one"){
                    myOutput = getPreviousDate(1, tokens[5]);
                }
                else if(is_number(tokens[4]) == true){
                    myOutput = getPreviousDate(stoi(tokens[4]), tokens[5]);
                }
                else{
                    myOutput = setError();
                }

            }
            else{
                myOutput = setError();
            }
        }

        else{
            myOutput = setError();
        }
    }
    else{
        myOutput = setError();
    }
}

	/**
	* @brief Destructor.
	*/
GetDate::~GetDate(){};

	/**
	*  @brief Gets the output.
	*
	*  Returns the generated output from the inputted command that will be said back to the user.
	*
	*  @return the response generated 
 	*/
string GetDate::getOutput(){
    return myOutput;
}


//MEMBER FUNCTIONS

	/**
	*   @brief is a string a number.
	*
	*	Checks to see if a string is a number.
	*
	*	@param s string token that is from the parsed command string, which is being tested to see if it is a number
	*	@return True if it is a number, False otherwise
	*/
bool GetDate::is_number(const string& s){
    return !s.empty() && find_if(s.begin(), 
        s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

	/**
	*  @brief sets output as error
	*
	*  If the input command is incorrectly formatted then the output will be set to an error.
	*
	*  @return error string
	*/
string GetDate::setError(){
    return "ERROR: Incorrect format of question\n";
}

	/**
	*  @brief gets a previous date.
	*
	*  Will return a previous date specified by how many days, weeks or years ago.
	*
	*  @param num the number of days, weeks or years
	*  @param type specifies if they want days, weeks, years
	*  @return a string response giving the previous date
	*/
string GetDate::getPreviousDate(int num, string type){
    int updateNum;
    
    time_t today = time(0);
    tm *td = localtime(&today);

    //All variables reflecting the CURRENT date
    int currentDate = td->tm_mday;
    int currentDay = td->tm_wday;
    int currentMonth = td->tm_mon;
    int currentYear = td->tm_year + 1900;

    if(type == "day" || type == "days"){
        updateNum = num;
    }
    else if(type == "week" || type == "weeks"){
        updateNum = num * 7; //7 days in a week
    }
    //type == "year" || type == "years"
    //by year refers to exact same day (ex. October 31) just __ years ago
    else{
        tm yearsAgo = {0,0,0,currentDate,currentMonth,(currentYear - num - 1900)};
        time_t year = mktime(&yearsAgo);

        tm *time_out = localtime(&year);
        currentDay = time_out->tm_wday;

        return to_string(num) + " " + type +" ago was " + days[currentDay] + ", " + months[currentMonth].name + " " + to_string(currentDate) + 
        ", " + to_string(currentYear - num) + "\n"; 
    }
    
    //repeat until updateNum is 0 which means that the current date takes in consideration
    //all of the previous days
    while(updateNum != 0){
        if(updateNum + 1 > currentDate){
            
            //if the current month is January then we have to go back to December and decrease the year
            if(currentMonth == 0){
                updateNum = updateNum - currentDate;
                currentMonth = 11;
                currentYear--;
                currentDate = months[currentMonth].days;
            }
            //if the month is march then we have to check to see if the year is a leap year or not
            //which will determine how many days February has
            else if(currentMonth == 2){
                //leap year
                if(currentYear % 4 == 0){
                    updateNum = updateNum - currentDate;
                    currentMonth--;
                    currentDate = months[currentMonth].days + 1;
                }
                //non-leap year
                else{
                    updateNum = updateNum - currentDate;
                    currentMonth--;
                    currentDate = months[currentMonth].days;
                }
            }

            else{
                updateNum = updateNum - currentDate;
                currentMonth--;
                currentDate = months[currentMonth].days;
            }
        }

        else{
            currentDate = currentDate - updateNum;
            updateNum = 0;
        }
    }

    //create new time to make it easier to get the day of the week
    tm yearsAgo = {0,0,0,currentDate,currentMonth,(currentYear - 1900)};
    time_t year = mktime(&yearsAgo);

    tm *time_out = localtime(&year);
    currentDay = time_out->tm_wday;

    //if they ask for yesterday or 1 day ago
    if(num == 1 && type != "week" && type != "weeks?"){
        return "Yesterday was " + days[currentDay] + ", " + months[currentMonth].name + " " + to_string(currentDate) + 
        ", " + to_string(currentYear) + "\n"; 
    }

    //if they ask for any amount of previous days ago greater then 1
    else{
        return to_string(num) + " " + type +" ago was " + days[currentDay] + ", " + months[currentMonth].name + " " + to_string(currentDate) + 
        ", " + to_string(currentYear) + "\n"; 
    }
    
}

	/**
	*  @brief gets a future date.
	*
	*  Will return a future date specified by how many days, weeks or years ago.
	*
	*  @param num the number of days, weeks or years
	*  @param type specifies if they want days, weeks, years
	*  @return a string response giving the future date
	*/
string GetDate::getFutureDate(int num, string type){
    int updateNum;
    
    time_t today = time(0);
    tm *td = localtime(&today);

    //all the variables reflecting the CURRENT date
    int currentDate = td->tm_mday;
    int currentDay = td->tm_wday;
    int currentMonth = td->tm_mon;
    int currentYear = td->tm_year + 1900;

    if(type == "day" || type == "days" || type == "days?" || type == "day?"){
        updateNum = num;
    }
    else if(type == "week" || type == "weeks" || type == "week?" || type == "weeks?"){
        updateNum = num * 7; //7 days in a week
    }
    //type == "year" || type == "years"
    //by year refers to exact same day (ex. October 31) just __ years ago
    else{
        tm inYears = {0,0,0,currentDate,currentMonth,(currentYear + num - 1900)};
        time_t year = mktime(&inYears);

        tm *time_out = localtime(&year);
        currentDay = time_out->tm_wday;

        return "In " + to_string(num) + " " + type +" it will be " + days[currentDay] + ", " + months[currentMonth].name + " " + to_string(currentDate) + 
        ", " + to_string(currentYear + num) + "\n"; 
    }
    
    //repeat until updateNum is 0 which means that the current date takes in consideration
    //all of the future days
    while(updateNum != 0){
        //check to see if it's a leap year or not

        //leap year and february
        if(currentMonth == 1 && currentYear % 4 == 0){
            
            if(updateNum + currentDate > months[currentMonth].days + 1){
                
                if(currentDate == months[currentMonth].days + 1){
                    updateNum = updateNum - 1;
                }
                else{
                    updateNum = updateNum - (months[currentMonth].days + 1);

                }
                currentMonth++;
                currentDate = 1;
            }

            else{
                currentDate = currentDate + updateNum;
                updateNum = 0;
            }
        }

        //non-leap year
        else{
            if(updateNum + currentDate > months[currentMonth].days){

                //if the current month is December then we have to go to January and increase the year
                if(currentMonth == 11){
                    if(currentDate == months[currentMonth].days){
                        updateNum = updateNum - 1;
                    }
                    else{
                        updateNum = updateNum - (months[currentMonth].days);
                    }

                    currentMonth = 0;
                    currentYear++;
                    currentDate = 1;
                }

                else{

                    if(currentDate == months[currentMonth].days){
                        updateNum = updateNum - 1;
                    }
                    else{
                        updateNum = updateNum - (months[currentMonth].days - currentDate + 1);
                    }                            

                    currentMonth++;
                    currentDate = 1;
                }
            }

            else{
                currentDate = currentDate + updateNum;
                updateNum = 0;
            }
        }
    }

    //create new time to make it easier to get the day of the week 
    tm yearsAgo = {0,0,0,currentDate,currentMonth,(currentYear - 1900)};
    time_t year = mktime(&yearsAgo);

    tm *time_out = localtime(&year);
    currentDay = time_out->tm_wday;

    //if they ask for today
    if(num == 0){
        return "Today is " + days[currentDay] + ", " + months[currentMonth].name + " " + to_string(currentDate) + 
        ", " + to_string(currentYear) + "\n"; 
    }
    //if they ask for tomorrow
    else if(num == 1 && type != "week" && type != "weeks?"){
        return "Tomorrow is " + days[currentDay] + ", " + months[currentMonth].name + " " + to_string(currentDate) + 
        ", " + to_string(currentYear) + "\n"; 
    }

    //if they ask for any amount of future days greater then 1
    else{
        return "In " + to_string(num) + " " + type + " it will be " + days[currentDay] + ", " + months[currentMonth].name + " " + to_string(currentDate) + 
        ", " + to_string(currentYear) + "\n"; 
    }
    
}


