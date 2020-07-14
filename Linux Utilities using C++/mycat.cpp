/* Author: Tyler Roberts
 * Description: my cat function that will print the contents of a file to the screen
 * Date: October 3, 2019
*/

//COULD NOT GET THIS ONE TO WORK
using namespace std;
#include "fileManager.h"

int main(int argc, char *argv[]){
    struct stat results;
    string temp;
    int currentArg = 1;

    temp = argv[currentArg];
    if(stat(temp.c_str(), &results) == 0){
        system(("cat " + temp).c_str()); //used system cat
    }
    else{
        cout << "No Such File or Directory.\n";
    }


    return 0;
}