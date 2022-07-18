//A* 80
//A 70 79
//B 60 69
//C 50 59
//D 40 49
//F 1 39
//U 0

#include <iostream>

using namespace std;

int main()
{
	int grade = 0;

	cout << "Enter a grade: ";
	cin >> grade;

	cout << "Entered grade is - " << grade << endl;
	cout << "Letter grade is - ";

	if (grade >= 80)
	{
		cout << "A*" << endl;
	}
	else if (70 <= grade && grade <= 79)
	{
		cout << "A" << endl;
	}
	else if (60 <= grade && grade <= 69)
	{
		cout << "B" << endl;
	}
	else if (50 <= grade && grade <= 59)
	{
		cout << "C" << endl;
	}
	else if (40 <= grade && grade <= 49)
	{
		cout << "D" << endl;
	}
	else if (1 <= grade && grade <= 39)
	{
		cout << "F" << endl;
	}
	else if (grade == 0)
	{
		cout << "U" << endl;
	}
	else
	{
		cout << "N/A invalid grade" << endl;
		return 1;
	}

	return 0;
}