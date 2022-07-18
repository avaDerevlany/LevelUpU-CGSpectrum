#include <iostream>

using namespace std;

int Cube(int);
int Power(int, int);

int main()
{
	int input = 0;

	cout << "Enter a number to be cubed : ";
	cin >> input;

	cout << input << " cubed is " << Cube(input) << endl;

	return 0;
}

int Cube(int num)
{
	return num * num * num;
}

int Power(int num, int pow)
{
	for (int x = 0; x < pow; x++)
	{
		num *= num;
	}

	return num;
}