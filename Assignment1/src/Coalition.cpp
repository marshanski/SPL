/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Coalitaion.cpp
****************************************/
//----------INCLUDE----------
#pragma once
#include <vector>
#include "Coalition.h"
#include <iostream>
#include <bits/stdc++.h>
//---------------------------

//----------USING----------
using std::vector;
using std::cout;
using std::endl;
//---------------------------


void Coalition::setCoalition(vector<Party> parties, Agent * agent,vector<int> aviable,int id)
{

    partiesInCoalition.push_back(agent->getPartyId());
    agentInCoalition.push_back(agent->getId());
    mandates = parties[agent->getPartyId()].getMandates(); 
    cId      = id;
    for (unsigned i = 0; i < aviable.size(); i++){aviableToOffer.push_back(aviable[i]);}  
}

void Coalition::addPartyToCoalition(Party * party, Agent * agent)
{
    partiesInCoalition.push_back(party->getId());
    mandates += party->getMandates();
    agentInCoalition.push_back(agent->getId());
}

vector<int> Coalition::getaviableToOffer()
{
    return aviableToOffer;
}
void Coalition::deleteFromCoalition(int partyId)
{
    auto iter = std::remove(aviableToOffer.begin(),aviableToOffer.end(),aviableToOffer.at(partyId));
    aviableToOffer.erase(iter,aviableToOffer.end());
}

int Coalition::getMandates() const
{
    return mandates;
}
int Coalition::getId() 
{
    return cId;
}


vector<int> Coalition::getParties()
{
    vector<int> v;
    for (unsigned i = 0; i < partiesInCoalition.size(); i++)
    {
        v.push_back(partiesInCoalition.at(i));
    }
    
    return v;
}

void Coalition::printAviable() 
{
    for (unsigned i = 0; i < aviableToOffer.size(); i++)
    {
        cout << aviableToOffer.at(i) << endl;
    }

    
}

vector<int> Coalition:: getAviable()
{
    return aviableToOffer;
}

/*Coalition Coalition::clone()
{
    //return Coalition c;
}*/





