#include <iostream>
#include <string>
#include "..\Section1Header.h"

using namespace std;

/*
Write a program to find the “Sum” and “Average” of “three” numbers. Provide a hint to the user, take the input and 
return some output results to show the user the calculations for their three numbers.
*/

void ThreeNumbers()
{
	int num1 = 0, num2 = 0, num3 = 0;
	cout << "Please enter 3 numbers, each followed by ENTER" << endl;

	string input = "";

	// get first number
	do
	{
		cout << "1st number: ";
		cin >> input;

	} while (!IsNum(input));

	num1 = stoi(input);
	
	// get second number
	do
	{
		cout << "2nd number: ";
		cin >> input;

	} while (!IsNum(input));

	num2 = stoi(input);

	// get third number
	do
	{
		cout << "3nd number: ";
		cin >> input;

	} while (!IsNum(input));

	num3 = stoi(input);

	// output
	int sum = (num1 + num2 + num3);

	cout << "\n";
	cout << "Sum:     " << num1 << " + " << num2 << " + " << num3 << " = " << sum << endl;

	cout << "Average: " << sum << "/3" << " = " << sum / 3.0 << endl;
}

// I know this is not the appropriate place to put this function, but....
bool IsNum(string num, bool signedNum)
{
	for (int i = 0; i < num.length(); i++)
	{
		// if the number is negative
		if (signedNum && i == 0 && num.length() > 1 && num[0] == '-') {/* is negative number */}
		else if (!isdigit(num[i])) return false;
	}
	return true;
}