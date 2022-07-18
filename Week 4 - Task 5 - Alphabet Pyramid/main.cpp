#include <iostream>

using namespace std;

int main()
{
	int input = 0;
	int spaces = 0;
	int letters = 0;
	char A = 'A';

	cout << "Enter positive integer value : ";
	cin >> input;
	cout << endl;

	letters = 1;

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
		for (int st = 0; st < letters / 2 + 1; st++)
		{
			cout << (char)(A + st);
		}
		for (int st = letters / 2; st > 0; st--)
		{
			cout << (char)(A + st - 1);
		}

		cout << endl;

		spaces--;
		letters += 2;
	}

	spaces = 0;
	if (input % 2 == 0)
	{
		letters = input - 1;
	}
	else
	{
		letters = input;
	}

	for (int x = input / 2; x >= 0; x--)
	{
		for (int sp = 0; sp < spaces; sp++)
		{
			cout << " ";
		}
		for (int st = 0; st < letters / 2 + 1; st++)
		{
			cout << (char)(A + st);
		}
		for (int st = letters / 2; st > 0; st--)
		{
			cout << (char)(A + st - 1);
		}

		cout << endl;

		spaces++;
		letters -= 2;
		if (letters < 1)
		{
			break;
		}
	}

	return 0;
}
