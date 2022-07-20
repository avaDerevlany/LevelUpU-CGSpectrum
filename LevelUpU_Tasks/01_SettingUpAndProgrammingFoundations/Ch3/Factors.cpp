#include <iostream>
#include <string>
#include "..\Section1Header.h"

using namespace std;

/* 
Write a program to display all factors of a number provided by the user. Take an input of a positive value and write 
back all of the values factors.
*/

void Factors()
{
	int num;
	cout << "Please enter a positive number that you wish to factor: ";

	string input = "";

	// get number
	do
	{
		if (input != "") cout << "Please enter a positive number: ";

		cin >> input;

	} while (!IsNum(input, false));

	num = stoi(input);

	cout << "Here are the factors for " << num << ": ";
	for (int i = 1; i <= num; i++)
	{
		if (num % i == 0)
		{
			if (i == num) cout << i;
			else cout << i << ", ";
		}
	}
	cout << endl;
}