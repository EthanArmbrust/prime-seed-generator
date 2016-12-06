#include <iostream>
#include <fstream>
#include <string>
#include "apstring.h"
#include "apvector.h"
#include "dirChecker.h"
#include "logChecker.h"
#include "windows.h"

using namespace std;
void bakup(const string theRootFolder);
void restore(const string theRootFolder);
bool dirExists(const string& dirName_in);

string metroid2 = "Metroid2.pak";
string metroid3 = "Metroid3.pak";
string metroid4 = "Metroid4.pak";
string metroid5 = "metroid5.pak";
string metroid6 = "Metroid6.pak";

string metroidRestore2 = "Metroid2.pak ";
string metroidRestore3 = "Metroid3.pak ";
string metroidRestore4 = "Metroid4.pak ";
string metroidRestore5 = "metroid5.pak ";
string metroidRestore6 = "Metroid6.pak ";

string full2;
string full3;
string full4;
string full5;
string full6;

string fullRestore2;
string fullRestore3;
string fullRestore4;
string fullRestore5;
string fullRestore6;

string copyCommand = "copy ";
string PakUp = " .\\PakBakUp\\";

string mostCommand2;
string mostCommand3;
string mostCommand4;
string mostCommand5;
string mostCommand6;

string mostRestoreCommand2;
string mostRestoreCommand3;
string mostRestoreCommand4;
string mostRestoreCommand5;
string mostRestoreCommand6;

string fullCommand2;
string fullCommand3;
string fullCommand4;
string fullCommand5;
string fullCommand6;

string fullRestoreCommand2;
string fullRestoreCommand3;
string fullRestoreCommand4;
string fullRestoreCommand5;
string fullRestoreCommand6;

void bakup(const string theRootFolder){
	
	system("md PakBakUp");
	
	
	full2 = theRootFolder + metroid2;
	full3 = theRootFolder + metroid3;
	full4 = theRootFolder + metroid4;
	full5 = theRootFolder + metroid5;
	full6 = theRootFolder + metroid6;
	
	mostCommand2 = copyCommand + full2;
	mostCommand3 = copyCommand + full3;
	mostCommand4 = copyCommand + full4;
	mostCommand5 = copyCommand + full5;
	mostCommand6 = copyCommand + full6;
	
	fullCommand2 = mostCommand2 + PakUp;
	fullCommand3 = mostCommand3 + PakUp;
	fullCommand4 = mostCommand4 + PakUp;
	fullCommand5 = mostCommand5 + PakUp;
	fullCommand6 = mostCommand6 + PakUp;
	
	
	system(fullCommand2.c_str());
	system(fullCommand3.c_str());
	system(fullCommand4.c_str());
	system(fullCommand5.c_str());
	system(fullCommand6.c_str());
	cout << "Copying complete" << endl;
}


void restore(const string theRootFolder){
	
	
	fullRestore2 = PakUp + metroidRestore2;
	fullRestore3 = PakUp + metroidRestore3;
	fullRestore4 = PakUp + metroidRestore4;
	fullRestore5 = PakUp + metroidRestore5;
	fullRestore6 = PakUp + metroidRestore6;
	
	mostRestoreCommand2 = copyCommand + fullRestore2;
	mostRestoreCommand3 = copyCommand + fullRestore3;
	mostRestoreCommand4 = copyCommand + fullRestore4;
	mostRestoreCommand5 = copyCommand + fullRestore5;
	mostRestoreCommand6 = copyCommand + fullRestore6;
	
	fullRestoreCommand2 = mostRestoreCommand2 + theRootFolder;
	fullRestoreCommand3 = mostRestoreCommand3 + theRootFolder;
	fullRestoreCommand4 = mostRestoreCommand4 + theRootFolder;
	fullRestoreCommand5 = mostRestoreCommand5 + theRootFolder;
	fullRestoreCommand6 = mostRestoreCommand6 + theRootFolder;
	
	
	system(fullRestoreCommand2.c_str());
	system(fullRestoreCommand3.c_str());
	system(fullRestoreCommand4.c_str());
	system(fullRestoreCommand5.c_str());
	system(fullRestoreCommand6.c_str());
	cout << "Restore complete" << endl;
}

bool dirExists(const string& dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}
