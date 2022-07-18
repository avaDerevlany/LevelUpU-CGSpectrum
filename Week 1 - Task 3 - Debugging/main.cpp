#include <iostream>

int main()
{
	int i = 4;
	int j = i + 1;

	if (j == 5)
	{
		std::cout << "Variable j is equal to 5";
	}
	//else statement is useless, should be deleted
	else
	{
		std::cout << "This else statement does nothing...";
	}
	
}