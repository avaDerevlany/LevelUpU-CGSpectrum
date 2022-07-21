#include <iostream>
#include <string>
#include "VehicleInheritance.h"
#include "..\Section1Header.h"

using namespace std;

/* 
Create a vehicle base class, and from that create the necessary classes to get to boat, car and airplane.

All classes should have an overridable function named Drive.

Create an object of each and demonstrate the Drive function works.

Feel free to add any additional functionality to better simulate these vehicles!
*/


Vehicle::Vehicle(int year, int miles, string brand, enum Condition condition)
		: year(year), miles(miles), brand(brand), condition(condition)
{

}

Vehicle::~Vehicle()
{

}

void Vehicle::Drive(int miles, bool print)
{
	this->miles += miles;

	if (print) cout << "Driving VEHICLE " << to_string(miles) << " miles, resulting in " << to_string(this->miles) << " miles traveled overall" << endl;
}

void Vehicle::PrintInfo()
{
	cout <<  "Info:\n--------------------------" << endl;
	cout << "Year: " << to_string(year) << endl;
	cout << "Miles: " << to_string(miles) << endl;
	cout << "Brand: " << brand << endl;
	cout << "Condition: " << Condition() << endl;
}

string Vehicle::Condition()
{
	switch (condition)
	{
	case New: return "New";
	case Good: return "Good";
	case Used: return "Used";
	case Poor: return "Poor";
	default: return "undefined";
	}
}

////////////////////////////////////

Boat::Boat(int year, int miles, string brand, enum Condition condition)
{
	this->year = year;
	this->miles = miles;
	this->brand = brand;
	this->condition = condition;
}

void Boat::Drive(int miles, bool print)
{
	Vehicle::Drive(miles, false);
	if (print) cout << "Driving BOAT " << to_string(miles) << " miles, resulting in " << to_string(this->miles) << " miles traveled overall" << endl;
}

void Boat::PrintInfo()
{
	Vehicle::PrintInfo();
}

////////////////////////////////////

Car::Car(int year, int miles, string brand, enum Vehicle::Condition condition, int numberOfSeats)
	: numberOfSeats(numberOfSeats)
{
	this->year = year;
	this->miles = miles;
	this->brand = brand;
	this->condition = condition;
}

void Car::Drive(int miles, bool print)
{
	Vehicle::Drive(miles, false);
	if (print) cout << "Driving CAR " << to_string(miles) << " miles, resulting in " << to_string(this->miles) << " miles traveled overall" << endl;
}

void Car::PrintInfo()
{
	Vehicle::PrintInfo();
	cout << "Number of Seats: " << to_string(numberOfSeats) << endl;
}

////////////////////////////////////

Airplane::Airplane(int year, int miles, std::string brand, enum Vehicle::Condition condition, int maxNumberOfPassengers)
	: maxNumberOfPassengers(maxNumberOfPassengers)
{
	this->year = year;
	this->miles = miles;
	this->brand = brand;
	this->condition = condition;

	currentNumberOfPassengers = 0;
}


void Airplane::Drive(int miles, bool print)
{
	Vehicle::Drive(miles, false);
	if (print) cout << "Driving PLANE " << to_string(miles) << " miles, resulting in " << to_string(this->miles) << " miles traveled overall" << endl;
}

void Airplane::PrintInfo()
{
	Vehicle::PrintInfo();
	cout << "Max number of passengers: " << to_string(maxNumberOfPassengers) << endl;
	cout << "Is plane full: " << BoolToIs_IsNot(IsPlaneFull()) << endl;
}

void Airplane::Board(int numberOfBoarders)
{
	currentNumberOfPassengers = numberOfBoarders;
}

void Airplane::Exit()
{
	currentNumberOfPassengers = 0;
}

bool Airplane::IsPlaneFull()
{
	if (currentNumberOfPassengers == maxNumberOfPassengers) return true;
	return false;
}