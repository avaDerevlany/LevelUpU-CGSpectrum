#include <iostream>

using namespace std;

int main()
{
	int choice = 0;

	cout << "Walking along the road during Halloween night, you see a creepy house.\nWhat do you do?\n\n";
	cout << "1. Approach the house" << endl
		<< "2. Continue on your way" << endl;
	cin >> choice;

	if (choice == 1)
	{
		cout << "Approaching the house, you see three ways to enter the house.\nWhich way do you go?\n\n";
		cout << "1. Knock on the door" << endl
			<< "2. Scale the wall to an open window" << endl
			<< "3. Descend into the cellar" << endl;
		cin >> choice;

		switch (choice)
		{
		case(1):
		{
			cout << "You knock roughly on the wooden door.\nA masked woman answers with a bowl full of candy."
				<< "\nShe compliments your costume and drops some candy into your bag."
				<< "\nLater that night, after eating your candy haul your stomach starts to turn."
				<< "\nYou've been poisoned! Vomity end" << endl;

			return 0;
			break;
		}
		case(2):
		{
			cout << "You attempt to scale up a gutter pipe along the corner of the house."
				<< "\nThe pipe is a bit slippery."
				<< "\nYour grip slips and you tumble down landing head first onto a rock. Bloody end." << endl;

			return 0;
			break;
		}
		case(3):
		{
			cout << "You descend the dark stairs through the open cellar door."
				<< "\nThe wooden stairs creak with each step and the smell of a dirt floor hits your nose."
				<< "\nThe room is dark and there is no way for you to see where you're going."
				<< "\nYou hear what could be voices somewhere ahead of you."
				<< "What do you do?\n\n";
			cout << "1. Feel around for a light" << endl
				<< "2. Follow the voices" << endl;
			cin >> choice;

			if (choice == 1)
			{
				cout << "You feel around the wall for a switch in hopes to turn on a light."
					<< "\nAs your hand slides, brick move under your fingers until you feel a wire."
					<< "\nYour hand traces the wire hoping for a lamp."
					<< "\nInstead, you're met with a powerful shock."
					<< "\nYou've grabbed an exposed live wire and suffered a massive shock."
					<< "\nYour heart is stopped and you die in the dark! Shocking end." << endl;
			}
			else if (choice == 2)
			{
				cout << "You walk straight ahead where you hear the sound coming from."
					<< "\nYour foot hits stairs which you follow up and enter a door at the top."
					<< "\nAs you open the door, the lights come on and everyone jumps out yelling"
					<< "\nSURPRISE!\n"
					<< "\nYour family approaches you and hugs are given."
					<< "\nNow you remember, it's your birthday today and this is your house."
					<< "\nYou should really try to be less forgetful. Birthday end." << endl;
			}

			break;
		}
		}
	}
	else
	{
		cout << endl << "With that, your adventure ends before it began. As you make your way home you're hit by a car in the dark. Sad end." << endl;
	}

	return 0;
}