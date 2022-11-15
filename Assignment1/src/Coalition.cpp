/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Coalitaion.cpp
****************************************/
//----------INCLUDE----------
#pragma once
#include <vector>
#include "Party.h"
#include "Agent.h"
#include "Coalition.h"
#include <iostream>
//---------------------------

//----------USING----------
using std::vector;
using std::cout;
//---------------------------

Coalition::Coalition(vector<Party> parties, Agent * agent)
{
    partiesInCoalition.push_back(& parties[agent->getPartyId()]);
    mandates = parties[agent->getPartyId()].getMandates();
    agentInCoalition.push_back(agent);
    //cout << partiesInCoalition[0]->getMandates();

}
int Coalition::getMandates() const
{
    return mandates;
}


