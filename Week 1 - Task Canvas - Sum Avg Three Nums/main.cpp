#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

bool validateNum(string);

int main()
{
	string userInput = "";
	int first = 0;
	int second = 0;
	int third = 0;
	int sum = 0;
	float avg = 0.0f;

	//getting first number
	cout << "I need three numbers...\nGive me the first one - ";
	cin >> userInput;

	while (validateNum(userInput))
	{
		cout << "\nThat wasn't a good number. Give me a real number - ";
		cin >> userInput;
	}

	first = atoi(userInput.c_str());

	//getting second number
	cout << "Great! Now the second one - ";
	cin >> userInput;

	while (validateNum(userInput))
	{
		cout << "\nThat wasn't a good number. Give me a real number - ";
		cin >> userInput;
	}

	second = atoi(userInput.c_str());

	//getting third number
	cout << "And finally, give me the third number - ";
	cin >> userInput;

	while (validateNum(userInput))
	{
		cout << "\nThat wasn't a good number. Give me a real number - ";
		cin >> userInput;
	}

	third = atoi(userInput.c_str());

	//final output of numbers
	cout << "\nFirst Number: " << first << endl;
	cout << "Second Number: " << second << endl;
	cout << "Third Number: " << third << endl;

	//calc and output sum and avg
	sum = first + second + third;
	avg = sum / 3.0f;

	cout << "\nSum: " << sum << endl;
	cout << "\nAvg: " << avg << endl;

	cout << "\nThanks for the numbers" << endl;
}

/*************************
validateNum function

return bool
if input is not all ints
	return true
else
	return false
*************************/
bool validateNum(string input)
{
	for (int x = 0; x < input.length(); x++)
	{
		if (input[x] < 48 || input[x] > 57)
			return true;
	}

	return false;
}