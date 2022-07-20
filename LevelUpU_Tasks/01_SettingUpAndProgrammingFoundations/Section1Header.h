#pragma once
#include <string>

// Ch 2
void ThreeNumbers();
void CubeNumber();

// Ch 3
void LeapYear();
bool CheckLeapYear(int year);
void Factors();

// helper functions
bool IsNum(std::string num, bool signedNum = true);
bool IsYear(std::string year);
std::string BoolToIs_IsNot(bool value);