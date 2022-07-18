#include <iostream>

using namespace std;

int main()
{
	int input = 0;
	int guesses = 0;

	while (input != 5)
	{
		cout << "Please input any number EXCEPT 5 - ";
		cin >> input;

		guesses++;

		if (guesses > 9)
		{
			cout << "Wow, you're more patient than I am. You win..." << endl;
			return 0;
		}
	}

	cout << "Hey! You weren't supposed to enter 5!" << endl;

	return 0;
}