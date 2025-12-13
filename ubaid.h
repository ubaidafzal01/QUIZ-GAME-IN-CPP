#pragma once
#ifndef UBAID_H   
#define UBAID_H  
#include <string>

using namespace std;
void appendLog(string filename, string playerName, string category, int score, int totalQuestions);
void showReview(string questions[], char userAns[], char correct[], int N,int ransI[],int score, string questionOption[][4]);
void adminAddQuestion(string filename);
int loadLeaderboard(string filename, string names[], int scores[], string categories[], int maxPlayers);
void sortLeaderboard(string names[], int scores[], string categories[], int N);
void displayTopPlayers(string names[], int scores[], string categories[], int totalPlayers, int topN);
void updateLeaderboard(string filename, string playerName, int score, string category);
#endif