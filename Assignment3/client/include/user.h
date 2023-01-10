#pragma once
#include "../include/event.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <functional>
using std::string;
using std::vector;

class User
{
private:
    string username;
    string passcode;
    bool isConnetd;
    std::map<std::string, int> topicToindex;
    std::map<std::string, std::vector<Event>> eventsInTopic;
    int count;

    
public:
    User();
    virtual ~User();
    void setUsername(string name);
    void setPassCode(string code);
    string getPassCode();
    bool getIsConnected();
    int getCount();
    void addTopic(string gamename);
    std::map<std::string, int> getTopicToindex();
    bool haveTopic(string topic);
    void deleteTopic(string topic);

};