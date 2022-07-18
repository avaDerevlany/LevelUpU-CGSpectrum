#include <iostream>

using namespace std;

int main()
{
	int first = 0;
	int second = 0;
	int third = 0;
	int fourth = 0;
	int fifth = 0;

	int smallest = 0;
	int biggest = 0;
	bool duplicates = false;

	cout << "Enter first number : ";
	cin >> first;
	cout << "Enter second number : ";
	cin >> second;
	cout << "Enter third number : ";
	cin >> third;
	cout << "Enter fourth number : ";
	cin >> fourth;
	cout << "Enter fifth number : ";
	cin >> fifth;

	if (first <= second && first <= third && first <= fourth && first <= fifth)
	{
		smallest = first;
	}
	else if (second <= first && second <= third && second <= fourth && second <= fifth)
	{
		smallest = second;
	}
	else if (third <= second && third <= first && third <= fourth && third <= fifth)
	{
		smallest = third;
	}
	else if (fourth <= second && fourth <= third && fourth <= first && fourth <= fifth)
	{
		smallest = fourth;
	}
	else
	{
		smallest = fifth;
	}

	if (first >= second && first >= third && first >= fourth && first >= fifth)
	{
		biggest = first;
	}
	else if (second >= first && second >= third && second >= fourth && second >= fifth)
	{
		biggest = second;
	}
	else if (third >= second && third >= first && third >= fourth && third >= fifth)
	{
		biggest = third;
	}
	else if (fourth >= second && fourth >= third && fourth >= first && fourth >= fifth)
	{
		biggest = fourth;
	}
	else
	{
		biggest = fifth;
	}

	if (first == second || first == third || first == fourth || first == fifth)
	{
		duplicates = true;
	}
	if (second == third || second == fourth || second == fifth)
	{
		duplicates = true;
	}
	if (third == fourth || third == fifth)
	{
		duplicates = true;
	}
	if (fourth == fifth)
	{
		duplicates = true;
	}
	
	cout << endl << "The smallest number is - " << smallest << endl;
	cout << "The biggest number is - " << biggest << endl;
	if (duplicates)
	{
		cout << "There ARE duplicated values" << endl;
	}
	else
	{
		cout << "There ARE NO duplicated values" << endl;
	}

	return 0;
}