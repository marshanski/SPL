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
#include <iostream>
#include <fstream>

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
    if(parametrs[0] == "login" )
        return ConnectToString(msg,user);

    if(!user.getIsConnected())
    {
        cout <<"--The user isn't log in--" << endl;
        return returnNoMessage(messages);

    }
    if(parametrs[0] =="join" && parametrs.size()==2)
        return SubscribeToString(msg,user);

    if(parametrs[0] =="exit"&& parametrs.size()==2)
        return unSubscribeToString(msg,user);
        
    if(parametrs[0] =="logout"&& parametrs.size()==1)
        return logOutToString(msg,user);

    if(parametrs[0] =="report"&&parametrs.size()==2)
        return reportToString(msg,user);

    if(parametrs[0] =="summary"&&parametrs.size()==4)
    {
        summeryTostring(msg,user);
        return returnNoMessage(messages);
    }

    cout << "Unrecognized order, try again" << endl;
    return returnNoMessage(messages);
}

vector<string>  Frame:: ConnectToString(std::string msg,User& user)
{
    vector<string> messages,parametrs    = split(msg,' ');
    string ip,port;
    ip   = split(parametrs[1],':')[0];
    port = split(parametrs[1],':')[1];
    if(parametrs.size() > 4)
    {
        cout << "Unrecognized order, try again" << endl;
        return returnNoMessage(messages);
    }
    if(split(parametrs[1],':')[0] != "127.0.0.1")
    {
        cout <<"404 NOT FOUND DESTINATION" << endl;
        return returnNoMessage(messages);
    }
    if(split(parametrs[1],':')[1] != "7777")
    {
        cout <<"UNVILED PORT" << endl;
        return returnNoMessage(messages);
    }
    
    //cheking the user isn't login
    if(user.getIsConnected())
    {
        cout << user.getUsername() + " is already loged in"<<endl;
        return returnNoMessage(messages);
    }

    //update the user according to the user name and the passcode, but still don't activate him
    toUserConnect(user,parametrs [2],parametrs [3]);

    //create the frame string
    string str ="CONNECT\n", host = "stomp.cs.bgu.ac.il",version="1.2";
    str +="host:"          + host           + "\n";
    str +="accept-version:"+ version        + "\n";
    str +="login:"         + parametrs [2]  + "\n";
    str +="passcode:"      + parametrs [3]  + "\n";
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
        cout << user.getUsername() + " is already subscribe to " + parametrs[1] <<endl;
        return returnNoMessage(messages);

    }
    if(user.inWaitSubList(parametrs[1]))
    {
        cout << user.getUsername() +" is already send a message to join that topic wait for the answer" << endl;
        return returnNoMessage(messages);

    }

    //create the frame string
    string str = "SUBSCRIBE\n";
    str +="destination:/"   + parametrs[1]                      + "\n";
    str +="id:"             + std::to_string(user.getCount())   + "\n";
    str +="receipt:"        + std::to_string(user.getCount())   + "\n";
    messages.push_back(str);

    //update the user 
    user.addToSubWaiting(parametrs[1]);
    return messages;
    //

}
vector<string>  Frame:: unSubscribeToString(std::string msg,User& user)
{
    std::vector<string> messages;
    vector<string> parametrs    = split(msg,' ');
    if(!user.haveTopic(parametrs[1]))
    {
        cout << user.getUsername() + " didn't subscribe to " + parametrs[1] <<endl;
        return returnNoMessage(messages);
    }
    if(user.inWaitUnSubList(parametrs[1]))
    {
        cout <<user.getUsername() + " is already send a message to exit that topic wait for the answer" << endl;
        return returnNoMessage(messages);
    }

    string str = "UNSUBSCRIBE\n";
    str +="id:"           + std::to_string(user.getReceiptId(parametrs[1]))+ "\n";
    str +="receipt:"      + std::to_string(user.getReceiptId(parametrs[1]))+ "\n";
    messages.push_back(str);
    user.addToUnSubWaiting(parametrs[1]);
    return messages;
}

vector<string>  Frame:: logOutToString(std::string msg,User& user)
{
    std::vector<string> messages;
    vector<string> parametrs    = split(msg,' ');
    string str = "DISCONNECT\n",recipt="73";
    str +="receipt:"      + recipt       + "\n";
    messages.push_back(str);
    return messages;
}

vector<string>  Frame:: reportToString(std::string msg,User& user)
{
    vector<string> parametrs    = split(msg,' ');
    std::vector<string> messages;
    std::string topic,team_a_name ,team_b_name,end = "\0",username = "meni",HALFTIME = "true";
    std::vector<Event> events;

    std::ifstream file(parametrs[1]);
    if (!file.good())
    {
        cout <<"That file doesn't exsist try another one"<<endl;
        return returnNoMessage(messages);
    }

    names_and_events NAE = parseEventsFile(parametrs[1]);

    if(NAE.team_a_name == "ERROR IN FILE")
        return returnNoMessage(messages);

    events = NAE.events;
    topic  = NAE.team_a_name + "_" + NAE.team_b_name;
    if(!user.haveTopic(topic))
    {
        cout << user.getUsername() + " didn't subscribe to that topic" << endl;
        return returnNoMessage(messages);
    }
    std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {return a.get_time() < b.get_time();});
    for(const Event& event: events)
    {
        string str ="SEND\n";
        str+= "destination:/"   + topic            + "\n"+"\n"; 
        str+= "user:"          + username          +"\n";
        str+= "team a:"         + NAE.team_a_name  +"\n";
        str+= "team b:"         + NAE.team_b_name  +"\n";
        str+= "event name:"    + event.get_name()  +"\n";

        str+= "time:"          + std::to_string(event.get_time()) + "\n";
        str+= "general game updates:\n";

        for (const auto& update :event.get_game_updates())
        {
            str+=update.first +":" + update.second + "\n";
            
        }
        str+="team a updates:\n" ;
        for (const auto& update :event.get_team_a_updates())
        {
            str+=update.first +":" + update.second + "\n";
        }
        
        str+="team b updates:\n";
        for (const auto& update :event.get_team_b_updates())
        {
            str+=update.first +":" + update.second + "\n";
        }

        str+="description:\n";
        str+=event.get_discription()+"\n";
        messages.push_back(str);

    }
    
    return messages;

}

void Frame:: summeryTostring(std::string msg,User& user)
{
    vector<string> parametrs    = split(msg,' ');
    string topic =parametrs[1] ,username=parametrs[2],file=parametrs[3],summery ="";

    if(!user.haveTopic(parametrs[1]))
    {
        cout << user.getUsername() + " didn't subscribe to " + parametrs[1] <<endl;
        return;
    }
    if(!user.isUserReported(topic,username))
    {
        cout << username + " didn't report to " + topic <<endl;
        return;

    }
    std::vector<Event> events = user.getEventsByUser(topic,username);
    std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {return a.get_time() < b.get_time();});

    summery += events[0].get_team_a_name() + " vs " + events[0].get_team_b_name() +"\n";
    summery += "Game stats:\n";
    summery += "Genral stats:\n";
    for (auto & event : events) 
    {    
        for (const auto& update :event.get_game_updates())
        {
            summery += "    "+ update.first +":" + update.second + "\n";
        }
    }
    summery += "team " + events[0].get_team_a_name()+ " updates:\n" ;
    for (auto & event : events) 
    {    
        for (const auto& update :event.get_team_a_updates())
        {
            summery += "    "+ update.first +":" + update.second + "\n";
        }
    }
    summery += "team " + events[0].get_team_b_name()+ " updates:\n" ;
    for (auto & event : events) 
    {    
        for (const auto& update :event.get_team_b_updates())
        {
            summery += "    "+ update.first +":" + update.second + "\n";
        }
    }
    summery += "Game event reports:\n" ;
    for (auto & event : events) 
    {
        summery += std::to_string(event.get_time()) +" - "+event.get_name() +"\n\n";
        summery += event.get_discription() +"\n\n";
        
    }
    std:: ofstream MyFile(file);
    MyFile << summery;
    MyFile.close();

}


void Frame:: toUserConnect(User& user,std::string username, std::string passcode)
{
    user.setUsername(username);
    user.setPassCode(passcode);
   
}
void Frame:: toUserSubscribe(User& user,int index)
{
    user.addTopic(index);
   
}

vector<string> Frame:: returnNoMessage(vector<string>messages)
{
    messages.push_back("NO MESSAGE");
    return messages;
}

bool Frame:: translateFrame(string msg,User& user)
{

    vector<string> parametrs    = split(msg,'\n');
    if (parametrs[0]=="CONNECTED")
    {
        if(!user.getIsConnected())
        {
            cout << "---" + user.getUsername() + " is Connected To The System" +"---" << endl;
            user.activateUser(parametrs[1],parametrs[2]);
        }
        else
        {
            cout << user.getUsername() + " is already Connected To The System" << endl;
        }
    }
    if (parametrs[0]=="SUBSCRIBED")
    {
        int index      = std::stoi(split(parametrs[1],':')[1]);
        //int index      = std::stoi(split(parametrs[2],':')[1]);
        string topic   = user.addTopic(index);
        cout <<"---"+ user.getUsername() + " is Subscribed: " + topic+"---" << endl;  
    }
    if (parametrs[0]=="UNSUBSCRIBED")
    {
        int index      = std::stoi(split(parametrs[1],':')[1]);
        //int index      = std::stoi(split(parametrs[2],':')[1]);
        string topic   = user.removeTopic(index);
        cout << "---" +user.getUsername() + " is Unsubscribed: " + topic + "---" << endl;
    }
    if (parametrs[0]=="DISCONNECTED")
    {
        cout << "---" + user.getUsername()+ " Disconected from the system. Thank you and have a good day" + "---"<< endl;
        return false;
    }

    if(parametrs[0]=="SEND")
    {
        //cout << "---------------------------------------------------" << endl;
        //cout << msg<< endl;
        //cout << "---------------------------------------------------" << endl;

        string teamA,teamB,topic,username,eventName,description;
        int time;
        topic     = split(parametrs[1],'/')[1] ;
        username  = split(parametrs[3],':')[1] ;
        teamA     = split(parametrs[4],':')[1] ;
        teamB     = split(parametrs[5],':')[1] ;
        eventName = split(parametrs[6],':')[1] ;
        
        time      = std::stoi(split(parametrs[7],':')[1]);
        std::map<std::string, std::string> game_updates,a_updates,b_updates;
        int i= 9;
        while (parametrs[i]!="team a updates:")
        {
            vector<string> update = split(parametrs[i],':');
            game_updates.insert(std::pair<string, string>(update[0],update[1]));
            
            i++;
        }
        i++;
        while (parametrs[i]!="team b updates:")
        {
            vector<string> update = split(parametrs[i],':');
            a_updates.insert(std::pair<string, string>(update[0],update[1]));
            
            i++;
        }
        i++;
        while (parametrs[i]!="description:")
        {
            vector<string> update = split(parametrs[i],':');
            b_updates.insert(std::pair<string, string>(update[0],update[1]));
            i++;
        }
        i++;
        description = parametrs[i];
        Event event = Event(teamA,teamB,eventName,time,game_updates,a_updates,b_updates,description);
        user.addEvent(topic,username,event);
    }
    if (parametrs[0]=="ERROR")
    {
        if(parametrs[1] == "USERNAME")
            cout << parametrs[2] + " is already taken" << endl;
        if(parametrs[1] == "PASSCODE")
            cout << "UnMatch Passowrd" << endl;
        else
        {
            cout << "Eror was occued the client will be disconnected" << endl;
            return false;
        }
    }

    return true;
}




