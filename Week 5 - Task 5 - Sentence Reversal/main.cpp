#include <iostream>
#include <string>

using namespace std;

int main()
{
	string input;
	int numSpaces = 0;

	cout << "Enter a sentence: ";
	getline(cin, input);

	cout << "That sentence reversed is : ";
	for (int x = input.length() - 1; x >= 0; x--)
	{
		if (input[x] == ' ')
		{
			for (int y = x + 1; y < input.length(); y++)
			{
				if (input[y] != ' ')
				{
					cout << input[y];
				}
				if (input[y] == ' ' || y == input.length()-1)
				{
					cout << " ";
					break;
				}
			}
		}
	}
	int x = 0;
	while (input[x] != ' ')
	{
		cout << input[x];
		x++;
	}
	cout << endl;

	return 0;
}