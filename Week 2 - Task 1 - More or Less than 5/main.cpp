#include <iostream>

using namespace std;

int main()
{
	int input = 0;

	cout << "Enter a number between 1 and 10 inclusive - ";
	cin >> input;

	cout << "Entered number is : " << input;

	if (input < 1 || input > 10)
	{
		cout << "\nThat is invalid" << endl;
		cout << "I'm done with you" << endl;

		return 1;
	}
	else if (input < 5)
	{
		cout << "\nThat number is less than five." << endl;
	}
	else if (input == 5)
	{
		cout << "\nThat number IS five." << endl;
	}
	else
	{
		cout << "\nThat number is greater than five." << endl;
	}

	return 0;
}