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
    Coalition ();
    //GET
    vector<int> getAviable();
    vector<int> getaviableToOffer();
    vector<int> getParties();
    int  getMandates() const;
    int getId(); 

    //SET
    void addPartyToCoalition(Party * party, Agent * agent);
    void deleteFromCoalition(int partyId);
    void setCoalition(vector<Party> parties, Agent * agent,vector<int> aviable,int id);

private:
    vector<int> partiesInCoalition;
    vector<int> agentInCoalition;
    vector<int> aviableToOffer;
    int mandates;
    int cId;
};
