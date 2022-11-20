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
    //GET
    vector<int> getAviable();
    int  getMandates() const;
    int getId(); 
    vector<int> getaviableToOffer();
    vector<int> getParties();

    //SET
    void setCoalition(vector<Party> parties, Agent * agent,vector<int> aviable,int id);
    void printAviable();
    void addPartyToCoalition(Party * party, Agent * agent);
    void deleteFromCoalition(int partyId);

    //Coalition clone();
    

private:
    vector<int> partiesInCoalition;
    vector<int> agentInCoalition;
    vector<int> aviableToOffer;
    int mandates;
    int cId;
};
