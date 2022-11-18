/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Agent.h
****************************************/
//----------INCLUDE----------
#pragma once
#include <vector>
#include "SelectionPolicy.h"
#include <vector>
#include <utility>
//---------------------------

//----------CLASS----------
class SelectionPolicy;
class Coalition;
//---------------------------


class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy,Coalition *  coal,vector<int> * connections);
    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void setCoalition(Coalition * col);
    Coalition * getCoalition(); 
    void setConnections(vector<int> * vec) ;
    vector<int> * getConnections(); 
    std::pair<int,int> choose(vector<Party *> aviable ,vector<int> * connections) ;
    SelectionPolicy * getSelectionPolicy();
    void deleteFromAgent(int partyToOffer);




private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    Coalition *  coal;
    vector<int> * connections;
};
