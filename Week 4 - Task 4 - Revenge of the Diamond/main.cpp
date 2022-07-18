#include <iostream>

using namespace std;

int main()
{
	int input = 0;
	int spaces = 0;
	int stars = 0;

	cout << "Enter positive integer value : ";
	cin >> input;
	cout << endl;

	stars = 1;

	if (input % 2 == 0)
	{
		spaces = input / 2 - 1;
	}
	else
	{
		spaces = input / 2;
	}


	for (int x = 0; x < input / 2; x++)
	{
		for (int sp = 0; sp < spaces; sp++)
		{
			cout << " ";
		}
		for (int st = 0; st < stars; st++)
		{
			cout << "*";
		}

		cout << endl;

		spaces--;
		stars += 2;
	}

	spaces = 0;
	if (input % 2 == 0)
	{
		stars = input - 1;
	}
	else
	{
		stars = input;
	}

	for (int x = input / 2; x >= 0; x--)
	{
		for (int sp = 0; sp < spaces; sp++)
		{
			cout << " ";
		}
		for (int st = 0; st < stars; st++)
		{
			cout << "*";
		}

		cout << endl;

		spaces++;
		stars -= 2;
		if (stars < 1)
		{
			break;
		}
	}

	return 0;
}
