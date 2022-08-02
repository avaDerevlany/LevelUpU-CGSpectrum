#include <chrono>
#include <vector>
#include <string>
#include "Section3Header.h"

uint32_t GetNanos()
{
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}

std::string VectorToString(std::vector<int> vectorToConvert)
{
    std::string returnString = "(";
    for (int i = 0; i < vectorToConvert.size(); i++)
    {
        if (i + 1 == vectorToConvert.size()) returnString += std::to_string(vectorToConvert[i]);
        else returnString += std::to_string(vectorToConvert[i]) + ", ";
    }
    returnString += ")";
    return returnString;
}

std::string VectorToString(std::vector<Node*> vectorToConvert)
{
    std::string returnString = "(";
    for (int i = 0; i < vectorToConvert.size(); i++)
    {
        if (i + 1 == vectorToConvert.size()) returnString += (*vectorToConvert[i]).name;
        else returnString += (*vectorToConvert[i]).name + ", ";
    }
    returnString += ")";
    return returnString;
}

std::string ArrayToString(int vectorToConvert[], int size)
{
    std::string returnString = "(";
    for (int i = 0; i < size; i++)
    {
        if (i + 1 == size) returnString += std::to_string(vectorToConvert[i]);
        else returnString += std::to_string(vectorToConvert[i]) + ", ";
    }
    returnString += ")";
    return returnString;
}