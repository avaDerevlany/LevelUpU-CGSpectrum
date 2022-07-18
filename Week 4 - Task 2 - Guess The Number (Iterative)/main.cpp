#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
	int randomNum = 0;
	int input = 0;

	srand(time(NULL));

	randomNum = rand() % 10 + 1;

	do
	{
		cout << "Input a guess, I'll let you know if you're right - ";
		cin >> input;
	} while (input != randomNum);

	cout << "You got the number!" << endl;

	return 0;
}