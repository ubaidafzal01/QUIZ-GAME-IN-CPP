#include<iostream>
#include<fstream>
#include<iomanip>
#include "faraz.h"
#include <cstdlib>
#include <conio.h>
#include <string>
#include<ctime>
using namespace std;

void appendLog(string filename, string playerName, string category, int score, int totalQuestions) {
    // to print heading just 1 time
    system("cls");
    bool fileIsEmpty = false;
    ifstream checkfile(filename);
    if (checkfile.peek() == EOF) {
        fileIsEmpty = true;
    }
    checkfile.close();

    ofstream out_file;
    out_file.open(filename, ios::app);

    if (out_file.is_open()) {
        time_t now = time(0);

         //--- CHANGE START ---
        char dt_buffer[26]; // Create a buffer (ctime needs at least 26 characters)
        ctime_s(dt_buffer, sizeof(dt_buffer), &now); // Use the secure function
        string dt(dt_buffer); // Convert char array to string to keep your logic below
        // --- CHANGE END ---

        dt.pop_back(); // Remove the automatic newline character

        if (fileIsEmpty) {
            out_file << "==============================================================================================================================\n";
            out_file << "#                                                   QUIZ GAME ACTIVITY LOG                                                   #\n";
            out_file << "==============================================================================================================================\n";
            out_file << "\n\n\n";
        }
        out_file << "[" << dt << "]  " <<left<<setw(30)<< playerName << " | Category: "<<setw(15) << category << " | Score: " << setw(4)<<score << " | Total Qestion Asked: " <<setw(3)<< totalQuestions << endl;

        out_file.close();
    }
    else {
        cout << "FILE IS NOT ACCESSED";
        return;
    }
}

void showReview(string questions[], char userAns[], char correct[],int N,int randI[],int score, string questionOption[][4]) {

    drawDecoration('#', '*', '#');
    cout << "\t#\t\t\t\t\t\tFinal Report\t\t                           #\n";
    drawDecoration('#', '*', '#');
    bool wrong = false;
    int wronganswers = 0;
    for (int i = 0; i < N; ++i) {
        if (userAns[i] != correct[randI[i]]) {
            wrong = true;
            cout << "\tQuestion: " << questions[randI[i]]<< endl;
            cout << "\tYour answer: " << userAns[i] << endl;
            cout << "\tCorrect answer: (" << correct[randI[i]] <<") ";
            if (correct[randI[i]] == 'A') cout << questionOption[randI[i]][0]<<endl;
            if (correct[randI[i]] == 'B') cout << questionOption[randI[i]][1]<<endl;
            if (correct[randI[i]] == 'C') cout << questionOption[randI[i]][2]<<endl;
            if (correct[randI[i]] == 'D') cout << questionOption[randI[i]][3]<<endl;
            wronganswers++;
        }
    }
    if (!wrong) {
        cout << "\n\n\tCongratulations!you attempted all correct. Your score is " << N << "/" << N << endl;
        cout << "\n" << setw(30) << "\tTotal Score" << ":    " << score << endl;
    }
    else {
        cout << "\n"<<setw(30)<<"\tTotal corrected Answers" <<":    " << N - wronganswers << " / " << N << endl << endl;
        cout << "\n"<<setw(30)<<"\tTotal Score" <<":    " << score << endl;

    }
    char esc;
    cout << "\n\t >> Press ESC to exit..";

    while (true)
    {
        esc = _getch();

        if (esc == 27)
        {
            break;
        }
    }
}


void adminAddQuestion(string filename) {
    string difficulties[300];
    string questions[300];
    string optA[300];
    string optB[300];
    string optC[300];
    string optD[300];
    string correct[300];
    int count = 0;

    ifstream in_file;
    in_file.open(filename);

    if (in_file.is_open()) {
        in_file >> count;
        string dummy;
        getline(in_file, dummy);

        for (int i = 0; i < count; ++i) {
            getline(in_file, difficulties[i]);
            getline(in_file, questions[i]);
            in_file >> optA[i] >> optB[i] >> optC[i] >> optD[i] >> correct[i];
            getline(in_file, dummy);
        }
        in_file.close();
    }

    if (count >= 300) {
        cout << "Error: Category is full" << endl;
        return;
    }

    cout << "---------------------WELCOME TO ADMIN PANEL------------------------" << endl;
    cout << "------------ADD A QUESTION---------" << endl;

    cout << "Difficulty level (1,2,3): ";
    getline(cin, difficulties[count]);
    

    cout << "Write a question here: ";
    getline(cin, questions[count]);

    cout << "Option A: ";
    getline(cin, optA[count]);

    cout << "Option B: ";
    getline(cin, optB[count]);

    cout << "Option C: ";
    getline(cin, optC[count]);

    cout << "Option D: ";
    getline(cin, optD[count]);

    cout << "Correct answer: ";
    getline(cin, correct[count]);

    count++;

    ofstream out_file;
    out_file.open(filename);

    if (out_file.is_open()) {
        out_file << count << endl;
        for (int i = 0; i < count; ++i) {
            out_file << difficulties[i] << endl;
            out_file << questions[i] << endl;
            out_file << optA[i] << " " << optB[i] << " " << optC[i] << " " << optD[i] << endl;
            out_file << correct[i] << endl;
        }
        cout << "Question added successfully!" << endl;
        out_file.close();
    }
    else {
        cout << "File is not accessed" << endl;
    }
}


// =========
int loadLeaderboard(string filename, string names[], int scores[], string categories[], int maxPlayers) {
	ifstream in_file(filename);
	int totalplayers = 0;

	if (!in_file.is_open()) {
		cout << "FILE IS NOT ACCESSED\n";
		return 0;
	}

	while (totalplayers < maxPlayers && !in_file.eof()) {
		string name, category;
		int score;

		in_file >> name >> score >> category;

		if (in_file.fail()) { 
			in_file.clear(); 
			string dummy;
			getline(in_file, dummy); 
			continue;
		}

		names[totalplayers] = name;
		scores[totalplayers] = score;
		categories[totalplayers] = category;
		totalplayers++;
	}

	in_file.close();
	return totalplayers;
}


void sortLeaderboard(string names[], int scores[], string categories[], int N) {
	for (int pass = 0; pass < N - 1; ++pass) {
		for (int i = 0; i < N - 1 - pass; ++i) {
			if (scores[i] < scores[i + 1]) {
				int tempScore = scores[i];
				scores[i] = scores[i + 1];
				scores[i + 1] = tempScore;

				string tempName = names[i];
				names[i] = names[i + 1];
				names[i + 1] = tempName;

				string tempCat = categories[i];
				categories[i] = categories[i + 1];
				categories[i + 1] = tempCat;
			}
		}
	}
}


void displayTopPlayers(string names[], int scores[], string categories[], int totalLoaded, int topN) {
	system("cls");
	cout << "\t----------------------------------------------------------------" << endl;
	cout << "\t               WELCOME TO LEADERBOARD                           " << endl;
	cout << "\t----------------------------------------------------------------" << endl;
	cout << "\tTHESE ARE TOP " << topN << " PLAYERS: " << endl;
	for (int i = 0; i < topN && i < totalLoaded; ++i) {
		cout << "\tName: " << " | " << names[i] << " |  Score: " << scores[i] << " | Category: " << categories[i] << endl;
	}
	cout << "\n\tCONGRATULATIONS! TO ALL WHO PLAYED WITH THIER DEPHT OF HEART :)" << endl;
}

void updateLeaderboard(string filename, string playerName, int score, string category) {
	string names[100];
	int scores[100];
	string categories[100];

	int totalplayers = loadLeaderboard(filename, names, scores, categories, 100);
	names[totalplayers] = playerName;
	scores[totalplayers] = score;
	categories[totalplayers] = category;
	totalplayers++;

	if (totalplayers > 1) {
		sortLeaderboard(names, scores, categories, totalplayers);
	}

	int topN = 5;
	if (totalplayers > topN) {
		totalplayers = topN;
	}

	ofstream out_file;
	out_file.open(filename);
	if (out_file.is_open()) {
		for (int i = 0; i < totalplayers; ++i) {
			out_file << names[i] << " " << scores[i] << " " << categories[i] << endl;
		}
		out_file.close();
	}
	else {
		cout << "FILE IS NOT ACCESSED";
	}
}