#include <iostream>
#include <string>
#include "..\Section1Header.h"

using namespace std;

/* 
Write a program to check and return whether it is currently a leap year.
*/

void LeapYear()
{
	int year;
	cout << "Please enter a year and I will let you know if it was a leap year: ";

	string input = "";

	// get number
	do
	{
		if (input != "") cout << "Please enter a valid year: ";

		cin >> input;

	} while (!IsYear(input));

	year = stoi(input);

	cout << "The year " << year << BoolToIs_IsNot(CheckLeapYear(year)) << "a leap year." << endl;
}

bool CheckLeapYear(int year)
{
	// any year that can be exactly divided by 4
	// except if it can be exactly divided by 100
	// except if it can be exactly divided by 400

	if (year % 4 == 0)
	{
		if (year % 400 == 0) return true;
		else if (year % 100 == 0) return false;
		else return true;
	}
	else return false;
}

bool IsYear(string year)
{
	if (year.length() == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!isdigit(year[i])) return false;
		}
		return true;
	}
	else return false;
}

string BoolToIs_IsNot(bool value)
{
	if (value) return " is ";
	else return " is not ";
}