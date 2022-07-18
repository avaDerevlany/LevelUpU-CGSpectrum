#include <iostream>

using namespace std;

void DiamondTop(int, int, int);
void DiamondBottom(int, int);
void PrintSpaces(int);
void PrintStars(int);

int main()
{
	int stars = 0;

	cout << "Enter positive integer value : ";
	cin >> stars;
	cout << endl;

	

	if (stars % 2 == 0)
	{
		DiamondTop(1, stars, stars / 2 - 1);
		DiamondBottom(stars - 3, 1);
	}
	else
	{
		DiamondTop(1, stars, stars / 2);
		DiamondBottom(stars - 2, 1);
	}

	return 0;
}

void DiamondTop(int current, int max, int spaces)
{
	if (current > max+1)
	{
		return;
	}

	if (current > max)
	{
		current = max-1;
		max--;
	}

	PrintSpaces(spaces);
	PrintStars(current);
	PrintSpaces(spaces);
	cout << endl;

	DiamondTop(current+2, max, spaces-1);
}

void DiamondBottom(int current, int spaces)
{
	if (current <= 0)
	{
		return;
	}

	PrintSpaces(spaces);
	PrintStars(current);
	PrintSpaces(spaces);
	cout << endl;

	DiamondBottom(current - 2, spaces + 1);
}

void PrintSpaces(int x)
{
	if (x <= 0)
		return;

	cout << " ";

	PrintSpaces(x - 1);
}

void PrintStars(int x)
{
	if (x <= 0)
		return;

	cout << "*";

	PrintStars(x - 1);
}