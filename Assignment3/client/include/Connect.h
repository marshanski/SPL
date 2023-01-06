#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <functional>
using std::string;
using std::vector;

class Frame
{
private:

   

public:
    Frame();
    virtual ~Frame();
    string toString(std::string order);
    string ConnectToString(std::string order);
};