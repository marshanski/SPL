#include "../include/Frame.h"
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
        return ConnectToString(msg,user);

    if(!user.getIsConnected())
    {
        cout <<"The user isn't log in";
        messages.push_back("NO MESSAGE");
        return messages;
    }
    if(parametrs[0] =="join")
        return SubscribeToString(msg,user);

    if(parametrs[0] =="exit")
        return unSubscribeToString(msg,user);
        
    if(parametrs[0] =="logout")
        return logOutToString(msg,user);
    if(parametrs[0] =="report")
        return reportToString(msg,user);

    messages.push_back("bye");
    return messages;
}

vector<string>  Frame:: ConnectToString(std::string msg,User& user)
{
    std::vector<string> messages;
    vector<string> parametrs    = split(msg,' ');
    //cheking the user isn't login
    if(user.getIsConnected())
    {
        cout <<"The user is already log in"<<endl;
        messages.push_back("NO MESSAGE");
        return messages;
    }

    //update the user according to the user name and the passcode, but still don't activate him
    toUserConnect(user,parametrs [2],parametrs [3]);

    //create the frame string
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
    std::vector<string> messages;
    vector<string> parametrs    = split(msg,' ');

    if(user.haveTopic(parametrs[1]))
    {
        cout <<"The user is already sunscribe to that topic"<<endl;
        messages.push_back("NO MESSAGE");
        return messages;
    }

    //create the frame string
    string str = "SUBSCRIBE \n", end = "\0",id = "17",recipt="73";
    str +="destination:/ " + parametrs[1]                      + "\n";
    str +="id:"            + std::to_string(user.getCount())   + "\n";
    str +="recipt: "       + recipt                            + "\n";
    messages.push_back(str);

    //update the user 
    toUserSubscribe(user,parametrs[1]);

    return messages;
    //

}
vector<string>  Frame:: unSubscribeToString(std::string msg,User& user)
{
    std::vector<string> messages;
    vector<string> parametrs    = split(msg,' ');
    if(!user.haveTopic(parametrs[1]))
    {
        cout <<"The user didn't subscribe to that topic"<<endl;
        messages.push_back("NO MESSAGE");
        return messages;
    }

    string str = "",command = "UNSUBSCRIBE", end = "\0",id = "17",recipt="73";
    str +="command: "     + command      + "\n";
    str +="id:"           + id           + "\n";
    str +="recipt: "      + recipt       + "\n";
    messages.push_back(str);
    user.deleteTopic(parametrs[1]);
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
    std::vector<string> messages;
    std::string team_a_name ,team_b_name,end = "\0",username = "meni",HALFTIME = "true";
    std::vector<Event> events;

    if(!user.haveTopic(parametrs[1]))
    {
        cout <<"The user didn't subscribe to that topic"<<endl;
        messages.push_back("NO MESSAGE");
        return messages;
    }

    
    names_and_events NAE = parseEventsFile("events1.json");
    events = NAE.events;
    std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {return a.get_time() < b.get_time();});
    for(const Event& event: events)
    {
        string str ="";
        str+= "SEND \n";
        str+= "destination: "   + NAE.team_a_name + "_" + NAE.team_b_name + "\n"+"\n"; 
        str+= "user: "          + username +"\n";
        str+= "event name: "    + event.get_name() + "\n";

        str+= "time: "          + std::to_string(event.get_time()) + "\n";
        str+= "general game updates: \n";

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



void Frame:: toUserConnect(User& user,std::string username, std::string passcode)
{
    user.setUsername(username);
    user.setPassCode(passcode);
   
}
void Frame:: toUserSubscribe(User& user,std::string topic)
{
    user.addTopic(topic);
   
}

void Frame:: translateFrame(string msg)
{
    
}




