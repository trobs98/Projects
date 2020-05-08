/**
*A To-Do class that allows user to keep track of 
*tasks for specific dates.
*@author: Pouya Langary
*/
#include "todo.h"

using namespace std;

    /**
    *constructor that initializes size to 0
    */
todo::todo(){ 
    size = 0;
    
}
    /**
    * Adds provided description and date to the list of tasks in the to-do list
    * @param description A description of the task
    * @param date The date for the task 
    * @return 0 if successful, 1 if unsucessful
    */
int todo::addToList(string description, string date) {
    if (size > 20) { 
        output = "Unable to add to list because it is full\n";
        return 1;
    } else {
        item toAdd = {description, std::move(date)}; 
        !toAdd.complete; 
        list[size] = toAdd;
        output = "Successfully added: " + description + " to your list!\n";
    }
    size++;
    return 0;
}
    /**
    * iterates through array of tasks and outputs each task
    * @param none
    * @return void
    */
void todo::getMyToDo() {
    string toReturn="Here's what you have left on your list: \n";

    for (int i = 0; i < size; i++) { 
        if (list[i].complete == 0) {
            toReturn.append(list[i].description + " : " +list[i].date + " is incomplete\n");
        } else {
            toReturn.append(list[i].description + " : " +list[i].date + " is complete\n");
                        }
    }output = toReturn.append("\n");
}
    /**
    * iterate through list and mark provided task as completed
    * @param task to mark as completed
    * @return 0 if successful, 1 if failed 
    */
int todo::markCompleted(string task) {
    for(int i=0; i < size; i++){

        if(list[i].description.compare(task) == 0){
            list[i].complete = 1;
            output = task + " has been set as complete.\n";
            return 0;
        }
    }
    output = "The item that specified is not in your To Do List.\n";
    return 1;
    }
    /*
    * outputs the final string output
    * @param none
    * @return output
    */
string todo::getOutput(){
    return output;
    }
    /*
    * returns the size of the list
    * @param none
    * @return size
    */
int todo::getSize(){
    return size;
}