/* Author: Tyler Roberts
 * Description: my rm function that will remove a file
 * Date: October 3, 2019
*/

using namespace std;
#include "fileManager.h"

int main(int argc, char *argv[]){
    struct stat results;

    string temp;
    int currentArg = 1;
    while(currentArg < argc){
        temp = argv[currentArg];
        if(stat(temp.c_str(), &results) == 0){
            fileManager *file = new fileManager(temp);
            file->removeFile();
        }
        else{
            cout << "No Such File or Directory.\n";
        }
        currentArg++;
    }

    return 0;
}
