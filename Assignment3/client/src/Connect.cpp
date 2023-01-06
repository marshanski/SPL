#include "../include/Connect.h"
#include "../include/json.hpp"
#include <string>
#include <bits/stdc++.h>
#include <cstdio>
#include <sstream>
#include <vector>

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
    return "bye";

}

string Frame:: ConnectToString(std::string msg)
{
    vector<string> parametrs    = split(msg,' ');
    vector<string>hostAndPort   = split(parametrs [1],':');
    string str = "";
    string command = "Connect", end = "\0" ;
    str +="Command: "  + command  + "\n";
    str +="Host: "     + hostAndPort[0] + "\n";
    str +="Port: "     + hostAndPort[1] + "\n";
    str +="Username: " + parametrs [2]  + "\n";
    str +="Password: " + parametrs [3]  + "\n";
    return str;
}

string Frame:: SubscribeToString(std::string msg)
{
    vector<string> parametrs    = split(msg,' ');
    string str = "",command = "Subscribe", end = "\0",id = "17",recipt="73";
    str +="Command: "     + command      + "\n";
    str +="destination:/ " + parametrs[1] + "\n";
    str +="id:"           + id           + "\n";
    str +="recipt: "      + recipt       + "\n";
    return str;

}
string Frame:: unSubscribeToString(std::string msg)
{
    vector<string> parametrs    = split(msg,' ');
    string str = "",command = "UNSUBSCRIBE", end = "\0",id = "17",recipt="73";
    str +="Command: "     + command      + "\n";
    str +="id:"           + id           + "\n";
    str +="recipt: "      + recipt       + "\n";
    return str;

}


