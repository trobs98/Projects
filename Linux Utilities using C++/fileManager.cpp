/* Author: Tyler Roberts
 * Description: Used as the file manager where functions can be applied to a file
 * Date: October 3, 2019
 */

using namespace std;
#include "fileManager.h"

/* Function Name: fileManager
 * Description: Constructor
 * Paramater Description: String corresponding to a filename
 * Return Description: Does not return (it is a class constructor)
 */
fileManager::fileManager(const string& fileName) {
    int pos;

    if (stat(fileName.c_str(), &results) == 0) {

        name = fileName;
        size = results.st_size;

        int currentType = (int) results.st_mode;

        //breaks up the currentType given from results into binary. This allowed me to
        // break up the bits into file type and then later on into the permissions as well
        string typeBits = bitset<18>(currentType).to_string();
        type = typeBits.substr(0,6); //the first 6 bits were the file type

        if(type == "010001"){
            type = "Socket";
        }

        else if(type == "001100"){
            type = "Symbolic Link";
        }

        else if(type == "001000"){
            type = "Regular File";
        }

        else if(type == "000110"){
            type = "Block Device";
        }

        else if(type == "000100"){
            type = "Directory";
        }

        else if(type == "000010"){
            type = "Character Device";
        }

        else if(type == "000001"){
            type = "FIFO";
        }

        //intializing the owner instance variable that I chose store as a struct
        //with a integer id field and a string username field
        fileOwner.id = results.st_uid;
        struct passwd *pwd = getpwuid(fileOwner.id);
        fileOwner.username = pwd->pw_name;

        //intializing the group instance variable that I chose store as a struct
        //with a integer id field and a string groupname field
        fileGroup.id = results.st_gid;
        struct group *grp = getgrgid(fileGroup.id);
        fileGroup.groupname = grp->gr_name;


        string permissionBits = typeBits.substr(6,12);//bits 6 till the end are the permission bits

        //loops through all 12 bits. When divided by 3, if the current bit's remainder is 0, then it refers to the
        //execution permission, if the current bit's remainder is 1, then it refers to the write permission and
        //if the current bit's remainder is 2, it refers to the read permission.
        for(int i=1; i<13; i++) {
            if (permissionBits[i] == '1') {
                if (i % 3 == 0) {
                    permissions = permissions.append("x");
                } else if (i % 3 == 1) {
                    permissions = permissions.append("w");
                } else {
                    permissions = permissions.append("r");
                }
            } else {
                permissions = permissions.append("-");
            }
        }

        time_t preAccessTime = results.st_atime;
        accessTime = ctime(&preAccessTime);

        time_t preModificationTime = results.st_mtime;
        modificationTime = ctime(&preModificationTime);

        time_t preStatusChangeTime = results.st_ctime;
        statusChangeTime = ctime(&preStatusChangeTime);

        blockSize = results.st_blksize;

    }
    else{
        cout << "Invalid file name'" << fileName <<"'. Object should be destroyed.\n";
    }
}

//destructor
fileManager::~fileManager(){}

//getter methods
string fileManager::getName(){
    return name;
}

string fileManager::getType(){
    return type;
}

off_t fileManager::getSize() {
    return size;
}

myOwner fileManager::getOwner(){
    return fileOwner;
}

myGroup fileManager::getGroup(){
    return fileGroup;
}

string fileManager::getPermissions(){
    return permissions;
}

string fileManager::getAccessTime(){
    return accessTime;
}

string fileManager::getModificationTime(){
    return modificationTime;
}

string fileManager::getStatusChangeTime(){
    return statusChangeTime;
}

blksize_t fileManager::getBlockSiZe(){
    return blockSize;
}

vector<fileManager*> fileManager::getChildren(){
    return children;
}

int fileManager::getErrorNumber(){
    return errorNumber;
}

//member functions

/* Function Name: dump
 * Description: takes in an open file stream, and the dumps the callers contents into the file stream
 * Paramater Description: ofstream which should be an open filestream
 * Return Description: returns an integer, either 0 for a successful operation, or errno for an unsuccessful operation
 */
int fileManager::dump(ofstream &outStream){
    if(type == "Regular File"){
        fstream inFile;
        inFile.open(name.c_str());

        char *buffer = new char[size];
        inFile.read(buffer, size);

        outStream.write(buffer, size);
        inFile.close();
        outStream.close();
        errorNumber = 0;
        return 0;
    }
    else{
        errorNumber = ENOTSUP;
        return errorNumber;
    }
}

/* Function Name: renameFile
 * Description: takes in a string that corresponds to the new name that you want to call the caller's file
 * Paramater Description: a string that is the new name of the file
 * Return Description: returns an integer, either 0 for a successful operation, or errno for an unsuccessful operation
 */
int fileManager::renameFile(string newName){
    int result;
    result = rename(name.c_str(), newName.c_str());

    if(result != 0){
        errorNumber = errno;
        return result;
    }
    else{
        name = newName;
        errorNumber = errno;
        return result;
    }

}

/* Function Name: removeFile
 * Description: removes the caller's file from the file system as well as deleting the caller's object
 * Paramater Description: no paramaters
 * Return Description: returns an integer, either 0 for a successful operation, or errno for an unsuccessful operation
 */
int fileManager::removeFile(){
    int result;
    result = unlink(name.c_str());

    if (result != 0) {
        errorNumber = errno;
        return result;
    }
    errorNumber = result;
    delete this;
    return result;
}

/* Function Name: compareFiles
 * Description: compares the caller file to another one to see if they are the same. If they are, it will
 *              print to the screen that they are the same, if not it will print to the screen that they are different
 * Paramater Description: Another fileManager object (should be a regular file type or it won't compare)
 * Return Description: returns an integer, either 0 for a successful operation, or errno for an unsuccessful operation
 */
int fileManager::compareFiles(fileManager *file){
    if(file->getType() != "Regular File"){
        errorNumber = 1;
        cout << "Cannot compare these files.\n";
        return 1;
    }

    ifstream thisFile, paramFile;

    thisFile.open(name.c_str());
    paramFile.open(file->getName().c_str());

    int thisLines, paramLines;
    thisLines = 0;
    paramLines = 0;
    string str;

    //checks to see how many lines each file has
    while(!thisFile.eof()){
        getline(thisFile,str);
        thisLines++;
    }
    while(!paramFile.eof()){
        getline(paramFile,str);
        paramLines++;
    }

    paramFile.clear();
    paramFile.seekg(0, ios::beg);

    thisFile.clear();
    thisFile.seekg(0, ios::beg);

    //compares the number of lines of the files, if they're different then they will be different files
    if(paramLines != thisLines){
        cout << "Different Files. \n";
        thisFile.close();
        paramFile.close();
        errorNumber = 0;
        return 0;
    }
    //if they have the same number of lines, then we will go character by character and compare the two files
    else {
        char thisString[256], paramString[256];
        int j=0;

        while(!thisFile.eof()){
            thisFile.getline(thisString, 256);
            paramFile.getline(paramString, 256);
            j++;

            if(strcmp(thisString, paramString) != 0){
                cout << "Different Files. \n";
                paramFile.close();
                thisFile.close();
                errorNumber = 0;
                return 0;
            }
        }
        thisFile.close();
        paramFile.close();
        cout << "Same Files. \n";
        errorNumber = 0;
        return 0;
    }
}

/* Function Name: expandFile
 * Description: if the file is a directory, it will create a fileManager object for each of it's children files
 * Paramater Description: no parameters
 * Return Description: returns an integer, either 0 for a successful operation, or errno for an unsuccessful operation
 */
int fileManager::expandFile(){
    if(type == "Directory"){
        DIR *currentDirectory;
        dirent *entry;
        fileManager *newFile;

        currentDirectory = opendir(name.c_str());

        while((entry = readdir(currentDirectory)) != NULL){

            //skips previous parent files and current files
            if(strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0) {
                continue;
            }
            else{
                newFile = new fileManager(name+"/"+entry->d_name);
                children.push_back(newFile);
            }
        }
        closedir(currentDirectory);
        return 0;
    }
    else{
        errorNumber = ENOTSUP;
        return 1;
    }
}






