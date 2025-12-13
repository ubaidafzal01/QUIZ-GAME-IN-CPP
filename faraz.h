// faraz.h
#ifndef FARAZ_H   
#define FARAZ_H  
#include <string>

using namespace std; // only use it in cpp files otherwise showing errors on cout (cout is ambigous) ===========>>>(TAHA)

char printMainMenu();
void printCentered(string text, char border = '|');
void verticlePadding();
void delay(int milliseconds);
void loadingScreen(string title);
void drawDecoration(char left, char fill, char right);
void printChoices(char ch);
char printCategory();
char printDifficulty();
void printInstructions();
void printCredits();
void programTermination();
void startSession(char cat, char diff,string playerName);
int loadData(string &fileName, int &N, int qDiff[], string qText[], string qOption[][4], char cOption[]);
void printQuestion(const int& N, const string qText[], const string qOption[][4], const int randI[], string &queText, string queOption[]);
void printLog(string& playerName);
////=== Taha Start===
//string trim(const string &s);
//char timedGetInput(int durationSeconds);
//void clear_kbhits();
//void printSession(const int& N, const  int questionDiff[], const string questionText[], const string questionOption[][4], const char correctAns[], const int randomIndex[],string playerName);
#endif