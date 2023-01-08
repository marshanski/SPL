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
    vector<string>  toString(std::string order);
    vector<string>  ConnectToString(std::string order);
    vector<string>  SubscribeToString(std::string msg);
    vector<string>  unSubscribeToString(std::string msg);
    vector<string>  logOutToString(std::string msg);
    vector<string>  reportToString(std::string msg);
};