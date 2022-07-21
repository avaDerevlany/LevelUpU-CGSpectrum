#pragma once
#include <string>

/*
Create a vehicle base class, and from that create the necessary classes to get to boat, car and airplane.

All classes should have an overridable function named Drive.

Create an object of each and demonstrate the Drive function works.

Feel free to add any additional functionality to better simulate these vehicles!
*/

class Vehicle
{
public:
	enum Condition
	{
		New,
		Good,
		Used,
		Poor
	};

	int year;
	int miles;
	std::string brand;
	Condition condition;

	Vehicle(int year = 1885, int miles = 0, std::string brand = "undefined", enum Condition condition = New);
	~Vehicle();
	virtual void Drive(int miles, bool print = true);
	virtual void PrintInfo();
	std::string Condition();
};

class Boat : public Vehicle
{
public:
	Boat(int year = 1885, int miles = 0, std::string brand = "undefined", enum Condition condition = New);
	void Drive(int miles, bool print = true) override;
	void PrintInfo() override;
};

class Car : public Vehicle
{
public:
	int numberOfSeats;

	Car(int year = 1885, int miles = 0, std::string brand = "undefined",  enum Vehicle::Condition condition = New, int numberOfSeats = 1);
	void Drive(int miles, bool print = true) override;
	void PrintInfo() override;
};

class Airplane : public Vehicle
{
private:
	int currentNumberOfPassengers;

public:
	int maxNumberOfPassengers;

	Airplane(int year = 1885, int miles = 0, std::string brand = "undefined", enum Vehicle::Condition condition = New, int maxNumberOfPassengers = 1);
	void Drive(int miles, bool print = true) override;
	void PrintInfo() override;
	void Board(int numberOfBoarders);
	void Exit();
	bool IsPlaneFull();
};