#include <iostream>

using namespace std;

int main()
{
	int numOne = 3, numTwo = 5;
	cout << numOne << " + " << numTwo << " = " << (numOne + numTwo) << endl << endl;

	cout << "Loop of Hello" << endl;
	for (int x = 0; x < 7; x++)
		cout << "Hello\n";

	cout << endl << "Float with 15 decimal places" << endl;
	float wideFloat = 10.1f;
	cout.precision(17);
	cout << wideFloat << endl;

	cout << endl << "Double with 20 decimal places" << endl;
	double wideDouble = 1.897;
	cout.precision(22);
	cout << wideDouble << endl;
}