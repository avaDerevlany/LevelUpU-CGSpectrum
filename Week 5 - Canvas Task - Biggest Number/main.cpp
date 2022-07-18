#include <iostream>

using namespace std;

int main()
{
	int nums[10];
	int largest = 0;

	for (int x = 0; x < 10; x++)
	{
		cout << "Enter a number for index " << x << " : ";
		cin >> nums[x];
	}

	largest = nums[0];

	for (int x = 1; x < 10; x++)
	{
		if (nums[x] > largest)
		{
			largest = nums[x];
		}
	}

	cout << endl << "The largest number is " << largest << endl;

	return 0;
}