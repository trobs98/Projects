//Author: Tyler Roberts
//Description: Header file needed for fileManager.cpp which contains
//             libraries, structs, functions and instance varaiables needed
//             to function.
//Date: October 3, 2019

#ifndef FILEMANAGER_H
#define FILEMANGER_H

//libraries
#include "iostream"
#include "sys/stat.h"
#include "map"
#include "vector"
#include "bitset"
#include "string.h"
#include "pwd.h"
#include "grp.h"
#include "iterator"
#include "stdio.h"
#include "cstdio"
#include "time.h"
#include "errno.h"
#include "fstream"
#include "unistd.h"
#include "dirent.h"

struct myOwner{
    int id;
    string username;
};
struct myGroup{
    int id;
    string groupname;
};


class fileManager{

    public:
        fileManager(const string& fileName);//constructor
        ~fileManager(); //destructor

        //getter methods
        string getName();
        string getType();
        off_t getSize();
        myOwner getOwner();
        myGroup getGroup();
        string getPermissions();
        string getAccessTime();
        string getModificationTime();
        string getStatusChangeTime();
        blksize_t getBlockSiZe();
        vector<fileManager*> getChildren();
        int getErrorNumber();

        //other functions
        int dump(ofstream &outStream);
        int renameFile(string newName);
        int removeFile();
        int compareFiles(fileManager *file);
        int expandFile();

    private:

        //instance variables
        string name;
        string type;
        off_t size;
        myOwner fileOwner;
        myGroup fileGroup;
        string permissions;
        string accessTime;
        string modificationTime;
        string statusChangeTime;
        blksize_t blockSize;
        vector<fileManager*> children;
        int errorNumber = 0;
        struct stat results;
};

#endif