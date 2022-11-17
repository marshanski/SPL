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


void Coalition::setCoalition(vector<Party> parties, Agent * agent,vector<Party *> aviable)
{

    partiesInCoalition.push_back(& parties[agent->getPartyId()]);
    mandates = parties[agent->getPartyId()].getMandates();
    agentInCoalition.push_back(agent);
    for (unsigned i = 0; i < aviable.size(); i++){aviableToOffer.push_back(aviable[i]);}  

}

int Coalition::getMandates() const
{
    return mandates;
}


void Coalition::printAviable() 
{
    for (unsigned i = 0; i < aviableToOffer.size(); i++)
    {
        cout << aviableToOffer.at(i) << endl;
    }

    
}

vector<Party *> Coalition:: getAviable()
{
    return aviableToOffer;
}

void Coalition::getParties()
{
    cout << "-------------------------------------------" << endl;
    cout << partiesInCoalition.size() << endl;
    
    cout << aviableToOffer.size() << endl;
    cout << mandates  << endl;
}



