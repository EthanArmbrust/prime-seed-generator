#include <iostream>
#include <string>
#include <dirent.h>
#include "apstring.h"
#include "apvector.h"

string logerino = "\\logs\\";
string logtxt = "log.txt";
string logFolder;


using namespace std;

void dirChecker(string pathName) {

string logFolder = pathName + logerino;
 const char * folderPath = logFolder.c_str();

apvector <string> files(30);
int x = 0;

    DIR*     dir;
    dirent*  pdir;

    dir = opendir(folderPath);     // open current directory

    while (pdir = readdir(dir)) {
        //cout << pdir->d_name << endl;
	files[x] = pdir->d_name;
	x++;
    }
	//cout << "BUFFER" << endl;
	//cout << files[4] << endl;
	string shortFilename = files[2];
	string totalFilename = logFolder + shortFilename;
	//cout << totalFilename << endl;
	string fullNew = logFolder + logtxt;
  const char * oldname = totalFilename.c_str();
  const char * newname = fullNew.c_str();
  rename( oldname , newname );



    closedir(dir);

}

