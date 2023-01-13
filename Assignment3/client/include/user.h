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
    std::map<string, std::map<std::string, std::vector<Event>>> eventsByTopic;
    std::map<int,std::string> SubWaitList;
    std::map<int,std::string> myMap;
    std::map<int,std::string> UnSubscribeWaitingList;
    std::map<int,std::string> indexToTopic;
    int count;

    
public:
    User();
    virtual ~User();
    void setUsername(string name);
    void setPassCode(string code);
    string getPassCode();
    bool getIsConnected();
    int getCount();
    std::string  addTopic(int index);
    std::map<std::string, int> getTopicToindex();
    bool haveTopic(string topic);
    void deleteTopic(string topic);
    void activateUser(string user,string code);
    string getUsername();
    void addEvent(string topic,string user, Event& event);
    int  getReceiptId(string topic);
    std::vector<Event> getEventsByUser(string topic,string username);
    void addToSubWaiting(string gamename);
    void addToUnSubWaiting(string gamename);
    int getIndexByTopic(string gamename);
    bool inWaitSubList(string topic);
    bool inWaitUnSubList(string topic);
    std::string removeTopic(int index);
    bool isUserReported(string topic,string username);

};