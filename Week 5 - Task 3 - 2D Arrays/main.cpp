#include <iostream>

using namespace std;

int main()
{
	int bigArray[5][3];

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			bigArray[x][y] = (x * y);
			cout << "bigArray[" << x << "][" << y << "] = " << bigArray[x][y] << endl;
		}
	}
	cout << endl;

	return 0;
}