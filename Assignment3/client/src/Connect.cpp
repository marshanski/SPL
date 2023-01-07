#include "../include/Connect.h"
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

string Frame:: toString(std::string msg)
{
    vector<string> parametrs    = split(msg,' ');
    if(parametrs[0] == "login")
        return ConnectToString(msg);
    if(parametrs[0] =="join")
        return SubscribeToString(msg);
    if(parametrs[0] =="exit")
        return unSubscribeToString(msg);
    if(parametrs[0] =="logout")
        return logOutToString(msg);
    if(parametrs[0] =="report")
        return reportToString(msg);
    return "bye";

}

string Frame:: ConnectToString(std::string msg)
{
    vector<string> parametrs    = split(msg,' ');
    //vector<string>hostAndPort   = split(parametrs [1],':');
    string str = "";
    string command = "Connect", host = "stomp.cs.bgu.ac.il",version="1.2",end = "\0" ;
    str +="command: "       + command        + "\n";
    str +="host: "          + host           + "\n";
    str +="accept-version: "+ version        + "\n";
    str +="login: "         + parametrs [2]  + "\n";
    str +="passcode: "      + parametrs [3]  + "\n";
    return str;
}

string Frame:: SubscribeToString(std::string msg)
{
    vector<string> parametrs    = split(msg,' ');
    string str = "",command = "SUBSCRIBE", end = "\0",id = "17",recipt="73";
    str +="command: "     + command      + "\n";
    str +="destination:/ " + parametrs[1] + "\n";
    str +="id:"           + id           + "\n";
    str +="recipt: "      + recipt       + "\n";
    return str;

}
string Frame:: unSubscribeToString(std::string msg)
{
    vector<string> parametrs    = split(msg,' ');
    string str = "",command = "UNSUBSCRIBE", end = "\0",id = "17",recipt="73";
    str +="command: "     + command      + "\n";
    str +="id:"           + id           + "\n";
    str +="recipt: "      + recipt       + "\n";
    return str;
}

string Frame:: logOutToString(std::string msg)
{
    vector<string> parametrs    = split(msg,' ');
    string str = "",command = "DISCONNECT", end = "\0",recipt="73";
    str +="command: "     + command      + "\n";
    str +="recipt: "      + recipt       + "\n";
    return str;
}

string Frame:: reportToString(std::string msg)
{
    vector<string> parametrs    = split(msg,' ');
    cout << parametrs[1] ;
    std::string team_a_name ,team_b_name,str="",end = "\0";
    std::vector<Event> events;
    std::vector<string> messages;
    names_and_events NAE = parseEventsFile(parametrs[1]);
    events = NAE.events;
    std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {return a.get_time() < b.get_time();});
    for(const Event& event: events)
    {
        str ="";
        str+= "command: send " + '\n';
        str+= "destination:/"  + NAE.team_a_name + "_" + NAE.team_b_name + "\n"+"\n"; 
        str+= "user: "         + 'meni' +'\n';
        str+="event time: "    + event.get_name() + "\n";
        str+="time: "          + std::to_string(event.get_time()) + "\n";
        str+="team a updates:  " +'\n';
        for (const auto& update :event.get_team_a_updates())
        {
            str+="    "+ update.first +": " + update.second + "\n";
        }
        str+="team b updates:  " +'\n';
        for (const auto& update :event.get_team_b_updates())
        {
            str+="    "+ update.first +": " + update.second + "\n";
        }
        str+="description:  " +'\n';
        str+=event.get_discription()+"\n";
        str+=end;
        messages.push_back(str);

    }

}




