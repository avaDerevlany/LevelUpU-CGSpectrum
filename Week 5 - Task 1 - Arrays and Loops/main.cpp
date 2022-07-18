#include <iostream>

using namespace std;

int main()
{
	int intArray[5];

	for (int x = 0; x < 5; x++)
	{
		cout << "Enter a number for index " << x << " - ";
		cin >> intArray[x];
	}

	cout << endl << "You entered the following values:" << endl;
	for (int x = 0; x < 5; x++)
	{
		cout << "intArray[" << x << "] = " << intArray[x] << endl;
	}

	return 0;
}