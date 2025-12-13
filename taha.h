#pragma once
#ifndef TAHA_H   
#define TAHA_H  
#include <string>

using namespace std;

char timedGetInput(int durationSeconds);
void clear_kbhits();
void input_validation(char &choosedch, bool isG_used, bool is_skip_used, bool is_swap_used);
int time_up_continue(char choosedch, int &points, int questionDiff[], int randomIndex[], int &streak_count, const int i);
void calcscore(int &points, const char choosedch, char correctAns[], const  int questionDiff[], int randomIndex[], int &streak_count, const int i);
void print_question_with_decoration(const int &i, string questionText[], string questionOption[][4], int randomIndex[], const int points, const int streak_count, const int swapped);
void printSession(const int& N, int questionDiff[],  string questionText[],  string questionOption[][4],  char correctAns[],  int randomIndex[],string playerName,char catagory);
void append_2player_quiz_log(string player1_name, string player2_name, int points1, int points2, string final_result);
void start_hotseat_session(char catagory, char difficulty, string player1_name, string player2_name);
void print__hotseat_question_with_decoration( int i, string questionText[], string questionOption[][4], int randomIndex[], const int points1, const int points2, const int streak_count1, const int streak_count2 , string player_name, int Qcount);
void print_hotseat_session(const int& N,  int questionDiff[], string questionText[], string questionOption[][4], char correctAns[], int randomIndex[], string player1_name, string player2_name, char catagory);
#endif