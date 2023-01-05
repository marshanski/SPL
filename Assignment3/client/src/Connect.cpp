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


Connect::Connect(std::string msg)
{
    vector<string> parametrs    = split(msg,' ');
    vector<string>hostAndPort   = split(parametrs [1],':');
    command = "Connect";
    host    = hostAndPort[0];
    port    = hostAndPort[1];
    username = parametrs [2];
    password = parametrs [3];
}


Connect::~Connect()
{
}

string Connect:: toString()
{
    string str = "";
    str +="Command: "  + command  + "\n";
    str +="Host: "     + host     + "\n";
    str +="Port: "     + port     + "\n";
    str +="Username: " + username + "\n";
    str +="Password: " + password + "\n";
    return str;

}


