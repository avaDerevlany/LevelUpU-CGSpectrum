#include <iostream>

using namespace std;

int main()
{
	int year = 0;

	bool leap = false;

	cout << "Enter a year : ";
	cin >> year;

	if (year % 4 == 0)
	{
		if (year % 100 == 0 && !(year % 400 == 0))
		{
			leap = false;
		}
		else
		{
			leap = true;
		}
	}
	else
	{
		leap = false;
	}

	if (leap)
	{
		cout << "The year " << year << " is a leap year!" << endl;
	}
	else
	{
		cout << "The year " << year << " is not a leap year." << endl;
	}

	return 0;
}