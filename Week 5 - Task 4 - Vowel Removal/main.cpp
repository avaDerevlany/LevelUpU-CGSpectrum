#include <iostream>
#include <string>

using namespace std;

int main()
{
	string input;
	string newWord = "";
	string vowels = "aeiouAEIOU";
	bool isVowel = false;

	cout << "Enter a string: ";
	getline(cin, input);

	cout << endl << "You entered: " << input << endl;

	for (int x = 0; x < input.length(); x++)
	{
		isVowel = false;
		for (int y = 0; y < vowels.length(); y++)
		{
			if (input[x] == vowels[y])
			{
				isVowel = true;
			}
		}
		if (!isVowel)
		{
			newWord += input[x];
		}
	}

	cout << "All vowels removed: " << newWord << endl;
	
	return 0;
}