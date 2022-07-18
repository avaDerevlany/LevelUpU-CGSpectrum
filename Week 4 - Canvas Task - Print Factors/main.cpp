#include <iostream>

using namespace std;

int main()
{
	int input = 0;

	cout << "Input a positive integer : ";
	cin >> input;

	if (input <= 0)
	{
		cout << "Invalid Number. Goodbye." << endl;
		return 1;
	}

	for (int x = 1; x <= input; x++)
	{
		if (input % x == 0)
			cout << x << " ";
	}

	cout << endl;

	return 0;
}