

#include "Alarm.h"

/*! \brief C++ Alarm Program, to be used later in Voice Assitant Software
* @author: Seif Elmolla
*  This program simulates the alarm program to be used by Voice services
*/

using namespace std; 


    
void Alarm::process_command(){};

/*! \brief Alarm function to show clock
* 
* @parameters: String type
* @return: no reutrn
*
*/
void Alarm::show_clock(string type)
{
    // system call to clear the screen
    system("clear");
    printf("         %s         \n", type.c_str());
    printf(" --------------------------\n");
    cout << "| " << setfill('0') << setw(2) << hours << " hrs | ";
    cout << setfill('0') << setw(2) << minutes << " min | ";
    cout << setfill('0') << setw(2) << seconds << " sec |" << endl;
    printf("\n");
    
}
/*! \brief Alarm function to set timer
* 
* @parameters: Integer time and string type 
* @return: no reutrn
*
*/
void Alarm::set_timer(int time, string type)
{
    while (time > -1) {
          
        // display the timer
        show_clock(type);
  
        sleep(1);
        seconds++;
  
        if (seconds == 60) {
            minutes++;
            if (minutes == 60) {
                hours++;
                minutes = 0;
            }
            seconds = 0;
        }
        time--;
    }
    printf("\n%s Ringing \n\n", type.c_str());
    
}

  
  
/** Main Function
 * To run the program ./a.out [insert seconds]
 * Mimics "Set a timer for x amount of seconds"
 */
/*
int main(int argc, char *argv[])
{
    Alarm obj1;
    
    if (argc > 2) {
        if (!strcmp(argv[1], "Timer")){
            int x = atoi(argv[2]);
            obj1.set_timer(x, "timer");
        }
            else if (!strcmp(argv[1], "Alarm")){
            int x = atoi(argv[2]);
            obj1.set_timer(x, "alarm");
        }
        
    }
    else {
            printf("Error: run ./a.out Timer [seconds] or ./a.out Alarm [seconds] \n");
    }
    
    return 0; 
} */
