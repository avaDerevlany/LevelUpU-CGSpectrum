#include <iostream>

using namespace std;

int main()
{
	int input = 0;
	int total = 0;

	cout << "Enter a number - ";
	cin >> input;

	for (int x = 1; x <= input; x++)
	{
		cout << x << " ";
		total += x;
	}

	cout << endl << "Total is " << total << endl;
	return 0;
}