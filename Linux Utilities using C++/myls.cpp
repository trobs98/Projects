/* Author: Tyler Roberts
 * Description: my ls function that prints the contents of the current working directory
 * Date: October 3, 2019
*/

using namespace std;
#include "fileManager.h"

int main(int argc, char *argv[]){
    struct stat results;

    string currentDir = ".";

    if(stat(currentDir.c_str(), &results) == 0){
        fileManager *currentDirectory = new fileManager(currentDir);
        currentDirectory->expandFile();
        vector<fileManager*> children = currentDirectory->getChildren();

        int vectorSize = children.size();

        //checks to see if the argument given is the -l option
        if(argc == 2 && strcmp(argv[1], "-l") == 0){
            for(int i=0; i<vectorSize; i++) {
                cout << children.at(i)->getPermissions() << " " <<
                     children.at(i)->getOwner().username << " " <<
                     children.at(i)->getGroup().groupname << " " <<
                     children.at(i)->getSize() << " " <<
                     children.at(i)->getAccessTime() << " " <<
                     children.at(i)->getName() << " " <<
                     "\n\n";
            }
        }
        //if any other argument is given other then the -l it sends an error message
        else if(argc >= 2){
            cout << "ERROR: Unrecognized option.\n";
        }
        else{
            for(int i=0; i<vectorSize; i++) {
                cout << children.at(i)->getName() << "\n";
            }
        }
    }
    else{
        cout << "No Such File or Directory.\n";
    }

    return 0;
}