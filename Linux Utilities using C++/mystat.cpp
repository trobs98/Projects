/* Author: Tyler Roberts
 * Description: my stat function that will return all the information of a file
 * Date: October 3, 2019
*/

using namespace std;
#include "fileManager.h"

int main(int argc, char *argv[]){
    struct stat results;

    string fileArg = argv[1];

    if(stat(fileArg.c_str(), &results) == 0){
        fileManager *file = new fileManager(fileArg);
        cout << "\nFile: " << file->getName() <<
             "\nType: " << file->getType() <<
             "\nSize: " << file->getSize() <<
             "\nBlock Size: " << file->getBlockSiZe() <<
             "\nOwner: " << file->getOwner().username << " / " << file->getOwner().id <<
             "\nGroup: " << file->getGroup().groupname << " / " << file->getGroup().id <<
             "\nPermissions: " << file->getPermissions() <<
             "\nAccess Time: " << file->getAccessTime() <<
             "Modification Time: " << file->getModificationTime() <<
             "Status Change Time: " << file->getStatusChangeTime() <<
             "\n";
    }
    else{
        cout << "No Such File or Directory.\n";
    }

    return 0;
}