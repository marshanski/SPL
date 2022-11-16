/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Coalitaion.h
****************************************/
//----------INCLUDE----------
#pragma once
#include <vector>
#include "Party.h"
#include "Agent.h"
//---------------------------

//----------USING------------
using std::vector;
//---------------------------


class Coalition
{
public:
    Coalition(vector<Party> parties, Agent * agent,vector<Party *> aviable);
    int  getMandates() const;
    void printAviable();
    vector<Party *> getAviable();
    

private:
    vector<Party *> partiesInCoalition;
    vector<Agent *> agentInCoalition;
    vector<Party *> aviableToOffer;
    int mandates;
};
