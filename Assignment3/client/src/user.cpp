#include "../include/user.h"
#include "../include/event.h"
#include "../include/json.hpp"
#include <string>
#include <bits/stdc++.h>
#include <cstdio>
#include <sstream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

User::User():username(""),passcode("RAZ"),isConnetd(true) ,topicToindex(),eventsInTopic(),count(0)
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
string User:: getPassCode()
{
    return passcode;
}
bool User:: getIsConnected()
{
    return isConnetd;
}
int User:: getCount()
{
    return count;
}

void User:: addTopic(string gamename)
{
    topicToindex.insert(std::pair<string, int>(gamename,count));
    count++;
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
