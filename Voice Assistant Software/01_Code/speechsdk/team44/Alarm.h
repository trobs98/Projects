#ifndef ALARM_H
#define ALARMM_H

#include <iomanip> 
#include <iostream> 
#include <stdlib.h> 
#include <unistd.h>
#include <cstdlib>
#include <string.h>

int strcmp(const char *leftStr, const char *rightStr);

class Alarm{
	public:
		void show_clock(std::string type);
		void set_timer(int time, std::string type);
	private:
		void process_command();
		int hours = 0; /*!< hours attribute */
		int minutes = 0; /*!< minutes attribute */
		int seconds = 0; /*!< seconds attribute */
	
};

#endif
