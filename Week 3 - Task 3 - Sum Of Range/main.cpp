#include <iostream>

using namespace std;

int SumOfRange(int);

int main()
{
	int input = 0;

	cout << "Enter a positive number : ";
	cin >> input;

	cout << "The sum of this range is " << SumOfRange(input) << endl;

	return 0;
}

int SumOfRange(int i)
{
	if (i > 0)
	{
		return i + SumOfRange(i - 1);
	}
	else
	{
		return 0;
	}
}