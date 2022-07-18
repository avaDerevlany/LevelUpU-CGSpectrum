#include <iostream>
#include <stdlib.h>
#include <time.h>
 
using namespace std;

bool GuessGame(int answer);

int main()
{
	int randomNum = 0;

	srand(time(NULL));

	randomNum = rand() % 10 + 1;

	if (GuessGame(randomNum))
	{
		cout << "\nCongrats! You've won the game!\n";
		cout << "The number was " << randomNum << endl;
	}
	else
	{
		cout << "\nOh no! You've failed to guess the number.\n";
		cout << "The number was " << randomNum << endl;
	}

	return 0;
}

bool GuessGame(int answer)
{
	int guess1 = 0;
	int guess2 = 0;
	int guess3 = 0;

	cout << "Hello! You have three chances to guess the number I've thought of.\n"
		<< "Pick a number from 1 - 10 : ";
	cin >> guess1;
	if (guess1 == answer)
	{
		return true;
	}
	
	cout << "That number is incorrect. Please try again : ";
	cin >> guess2;
	if (guess2 == answer)
	{
		return true;
	}
	else if (guess2 == guess1)
	{
		cout << "You've already tried that number!" << endl;
	}

	cout << "That number is also incorrect. Please try again again : ";
	cin >> guess3;

	if (guess3 == answer)
	{
		return true;
	}
	else if (guess3 == guess2 || guess3 == guess1)
	{
		cout << "You've already tried that number!" << endl;
	}

	return false;
}