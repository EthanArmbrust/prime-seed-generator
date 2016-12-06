#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <thread>
#include <future>
#include "apstring.h"
#include "apvector.h"
#include "dirChecker.h"
#include "logChecker.h"
#include "windows.h"
#include "cleanup.h"

void mainMenu();
void processOption();
void getNormalSeed(bool print);
void getVeteranSeed(bool print);
void getEasySeed(bool print);
void getHypermodeSeed(bool print);
//void getMultipleSeed();
//void checkUpperBound();
//bool checkLowerBound();
void getHypermodeSeedOnly(bool print);
void getVeteranSeedOnly(bool print);
void getNormalSeedOnly(bool print);
void moveGoodSeeds(int difficulty, string logLocation);
void manualChecker();
void printMenu();
static void copyFile(const std::string& fileNameFrom, const std::string& fileNameTo);
bool fileExists(const std::string& fileName);
void genSettings();

using namespace std;





string randomizerPath;
string rootPath;
string exceptions;
string randomizerExe = "Prime_Randomizer.exe ";
string fullRandomizer;
string theE = " -e ";
apstring header1 = "			    Seed Generator v0.9";
apstring header2 = "			  by Interslice and Sjorec";
string copyThat = "copy ";
string fullCopy;
string fullExceptions;
string fullCommand;
string randoPath;
string logFile;
string option;
string printOption;
string upperBound;
string lowerBound;
string command1;
string command2;
string command3;
string command4;
string logForMoving;
string manualLogFile;
bool newRando;
string newRandomizer;
string popupBlocker;
bool popup;


const char * charCommand;
const char * charLog;
const char * charRoot;
const char * charExceptions;




int main(){

ifstream checkingFile ("File Paths.txt");	
if(!(checkingFile.is_open())){
checkingFile.close();
cout << "Folder where Prime_Randomizer.exe is located: " << endl;
cout << "Please leave a backslash (\\) at the end." << endl;
cout << "If any folders contain spaces, enclose those folders in quotation marks" << endl;

getline(cin, randomizerPath);

cout << "Identify root folder:" << endl;
cout << "Please leave a backslash (\\) at the end." << endl;

getline(cin, rootPath);	

cout << "Using Randomizer V3 or V2?" << endl;
cout << "Respond with 2 or 3" << endl;

getline(cin, newRandomizer);
while(newRandomizer != "2" && newRandomizer != "3"){
	cout << "INVALID SELECTION.  Respond with 2 or 3" << endl;
	getline(cin, newRandomizer);
}

if(newRandomizer == "3"){
	cout << "Turn on popup blocker? (Y/N)" << endl;
	getline(cin, popupBlocker);
	while(popupBlocker != "Y" && popupBlocker != "N"){
				cout << "INVALID SELECTION. Respond with Y or N" << endl;
				getline(cin, popupBlocker);
			}
}

 ofstream filepathfile;
  filepathfile.open ("File Paths.txt");
  filepathfile << randomizerPath << endl;
  filepathfile << rootPath << endl;
  filepathfile << newRandomizer << endl;
  filepathfile << popupBlocker << endl;
 
  filepathfile.close();
 	
}

ifstream myfile ("File Paths.txt");
if (myfile.is_open())
  {
	getline(myfile,randomizerPath);
	getline(myfile,rootPath);
	getline(myfile, newRandomizer);
	getline(myfile, popupBlocker);
	myfile.close();
  }
	
else {cout << "Unable to open the file path config";}
  
 
  
  mainMenu();

  

return 0;
}

void mainMenu(){
	if(newRandomizer == "3"){
		newRando = true;
	}
	else newRando = false;
	
	if(popupBlocker == "Y"){
		popup = true;
	}
	else popup = false;
	
	if(newRando){
		randomizerExe = "Randomizer.exe ";
		if(popup){
			theE = " -g MP1 -h -e ";}
		else theE = " -g MP1 -e ";
	}
	else{
		randomizerExe = "Prime_Randomizer.exe ";
		theE = " -e ";}
	
	system("cls");
	cout << header1 << endl;
	cout << header2 << endl << endl;
	cout << "1 - Backup Pak files \(recommended for first time users) \n \n";
	cout << "2 - Restore Pak files \n \n";
	cout << "3 - Generate an \"Easy\" difficulty seed \n \n";
	cout << "4 - Generate a \"Normal\" difficulty seed \n \n";
	cout << "5 - Generate a \"Veteran\" difficulty seed		|    Type S \n \n";
	cout << "6 - Generate a \"Hypermode\" difficulty seed    		| for Settings \n \n";
	cout << "7 - Generate a \"Why\" difficulty seed \n \n";
	//cout << "8 - Hypermode only testing \n \n";
	cout << "8 - Manually check a log file \n \n";
	cout << "9 - Export seeds to text file \n \n";
	cout << "Type $# to give a seed of ONLY a difficulty. Type HELP $ for more info." << endl;
	//cout << "For example, $5 will generate a seed that is completable by a \"Veteran Player\", but not a \"Normal\" player \n \n";
	cout << "Type \"HELP #\" for more information on an option.\n" << endl;
	cout << "> ";
	getline(cin, option);
	processOption();
}

void processOption(){
	system("cls");
	if(option == "1"){
		bakup(rootPath);
	}
	if(option == "2"){
		restore(rootPath);
	}
	if(option == "3" || option == "$3" || option == "$ 3"){
		getEasySeed(false);
	}
	if(option == "4"){
		getNormalSeed(false);
	}
	if(option == "5"){
		getVeteranSeed(false);
	}
	if(option == "6"){
		getHypermodeSeed(false);
	}
	if(option == "7" || option == "$7"){
		cout << "This will be added sometime in the future" << endl;
		system("pause");
	}
	
	
	if(option == "8"){
		manualChecker();
	}
	
	if(option == "9"){
		printMenu();
	}
	
	if(option == "S" || option == "s"){
		genSettings();
	}
	
	if(option == "test"){
		printList();
		system("pause");
	}
	if(option == "test2"){
		CheckFinishNormal("3Test.txt", newRando);
		system("pause");
	}

	
	if(option == "$4" || option == "$ 4"){
		getNormalSeedOnly(false);
	}
	if(option == "$5" || option == "$ 5"){
		getVeteranSeedOnly(false);
	}
	
	if(option == "$6" || option == "$ 6"){
		getHypermodeSeedOnly(false);
	}
	if(option == "HELP 1" || option == "help 1" || option == "Help 1"|| option == "HELP1" || option == "help1" || option == "Help1"){
		cout << "This will backup important pak files in case the randomizer ruins them.  They are stored in the PakBakUp directory." << endl;
		system("pause");
		
	}
	if(option == "HELP 2" || option == "help 2" || option == "Help 2"|| option == "HELP2" || option == "help2" || option == "Help2"){
		cout << "This will restore the pak files if they get mangled by the randomizer (usually caused by quitting the program in the middle of making a seed).  You must have backed up some good pak files previously using the first option.  If you did not, you must dump your pak files again." << endl;
		system("pause");
	}
	if(option == "HELP 3" || option == "help 3" || option == "Help 3"|| option == "HELP3" || option == "help3" || option == "Help3"){
		cout << "This is the easiest difficulty seed.  These seeds can be completed with little to no sequence breaking.  Good for those unfamiliar with Metroid Prime speedrunning or if you are playing on a patched version of the game." << endl;
		system("pause");
	}
	if(option == "HELP 4" || option == "help 4" || option == "Help 4"|| option == "HELP4" || option == "help4" || option == "Help4"){
		cout << "This is the original rendition of the seed generator.  This difficulty will NOT require the player to do any Hyper Bomb Jumps or Uber Bomb Jumps, do a Suitless Magmoor run (except from the Tallon elevator to South Magmoor), do the Chozo floaty glitch without Space Jump, or any other stupid tricks.  Good for beginner speedrunners with moderate knowledge of sequence breaking.  A full list of item requirements can be found here: http://bombch.us/BNcL" << endl;
		system("pause");
	}
	if(option == "HELP 5" || option == "help 5" || option == "Help 5"|| option == "HELP5" || option == "help5" || option == "Help5"){
		cout << "This is a step up from the previous difficulty.  Players will be expected to be able to do all 22% tricks, as well as some of the easier 21% tricks.  A full list of item requirements can be found here: http://bombch.us/BNcM " << endl;
		system("pause");
	}
	
	if(option == "HELP 6" || option == "help 6" || option == "Help 6"|| option == "HELP6" || option == "help6" || option == "Help6"){
		cout << "This difficulty requires the player to do pretty much everything, minus some very difficult tricks such as Life Grove 21%, Root Cave without Space Jump, and other tricks that you wish were never discovered. " << endl;
		system("pause");
	}
	if(option == "HELP $" || option == "help $" || option == "Help $"|| option == "HELP$" || option == "help$" || option == "Help$"){
		cout << "Gives you a seed that is completable only by a player of desired skill level. For example, $5 will generate a seed that is completable by a \"Veteran Player\", but not a \"Normal\" player \n \n" << endl;
		system("pause");
	}
	if(option == "HELP 7" || option == "help 7" || option == "Help 7"|| option == "HELP7" || option == "help7" || option == "Help7"){
		cout << "If it is possible, you might have to do it.  To be added soon." << endl;
		system("pause");
	}
	if(option == "HELP 8" || option == "help 8" || option == "Help 8"|| option == "HELP8" || option == "help8" || option == "Help8"){
		cout << "Allows you to manually check a log file.  Enter the file path of the log file when prompted.  Will return the lowest possible difficulty that it is completable on." << endl;
		system("pause");
	}
	if(option == "HELP 9" || option == "help 9" || option == "Help 9"|| option == "HELP9" || option == "help9" || option == "Help9"){
		cout << "Allows you to pick a difficulty and run the randomizer indefinatly while dumping completable seeds into a text file.  Lists are located in the CompletableSeeds folder." << endl;
		system("pause");
	}
	if(option == "df" || option == "DF" || option == "Df" || option == "dF"){
		cout << "df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df \n Here's your seed: 69696969 \n Exceptions: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99 \n  df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df df" << endl;
		system("pause");
	}
	
	
	mainMenu();
}

void getNormalSeed(bool print){



	
cout << "Please do enter the numbers of the exceptions you wanted, seperated with commas and no spaces" << endl;

getline(cin, exceptions);

bool isStringBad = false;
int k = 0;

charExceptions = exceptions.c_str();

while(k < exceptions.length()){
	if((isdigit(charExceptions[k])) || ((charExceptions[k]) == ',')){
		k++;
	}
	else{
		k++;
		isStringBad = true;
	}
}

if(exceptions == ""){
	isStringBad = true;
}

if(exceptions == "none" || exceptions == "none " ||exceptions == " none"){
	isStringBad = false;
}

if(!isStringBad){

if(newRando){
	cout << "Please note that this window must remain in focus while using Randomizer 3.X \nwith  the Seed Generator." << endl;
	cout << "If focus is lost, the seed generation will cease, and must be manually started \nagain by regaining focus and pressing ENTER." << endl;
	system("pause");
}


fullRandomizer = randomizerPath + randomizerExe;
fullExceptions = theE + exceptions;
randoPath = fullRandomizer + rootPath;
fullCommand = randoPath + fullExceptions;
logFile = randomizerPath + "\\logs\\log.txt";


charCommand = fullCommand.c_str();
charLog = logFile.c_str();
charRoot = rootPath.c_str();


if(!print){
	while(!returnCompletableNormal()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
	if(!newRando)
		{	if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishNormal(logFile.c_str(), newRando);
}
header1 = returnSeed();
header2 = returnExceptions();
resetFlags();
moveGoodSeeds(2,logFile.c_str());
}

if(print){
system("md CompletableSeeds");
ofstream seedList;
seedList.open(".\\CompletableSeeds\\NormalSeedList.txt", ios::app);

time_t now = time(0);
char* dt = ctime(&now);

seedList << "List segment started on  " << dt << endl;

for(;;){ //infinite loop
	while(!returnCompletableNormal()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
	if(!newRando)
		{	if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishNormal(logFile.c_str(), newRando);
	
	
	}
seedList << returnSeed() << " -e " << exceptions << endl;
resetFlags();
	
}
}
}
else{ system("cls");
getNormalSeed(print);}

}

void getVeteranSeed(bool print){
	
cout << "Please do enter the numbers of the exceptions you wanted, seperated with commas and no spaces" << endl;

getline(cin, exceptions);

bool isStringBad = false;
int k = 0;

charExceptions = exceptions.c_str();

while(k < exceptions.length()){
	if((isdigit(charExceptions[k])) || ((charExceptions[k]) == ',')){
		k++;
	}
	else{
		k++;
		isStringBad = true;
	}
}

if(exceptions == ""){
	isStringBad = true;
}

if(exceptions == "none" || exceptions == "none " ||exceptions == " none"){
	isStringBad = false;
}

if(!isStringBad){
fullRandomizer = randomizerPath + randomizerExe;
fullExceptions = theE + exceptions;
randoPath = fullRandomizer + rootPath;
fullCommand = randoPath + fullExceptions;
logFile = randomizerPath + "\\logs\\log.txt";


charCommand = fullCommand.c_str();
charLog = logFile.c_str();
charRoot = rootPath.c_str();

if(!print){
	while(!returnCompletableNormal()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
	if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishNormal(logFile.c_str(), newRando);
}
header1 = returnSeed();
header2 = returnExceptions();
resetFlags();
moveGoodSeeds(2,logFile.c_str());
}

if(print){
system("md CompletableSeeds");
ofstream seedList;
seedList.open(".\\CompletableSeeds\\NormalSeedList.txt", ios::app);

time_t now = time(0);
char* dt = ctime(&now);

seedList << "List segment started on  " << dt << endl;

for(;;){ //infinite loop
	while(!returnCompletableNormal()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
	if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishNormal(logFile.c_str(), newRando);
	
	
	}
seedList << returnSeed() << " -e " << exceptions << endl;
resetFlags();
	
}
}
}
	
else{
	system("cls");
 getVeteranSeed(print); }
}

void getEasySeed(bool print){
	
cout << "Please do enter the numbers of the exceptions you wanted, seperated with commas and no spaces" << endl;

getline(cin, exceptions);

bool isStringBad = false;
int k = 0;

charExceptions = exceptions.c_str();

while(k < exceptions.length()){
	if((isdigit(charExceptions[k])) || ((charExceptions[k]) == ',')){
		k++;
	}
	else{
		k++;
		isStringBad = true;
	}
}

if(exceptions == ""){
	isStringBad = true;
}

if(exceptions == "none" || exceptions == "none " ||exceptions == " none"){
	isStringBad = false;
}

if(!isStringBad){

fullRandomizer = randomizerPath + randomizerExe;
fullExceptions = theE + exceptions;
randoPath = fullRandomizer + rootPath;
fullCommand = randoPath + fullExceptions;
logFile = randomizerPath + "\\logs\\log.txt";


charCommand = fullCommand.c_str();
charLog = logFile.c_str();
charRoot = rootPath.c_str();
	
if(!print){
	
	while(!returnCompletableEasy()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishEasy(logFile.c_str(), newRando);
}
	
header1 = returnSeed();
header2 = returnExceptions();
resetFlags();
moveGoodSeeds(1,logFile.c_str());
}

if(print){
system("md CompletableSeeds");
ofstream seedList;
seedList.open(".\\CompletableSeeds\\EasySeedList.txt", ios::app);

time_t now = time(0);
char* dt = ctime(&now);

seedList << "List segment started on  " << dt << endl;

for(;;){ //infinite loop
	while(!returnCompletableEasy()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishEasy(logFile.c_str(), newRando);
	}
seedList << returnSeed() << " -e " << exceptions << endl;
resetFlags();
	
}
}
}

else{
	system("cls");
 getEasySeed(print); }

}

void getHypermodeSeed(bool print){
	
cout << "Please do enter the numbers of the exceptions you wanted, seperated with commas and no spaces" << endl;

getline(cin, exceptions);

bool isStringBad = false;
int k = 0;

charExceptions = exceptions.c_str();

while(k < exceptions.length()){
	if((isdigit(charExceptions[k])) || ((charExceptions[k]) == ',')){
		k++;
	}
	else{
		k++;
		isStringBad = true;
	}
}

if(exceptions == ""){
	isStringBad = true;
}

if(exceptions == "none" || exceptions == "none " ||exceptions == " none"){
	isStringBad = false;
}

if(!isStringBad){

fullRandomizer = randomizerPath + randomizerExe;
fullExceptions = theE + exceptions;
randoPath = fullRandomizer + rootPath;
fullCommand = randoPath + fullExceptions;
logFile = randomizerPath + "\\logs\\log.txt";


charCommand = fullCommand.c_str();
charLog = logFile.c_str();
charRoot = rootPath.c_str();
	
if(!print){
	while(!returnCompletableHypermode()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishHypermode(logFile.c_str(), newRando);
}
header1 = returnSeed();
header2 = returnExceptions();
resetFlags();
moveGoodSeeds(4,logFile.c_str());
}
	
if(print){
system("md CompletableSeeds");
ofstream seedList;
seedList.open(".\\CompletableSeeds\\HypermodeSeedList.txt", ios::app);

time_t now = time(0);
char* dt = ctime(&now);

seedList << "List segment started on  " << dt << endl;

for(;;){ //infinite loop
	while(!returnCompletableHypermode()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishHypermode(logFile.c_str(), newRando);
	}
seedList << returnSeed() << " -e " << exceptions << endl;
resetFlags();
	
		}
	}
}

else{
	system("cls");
getHypermodeSeed(print); }
}

/*
void getMultipleSeed(){
cout << "Enter the number of the LOWEST difficulty you will accept \n \n";
cout << "1 for Easy \n \n";
cout << "2 for Normal \n \n";
cout << "3 for Veteran \n \n";
cout << "4 for Hypermode \n \n";
cout << "> ";
getline(cin, lowerBound);
system("cls");
cout << "Enter the number of the HIGHEST difficulty you will accept \n \n";
cout << "1 for Easy \n \n";
cout << "2 for Normal \n \n";
cout << "3 for Veteran \n \n";
cout << "4 for Hypermode \n \n";
cout << "> ";
getline(cin, upperBound);
system("cls");

cout << "Please do enter the numbers of the exceptions you wanted, seperated with commas and no spaces" << endl;

getline(cin, exceptions);

fullRandomizer = randomizerPath + randomizerExe;
fullExceptions = theE + exceptions;
randoPath = fullRandomizer + rootPath;
fullCommand = randoPath + fullExceptions;
logFile = randomizerPath + "\\logs\\log.txt";


charCommand = fullCommand.c_str();
charLog = logFile.c_str();
charRoot = rootPath.c_str();

checkUpperBound();
while(!checkLowerBound()){
	checkUpperBound();}

	header1 = returnSeed();
	header2 = returnExceptions();
}


void checkUpperBound(){
	if(upperBound == "1"){
	while(!returnCompletableEasy()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishEasy(logFile.c_str());
	}
	}
	else if(upperBound == "2"){
	while(!returnCompletableNormal()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishNormal(logFile.c_str());
	}
	}
	else if(upperBound == "3"){
	while(!returnCompletableVeteran()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishVeteran(logFile.c_str());
	}
	}
	else if(upperBound == "4"){
	while(!returnCompletableHypermode()){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishHypermode(logFile.c_str());
	}
	}
	resetFlags();
}

bool checkLowerBound(){
	
	if(lowerBound == "2"){
	CheckFinishEasy(logFile.c_str());
	if(!returnCompletableEasy()){
		return true;}
	else return false;
	}
	
	if(lowerBound == "3"){
	CheckFinishNormal(logFile.c_str());
	if(!returnCompletableNormal()){
		return true;}
	else return false;
	}
	
	if(lowerBound == "4"){
	CheckFinishVeteran(logFile.c_str());
	if(!returnCompletableVeteran()){
		return true;}
	else return false;
	}
	
	if(lowerBound == "1"){
		return true;
	}
	resetFlags();
}
*/

void getHypermodeSeedOnly(bool print){
bool failedVeteran =false;
cout << "Please do enter the numbers of the exceptions you wanted, seperated with commas and no spaces" << endl;

getline(cin, exceptions);

bool isStringBad = false;
int k = 0;

charExceptions = exceptions.c_str();

while(k < exceptions.length()){
	if((isdigit(charExceptions[k])) || ((charExceptions[k]) == ',')){
		k++;
	}
	else{
		k++;
		isStringBad = true;
	}
}

if(exceptions == ""){
	isStringBad = true;
}

if(exceptions == "none" || exceptions == "none " ||exceptions == " none"){
	isStringBad = false;
}


if(!isStringBad){
	

fullRandomizer = randomizerPath + randomizerExe;
fullExceptions = theE + exceptions;
randoPath = fullRandomizer + rootPath;
fullCommand = randoPath + fullExceptions;
logFile = randomizerPath + "\\logs\\log.txt";


charCommand = fullCommand.c_str();
charLog = logFile.c_str();
charRoot = rootPath.c_str();

if(!print){
	
	while(!(returnCompletableHypermode() && !returnCompletableVeteran())){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishHypermode(logFile.c_str(), newRando);
	CheckFinishVeteran(logFile.c_str(), newRando);

}
header1 = returnSeed();
header2 = returnExceptions();
resetFlags();
moveGoodSeeds(4,logFile.c_str());
}
	
if(print){

ofstream seedList;
system("md CompletableSeeds");
seedList.open(".\\CompletableSeeds\\HypermodeOnlySeedList.txt", ios::app);

time_t now = time(0);
char* dt = ctime(&now);

seedList << "List segment started on  " << dt << endl;

for(;;){ //infinite loop
	while(!(returnCompletableHypermode() && !returnCompletableVeteran())){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishHypermode(logFile.c_str(), newRando);
	CheckFinishVeteran(logFile.c_str(), newRando);
	}
seedList << returnSeed() << " -e " << exceptions << endl;
resetFlags();
	
}
}
}


else{
	system("cls");
 getHypermodeSeedOnly(print); }

}


void getVeteranSeedOnly(bool print){
bool failedNormal = false;
cout << "Please do enter the numbers of the exceptions you wanted, seperated with commas and no spaces" << endl;

getline(cin, exceptions);


bool isStringBad = false;
int k = 0;

charExceptions = exceptions.c_str();

while(k < exceptions.length()){
	if((isdigit(charExceptions[k])) || ((charExceptions[k]) == ',')){
		k++;
	}
	else{
		k++;
		isStringBad = true;
	}
}

if(exceptions == ""){
	isStringBad = true;
}

if(exceptions == "none" || exceptions == "none " ||exceptions == " none"){
	isStringBad = false;
}

if(!isStringBad){
	

fullRandomizer = randomizerPath + randomizerExe;
fullExceptions = theE + exceptions;
randoPath = fullRandomizer + rootPath;
fullCommand = randoPath + fullExceptions;
logFile = randomizerPath + "\\logs\\log.txt";


charCommand = fullCommand.c_str();
charLog = logFile.c_str();
charRoot = rootPath.c_str();

if(!print){
	
	while(!(returnCompletableVeteran() && !returnCompletableNormal())){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishVeteran(logFile.c_str(), newRando);
	CheckFinishNormal(logFile.c_str(), newRando);

}
header1 = returnSeed();
header2 = returnExceptions();
resetFlags();
moveGoodSeeds(3,logFile.c_str());
}
	
if(print){
system("md CompletableSeeds");
ofstream seedList;
seedList.open(".\\CompletableSeeds\\VeteranOnlySeedList.txt", ios::app);

time_t now = time(0);
char* dt = ctime(&now);

seedList << "List segment started on  " << dt << endl;

for(;;){ //infinite loop
	while(!(returnCompletableVeteran() && !returnCompletableNormal())){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishVeteran(logFile.c_str(), newRando);
	CheckFinishNormal(logFile.c_str(), newRando);
	}
seedList << returnSeed() << " -e " << exceptions << endl;
resetFlags();
	
}
}
}


else {
	system("cls");
getVeteranSeedOnly(print); }

}


void getNormalSeedOnly(bool print){
bool failedEasy = false;
cout << "Please do enter the numbers of the exceptions you wanted, seperated with commas and no spaces" << endl;

getline(cin, exceptions);


bool isStringBad = false;
int k = 0;

charExceptions = exceptions.c_str();

while(k < exceptions.length()){
	if((isdigit(charExceptions[k])) || ((charExceptions[k]) == ',')){
		k++;
	}
	else{
		k++;
		isStringBad = true;
	}
}

if(exceptions == ""){
	isStringBad = true;
}

if(exceptions == "none" || exceptions == "none " ||exceptions == " none"){
	isStringBad = false;
}

if(!isStringBad){
	

fullRandomizer = randomizerPath + randomizerExe;
fullExceptions = theE + exceptions;
randoPath = fullRandomizer + rootPath;
fullCommand = randoPath + fullExceptions;
logFile = randomizerPath + "\\logs\\log.txt";


charCommand = fullCommand.c_str();
charLog = logFile.c_str();
charRoot = rootPath.c_str();
	
if(!print){

	while(!(returnCompletableNormal() && !returnCompletableEasy())){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishNormal(logFile.c_str(), newRando);
	CheckFinishEasy(logFile.c_str(), newRando);
}



header1 = returnSeed();
header2 = returnExceptions();
resetFlags();
moveGoodSeeds(2,logFile.c_str());
}
	
if(print){
system("md CompletableSeeds");
ofstream seedList;
seedList.open(".\\CompletableSeeds\\NormalOnlySeedList.txt", ios::app);

time_t now = time(0);
char* dt = ctime(&now);

seedList << "List segment started on " << dt << endl;

for(;;){ //infinite loop
	while(!(returnCompletableNormal() && !returnCompletableEasy())){
	cout << "Creating a seed.  This may take a while." << endl;
	remove(charLog);
		if(!newRando)
		{system(charCommand);}
	else if (newRando){
		std::future<int> fut = std::async(system, charCommand);
		keybd_event(VK_RETURN,0x9C,0,0);
		keybd_event(VK_RETURN,0x9C, 0,0);
		fut.get();
		}
	dirChecker(randomizerPath);
	CheckFinishNormal(logFile.c_str(), newRando);
	CheckFinishEasy(logFile.c_str(), newRando);
	}
seedList << returnSeed() << " -e " << exceptions << endl;
resetFlags();
	
}
}
}


else {
	system("cls");
 getNormalSeedOnly(print); }

}

void moveGoodSeeds(int difficulty, string logLocation){
	system("md CompletableSeeds");
	string earlyDifficulty;
	if(difficulty == 2){
			earlyDifficulty = "Normal";
	}
	if(difficulty == 1){
			earlyDifficulty = "Easy";
	}
	if(difficulty == 3){
			earlyDifficulty = "Veteran";
	}
	if(difficulty == 4){
			earlyDifficulty = "Hypermode";
	}
	
	command4 = " .\\CompletableSeeds\\";
	string pFreddy = " difficulty with seed ";
	string textFile = ".txt";
	apstring goodSeed = returnSeed();
	//apstring goodSeed = "Seed: 217316257";
	apstring cuttingSeed = goodSeed.substr(6, goodSeed.length() - 6);
	//string fullNewName = command4;
	string fullNewName = earlyDifficulty;
	fullNewName += pFreddy;
	fullNewName.append(cuttingSeed.c_str());
	fullNewName += textFile;

	

	
	rename(logLocation.c_str(), fullNewName.c_str());

	
	command1 = "move \"";
	string oldNewName = fullNewName + "\"";
	fullNewName += "\" ";
	command1 += fullNewName;
	
	command1 += "\".\\CompletableSeeds\\";
	command1 += oldNewName;

	
	system(command1.c_str());
	
	
	
	/*command4 = " .\\CompletableSeeds\\";
	command3 = command2 + command4;
	system(command3.c_str());
	
	string QZ7oldName = ".\\CompletableSeeds\\log.txt";
	*/
	
	//const char * oldLogName = oldName.c_str();
	//const char * QZ = QZ7oldName.c_str();
	
	//string endDif = " difficulty randomizer with ";
	//string fullDif = difficulty + endDif;
	//string theAnd = " and ";
	
	//apstring goodSeed = returnSeed();
	
	//apstring goodExceptions = returnExceptions();
	
	//for testing purposes
	//goodSeed = "Seed: 576053769";
	//goodExceptions = "Excluded pickups: 5 19 28 ";
	
	/*
//	const char * charDif = fullDif.c_str();
	const char * renamingTest;
	
	if(difficulty == 2){
			renamingTest = ".\\CompletableSeeds\\NormalDifficultySeed.txt";
	}
	if(difficulty == 1){
			renamingTest = ".\\CompletableSeeds\\EasyDifficultySeed.txt";
	}
	if(difficulty == 3){
			renamingTest = ".\\CompletableSeeds\\VeteranDifficultySeed.txt";
	}
	if(difficulty == 4){
			renamingTest = ".\\CompletableSeeds\\HypermodeDifficultySeed.txt";
	}
	//const char * renamingTest = ".\\CompletableSeeds\\NotWorking.txt";
	//const char * addingText = ".txt";
	
	//string buf(charDif);  
	//buf.append(goodSeed.c_str());
	
	//string startingOver = command4 + difficulty;
	//startingOver.append(addingText);
	
	//const char * charStartOver = startingOver.c_str();
	
	//buf += theAnd;
	//buf.append(goodExceptions.c_str());
	//buf.append(addingText);
	
	//string fullNew = command4 + buf;
	//const char * fullGNU = fullNew.c_str();
	
	//cout << startingOver << endl;
	//cout << goodSeed.c_str() << endl;
	//cout << goodSeed << endl;
	
	//rename(QZ, renamingTest);
	*/
}

void manualChecker(){
	bool tempVersion;
	string firstLine;
	
	cout << "Please enter the path to a valid log file" << endl;
	getline(cin, manualLogFile);
	
	ifstream existanceChecker (manualLogFile.c_str());
	if(existanceChecker.is_open()){
	
	getline(existanceChecker, firstLine);
	if(firstLine.substr(0,5) == "Rando")
		tempVersion = true;
	else tempVersion = false;

	CheckFinishEasy(manualLogFile.c_str(), tempVersion);
		if(returnCompletableEasy()){
			cout << "Seed is completable (Easy Difficulty)" << endl;
			system("pause");
		}
		else{CheckFinishNormal(manualLogFile.c_str(), tempVersion);
			if(returnCompletableNormal()){
				cout << "Seed is completable (Normal Difficulty)" << endl;
				system("pause");
			}
			else{CheckFinishVeteran(manualLogFile.c_str(), tempVersion);
				if(returnCompletableVeteran()){
					cout << "Seed is completable (Veteren Difficulty)" << endl;
					system("pause");
				}
				else{CheckFinishHypermode(manualLogFile.c_str(), tempVersion);
					if(returnCompletableHypermode()){
						cout << "Seed is completable (Hypermode Difficulty)" << endl;
						system("pause");
					}
					else{
						cout << "This seed is NOT completable (Easy through Hypermode)" << endl;
						system("pause");
					}
				}
			}
		}
	
	}
	
	else{ cout << "Unable to open log file.  Please check your paths to make sure they are correct." << endl;
	system("pause");}
}

void printMenu(){
	cout << "Seeds and exceptions will be printed to a log file.  The seeds will be generated and recorded until the user stops the program. \n \n";
	cout << "Please select the difficulty.  Note that you may use the $ operator to get an exclusive difficulty. \n \n";
	cout << "1 - Easy \n \n";
	cout << "2 - Normal \n \n";
	cout << "3 - Veteran \n \n";
	cout << "4 - Hypermode \n \n";
	cout << "EXIT - Return to Main Menu \n \n \n \n";
	cout << "> ";
	
	getline(cin, printOption);
	
	if(printOption == "1"){
		getEasySeed(true);
	}
	if(printOption == "2"){
		getNormalSeed(true);
	}
	if(printOption == "3"){
		getVeteranSeed(true);
	}
	if(printOption == "4"){
		getHypermodeSeed(true);
	}
	if(printOption == "$1"){
		getEasySeed(true);
	}
	if(printOption == "$2"){
		getNormalSeedOnly(true);
	}
	if(printOption == "$3"){
		getVeteranSeedOnly(true);
	}
	if(printOption == "$4"){
		getHypermodeSeedOnly(true);
	}
	if(printOption == "EXIT" || printOption == "exit"){
		mainMenu();
	}
	printMenu();
}

void genSettings(){
	string settingsOption;
	system("cls");
	cout << "Please select an option to modify \n \n \n \n";
	cout << "1 - Change location of Prime_Randomizer.exe \n \n";
	cout << "2 - Change location of root folder \n \n";  //10 new lines
	cout << "3 - Change Randomizer Version \n \n";
	cout << "4 - Enable or Disable Popup Blocker \n \n \n \n \n \n \n";
	cout << "EXIT - Return to main menu \n \n";
	cout << "> ";
	
	getline(cin, settingsOption);
	
	if(settingsOption == "1"){
		system("cls");
		cout << "Folder where Randomizer program is located: " << endl;
		cout << "Please leave a backslash (\\) at the end." << endl;
		cout << "If any folders contain spaces, enclose those folders in quotation marks \n" << endl;
		cout << "Enter \"BACK\" to cancel and return to options menu." << endl;
		cout << "Current Randomizer folder: " << randomizerPath << endl;
		cout << "> ";
		string oldRandoPath = randomizerPath;
		
		getline(cin, randomizerPath);
		if(randomizerPath != "back" && randomizerPath != "Back" && randomizerPath != "BACK"){
		cout << randomizerPath << " before opening file" << endl;
		 ofstream filepathfile;
		filepathfile.open ("File Paths.txt");
		filepathfile << randomizerPath << endl;
		filepathfile << rootPath << endl;
		filepathfile << newRandomizer << endl;
		filepathfile << popupBlocker << endl;
		filepathfile.close();
		cout << randomizerPath << endl;
		genSettings();
	}
		else {randomizerPath = oldRandoPath;
			genSettings();}
	}
	if(settingsOption == "2"){
		system("cls");
		cout << "Identify root folder:" << endl;
		cout << "Please leave a backslash (\\) at the end. \n" << endl;
		cout << "Enter \"BACK\" to cancel and return to options menu." << endl;
		cout << "Current root folder: " << rootPath << endl;
		cout << "> ";
		string oldPath = rootPath;
		
		getline(cin, rootPath);
		if(rootPath != "back" && rootPath != "Back" && rootPath != "BACK"){

		ofstream filepathfile;
		filepathfile.open ("File Paths.txt");
		filepathfile << randomizerPath << endl;
		filepathfile << rootPath << endl;
		filepathfile << newRandomizer << endl;
		filepathfile << popupBlocker << endl;
		filepathfile.close();
		genSettings();
	}
		else {rootPath = oldPath;
		genSettings();}
	}
	if(settingsOption == "3"){
			system("cls");
			cout << "Using Randomizer V3 or V2?" << endl;
			cout << "Respond with 2 or 3" << endl;
			cout << "Current Setting: " << newRandomizer << endl;
			cout << "> ";

			getline(cin, newRandomizer);
			while(newRandomizer != "2" && newRandomizer != "3"){
				cout << "INVALID SELECTION.  Respond with 2 or 3" << endl;
				getline(cin, newRandomizer);
				}
		ofstream filepathfile;
		filepathfile.open ("File Paths.txt");
		filepathfile << randomizerPath << endl;
		filepathfile << rootPath << endl;
		filepathfile << newRandomizer << endl;
		filepathfile << popupBlocker << endl;
		filepathfile.close();
		genSettings();
	}
	
	if(settingsOption == "4"){
			system("cls");
			cout << "Enable Popup Blocker? (Y/N)" << endl;
			cout << "Current Setting: " << popupBlocker << endl;
			cout << "> ";
			getline(cin, popupBlocker);
			while(popupBlocker != "Y" && popupBlocker != "N"){
				cout << "INVALID SELECTION. Respond with Y or N" << endl;
				getline(cin, popupBlocker);
			}
			ofstream filepathfile;
		filepathfile.open ("File Paths.txt");
		filepathfile << randomizerPath << endl;
		filepathfile << rootPath << endl;
		filepathfile << newRandomizer << endl;
		filepathfile << popupBlocker << endl;
		filepathfile.close();
		genSettings();
	}
	if(settingsOption == "EXIT" || settingsOption == "Exit" || settingsOption == "exit"){
		mainMenu();
	}
}

static void copyFile(const std::string& fileNameFrom, const std::string& fileNameTo)
{
     assert(fileExists(fileNameFrom));
     std::ifstream in (fileNameFrom.c_str());
     std::ofstream out (fileNameTo.c_str());
     out << in.rdbuf();
     out.close();
     in.close();
}

bool fileExists(const std::string& fileName)
{
     std::fstream file;
     file.open(fileName.c_str(), std::ios::in);
     if (file.is_open() == true)
     {
         file.close();
         return true;
     }
     file.close();
     return false;
}

