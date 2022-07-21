#include <iostream>
#include <string>
#include "..\Section1Header.h"

using namespace std;

/*
Write a program to find and display the biggest number(element) in an array of integers.
Hint the size of the array is unimportant as long as there's a way to check that the number displayed is definitely 
the biggest number.
*/

void BiggestNumber(int intArray[], int size)
{
	int biggestNum = intArray[0];		// all arrays will have at least 1 value (cannot declare an array of length 0
	for (int i = 1; i < size; i++)
	{
		if (intArray[i] > biggestNum) biggestNum = intArray[i];
	}

	cout << "The biggest number in the array " << IntArrayToString(intArray, size) << " is: " << biggestNum << endl;
	
}

string IntArrayToString(int intArray[], int size)
{
	string returnString = "(";

	for (int i = 0; i < size; i++)
	{
		if (i + 1 == size) returnString += to_string(intArray[i]);
		else returnString += to_string(intArray[i]) + ", ";
	}
	returnString += ")";

	return returnString;
}