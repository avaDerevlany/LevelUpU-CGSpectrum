#include <iostream>
#include <string>
#include "Week2.h"

using namespace std;

// function declarations
int Power(int number, int power);


/*
Write a program that uses a function to return the value of a number cubed.
Take the number as an input from the user and print the cubed value back to the user.
*/

void CubeNumber()
{
	int num;
	cout << "Please enter a number that you wish to cube: ";

	string input = "";

	// get number
	do
	{
		cin >> input;

	} while (!IsNum(input));

	num = stoi(input);

	// output
	cout << num << "^3 = " << Power(num, 3) << endl;
}

// recursion cuz why not
int Power(int number, int power)
{
	if (power == 0) return 1;	// returning number would be one too many multiplications

	return number * Power(number, power - 1);
}