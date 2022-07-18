#include <iostream>

using namespace std;

int main()
{
	//ignore bad variable names please and thanks
	int i = 3;
	float f = 6.7f;
	double d = 24.92;
	char c = ' ';

	cout << "INITIAL VARIABLES" << endl;
	cout << "-----------------" << endl;
	cout << "i = " << i << endl;
	cout << "f = " << f << endl;
	cout << "d = " << d << endl;
	cout << "c = " << c << endl << endl;

	i++;
	f--;
	d++;
	c--;

	cout << "INCREMENTED OR DECREMENTED" << endl;
	cout << "--------------------------" << endl;
	cout << "i = " << i << endl;
	cout << "f = " << f << endl;
	cout << "d = " << d << endl;
	cout << "c = " << c << endl << endl;

	int iResult = i + f + d + c;
	float fResult = i + f + d + c;
	double dResult = i + f + d + c;
	char cResult = i + f + d + c;

	cout << "SUM ALL FOR EACH" << endl;
	cout << "----------------" << endl;
	cout << "iResult = " << iResult << endl;
	cout << "fResult = " << fResult << endl;
	cout << "dResult = " << dResult << endl;
	cout << "cResult = " << cResult << endl << endl;
}