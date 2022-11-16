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
//---------------------------

//----------USING----------
using std::vector;
using std::cout;
using std::endl;
//---------------------------

Coalition::Coalition(vector<Party> parties, Agent * agent)
{
    partiesInCoalition.push_back(& parties[agent->getPartyId()]);
    mandates = parties[agent->getPartyId()].getMandates();
    agentInCoalition.push_back(agent);
}
int Coalition::getMandates() const
{
    return mandates;
}
void Coalition::setAviable(vector<Party *> aviable) 
{
    for (unsigned i = 0; i < aviable.size(); i++)
    {
        aviableToOffer.push_back(aviable[i]);
    }
    
}

void Coalition::printAviable() 
{
    for (unsigned i = 0; i < aviableToOffer.size(); i++)
    {
        cout << aviableToOffer[i] << endl;
    }
    
}

vector<Party *> Coalition:: getAviable()
{
    return aviableToOffer;
}


