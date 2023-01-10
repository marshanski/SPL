#pragma once

#include "../include/user.h"
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
    vector<string>  toString(std::string order,User& user);
    vector<string>  ConnectToString(std::string order,User& user);
    vector<string>  SubscribeToString(std::string msg,User& user);
    vector<string>  unSubscribeToString(std::string msg,User& user);
    vector<string>  logOutToString(std::string msg,User& user);
    vector<string>  reportToString(std::string msg,User& user);
    void toUser(std::string msg,User& user);
    void toUserConnect(User& user,std::string username, std::string passcode);
    void toUserSubscribe(User& user,std::string topic);
    bool translateFrame(std::string msg,User& user);
};