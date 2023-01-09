#include "../include/Connect.h"
#include "../include/event.h"
#include "../include/user.h"
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


std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

Frame::Frame()
{
    
}


Frame::~Frame()
{
}

vector<string>  Frame:: toString(std::string msg, User& user)
{
    vector<string> parametrs    = split(msg,' ');
    std::vector<string> messages;
    if(parametrs[0] == "login")
        return ConnectToString(msg,User& user);
    if(parametrs[0] =="join")
        return SubscribeToString(msg,User& user);
    if(parametrs[0] =="exit")
        return unSubscribeToString(msg,User& user);
    if(parametrs[0] =="logout")
        return logOutToString(msg,User& user);
    if(parametrs[0] =="report")
        return reportToString(msg,User& user);

    messages.push_back("bye");
    return messages;
}

vector<string>  Frame:: ConnectToString(std::string msg,User& user)
{
    std::vector<string> messages;
    if(user.getIsConnected())
    {
        cout <<"The user is already log in";
        messages.push_back("NO MESSAGE");
        return messages;

    }
    vector<string> parametrs    = split(msg,' ');
    //vector<string>hostAndPort   = split(parametrs [1],':');
    string str = "";
    string command = "CONNECT", host = "stomp.cs.bgu.ac.il",version="1.2",end = "\0" ;
    str +=command        + "\n";
    str +="host: "          + host           + "\n";
    str +="accept-version: "+ version        + "\n";
    str +="login: "         + parametrs [2]  + "\n";
    str +="passcode: "      + parametrs [3]  + "\n";
    str += "\n";
    messages.push_back(str);
    return messages;
}

vector<string>  Frame:: SubscribeToString(std::string msg,User& user)
{
    if(!user.getIsConnected())
    {
        cout <<"The user is already log in";
        messages.push_back("NO MESSAGE");
        return messages;

    }
    std::vector<string> messages;
    vector<string> parametrs    = split(msg,' ');
    string str = "",command = "SUBSCRIBE", end = "\0",id = "17",recipt="73";
    str +="command: "     + command      + "\n";
    str +="destination:/ " + parametrs[1] + "\n";
    str +="id:"           + id           + "\n";
    str +="recipt: "      + recipt       + "\n";
    messages.push_back(str);
    return messages;

}
vector<string>  Frame:: unSubscribeToString(std::string msg,User& user)
{
    std::vector<string> messages;
    vector<string> parametrs    = split(msg,' ');
    string str = "",command = "UNSUBSCRIBE", end = "\0",id = "17",recipt="73";
    str +="command: "     + command      + "\n";
    str +="id:"           + id           + "\n";
    str +="recipt: "      + recipt       + "\n";
    messages.push_back(str);
    return messages;
}

vector<string>  Frame:: logOutToString(std::string msg,User& user)
{
    std::vector<string> messages;
    vector<string> parametrs    = split(msg,' ');
    string str = "",command = "DISCONNECT", end = "\0",recipt="73";
    str +="command: "     + command      + "\n";
    str +="recipt: "      + recipt       + "\n";
    messages.push_back(str);
    
    return messages;
}

vector<string>  Frame:: reportToString(std::string msg,User& user)
{
    vector<string> parametrs    = split(msg,' ');
    std::string team_a_name ,team_b_name,end = "\0",username = "meni",HALFTIME = "true";
    std::vector<Event> events;
    std::vector<string> messages;
    names_and_events NAE = parseEventsFile("events1.json");
    events = NAE.events;
    std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {return a.get_time() < b.get_time();});
    for(const Event& event: events)
    {
        string str ="";
        str+= "command: send \n";
        str+= "destination: "  + NAE.team_a_name + "_" + NAE.team_b_name + "\n"+"\n"; 
        str+= "user: "         + username +"\n";
        str+= "event name: "    + event.get_name() + "\n";

        str+="time: "          + std::to_string(event.get_time()) + "\n";
        str+="general game updates: \n";

        for (const auto& update :event.get_game_updates())
        {
            str+="    "+ update.first +": " + update.second + "\n";
            
        }
        str+="team a updates:  \n" ;
        for (const auto& update :event.get_team_a_updates())
        {
            str+="    "+ update.first +": " + update.second + "\n";
        }
        
        str+="team b updates:  \n";
        for (const auto& update :event.get_team_b_updates())
        {
            str+="    "+ update.first +": " + update.second + "\n";
        }
        str+="description:  \n";
        str+=event.get_discription()+"\n";
        cout << str << endl;
        messages.push_back(str);

    }
    
    return messages;

}

void Frame:: toUser(std::string msg, User& user)
{
    vector<string> parametrs    = split(msg,' ');
    std::vector<string> messages;
    cout <<"wiwi" << endl; 
    if(parametrs[0] == "login")
        toUserConnect(msg,user);
    /*if(parametrs[0] =="join")
        return SubscribeToString(msg);
    if(parametrs[0] =="exit")
        return unSubscribeToString(msg);
    if(parametrs[0] =="logout")
        return logOutToString(msg);
    if(parametrs[0] =="report")
        return reportToString(msg);

    messages.push_back("bye");
    return messages;*/
}


void Frame:: toUserConnect(std::string msg, User& user)
{
    vector<string> parametrs    = split(msg,' ');
    user.setUsername(parametrs [2]);
    user.setPassCode(parametrs [3]);
   
}




