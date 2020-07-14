/* Author: Tyler Roberts
 * Description: my mv function that will move a file to a different directory (or rename it)
 * Date: October 3, 2019
*/

using namespace std;
#include "fileManager.h"

int main(int argc, char *argv[]){
    struct stat results;

    string temp = argv[1];

    if(stat(temp.c_str(), &results) == 0){
        fileManager *object = new fileManager(argv[1]);
        object->renameFile(argv[2]);
    }
    else{
        cout << "No Such File or Directory.\n";
    }

    return 0;
}