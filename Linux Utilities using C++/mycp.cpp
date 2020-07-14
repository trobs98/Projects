/* Author: Tyler Roberts
 * Description: my cp function that will copy a file to another location
 * Date: October 3, 2019
*/

using namespace std;
#include "fileManager.h"

int main(int argc, char *argv[]){
    struct stat results;

    string source = argv[1];
    string destination = argv[2];

    if(stat(source.c_str(), &results) == 0){
        fileManager *sourceFile = new fileManager(source);
        system(("touch " + destination).c_str());
        ofstream fs;
        fs.open(destination.c_str());
        sourceFile->dump(fs);

    }
    else{
        cout << "No Such File or Directory.\n";
    }

    return 0;
}
