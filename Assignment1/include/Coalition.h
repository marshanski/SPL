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
    Coalition(vector<Party> parties, Agent * agent);
    int  getMandates() const;
    void setAviable(vector<Party *> aviable );
    void printAviable();
    vector<Party *> getAviable();
    

private:
    vector<Party *> partiesInCoalition;
    vector<Agent *> agentInCoalition;
    vector<Party *> watingForResponse;
    vector<Party *> aviableToOffer;
    int mandates;
};
