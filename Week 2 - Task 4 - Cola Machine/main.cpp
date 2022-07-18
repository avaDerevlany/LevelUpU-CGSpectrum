#include <iostream>

using namespace std;

int main()
{
	int choice = 0;

	cout << "Drink choices : \n"
		<< "1: Coke\n"
		<< "2: Dr. Pepper\n"
		<< "3: Sprite\n"
		<< "4: Red Bull\n"
		<< "5: Water\n" << endl;

	cout << "Enter a number : ";
	cin >> choice;

	switch (choice)
	{
	case(1):
	{
		cout << "You chose Coke!" << endl;
		break;
	}
	case(2):
	{
		cout << "You chose Dr. Pepper!" << endl;
		break;
	}
	case(3):
	{
		cout << "You chose Sprite!" << endl;
		break;
	}
	case(4):
	{
		cout << "You chose Red Bull!" << endl;
		break;
	}
	case(5):
	{
		cout << "You chose Water." << endl;
		break;
	}
	default:
	{
		cout << "Invalid choice" << endl;
		return 1;
	}
	}

	return 0;
}