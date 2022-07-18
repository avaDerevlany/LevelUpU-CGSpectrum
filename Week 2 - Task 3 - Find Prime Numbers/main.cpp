#include <iostream>

using namespace std;

//1 - 10
// find if prime
// outside of range is invalid

int main()
{
	int input = 0;
	bool isPrime = true;

	cout << "Enter a number between 1 - 10 : ";
	cin >> input;

	cout << "Entered number is - " << input << endl;

	if (input > 10 || input < 1)
	{
		cout << "Invalid number. Goodbye." << endl;
		return 1;
	}


	for (int x = input-1; x > 1; x--)
	{
		if (input % x == 0)
		{
			isPrime = false;
		}
	}

	if (input == 1)
	{
		isPrime = false;
	}

	if (isPrime)
	{
		cout << "That is a prime number!" << endl;
	}
	else
	{
		cout << "That is NOT a prime number" << endl;
	}

	return 0;
}