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
    std::map<std::string, std::map<std::string, std::vector<Event>>> eventsByTopic;
    std::map<int,string> SubscribeWaitingList;
    std::map<int,string> UnSubscribeWaitingList;
    std::map<int,string> indexToTopic;
    int count;

    
public:
    User();
    virtual ~User();
    void setUsername(string name);
    void setPassCode(string code);
    string getPassCode();
    bool getIsConnected();
    int getCount();
    void addTopic(int index);
    std::map<std::string, int> getTopicToindex();
    bool haveTopic(string topic);
    void deleteTopic(string topic);
    void activateUser();
    string getUsername();
    void addEvent(string topic,string user, Event& event);
    int  getReciptId(string topic);
    std::vector<Event> getEventsByUser(string topic,string username);
    void addToSubWaiting(string gamename);
    void addToUnSubWaiting(string gamename);
    int getIndexByTopic(string gamename);
    bool User:: inWaitSubList(string topic);
    bool User:: inWaitUnSubList(string topic);

};