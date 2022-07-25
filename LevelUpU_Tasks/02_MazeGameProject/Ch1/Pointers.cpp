#include <iostream>
#include <string>
#include "..\Section2Header.h"

using namespace std;

/*
Write a program that asks the user to enter integers to be stored in the variables 'a' and 'b'.
Then create two integer pointers named ptrA and ptrB. Assign the values of 'a' and 'b' to ptrA and ptrB, and display them.

Take an input variable and display the same value by pointer.
*/

void Pointers()
{
	int a = 0, b = 0;
	cout << "Please enter two numbers: " << endl;

	string input = "";

	// get first number
	do
	{
		cout << "a: ";
		cin >> input;

	} while (!IsNumber(input));

	a = stoi(input);

	// get second number
	do
	{
		cout << "b: ";
		cin >> input;

	} while (!IsNumber(input));

	b = stoi(input);


	// Pointers
	int* ptrA = &a;
	int* ptrB = &b;


	// Display
	cout << "Pointer a = " << *ptrA << " @ address " << ptrA << endl;
	cout << "Pointer b = " << *ptrB << " @ address " << ptrB << endl;
}

bool IsNumber(string number)
{
	try
	{
		int num = stoi(number);
		return true;
	}
	catch (...)
	{
		return false;
	}
}