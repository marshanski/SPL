#include "../include/user.h"
#include "../include/event.h"
#include "../include/json.hpp"
#include <string>
#include <bits/stdc++.h>
#include <cstdio>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

User::User():username(""),passcode(""),isConnetd(false) ,topicToindex(),eventsByTopic(),SubWaitList(),myMap(),UnSubscribeWaitingList(),indexToTopic(),count(0)
{

}


User::~User()
{
}

void User:: setUsername(string name)
{
    username = name;
}
void User:: setPassCode(string code)
{
    passcode = code;
}
void User:: activateUser()
{
    isConnetd = true;
}

string User:: getPassCode()
{
    return passcode;
}
string User:: getUsername()
{
    return username;
}
bool User:: getIsConnected()
{
    return isConnetd;
}
int User:: getCount()
{
    return count;
}

string User:: addTopic(int index)
{
    string topic = myMap[index];
    topicToindex.insert(std::pair<std::string, int>(topic,index));
    indexToTopic.insert(std::pair<int, std::string>(index,topic));
    std::map<int,string>::iterator it;
    it = myMap.find(index);
    myMap.erase(it);
    return topic;

}
string User:: removeTopic(int index)
{
    string topic = indexToTopic[index];
    std::map<string,int>::iterator it;
    std::map<int,string>::iterator it2;
    it  = topicToindex.find(indexToTopic[index]);
    it2 = indexToTopic.find(index);
    topicToindex.erase(it);  
    indexToTopic.erase(it2); 
    std::map<int,string>::iterator it3;
    it3 = UnSubscribeWaitingList.find(index);
    UnSubscribeWaitingList.erase(it3);
    return topic;
}

void User:: addToSubWaiting(string gamename)
{
    //SubWaitList.insert(std::make_pair(count, gamename));

    myMap.insert(std::make_pair(count, gamename));
    count++;
}
void User:: addToUnSubWaiting(string gamename)
{
    
    UnSubscribeWaitingList.insert(std::pair<int,std::string>(topicToindex[gamename],gamename));

}
int User:: getIndexByTopic(string gamename)
{
    return topicToindex[gamename];
}

std::map<std::string, int> User:: getTopicToindex()
{
    return topicToindex;
}

bool User:: haveTopic(string topic)
{
    return topicToindex.count(topic);
}

void User:: deleteTopic(string topic)
{
    topicToindex.erase(topic); 
}

void User:: addEvent(string topic,string user, Event& event)
{
    eventsByTopic[topic][user].push_back(event);
}

int User:: getReceiptId(string topic)
{
    return topicToindex[topic];
}

std::vector<Event> User:: getEventsByUser(string topic,string username)
{
    return eventsByTopic[topic][username];
}
bool User:: isUserReported(string topic,string username)
{
    return eventsByTopic[topic].count(username);
}

bool User:: inWaitSubList(string topic)
{
    std::map<int,std::string>::iterator it;
    for (std::map<int,std::string>::iterator it = myMap.begin();it != myMap.end();++it) 
    {
        if (it->second  == topic) 
            return true;
    }
    return false;
}

bool User:: inWaitUnSubList(string topic)
{
    std::map<int,std::string>::iterator it;
    for (std::map<int,std::string>::iterator it = UnSubscribeWaitingList.begin();it != UnSubscribeWaitingList.end();++it) 
    {
        if (it->second  == topic) 
            return true;
    }
    return false;
}