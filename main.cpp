#include <iostream>
#include <iomanip>
#include "faraz.h"
#include "taha.h"
#include "ubaid.h"

using namespace std;

int main()
{
	char choice = 0;
	do
	{
		choice = printMainMenu();
		printChoices(choice);
	} while (choice != '7');
	return 0;
}