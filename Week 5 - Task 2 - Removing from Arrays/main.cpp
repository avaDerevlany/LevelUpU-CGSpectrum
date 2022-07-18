#include <iostream>

using namespace std;

int main()
{
	float floatArray[5];
	int deleteIndex = 0;

	for (int x = 0; x < 5; x++)
	{
		cout << "Enter a value for index " << x << " - ";
		cin >> floatArray[x];
	}

	cout << endl << "You entered the following values:" << endl;
	for (int x = 0; x < 5; x++)
	{
		cout << "floatArray[" << x << "] = " << floatArray[x] << endl;
	}

	cout << endl << "Enter an index to delete : ";
	cin >> deleteIndex;

	while (deleteIndex > 4 || deleteIndex < 0)
	{
		cout << "Invalid index. Enter a valid index : ";
		cin >> deleteIndex;
	}

	for (int x = deleteIndex; x < 4; x++)
	{
		floatArray[x] = floatArray[x + 1];
	}
	floatArray[4] = 0;

	cout << endl << "The array now looks like this:" << endl;
	for (int x = 0; x < 5; x++)
	{
		cout << "floatArray[" << x << "] = " << floatArray[x] << endl;
	}
	cout << endl;

	return 0;
}