/* Author: Tyler Roberts
 * Description: my diff function that will compare two files to see if they are the same
 * Date: October 3, 2019
*/

using namespace std;
#include "fileManager.h"

int main(int argc, char *argv[]){

    struct stat results1;
    struct stat results2;

    string compare1 = argv[1];
    string compare2 = argv[2];

    if (stat(compare1.c_str(), &results1) == 0 && stat(compare2.c_str(), &results2) == 0) {
        fileManager *file1 = new fileManager(compare1);
        fileManager *file2 = new fileManager(compare2);

        file1->compareFiles(file2);
    } else {
        cout << "No Such File or Directory.\n";
    }

    return 0;
}