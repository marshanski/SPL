#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>
using std::string;
using std::vector;

class Connect
{
private:
    string command;
    string host;
    string  port;
    string username;
    string password;

public:
    Connect(std::string order);
    virtual ~Connect();
    string toString();
};