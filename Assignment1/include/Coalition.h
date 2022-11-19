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
    Coalition(){};
    void setCoalition(vector<Party> parties, Agent * agent,vector<Party *> aviable,int id);
    int  getMandates() const;
    void printAviable();
    vector<Party *> getAviable();
    void addPartyToCoalition(Party * party, Agent * agent);
    int getId(); 
    void deleteFromCoalition(int partyId);
    vector<Party *> getaviableToOffer();
    vector<int> getParties();
    //Coalition clone();
    

private:
    vector<Party *> partiesInCoalition;
    vector<Agent *> agentInCoalition;
    vector<Party *> aviableToOffer;
    int mandates;
    int cId;
};
