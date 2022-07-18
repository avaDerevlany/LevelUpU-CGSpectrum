#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

float FunctionA(int, int, float);
bool FunctionB(float);

int main()
{
	int num1 = 0;
	int num2 = 0;
	float num3 = 0.0f;

	cout << "Enter an integer : ";
	cin >> num1;
	cout << "Enter a second integer : ";
	cin >> num2;
	cout << "Enter a decimal number : ";
	cin >> num3;

	if (FunctionB(FunctionA(num1, num2, num3)))
	{
		cout << "The function returned true!" << endl;
	}
	else
	{
		cout << "The function returned false." << endl;
	}

	return 0;
}

float FunctionA(int x, int y, float f)
{
	float result = (x + y) * f;

	return result;
}

bool FunctionB(float f)
{
	srand(time(NULL));
	int random = rand() % 10 + 1;

	return f < random;
}