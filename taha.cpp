#define _CRT_SECURE_NO_WARNINGS			// to disable warning getting while using ctime in quizlog_2player.txt append
#include <iostream>
#include <iomanip>
#include <conio.h>	//_kbhit()  & _getch()
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "faraz.h"
#include "taha.h"
#include "ubaid.h"
#include <cctype>

using namespace std;
int points = 0;
int points1 = 0;
int points2 = 0;
const int WIDTH = 100;
const int HEIGHT_PAD = 8;
const int SIZE = 1000;
const int MAXQ = 10;
// main input validation
void input_validation(char &choosedch, bool isG_used, bool is_skip_used, bool is_swap_used) {
	bool input_received = false;

	clear_kbhits();  // clearing input stream buffer to avoid misunderstanding or multiple clicks

	while (!input_received) {

		// Get input within a 10-second timeout
		clear_kbhits(); // wrote this function just before every _getch() call / input so that previous buffered key wont processed
		choosedch = timedGetInput(10);
		clear_kbhits();
		// Check if time ran out
		if (choosedch == '\0') {
			cout << endl;
			drawDecoration('|', '$', '|');
			cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
			drawDecoration('|', '$', '|');
			cout << endl << endl;
			input_received = true; // Exit the loop
			continue;
		}
		// if enter multiple keys
		clear_kbhits();
		// Validate the input character
		if (choosedch != 'A' && choosedch != 'B' && choosedch != 'C' && choosedch != 'D'
			&& choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
		{
			cout << "\tInvalid input.\n\t>> Enter the Answer (A-D) or lifelines (G/S/O) only: ";
			continue;
		}
		// Check lifeline availability
		if (choosedch == 'G' && isG_used) {
			cout << "\t50/50 is already used. Please try again: ";
			continue;
		}
		if (choosedch == 'S' && is_skip_used) {
			cout << "\tSkip is already used. Please try again: ";
			continue;
		}
		if (choosedch == 'O' && is_swap_used) {
			cout << "\tSwap is already used. Please try again: ";
			continue;
		}
		input_received = true; // Valid input or lifeline chosen
	}
}
// timedGetInput =====>>>> time logic
char timedGetInput(int durationSeconds) {
	clock_t start_time = clock();			// clock_t ===> data type to store time in "clock ticks" rather than seconds.
	clock_t end_time = start_time + (durationSeconds * CLOCKS_PER_SEC); // CLOCKS_PER_SEC is the number of clock ticks per second.
																		// durationSeconds * CLOCKS_PER_SEC converts your duration in seconds to clock ticks.
	while (clock() < end_time) {

		// Check for pending key press
		if (_kbhit()) {				// Returns true if a key has been pressed, false otherwise. ,Non-blocking, so it doesn’t stop the program if no key is pressed.
			char choosedch = toupper(_getch());
			cout << choosedch << endl; // Echo/ print the input character because _getch() do not print implicitly on console so you have to print the typed ch explicitly
			return choosedch;
		}
		delay(50); // small delay to prevent the loop from consuming 100% CPU
	}
	return '\0';	// Time ran out
}

int time_up_continue(char choosedch, int &points, int questionDiff[], int randomIndex[], int &streak_count, const int i) {
	if (choosedch == '\0') {
		streak_count = 0;
		if (questionDiff[randomIndex[i]] == 3) {
			points -= 5;
		}
		else if (questionDiff[randomIndex[i]] == 2) {
			points -= 3;
		}
		else {
			points -= 2;
		}
		delay(2000);
		return 1;
	}
}
// clear the leftovers by clear_kbhits()
void clear_kbhits() {
	while (_kbhit()) {
		_getch(); // Read and discard the character
	}
}
// Calculate Score Function Definition
void calcscore(int &points, const char choosedch, char correctAns[], const  int questionDiff[], int randomIndex[], int &streak_count , const int i) {
	if (choosedch == correctAns[randomIndex[i]]) {
		streak_count++;
		if (streak_count >= 5) {
			points += 15;
		}
		else if (streak_count >= 3) {
			points += 5;
		}
		else
			points += 1;
	}
	else if (questionDiff[randomIndex[i]] == 3) {
		streak_count = 0;
		points -= 5;
	}
	else if (questionDiff[randomIndex[i]] == 2) {
		streak_count = 0;
		points -= 3;
	}
	else {
		streak_count = 0;
		points -= 2;
	}
}
void print_question_with_decoration(const int &i,string questionText[],string questionOption[][4],int randomIndex[], const int points, const int streak_count, const int swapped) {
	drawDecoration('.', '=', '.');
	cout << "\t" << "|" << "\t\t\t\t\t" << "Question No: " << i + 1 - swapped << "\t\t\t\t\t\t   " << '|' << endl;
	drawDecoration('.', '=', '.');
	cout << endl;
	cout << "\t" << left << "Point(s) = " << points << "\t\t\t" << "50/50 [G]" << "\t" << "SKIP [S]" << "\t" << "SWAP [O]" << "\t\tStreak: " << streak_count << endl << endl;
	cout << "\t" << questionText[randomIndex[i]] << endl << endl;
	cout << "\t" << "A) " << left << setw(25) << questionOption[randomIndex[i]][0] << "  " << "B) " << left << setw(25) << questionOption[randomIndex[i]][1] << endl << "\t" << "C) " << left << setw(25) << questionOption[randomIndex[i]][2] << "  " << "D) " << left << setw(25) << questionOption[randomIndex[i]][3] << "  ";
	cout << "\n\n" << "\t" << ">> Enter the Answer (A-D) or lifelines (G/S/O) only: ";
}
// Print session ======>>> print question functionc call + take input with input validation + scoring function call + lifeline + skip + 50/50 + time logic
void printSession(const int& N,  int questionDiff[], string questionText[],  string questionOption[][4],  char correctAns[],int randomIndex[],string playerName,char catagory) {
	system("cls");
	drawDecoration('.', '=', '.');
	cout << "\t" << "|" << "       \t\t\t\t" << "QUIZ STARTED ___ Difficulty: " << questionDiff[randomIndex[0]] << "  \t\t\t   " << '|' << endl;
	drawDecoration('.', '=', '.');
	cout << "\n\n\n\n";
	// declarations for input validation and lifelines
	string temp;
	char userAnswer[25];
	char choosedch;
	bool isG_used = false;
	bool is_skip_used = false;
	bool is_swap_used = false;
	int skipped_index;
	string catagoryName;
	int swapped = 0;
	points = 0;
	int streak_count = 0;
	// Loop For MAXQ = 10 Questions
	for (int i = 0; i < MAXQ + swapped; i++) {
		

		print_question_with_decoration(i, questionText, questionOption, randomIndex, points, streak_count, swapped);

		input_validation(choosedch, isG_used, is_skip_used, is_swap_used);
		int temp = time_up_continue(choosedch, points, questionDiff, randomIndex, streak_count, i);
		if (temp == 1) continue;
		// Process Lifelines (G/S/O)
		if (choosedch == 'G' && !isG_used) {
			streak_count = 0;
			isG_used = true;
			cout << "\n\n\t50/50 used! You have 10 seconds to answer...\n";
			if (correctAns[randomIndex[i]] == 'A') {
				int p = (rand() % (3 - 1 + 1)) + 1;
				char temp_ch[3] = { 'B','C','D' };
				cout << "\t(" << correctAns[randomIndex[i]] << ") " << left << setw(35) << questionOption[randomIndex[i]][0];
				cout << "(" << temp_ch[p] << ") " << left << setw(35) << questionOption[randomIndex[i]][p];
				cout << endl;
				cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
				bool input_received = false;
				while (!input_received) {
					clear_kbhits();
					char temp_char = timedGetInput(10);
					clear_kbhits();
					choosedch = temp_char;
					if (choosedch == '\0') {
						cout << endl;
						drawDecoration('|', '$', '|');
						cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
						drawDecoration('|', '$', '|');
						cout << endl << endl;
						input_received = true;
						continue;
					}
					// Validate the input character
					if (choosedch != 'A' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
					{
						cout << "\n\tInvalid input;\n" << "\t" << ">> Enter the Answer (A/" << temp_ch[p] << ") or lifelines (G/S/O) only: ";
						// Go back to the start of the while(!input_received) loop
						continue;
					}
					// Check lifeline availability
					if (choosedch == 'G' && isG_used) {
						cout << "\t50/50 is already used. Please try again: ";
						continue;
					}
					if (choosedch == 'S' && is_skip_used) {
						cout << "\tSkip is already used. Please try again: ";
						continue;
					}
					if (choosedch == 'O' && is_swap_used) {
						cout << "\tSwap is already used. Please try again: ";
						continue;
					}
					input_received = true; // Valid input or lifeline chosen
				}
				if (choosedch == 'O' && !is_swap_used) {
					is_swap_used = true;
					swapped++;
					continue;
				}
				if (choosedch == '\0') {
					streak_count = 0;
					if (questionDiff[randomIndex[i]] == 3) {
						points -= 5;
					}
					else if (questionDiff[randomIndex[i]] == 2) {
						points -= 3;
					}
					else {
						points -= 2;
					}
					delay(2000);
					continue;
				}
				else if (choosedch == correctAns[randomIndex[i]]) {
					streak_count++;
					if (streak_count >= 5) {
						points += 15;
					}
					else if (streak_count >= 3) {
						points += 5;
					}
					else
						points += 1;
				}
				else if (questionDiff[randomIndex[i]] == 3) {
					streak_count = 0;
					points -= 5;
				}
				else if (questionDiff[randomIndex[i]] == 2) {
					streak_count = 0;
					points -= 3;
				}
				else {
					streak_count = 0;
					points -= 2;
				}
			}
			if (correctAns[randomIndex[i]] == 'B') {
				int p = rand() % (3);
				if (p == 1) p += 1;
				char temp_ch[3] = { 'A','C','D' };
				if (p == 0) {
					cout << "\t(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
					cout << "(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][1];
					cout << endl;
					cout << "\n\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
					bool input_received = false;
					while (!input_received) {
						clear_kbhits();
						char temp_char = timedGetInput(10);
						clear_kbhits();
						choosedch = temp_char;
						if (choosedch == '\0') {
							cout << endl;
							drawDecoration('|', '$', '|');
							cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
							drawDecoration('|', '$', '|');
							cout << endl << endl;
							input_received = true;
							continue;
						}
						if (choosedch != 'B' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
						{
							cout << "\nInvalid Input:\n" << "\t" << ">> Enter the Answer (A/B) or lifelines (G/S/O) only: ";
							continue;
						}
						if (choosedch == 'G' && isG_used) {
							cout << "\t50/50 is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'S' && is_skip_used) {
							cout << "\tSkip is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'O' && is_swap_used) {
							cout << "\tSwap is already used. Please try again: ";
							continue;
						}
						input_received = true;
					}
					if (choosedch == 'O' && !is_swap_used) {
						is_swap_used = true;
						swapped++;
						continue;
					}
					if (choosedch == '\0') {
						streak_count = 0;
						if (questionDiff[randomIndex[i]] == 3) {
							points -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							points -= 3;
						}
						else {
							points -= 2;
						}
						delay(2000);
						continue;
					}
					else if (choosedch == correctAns[randomIndex[i]]) {
						streak_count++;
						if (streak_count >= 5) {
							points += 15;
						}
						else if (streak_count >= 3) {
							points += 5;
						}
						else
							points += 1;
					}
					else if (questionDiff[randomIndex[i]] == 3) {
						streak_count = 0;
						points -= 5;
					}
					else if (questionDiff[randomIndex[i]] == 2) {
						streak_count = 0;
						points -= 3;
					}
					else {
						streak_count = 0;
						points -= 2;
					}
				}
				else {
					cout << "\t(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][1];
					cout << "(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
					cout << endl;
					cout << "\n\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
					bool input_received = false;
					while (!input_received) {
						clear_kbhits();
						char temp_char = timedGetInput(10);
						clear_kbhits();
						choosedch = temp_char;
						if (choosedch == '\0') {
							cout << endl;
							drawDecoration('|', '$', '|');
							cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
							drawDecoration('|', '$', '|');
							cout << endl << endl;
							input_received = true;
							continue;
						}
						if (choosedch != 'B' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
						{
							cout << "\nInvalid Input:\n" << "\t" << ">> Enter the Answer (B/" << temp_ch[p] << ") or lifelines (G/S/O) only: ";
							continue;
						}
						if (choosedch == 'G' && isG_used) {
							cout << "\t50/50 is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'S' && is_skip_used) {
							cout << "\tSkip is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'O' && is_swap_used) {
							cout << "\tSwap is already used. Please try again: ";
							continue;
						}
						input_received = true;
					}
					if (choosedch == '\0') {
						streak_count = 0;
						if (questionDiff[randomIndex[i]] == 3) {
							points -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							points -= 3;
						}
						else {
							points -= 2;
						}
						delay(2000);
						continue;
					}
					else if (choosedch == correctAns[randomIndex[i]]) {
						streak_count++;
						if (streak_count >= 5) {
							points += 15;
						}
						else if (streak_count >= 3) {
							points += 5;
						}
						else
							points += 1;
					}
					else if (questionDiff[randomIndex[i]] == 3) {
						streak_count = 0;
						points -= 5;
					}
					else if (questionDiff[randomIndex[i]] == 2) {
						streak_count = 0;
						points -= 3;
					}
					else {
						streak_count = 0;
						points -= 2;
					}
				}
			}
			if (correctAns[randomIndex[i]] == 'C') {
				int p = rand() % (3);
				if (p == 2) p += 1;
				char temp_ch[3] = { 'A','B','D' };
				if (p == 0 || p == 1) {
					cout << "\t(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
					cout << "(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][2];
					cout << endl;
					cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
					bool input_received = false;
					while (!input_received) {
						clear_kbhits();
						char temp_char = timedGetInput(10);
						clear_kbhits();
						choosedch = temp_char;
						if (choosedch == '\0') {
							cout << endl;
							drawDecoration('|', '$', '|');
							cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
							drawDecoration('|', '$', '|');
							cout << endl << endl;
							input_received = true;
							continue;
						}
						if (choosedch != 'C' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
						{
							cout << "\nInvalid Input:\n" << "\t" << ">> Enter the Answer (" << temp_ch[p] << "/C) or lifelines (G/S/O) only: ";
							continue;
						}
						if (choosedch == 'G' && isG_used) {
							cout << "\t50/50 is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'S' && is_skip_used) {
							cout << "\tSkip is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'O' && is_swap_used) {
							cout << "\tSwap is already used. Please try again: ";
							continue;
						}
						input_received = true;
					}
					if (choosedch == 'O' && !is_swap_used) {
						is_swap_used = true;
						swapped++;
						continue;
					}
					if (choosedch == '\0') {
						streak_count = 0;
						if (questionDiff[randomIndex[i]] == 3) {
							points -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							points -= 3;
						}
						else {
							points -= 2;
						}
						delay(2000);
						continue;
					}
					else if (choosedch == correctAns[randomIndex[i]]) {
						streak_count++;
						if (streak_count >= 5) {
							points += 15;
						}
						else if (streak_count >= 3) {
							points += 5;
						}
						else
							points += 1;
					}
					else if (questionDiff[randomIndex[i]] == 3) {
						streak_count = 0;
						points -= 5;
					}
					else if (questionDiff[randomIndex[i]] == 2) {
						streak_count = 0;
						points -= 3;
					}
					else {
						streak_count = 0;
						points -= 2;
					}
				}
				else {
					cout << "\t(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][2];
					cout << "(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
					cout << endl;
					cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
					bool input_received = false;
					while (!input_received) {
						clear_kbhits();
						char temp_char = timedGetInput(10);
						clear_kbhits();
						choosedch = temp_char;
						if (choosedch == '\0') {
							cout << endl;
							drawDecoration('|', '$', '|');
							cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
							drawDecoration('|', '$', '|');
							cout << endl << endl;
							input_received = true;
							continue;
						}
						if (choosedch != 'C' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
						{
							cout << "\n\tInvalid Input\n" << "\t" << ">> Enter the Answer (C/)" << temp_ch[p] << " or lifelines (G/S/O) only: ";
							continue;
						}
						if (choosedch == 'G' && isG_used) {
							cout << "\t50/50 is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'S' && is_skip_used) {
							cout << "\tSkip is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'O' && is_swap_used) {
							cout << "\tSwap is already used. Please try again: ";
							continue;
						}
						input_received = true;
					}
					if (choosedch == '\0') {
						streak_count = 0;
						if (questionDiff[randomIndex[i]] == 3) {
							points -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							points -= 3;
						}
						else {
							points -= 2;
						}
						delay(2000);
						continue;
					}
					else if (choosedch == correctAns[randomIndex[i]]) {
						streak_count++;
						if (streak_count >= 5) {
							points += 15;
						}
						else if (streak_count >= 3) {
							points += 5;
						}
						else
							points += 1;
					}
					else if (questionDiff[randomIndex[i]] == 3) {
						streak_count = 0;
						points -= 5;
					}
					else if (questionDiff[randomIndex[i]] == 2) {
						streak_count = 0;
						points -= 3;
					}
					else {
						streak_count = 0;
						points -= 2;
					}
				}
			}
			if (correctAns[randomIndex[i]] == 'D') {
				int p = rand() % (3);
				char temp_ch[3] = { 'A','B','C' };
				cout << "\t(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
				cout << "(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][3];
				cout << endl;
				cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
				bool input_received = false;
				while (!input_received) {
					clear_kbhits();
					char temp_char = timedGetInput(10);
					clear_kbhits();
					choosedch = temp_char;
					if (choosedch == '\0') {
						cout << endl;
						drawDecoration('|', '$', '|');
						cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
						drawDecoration('|', '$', '|');
						cout << endl << endl;
						input_received = true;
						continue;
					}
					if (choosedch != 'D' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
					{
						cout << "\n" << "\t" << ">> Enter the Answer (" << temp_ch[p] << "/D) or lifelines (G/S/O) only: ";
						continue;
					}
					if (choosedch == 'G' && isG_used) {
						cout << "\t50/50 is already used. Please try again: ";
						continue;
					}
					if (choosedch == 'S' && is_skip_used) {
						cout << "\tSkip is already used. Please try again: ";
						continue;
					}
					if (choosedch == 'O' && is_swap_used) {
						cout << "\tSwap is already used. Please try again: ";
						continue;
					}
					input_received = true;
				}
				if (choosedch == 'O' && !is_swap_used) {
					is_swap_used = true;
					swapped++;
					continue;
				}
				if (choosedch == '\0') {
					streak_count = 0;
					if (questionDiff[randomIndex[i]] == 3) {
						points -= 5;
					}
					else if (questionDiff[randomIndex[i]] == 2) {
						points -= 3;
					}
					else {
						points -= 2;
					}
					delay(2000);
					continue;
				}
				else if (choosedch == correctAns[randomIndex[i]]) {
					streak_count++;
					if (streak_count >= 5) {
						points += 15;
					}
					else if (streak_count >= 3) {
						points += 5;
					}
					else
						points += 1;
				}
				else if (questionDiff[randomIndex[i]] == 3) {
					streak_count = 0;
					points -= 5;
				}
				else if (questionDiff[randomIndex[i]] == 2) {
					streak_count = 0;
					points -= 3;
				}
				else {
					streak_count = 0;
					points -= 2;
				}
			}

		}
		else if (choosedch == 'S' && !is_skip_used) {
			is_skip_used = true;
			skipped_index = i;
			cout << endl;
			drawDecoration('#', '*', '#');
			cout << "\t" << "|" << "\t\t\t\t\t" << "Question: " << i + 1 - swapped << " Skipped \t\t\t\t\t   " << '|' << endl;
			drawDecoration('#', '*', '#');
			cout << endl << endl;
		}
		else if (choosedch == 'O' && !is_swap_used) {
			is_swap_used = true;
			swapped++;
			continue;
		}
		else
		calcscore(points,choosedch,correctAns,questionDiff,randomIndex,streak_count,i);
		userAnswer[i] = choosedch;
		cout << "\t"; system("pause"); // so that no extra key enters
		//=============// prevent empty input crash + input validation
	}
	if (catagory == '1')
	{
		catagoryName = "Science";
	}
	else if (catagory == '2') {
		catagoryName = "General Knowledeg";
	}else if (catagory == '3') {
		catagoryName = "Math & Logic";
	}else if (catagory == '4') {
		catagoryName = "Pakistan Studies";
	}else if (catagory == '5') {
		catagoryName = "Mix";
	}
	appendLog("quiz_log.txt", playerName, catagoryName, points, 10);
	updateLeaderboard("highscores.txt",  playerName,points, catagoryName);
	showReview(questionText, userAnswer, correctAns, 10,randomIndex,points, questionOption);
}
//=======
//=======
//=======
//=======
// 2 Player Mode Codes
// 2 Player Mode Codes
// 2 Player Mode Codes
//=======
//=======
//=======
//=======
void append_2player_quiz_log(string player1_name, string player2_name,int points1, int points2, string final_result) {
	ofstream fout;
	fout.open("quiz_log_2player.txt", ios::app);
	time_t currentTime = time(nullptr);
	fout << ctime(&currentTime) << endl;
	fout << left<<setw(35) << player1_name << setw(4) << points1 <<" Points"  << endl;
	fout << left<<setw(35) << player2_name << setw(4) << points2 << " Points" << endl;
	fout << "RESULT: " << final_result << endl;;
	fout << "==========================================================================\n";
	fout.close();
}
void start_hotseat_session(char catagory, char difficulty, string player1_name, string player2_name) { // code from faraz.cpp with some modifications
	int diffN = difficulty - '0';
	srand(time(0));
	int N = 0, error;
	int questionDiff[SIZE];
	string questionText[SIZE];
	string questionOption[SIZE][4];
	char correctAns[SIZE];
	int diffIndex[SIZE] = { 0 };
	int randomIndex[MAXQ + 50];
	string sci = "science.txt", ps = "ps.txt", gk = "gk.txt", m_l = "m&l.txt", mix = "mix.txt";
	switch (catagory)
	{
	case '1':
		error = loadData(sci, N, questionDiff, questionText, questionOption, correctAns);
		break;
	case '2':
		error = loadData(gk, N, questionDiff, questionText, questionOption, correctAns);
		break;
	case '3':
		error = loadData(m_l, N, questionDiff, questionText, questionOption, correctAns);
		break;
	case '4':
		error = loadData(ps, N, questionDiff, questionText, questionOption, correctAns);
		break;
	case '5':
		error = loadData(mix, N, questionDiff, questionText, questionOption, correctAns);
		break;
	}
	if (error != -1)
	{
		int k = 0;		// indexes for randomIndexes
		for (int i = 0; i < N; i++)
		{
			if (questionDiff[i] == diffN)
			{
				diffIndex[k] = i;
				k++;
			}
		}
		for (int i = 0; i < 24; i++)
		{
			bool isDuplicate;
			do
			{
				if (k == 0) break;
				randomIndex[i] = diffIndex[rand() % k];
				isDuplicate = false;
				for (int j = 0; j < i; j++)
				{
					if (randomIndex[i] == randomIndex[j])
					{
						isDuplicate = true;
						break;
					}
				}
			} while (isDuplicate);
		}
		if (k == 0) return;
		print_hotseat_session(N, questionDiff, questionText, questionOption, correctAns, randomIndex, player1_name, player2_name, catagory);
	}
}
// Print Hotseat Quesion Function Definition
void print__hotseat_question_with_decoration( int i, string questionText[], string questionOption[][4], int randomIndex[], const int points1, const int points2,const int streak_count1, const int streak_count2, string player_name,int Qcount) {
	int streak_count;
	int player_no;
	int points;
	if(i% 2 == 0) {
		player_no = 1;
		points = points1;
		streak_count = streak_count1;
	}
	else {
		player_no = 2;
		points = points2;
		streak_count = streak_count2;
	}
	cout << endl << endl << endl;
	drawDecoration('.', '=', '.');
	cout << "\t" << "|" << "\t\t\t\t\t" << "Question No: " << Qcount<< "\t\t\t\t\t\t   " << '|' << endl;
	drawDecoration('.', '=', '.');
	cout << "\tPlayer "<<player_no<<" : "<<player_name;
	cout << endl;
	cout << "\t" << left << "Point(s) = " << points << "\t\t\t" << "50/50 [G]" << "\t" << "SKIP [S]" << "\t" << "SWAP [O]" << "\t\tStreak: " << streak_count << endl << endl;
	cout << "\t" << questionText[randomIndex[i]] << endl << endl;
	cout << "\t" << "A) " << left << setw(25) << questionOption[randomIndex[i]][0] << "  " << "B) " << left << setw(25) << questionOption[randomIndex[i]][1] << endl << "\t" << "C) " << left << setw(25) << questionOption[randomIndex[i]][2] << "  " << "D) " << left << setw(25) << questionOption[randomIndex[i]][3] << "  ";
	cout << "\n\n" << "\t" << ">> Enter the Answer (A-D) or lifelines (G/S/O) only: ";
}
void print_hotseat_session(const int& N,  int questionDiff[], string questionText[], string questionOption[][4], char correctAns[], int randomIndex[], string player1_name, string player2_name, char catagory) {
	system("cls");
	drawDecoration('.', '=', '.');
	cout << "\t" << "|" << "       \t\t\t\t" << "QUIZ STARTED ___ Difficulty: " << questionDiff[randomIndex[0]] << "  \t\t\t   " << '|' << endl;
	drawDecoration('.', '=', '.');
	cout << "\n\n\n\n";
	cout << "\t";system("pause");
	// declarations for input validation and lifelines
	string temp;
	char userAnswer[25];
	char choosedch;
	bool isG_used1 = false;
	bool isG_used2 = false;
	bool is_skip_used1 = false;
	bool is_skip_used2 = false;
	bool is_swap_used1 = false;
	bool is_swap_used2 = false;
	int skipped_index;
	string catagoryName;
	int swapped1 = 0;
	int swapped2 = 0;
	int Qcount1 = 0;
	int Qcount2 = 0;
	points1 = 0;
	points2 = 0;

	for (int i = 0;i < 20 + swapped1+swapped2;i++) {
		static int skipped1 = 0; // for to show correct question no. when skipped
		static int skipped2 = 0;
		static int streak_count1 = 0;
		static int streak_count2 = 0;
		if (i % 2 == 0 && (Qcount1<10+swapped1)) { // player1
			Qcount1++;
			static string player_name = player1_name;
			print__hotseat_question_with_decoration(i, questionText, questionOption, randomIndex, points1,points2, streak_count1,streak_count2, player_name, Qcount1);
			// input + validation (correct, invalid , lifelines)
			input_validation(choosedch, isG_used1, is_skip_used1, is_swap_used1);
			int temp = time_up_continue(choosedch, points1, questionDiff, randomIndex, streak_count1, i);
			if (temp == 1) continue;
			// Process Lifelines (G/S/O)
			if (choosedch == 'G' && !isG_used1) {
				streak_count1 = 0;
				isG_used1 = true;
				cout << "\n\n\t50/50 used! You have 10 seconds to answer...\n";
				if (correctAns[randomIndex[i]] == 'A') {
					int p = (rand() % (3 - 1 + 1)) + 1;
					char temp_ch[3] = { 'B','C','D' };
					cout << "\t(" << correctAns[randomIndex[i]] << ") " << left << setw(35) << questionOption[randomIndex[i]][0];
					cout << "(" << temp_ch[p] << ") " << left << setw(35) << questionOption[randomIndex[i]][p];
					cout << endl;
					cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
					bool input_received = false;
					while (!input_received) {
						clear_kbhits();
						char temp_char = timedGetInput(10);
						clear_kbhits();
						choosedch = temp_char;
						if (choosedch == '\0') {
							cout << endl;
							drawDecoration('|', '$', '|');
							cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
							drawDecoration('|', '$', '|');
							cout << endl << endl;
							input_received = true;
							continue;
						}
						// Validate the input character
						if (choosedch != 'A' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
						{
							cout << "\n\tInvalid input;\n" << "\t" << ">> Enter the Answer (A/" << temp_ch[p] << ") or lifelines (G/S/O) only: ";
							// Go back to the start of the while(!input_received) loop
							continue;
						}
						// Check lifeline availability
						if (choosedch == 'G' && isG_used1) {
							cout << "\t50/50 is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'S' && is_skip_used1) {
							cout << "\tSkip is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'O' && is_swap_used1) {
							cout << "\tSwap is already used. Please try again: ";
							continue;
						}
						input_received = true; // Valid input or lifeline chosen
					}
					if (choosedch == '\0') {
						streak_count1 = 0;
						if (questionDiff[randomIndex[i]] == 3) {
							points1 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							points1 -= 3;
						}
						else {
							points1 -= 2;
						}
						delay(2000);
						continue;
					}
					else if (choosedch == correctAns[randomIndex[i]]) {
						streak_count1++;
						if (streak_count1 >= 5) {
							points1 += 15;
						}
						else if (streak_count1 >= 3) {
							points1 += 5;
						}
						else
							points1 += 1;
					}
					else if (questionDiff[randomIndex[i]] == 3) {
						streak_count1 = 0;
						points1 -= 5;
					}
					else if (questionDiff[randomIndex[i]] == 2) {
						streak_count1 = 0;
						points1 -= 3;
					}
					else {
						streak_count1 = 0;
						points1 -= 2;
					}
				}
				if (correctAns[randomIndex[i]] == 'B') {
					int p = rand() % (3);
					if (p == 1) p += 1;
					char temp_ch[3] = { 'A','C','D' };
					if (p == 0) {
						cout << "\t(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
						cout << "(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][1];
						cout << endl;
						cout << "\n\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
						bool input_received = false;
						while (!input_received) {
							clear_kbhits();
							char temp_char = timedGetInput(10);
							clear_kbhits();
							choosedch = temp_char;
							if (choosedch == '\0') {
								cout << endl;
								drawDecoration('|', '$', '|');
								cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
								drawDecoration('|', '$', '|');
								cout << endl << endl;
								input_received = true;
								continue;
							}
							if (choosedch != 'B' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
							{
								cout << "\nInvalid Input:\n" << "\t" << ">> Enter the Answer (A/B) or lifelines (G/S/O) only: ";
								continue;
							}
							if (choosedch == 'G' && isG_used1) {
								cout << "\t50/50 is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'S' && is_skip_used1) {
								cout << "\tSkip is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'O' && is_swap_used1) {
								cout << "\tSwap is already used. Please try again: ";
								continue;
							}
							input_received = true;
						}
						if (choosedch == '\0') {
							streak_count1 = 0;
							if (questionDiff[randomIndex[i]] == 3) {
								points1 -= 5;
							}
							else if (questionDiff[randomIndex[i]] == 2) {
								points1 -= 3;
							}
							else {
								points1 -= 2;
							}
							delay(2000);
							continue;
						}
						else if (choosedch == correctAns[randomIndex[i]]) {
							streak_count1++;
							if (streak_count1 >= 5) {
								points1 += 15;
							}
							else if (streak_count1 >= 3) {
								points1 += 5;
							}
							else
								points1 += 1;
						}
						else if (questionDiff[randomIndex[i]] == 3) {
							streak_count1 = 0;
							points1 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							streak_count1 = 0;
							points1 -= 3;
						}
						else {
							streak_count1 = 0;
							points1 -= 2;
						}
					}
					else {
						cout << "\t(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][1];
						cout << "(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
						cout << endl;
						cout << "\n\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
						bool input_received = false;
						while (!input_received) {
							clear_kbhits();
							char temp_char = timedGetInput(10);
							clear_kbhits();
							choosedch = temp_char;
							if (choosedch == '\0') {
								cout << endl;
								drawDecoration('|', '$', '|');
								cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
								drawDecoration('|', '$', '|');
								cout << endl << endl;
								input_received = true;
								continue;
							}
							if (choosedch != 'B' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
							{
								cout << "\nInvalid Input:\n" << "\t" << ">> Enter the Answer (B/" << temp_ch[p] << ") or lifelines (G/S/O) only: ";
								continue;
							}
							if (choosedch == 'G' && isG_used1) {
								cout << "\t50/50 is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'S' && is_skip_used1) {
								cout << "\tSkip is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'O' && is_swap_used1) {
								cout << "\tSwap is already used. Please try again: ";
								continue;
							}
							input_received = true;
						}
						if (choosedch == '\0') {
							streak_count1 = 0;
							if (questionDiff[randomIndex[i]] == 3) {
								points1 -= 5;
							}
							else if (questionDiff[randomIndex[i]] == 2) {
								points1 -= 3;
							}
							else {
								points1 -= 2;
							}
							delay(2000);
							continue;
						}
						else if (choosedch == correctAns[randomIndex[i]]) {
							streak_count1++;
							if (streak_count1 >= 5) {
								points1 += 15;
							}
							else if (streak_count1 >= 3) {
								points1 += 5;
							}
							else
								points1 += 1;
						}
						else if (questionDiff[randomIndex[i]] == 3) {
							streak_count1 = 0;
							points1 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							streak_count1 = 0;
							points1 -= 3;
						}
						else {
							streak_count1 = 0;
							points1 -= 2;
						}
					}
				}
				if (correctAns[randomIndex[i]] == 'C') {
					int p = rand() % (3);
					if (p == 2) p += 1;
					char temp_ch[3] = { 'A','B','D' };
					if (p == 0 || p == 1) {
						cout << "\t(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
						cout << "(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][2];
						cout << endl;
						cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
						bool input_received = false;
						while (!input_received) {
							clear_kbhits();
							char temp_char = timedGetInput(10);
							clear_kbhits();
							choosedch = temp_char;
							if (choosedch == '\0') {
								cout << endl;
								drawDecoration('|', '$', '|');
								cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
								drawDecoration('|', '$', '|');
								cout << endl << endl;
								input_received = true;
								continue;
							}
							if (choosedch != 'C' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
							{
								cout << "\nInvalid Input:\n" << "\t" << ">> Enter the Answer (" << temp_ch[p] << "/C) or lifelines (G/S/O) only: ";
								continue;
							}
							if (choosedch == 'G' && isG_used1) {
								cout << "\t50/50 is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'S' && is_skip_used1) {
								cout << "\tSkip is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'O' && is_swap_used1) {
								cout << "\tSwap is already used. Please try again: ";
								continue;
							}
							input_received = true;
						}
						if (choosedch == '\0') {
							streak_count1 = 0;
							if (questionDiff[randomIndex[i]] == 3) {
								points1 -= 5;
							}
							else if (questionDiff[randomIndex[i]] == 2) {
								points1 -= 3;
							}
							else {
								points1 -= 2;
							}
							delay(2000);
							continue;
						}
						else if (choosedch == correctAns[randomIndex[i]]) {
							streak_count1++;
							if (streak_count1 >= 5) {
								points1 += 15;
							}
							else if (streak_count1 >= 3) {
								points1 += 5;
							}
							else
								points1 += 1;
						}
						else if (questionDiff[randomIndex[i]] == 3) {
							streak_count1 = 0;
							points1 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							streak_count1 = 0;
							points1 -= 3;
						}
						else {
							streak_count1 = 0;
							points1 -= 2;
						}
					}
					else {
						cout << "\t(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][2];
						cout << "(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
						cout << endl;
						cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
						bool input_received = false;
						while (!input_received) {
							clear_kbhits();
							char temp_char = timedGetInput(10);
							clear_kbhits();
							choosedch = temp_char;
							if (choosedch == '\0') {
								cout << endl;
								drawDecoration('|', '$', '|');
								cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
								drawDecoration('|', '$', '|');
								cout << endl << endl;
								input_received = true;
								continue;
							}
							if (choosedch != 'C' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
							{
								cout << "\n\tInvalid Input\n" << "\t" << ">> Enter the Answer (C/)" << temp_ch[p] << " or lifelines (G/S/O) only: ";
								continue;
							}
							if (choosedch == 'G' && isG_used1) {
								cout << "\t50/50 is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'S' && is_skip_used1) {
								cout << "\tSkip is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'O' && is_swap_used1) {
								cout << "\tSwap is already used. Please try again: ";
								continue;
							}
							input_received = true;
						}
						if (choosedch == '\0') {
							streak_count1 = 0;
							if (questionDiff[randomIndex[i]] == 3) {
								points1 -= 5;
							}
							else if (questionDiff[randomIndex[i]] == 2) {
								points1 -= 3;
							}
							else {
								points1 -= 2;
							}
							delay(2000);
							continue;
						}
						else if (choosedch == correctAns[randomIndex[i]]) {
							streak_count1++;
							if (streak_count1 >= 5) {
								points1 += 15;
							}
							else if (streak_count1 >= 3) {
								points1 += 5;
							}
							else
								points1 += 1;
						}
						else if (questionDiff[randomIndex[i]] == 3) {
							streak_count1 = 0;
							points1 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							streak_count1 = 0;
							points1 -= 3;
						}
						else {
							streak_count1 = 0;
							points1 -= 2;
						}
					}
				}
				if (correctAns[randomIndex[i]] == 'D') {
					int p = rand() % (3);
					char temp_ch[3] = { 'A','B','C' };
					cout << "\t(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
					cout << "(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][3];
					cout << endl;
					cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
					bool input_received = false;
					while (!input_received) {
						clear_kbhits();
						char temp_char = timedGetInput(10);
						clear_kbhits();
						choosedch = temp_char;
						if (choosedch == '\0') {
							cout << endl;
							drawDecoration('|', '$', '|');
							cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
							drawDecoration('|', '$', '|');
							cout << endl << endl;
							input_received = true;
							continue;
						}
						if (choosedch != 'D' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
						{
							cout << "\n" << "\t" << ">> Enter the Answer (" << temp_ch[p] << "/D) or lifelines (G/S/O) only: ";
							continue;
						}
						if (choosedch == 'G' && isG_used1) {
							cout << "\t50/50 is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'S' && is_skip_used1) {
							cout << "\tSkip is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'O' && is_swap_used1) {
							cout << "\tSwap is already used. Please try again: ";
							continue;
						}
						input_received = true;
					}
					if (choosedch == '\0') {
						streak_count1 = 0;
						if (questionDiff[randomIndex[i]] == 3) {
							points1 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							points1 -= 3;
						}
						else {
							points1 -= 2;
						}
						delay(2000);
						continue;
					}
					else if (choosedch == correctAns[randomIndex[i]]) {
						streak_count1++;
						if (streak_count1 >= 5) {
							points1 += 15;
						}
						else if (streak_count1 >= 3) {
							points1 += 5;
						}
						else
							points1 += 1;
					}
					else if (questionDiff[randomIndex[i]] == 3) {
						streak_count1 = 0;
						points1 -= 5;
					}
					else if (questionDiff[randomIndex[i]] == 2) {
						streak_count1 = 0;
						points1 -= 3;
					}
					else {
						streak_count1 = 0;
						points1 -= 2;
					}
				}

			}
			else if (choosedch == 'S' && !is_skip_used1) {
				is_skip_used1 = true;
				skipped_index = i;
				cout << endl;
				drawDecoration('#', '*', '#');
				cout << "\t" << "|" << "\t\t\t\t\t" << "Question: " << Qcount1 << " Skipped \t\t\t\t\t   " << '|' << endl;
				drawDecoration('#', '*', '#');
				cout << endl << endl;
			}
			else if (choosedch == 'O' && !is_swap_used1) {
			cout << endl;
			drawDecoration('#', '*', '#');
			cout << "\t" << "|" << "\t\t\t\t\t" << "Question: " << Qcount1 << " Skipped \t\t\t\t\t   " << '|' << endl;
			drawDecoration('#', '*', '#');
			cout << endl << endl;
				is_swap_used1 = true;
				swapped1++;
				Qcount1--;
				i ++;
				continue;
			}
			else
			calcscore(points1, choosedch, correctAns, questionDiff, randomIndex, streak_count1, i);
			userAnswer[i] = choosedch;
			cout << "\t"; system("pause"); // so that no extra key enters


		}
		else if (i%2!=0 &&(Qcount2<10+swapped2)){
		Qcount2++;
			static string player_name = player2_name;
			print__hotseat_question_with_decoration(i, questionText, questionOption, randomIndex, points1, points2, streak_count1, streak_count2, player_name,Qcount2);
			
			input_validation(choosedch, isG_used2, is_skip_used2, is_swap_used2);
			int temp = time_up_continue(choosedch, points2,  questionDiff,randomIndex, streak_count2, i);
			if (temp == 1) continue;
			// Process Lifelines (G/S/O)
			if (choosedch == 'G' && !isG_used2) {
				streak_count2 = 0;
				isG_used2 = true;
				cout << "\n\n\t50/50 used! You have 10 seconds to answer...\n";
				if (correctAns[randomIndex[i]] == 'A') {
					int p = (rand() % (3 - 1 + 1)) + 1;
					char temp_ch[3] = { 'B','C','D' };
					cout << "\t(" << correctAns[randomIndex[i]] << ") " << left << setw(35) << questionOption[randomIndex[i]][0];
					cout << "(" << temp_ch[p] << ") " << left << setw(35) << questionOption[randomIndex[i]][p];
					cout << endl;
					cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
					bool input_received = false;
					while (!input_received) {
						clear_kbhits();
						char temp_char = timedGetInput(10);
						clear_kbhits();
						choosedch = temp_char;
						if (choosedch == '\0') {
							cout << endl;
							drawDecoration('|', '$', '|');
							cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
							drawDecoration('|', '$', '|');
							cout << endl << endl;
							input_received = true;
							continue;
						}
						// Validate the input character
						if (choosedch != 'A' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
						{
							cout << "\n\tInvalid input;\n" << "\t" << ">> Enter the Answer (A/" << temp_ch[p] << ") or lifelines (G/S/O) only: ";
							// Go back to the start of the while(!input_received) loop
							continue;
						}
						// Check lifeline availability
						if (choosedch == 'G' && isG_used2) {
							cout << "\t50/50 is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'S' && is_skip_used2) {
							cout << "\tSkip is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'O' && is_swap_used2) {
							cout << "\tSwap is already used. Please try again: ";
							continue;
						}
						input_received = true; // Valid input or lifeline chosen
					}
					if (choosedch == '\0') {
						streak_count2 = 0;
						if (questionDiff[randomIndex[i]] == 3) {
							points2 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							points2 -= 3;
						}
						else {
							points2 -= 2;
						}
						delay(2000);
						continue;
					}
					else if (choosedch == correctAns[randomIndex[i]]) {
						streak_count2++;
						if (streak_count2 >= 5) {
							points2 += 15;
						}
						else if (streak_count2 >= 3) {
							points2 += 5;
						}
						else
							points2 += 1;
					}
					else if (questionDiff[randomIndex[i]] == 3) {
						streak_count2 = 0;
						points2 -= 5;
					}
					else if (questionDiff[randomIndex[i]] == 2) {
						streak_count2 = 0;
						points2 -= 3;
					}
					else {
						streak_count2 = 0;
						points2 -= 2;
					}
				}
				if (correctAns[randomIndex[i]] == 'B') {
					int p = rand() % (3);
					if (p == 1) p += 1;
					char temp_ch[3] = { 'A','C','D' };
					if (p == 0) {
						cout << "\t(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
						cout << "(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][1];
						cout << endl;
						cout << "\n\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
						bool input_received = false;
						while (!input_received) {
							clear_kbhits();
							char temp_char = timedGetInput(10);
							clear_kbhits();
							choosedch = temp_char;
							if (choosedch == '\0') {
								cout << endl;
								drawDecoration('|', '$', '|');
								cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
								drawDecoration('|', '$', '|');
								cout << endl << endl;
								input_received = true;
								continue;
							}
							if (choosedch != 'B' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
							{
								cout << "\nInvalid Input:\n" << "\t" << ">> Enter the Answer (A/B) or lifelines (G/S/O) only: ";
								continue;
							}
							if (choosedch == 'G' && isG_used2) {
								cout << "\t50/50 is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'S' && is_skip_used2) {
								cout << "\tSkip is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'O' && is_swap_used2) {
								cout << "\tSwap is already used. Please try again: ";
								continue;
							}
							input_received = true;
						}
						if (choosedch == '\0') {
							streak_count2 = 0;
							if (questionDiff[randomIndex[i]] == 3) {
								points2 -= 5;
							}
							else if (questionDiff[randomIndex[i]] == 2) {
								points2 -= 3;
							}
							else {
								points2 -= 2;
							}
							delay(2000);
							continue;
						}
						else if (choosedch == correctAns[randomIndex[i]]) {
							streak_count2++;
							if (streak_count2 >= 5) {
								points2 += 15;
							}
							else if (streak_count2 >= 3) {
								points2 += 5;
							}
							else
								points2 += 1;
						}
						else if (questionDiff[randomIndex[i]] == 3) {
							streak_count2 = 0;
							points2 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							streak_count2 = 0;
							points2 -= 3;
						}
						else {
							streak_count2 = 0;
							points2 -= 2;
						}
					}
					else {
						cout << "\t(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][1];
						cout << "(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
						cout << endl;
						cout << "\n\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
						bool input_received = false;
						while (!input_received) {
							clear_kbhits();
							char temp_char = timedGetInput(10);
							clear_kbhits();
							choosedch = temp_char;
							if (choosedch == '\0') {
								cout << endl;
								drawDecoration('|', '$', '|');
								cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
								drawDecoration('|', '$', '|');
								cout << endl << endl;
								input_received = true;
								continue;
							}
							if (choosedch != 'B' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
							{
								cout << "\nInvalid Input:\n" << "\t" << ">> Enter the Answer (B/" << temp_ch[p] << ") or lifelines (G/S/O) only: ";
								continue;
							}
							if (choosedch == 'G' && isG_used2) {
								cout << "\t50/50 is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'S' && is_skip_used2) {
								cout << "\tSkip is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'O' && is_swap_used2) {
								cout << "\tSwap is already used. Please try again: ";
								continue;
							}
							input_received = true;
						}
						if (choosedch == '\0') {
							streak_count2 = 0;
							if (questionDiff[randomIndex[i]] == 3) {
								points2 -= 5;
							}
							else if (questionDiff[randomIndex[i]] == 2) {
								points2 -= 3;
							}
							else {
								points2 -= 2;
							}
							delay(2000);
							continue;
						}
						else if (choosedch == correctAns[randomIndex[i]]) {
							streak_count2++;
							if (streak_count2 >= 5) {
								points2 += 15;
							}
							else if (streak_count2 >= 3) {
								points2 += 5;
							}
							else
								points2 += 1;
						}
						else if (questionDiff[randomIndex[i]] == 3) {
							streak_count2 = 0;
							points2 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							streak_count2 = 0;
							points2 -= 3;
						}
						else {
							streak_count2 = 0;
							points2 -= 2;
						}
					}
				}
				if (correctAns[randomIndex[i]] == 'C') {
					int p = rand() % (3);
					if (p == 2) p += 1;
					char temp_ch[3] = { 'A','B','D' };
					if (p == 0 || p == 1) {
						cout << "\t(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
						cout << "(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][2];
						cout << endl;
						cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
						bool input_received = false;
						while (!input_received) {
							clear_kbhits();
							char temp_char = timedGetInput(10);
							clear_kbhits();
							choosedch = temp_char;
							if (choosedch == '\0') {
								cout << endl;
								drawDecoration('|', '$', '|');
								cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
								drawDecoration('|', '$', '|');
								cout << endl << endl;
								input_received = true;
								continue;
							}
							if (choosedch != 'C' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
							{
								cout << "\nInvalid Input:\n" << "\t" << ">> Enter the Answer (" << temp_ch[p] << "/C) or lifelines (G/S/O) only: ";
								continue;
							}
							if (choosedch == 'G' && isG_used2) {
								cout << "\t50/50 is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'S' && is_skip_used2) {
								cout << "\tSkip is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'O' && is_swap_used2) {
								cout << "\tSwap is already used. Please try again: ";
								continue;
							}
							input_received = true;
						}
						if (choosedch == '\0') {
							streak_count2 = 0;
							if (questionDiff[randomIndex[i]] == 3) {
								points2 -= 5;
							}
							else if (questionDiff[randomIndex[i]] == 2) {
								points2 -= 3;
							}
							else {
								points2 -= 2;
							}
							delay(2000);
							continue;
						}
						else if (choosedch == correctAns[randomIndex[i]]) {
							streak_count2++;
							if (streak_count2 >= 5) {
								points2 += 15;
							}
							else if (streak_count2 >= 3) {
								points2 += 5;
							}
							else
								points2 += 1;
						}
						else if (questionDiff[randomIndex[i]] == 3) {
							streak_count2 = 0;
							points2 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							streak_count2 = 0;
							points2 -= 3;
						}
						else {
							streak_count2 = 0;
							points2 -= 2;
						}
					}
					else {
						cout << "\t(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][2];
						cout << "(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
						cout << endl;
						cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
						bool input_received = false;
						while (!input_received) {
							clear_kbhits();
							char temp_char = timedGetInput(10);
							clear_kbhits();
							choosedch = temp_char;
							if (choosedch == '\0') {
								cout << endl;
								drawDecoration('|', '$', '|');
								cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
								drawDecoration('|', '$', '|');
								cout << endl << endl;
								input_received = true;
								continue;
							}
							if (choosedch != 'C' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
							{
								cout << "\n\tInvalid Input\n" << "\t" << ">> Enter the Answer (C/)" << temp_ch[p] << " or lifelines (G/S/O) only: ";
								continue;
							}
							if (choosedch == 'G' && isG_used2) {
								cout << "\t50/50 is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'S' && is_skip_used2) {
								cout << "\tSkip is already used. Please try again: ";
								continue;
							}
							if (choosedch == 'O' && is_swap_used2) {
								cout << "\tSwap is already used. Please try again: ";
								continue;
							}
							input_received = true;
						}
						if (choosedch == '\0') {
							streak_count2 = 0;
							if (questionDiff[randomIndex[i]] == 3) {
								points2 -= 5;
							}
							else if (questionDiff[randomIndex[i]] == 2) {
								points2 -= 3;
							}
							else {
								points2 -= 2;
							}
							delay(2000);
							continue;
						}
						else if (choosedch == correctAns[randomIndex[i]]) {
							streak_count2++;
							if (streak_count2 >= 5) {
								points2 += 15;
							}
							else if (streak_count2 >= 3) {
								points2 += 5;
							}
							else
								points2 += 1;
						}
						else if (questionDiff[randomIndex[i]] == 3) {
							streak_count2 = 0;
							points2 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							streak_count2 = 0;
							points2 -= 3;
						}
						else {
							streak_count2 = 0;
							points2 -= 2;
						}
					}
				}
				if (correctAns[randomIndex[i]] == 'D') {
					int p = rand() % (3);
					char temp_ch[3] = { 'A','B','C' };
					cout << "\t(" << temp_ch[p] << ") " << setw(40) << questionOption[randomIndex[i]][p];
					cout << "(" << correctAns[randomIndex[i]] << ") " << setw(40) << questionOption[randomIndex[i]][3];
					cout << endl;
					cout << "\n" << "\t" << ">> Choose correct answer or lifelines (G/S/O) only: ";
					bool input_received = false;
					while (!input_received) {
						clear_kbhits();
						char temp_char = timedGetInput(10);
						clear_kbhits();
						choosedch = temp_char;
						if (choosedch == '\0') {
							cout << endl;
							drawDecoration('|', '$', '|');
							cout << "\t" << "|" << "\t\t\t\t Time's Up Moving on to the next question\t\t\t   " << '|' << endl;
							drawDecoration('|', '$', '|');
							cout << endl << endl;
							input_received = true;
							continue;
						}
						if (choosedch != 'D' && choosedch != temp_ch[p] && choosedch != 'G' && choosedch != 'S' && choosedch != 'O')
						{
							cout << "\n" << "\t" << ">> Enter the Answer (" << temp_ch[p] << "/D) or lifelines (G/S/O) only: ";
							continue;
						}
						if (choosedch == 'G' && isG_used2) {
							cout << "\t50/50 is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'S' && is_skip_used2) {
							cout << "\tSkip is already used. Please try again: ";
							continue;
						}
						if (choosedch == 'O' && is_swap_used2) {
							cout << "\tSwap is already used. Please try again: ";
							continue;
						}
						input_received = true;
					}
					if (choosedch == '\0') {
						streak_count2 = 0;
						if (questionDiff[randomIndex[i]] == 3) {
							points2 -= 5;
						}
						else if (questionDiff[randomIndex[i]] == 2) {
							points2 -= 3;
						}
						else {
							points2 -= 2;
						}
						delay(2000);
						continue;
					}
					else if (choosedch == correctAns[randomIndex[i]]) {
						streak_count2++;
						if (streak_count2 >= 5) {
							points2 += 15;
						}
						else if (streak_count2 >= 3) {
							points2 += 5;
						}
						else
							points2 += 1;
					}
					else if (questionDiff[randomIndex[i]] == 3) {
						streak_count2 = 0;
						points2 -= 5;
					}
					else if (questionDiff[randomIndex[i]] == 2) {
						streak_count2 = 0;
						points2 -= 3;
					}
					else {
						streak_count2 = 0;
						points2 -= 2;
					}
				}

			}
			else if (choosedch == 'S' && !is_skip_used2) {
				is_skip_used2 = true;
				skipped_index = i;
				cout << endl;
				drawDecoration('#', '*', '#');
				cout << "\t" << "|" << "\t\t\t\t\t" << "Question: " << Qcount2 << " Skipped \t\t\t\t\t   " << '|' << endl;
				drawDecoration('#', '*', '#');
				cout << endl << endl;
			}
			else if (choosedch == 'O' && !is_swap_used2) {
			cout << endl;
			drawDecoration('#', '*', '#');
			cout << "\t" << "|" << "\t\t\t\t\t" << "Question: " << Qcount2 << " Swapped \t\t\t\t\t   " << '|' << endl;
			drawDecoration('#', '*', '#');
			cout << endl << endl;
				is_swap_used2 = true;
				swapped2+=1;
				Qcount2--;
				i += 1;
				continue;
			}
			else {
				calcscore(points2, choosedch, correctAns, questionDiff, randomIndex, streak_count2, i);
			}
			userAnswer[i] = choosedch;
			cout << "\t"; system("pause"); // so that no extra key enters
		}
	}
	cout << "\n\n\t Player 1: " << left << setw(30) << player1_name<<"Points: "<<setw(3)<<points1;
	cout << "\n\n\t Player 2: " << left << setw(30) << player2_name<<"Points: "<<setw(3)<<points2;
	cout << endl<<endl;
	string final_result;
	if (points1 > points2) {
		final_result = player1_name + " is Winner\n";
		cout << "\t Winner : "<<player1_name<<endl;
	}
	else if (points2 > points1) {
		final_result = player2_name + " is Winner\n";
		cout << "\t Winner : " << player2_name << endl;
	}
	else {
		final_result = "Draw\n";
		cout << "\t Final Result: Draw\n";
	}
	cout << "\n\n\n\t";
	append_2player_quiz_log(player1_name, player2_name, points1, points2,final_result);
	system("pause");
}