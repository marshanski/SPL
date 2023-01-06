#include "../include/Connect.h"
#include "../include/json.hpp"
#include <string>
#include <bits/stdc++.h>
#include <cstdio>
#include <sstream>
#include <vector>

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
    str += "\n" +end;
    return str;

}


