#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "faraz.h"
#include "taha.h"
#include "ubaid.h"
#include<cctype>	

using namespace std;

const int WIDTH = 100; //Almost 100% width of the screen
const int HEIGHT_PAD = 8;
const int SIZE = 1000;
const int MAXQ = 10;
//==
string names[100];
int scores[100];
string categories[100];
char printMainMenu()
{
	loadingScreen("INITIALIZING QUIZ SYSTEM...");

	char choice = 0;
	bool correctInput = true;

	system("cls");
	verticlePadding();

	drawDecoration('.', '=', '.');
	drawDecoration('|', ' ', '|');
	printCentered("  ____   _    _  _____  ______", '|');
	printCentered(" / __ \\ | |  | ||_   _||___  /", '|');
	printCentered("| |  | || |  | |  | |    / / ", '|');
	printCentered("| |  | || |  | |  | |   / /  ", '|');
	printCentered("| |__| || |__| | _| |_ / /__ ", '|');
	printCentered(" \\___\\_\\ \\____/ |_____/_____|", '|');
	printCentered(" ", '|');
	printCentered("C++ CONSOLE EDITION", '|');

	drawDecoration('|', ' ', '|');
	drawDecoration('+', '-', '+');

	printCentered(" ", '|');
	printCentered("    M A I N   M E N U   ", '|');
	printCentered(" ", '|');
	printCentered("    [ 1 ] START NEW GAME", '|');
	printCentered("    [ 2 ] Leaderboard   ", '|');
	printCentered("    [ 3 ] INSTRUCTIONS  ", '|');
	printCentered("    [ 4 ] CREDITS       ", '|');
	printCentered("    [ 5 ] ADMIN MODE    ", '|');
	printCentered("    [ 6 ] 2-PLAYER MODE ", '|');
	printCentered("    [ 7 ] EXIT          ", '|');
	printCentered(" ", '|');

	drawDecoration('.', '=', '.');

	cout << endl << ">> ENTER YOUR CHOICE (1-6): ";

	//User cant enter wrong input
	while (_kbhit()) _getch();
	while (true)
	{
		choice = _getch();

		if (choice >= '1' && choice <= '7')
		{
			cout << choice;
			delay(1000);
			break;
		}
	}
	return choice;
}

void printChoices(char ch)
{
	char catagory, difficulty;
	string playerName;
	switch (ch)
	{
	case '1':
		do
		{
			catagory = printCategory();
			if (catagory != '6')
			{
				difficulty = printDifficulty();
				if (difficulty != '4')
					printLog(playerName);
					startSession(catagory, difficulty,playerName);
			}
		} while (catagory != '6');
		break;
	case '2': {
		
		int totalPlayers = loadLeaderboard("highscores.txt", names, scores, categories, 100);
		if (totalPlayers == 0) {
			system("cls");
			verticlePadding();
			drawDecoration('.', '=', '.');
			printCentered("No players in leaderboard yet.", '|');
			drawDecoration('.', '=', '.');
		}
		else {
			sortLeaderboard(names, scores, categories, totalPlayers);
			displayTopPlayers(names, scores, categories, totalPlayers, 5);
		}
		cout << "\nPress any key to return to main menu...";
		_getch();
		break;
	}
	case '3':
		printInstructions();
		break;

	case '4':
		printCredits();
		break;
	case '5':
	{
		    loadingScreen("ENTERING ADMIN MODE...");
            system("cls");
            cout << "\n\n\tADMIN PANEL - CHOOSE CATEGORY FILE\n\n";
            cout << "\t1. Science\n";
            cout << "\t2. General Knowledge\n";
            cout << "\t3. Math and IQ\n";
            cout << "\t4. Pakistan Studies\n";
            cout << "\t5. Mix Test\n";
            cout << "\t6. Back to Main Menu\n\n";
            cout << "\t>> Enter your choice: ";

            char opt;
			while (_kbhit()) _getch();
            while (true)
            {
                opt = _getch();
                if (opt >= '1' && opt <= '6')
                {
                    cout << opt << endl;
                    delay(500);
                    break;
                }
            }

            string file;
            switch (opt)
            {
            case '1': file = "science.txt"; break;
            case '2': file = "gk.txt";      break;
            case '3': file = "m&l.txt";     break;
            case '4': file = "ps.txt";      break;
            case '5': file = "mix.txt";     break;
            case '6': default: file = "";   break;
            }

            if (!file.empty())
            {
                adminAddQuestion(file);
                cout << "\n\t>> Press any key to return to main menu...";
                _getch();
            }
        }
        break;
	case '7':
		programTermination();
		break;
	case '6': { // TAHA
		string player1_name, player2_name;
		do
		{
			catagory = printCategory();
			if (catagory != '6')
			{
				difficulty = printDifficulty();
				if (difficulty != '4') {
					cout << "\n\n\n\n\t >> Enter Player 1 Name: ";
					getline(cin, player1_name);
					cout << "\t >> Enter Player 2 Name: ";
					getline(cin, player2_name);
				}
				
				start_hotseat_session(catagory, difficulty, player1_name, player2_name);
			}
		} while (catagory != '6');
		break;
	}
	}

}
//Print Categories

char printCategory()
{
	system("cls");
	char cat;
	loadingScreen("ENTERING INTO GAME....");
	system("cls");
	verticlePadding();
	drawDecoration('.', '=', '.');
	drawDecoration('|', ' ', '|');
	drawDecoration('|', ' ', '|');
	printCentered("Select Category");
	drawDecoration('|', ' ', '|');
	drawDecoration('|', '-', '|');
	printCentered("    1. Science          ");
	printCentered("    2. General Knowledge");
	printCentered("    3. Math and IQ      ");
	printCentered("    4. Pakistan Studies ");
	printCentered("    5. Mix Test         ");
	printCentered("    6. Exit             ");
	drawDecoration('|', ' ', '|');
	drawDecoration('.', '=', '.');

	cout << "\t >>Enter the Category: ";
	while (_kbhit()) _getch();
	while (true)
	{
		cat = _getch();

		if (cat >= '1' && cat <= '6')
		{
			cout << cat;
			delay(1000);
			break;
		}
	}


	return cat;
}

char printDifficulty()
{
	char diff;
	system("cls");
	verticlePadding();
	drawDecoration('.', '=', '.');
	drawDecoration('|', ' ', '|');
	drawDecoration('|', ' ', '|');
	printCentered("Select Difficulty Level");
	drawDecoration('|', ' ', '|');
	drawDecoration('|', '-', '|');
	printCentered("    1. Easy  ");
	printCentered("    2. Medium");
	printCentered("    3. Hard  ");
	printCentered("    4. Exit  ");
	drawDecoration('|', ' ', '|');
	drawDecoration('.', '=', '.');

	cout << "\t >>Enter the Difficulty Level: ";
	while (_kbhit()) _getch();
	while (true)
	{
		diff = _getch();

		if (diff >= '1' && diff <= '5')
		{
			cout << diff;
			delay(1000);
			break;
		}
	}


	return diff;
}

void printLog(string& playerName)
{
	verticlePadding();
	drawDecoration('.', '=', '.');
	cout << "\t >>Enter your Name to start game: ";
	getline(cin, playerName);
}


//Print Instructions
void printInstructions()
{
	char esc;
	delay(500);
	system("cls");
	verticlePadding();
	drawDecoration('.', '=', '.');
	drawDecoration('|', ' ', '|');
	drawDecoration('|', ' ', '|');
	printCentered("      INSTRUCTIONS      ");
	drawDecoration('|', ' ', '|');
	drawDecoration('|', ' ', '|');
	printCentered("    1.0. The Quiz consist of 10 questions / MCQ's                 ", '|');
	printCentered("    2.0. Select the correct option (A-D)                          ", '|');
	printCentered("    3.0. You have 10 seconds for each MCQ                         ", '|');
	printCentered("    4.0. Each correct answer =  1 point                           ", '|');
	printCentered("    5.0. Wrong Answer = -2 points for difficulty 1                ", '|');
	printCentered("    5.1. Wrong Answer = -3 points for difficulty 2                ", '|');
	printCentered("    5.2. Wrong Answer = -5 points for difficulty 3                ", '|');
	drawDecoration('|', ' ', '|');
	drawDecoration('|', ' ', '|');
	printCentered("GOOD LUCK!");
	drawDecoration('|', ' ', '|');
	drawDecoration('|', ' ', '|');
	drawDecoration('.', '=', '.');

	cout << "\t >> Press ESC to exit..";

	while (true)
	{
		esc = _getch();

		if (esc == 27)
		{
			break;
		}
	}

}

//Print Credits
void printCredits()
{

	char esc;
	delay(500);
	system("cls");
	verticlePadding();
	drawDecoration('.', '=', '.');
	drawDecoration('|', ' ', '|');
	drawDecoration('|', ' ', '|');
	printCentered("CREDITS:", '|');
	printCentered("    Ahmad Faraz (25F-0510)    ", '|');
	printCentered("    Ubaid Afzal (25F-0570)    ", '|');
	printCentered("    Taha (25F-0755)           ", '|');
	drawDecoration('|', ' ', '|');
	drawDecoration('|', ' ', '|');
	drawDecoration('.', '=', '.');

	cout << "\t >> Press ESC to exit..";

	while (true)
	{
		esc = _getch();

		if (esc == 27)
		{
			break;
		}
	}

}
//Program Termination Screen
void programTermination()
{
	loadingScreen("Program Terminated....");
}

//Display Content in the centre of the screen
void printCentered(string text, char border)
{
	int len = text.length();
	int padding = (WIDTH - 2 - len) / 2; //Appropriate Padding for content
	int remaining = WIDTH - 2 - padding - len; //Remaining space after padding

	cout << "\t" << border << string(padding, ' ') << text << string(remaining, ' ') << border << endl;

}

//Print some blank lines for cntring the content
void verticlePadding()
{
	for (int i = 0; i < HEIGHT_PAD; i++)
	{
		cout << endl;
	}
}

//Function to add delay in displaying content
void delay(int milliseconds) {
	clock_t goal = milliseconds * (CLOCKS_PER_SEC / 1000);
	clock_t start = clock();
	while ((clock() - start) < goal);
}

void loadingScreen(string title)
{
	system("cls");
	verticlePadding();
	cout << endl << endl << endl;
	printCentered(title, ' ');
	cout << endl;

	//Print bars
	cout << "\t   " << string(WIDTH, '_') << "\n";
	cout << "\t  |";

	//Fill the bar with delay

	for (int i = 0; i < WIDTH; i++)
	{
		cout << "#";
		delay(5);
	}
	cout << "| 100%" << endl << endl;

	//Add delay before screen comes

	delay(500);
}

void drawDecoration(char left, char fill, char right)
{
	cout << "\t" << left << string(WIDTH - 2, fill) << right << endl;
}

void startSession(char catagory, char difficulty,string playerName)
{
	int diffN = difficulty - '0';
	srand(time(0));
	int N = 0, error;
	int questionDiff[SIZE];
	string questionText[SIZE];
	string questionOption[SIZE][4];
	char correctAns[SIZE];
	int diffIndex[SIZE] = { 0 };
	int randomIndex[MAXQ+50];		
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
		for (int i = 0; i < 11; i++)
		{
			bool isDuplicate;
			do
			{
				if (k == 0) break; // taha
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
		if (k == 0) return; // taha
		printSession(N, questionDiff, questionText, questionOption, correctAns, randomIndex,playerName,catagory);
	}

}

int loadData(string& fileName, int &N, int questionDiff[], string questionText[], string questionOption[][4], char correctAns[])
{
	ifstream fin;
	fin.open(fileName);
	if (!fin)
	{
		system("cls");
		drawDecoration('.', '=', '.');
		printCentered("Error! File Not Found!", '|');
		drawDecoration('.', '=', '.');
		delay(2000);
		return -1;
	}

	fin >> N;
	for (int i = 0; i < N; i++)
	{
		fin >> questionDiff[i];
		char newLine;
		fin.get(newLine);
		getline(fin, questionText[i], '\n');
		for (int j = 0; j < 4; j++)
		{
			fin >> questionOption[i][j];
		}
		fin >> correctAns[i];
	}
}

