/**
*  @brief Gets the time
*  @author Tyler Roberts
*  This class will allow the user to get the time at different times of the day. 
* 	This could include future times or past times specified by a number and minutes or hours
*/

using namespace std;
#include "GetTime.h"

//PUBLIC FUNCTIONS

	/**
	*  @brief Constructor. 
	*  
	*  The constructor for the GetTime class that will take in 
	*  a command and parse it to send to it's corresponding function.
	*
	*  @param input string input which is the user command
	*/
GetTime::GetTime(string input){
    myInput = input; //input command
    vector<string> tokens;

    //split the input command into it's individual words
    istringstream iss(myInput);
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(tokens));

    //check to see that the input command is formatted correctly and check to see what they are asking for 
    if(tokens[0] == "What" && tokens[1] == "time" && tokens[2] == "is" && tokens[3] == "it"){
        if(tokens[4] == "right" && tokens [5] == "now?" && tokens.size() == 6){
            myOutput = getCurrentTime();
        }
        else if(tokens[4] == "in" && (tokens[6] == "minutes?" || tokens[6] == "minute?" ||
            tokens[6] == "hours?" || tokens[6] == "hour?") && tokens.size() == 7){
                if(tokens[5] == "one"){
                    myOutput = getFutureTime(1, tokens[6].substr(0,tokens[6].size()-1));
                }
                else if(is_number(tokens[5]) == true){
                    myOutput = getFutureTime(stoi(tokens[5]), tokens[6].substr(0,tokens[6].size()-1));
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
	*  @brief Destructor.
	*/
GetTime::~GetTime(){}

	/**
	*  @brief Gets the output.
	*  
	*  Returns the generated output from the inputted command that will be said back to the user.
	*
	*  @return the response generated 
 	*/
string GetTime::GetOutput(){
    return myOutput;
}


//MEMBER FUNCTIONS

	/**
	*  @brief sets output as error.
	*
	*  If the input command is incorrectly formatted then the output will be set to an error.
	*
	*  @return error string
	*/
string GetTime::setError(){
    return "ERROR: Incorrect format of question\n";
}

	/**
	*   @brief Is a string a number.
	*
	*	Checks to see if a string is a number.
	*
	*	@param s string token that is from the parsed command string
	*	@return True if it is a number, False otherwise
	*/
bool GetTime::is_number(const string& s){
    return !s.empty() && find_if(s.begin(), 
        s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

	/**
	*  @brief gets the current time.
	*
	*  Will return the current time.
	*
	*  @return a string response giving the current time 
	*/
string GetTime::getCurrentTime(){
    time_t now = time(0);
    tm *current = localtime(&now);

    string currentMinString = to_string(current->tm_min);
    if(current->tm_min < 10){
        currentMinString = '0' + to_string(current->tm_min);
    }

    if(current->tm_hour == 0){
        return to_string(12) + ":" + currentMinString + " AM\n";
    }
    else if(current->tm_hour == 12){
        return to_string(12) + ":" + currentMinString + " PM\n";
    }
    else if(current->tm_hour > 12){
        return to_string(current->tm_hour - 12) + ":" + currentMinString + " PM\n"; 
    }
    else{
        return to_string(current->tm_hour) + ":" + currentMinString + " AM\n";
    }
}
	/**
	*  @brief gets the future time.
	*
	*  Will return a time in the future specified by a number and whether that number is minutes or hours.
	*
	*  @param num the number of minutes or hours
	*  @param type specifies if the number is minutes or hours
	*  @return a string response giving the future time 
	*/
string GetTime::getFutureTime(int num, string type){
    time_t now = time(0);
    tm *current = localtime(&now);
    
    int currentHourTime = current->tm_hour;
    int currentMinuteTime = current->tm_min; 

    if(type == "hours" || type == "hour"){
        currentHourTime = currentHourTime + num;

        if(currentHourTime >= 24){
            currentHourTime = currentHourTime % 24;
        }     
    }
    else{
        currentMinuteTime = currentMinuteTime + num;

        if(currentMinuteTime >= 60){
            int howManyHours = currentMinuteTime/60;
            currentHourTime = currentHourTime + howManyHours;
            currentMinuteTime = currentMinuteTime % 60;

            if(currentHourTime >= 24){
                currentHourTime = currentHourTime % 24;
            }
        }
    }

    string currentMinString = to_string(currentMinuteTime);
    if(currentMinuteTime < 10){
        currentMinString = '0' + to_string(currentMinuteTime);
    }

    if(currentHourTime == 0){
        return to_string(12) + ":" + currentMinString + " AM\n";
    }
    else if(currentHourTime == 12){
        return to_string(12) + ":" + currentMinString + " PM\n";
    }
    else if(currentHourTime > 12){
        return to_string(currentHourTime - 12) + ":" + currentMinString + " PM\n"; 
    }
    else{
        return to_string(currentHourTime) + ":" + currentMinString + " AM\n";
    }
}

//TESTER 

//Must follow this format
/*
    -format 1 = "what time is it _z_ ?"
        - z = "", "right now", "currently"

    -format 2 = "what time is it in _x_ _y_ ?"
        - x = any positive number
        - y = "minutes", "hours" 
*/

/*
int main(){
    //treating input string to class as what will be the command given through speech later on
    cout << "\nTime currently: \n";
    GetTime timeNow = GetTime("what time is it ?");
    cout << timeNow.GetOutput();

    cout << "\nTime in 10 hours: \n";
    GetTime time = GetTime("what time is it in 10 hours ?");
    cout << time.GetOutput();

    cout << "\nTime in 3000 mins: \n";
    GetTime timeMins = GetTime("what time is it in 3000 minutes ?");
    cout << timeMins.GetOutput();

    cout << "\nError Command: \n";
    GetTime timeError = GetTime("what time is 2 minutes ?");
    cout << timeError.GetOutput();

}*/
