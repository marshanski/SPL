/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Agent.h
****************************************/
//----------INCLUDE----------
#pragma once
#include <vector>
#include "Graph.h"
#include "SelectionPolicy.h"
//---------------------------

//----------CLASS----------
class SelectionPolicy;
class Coalition;
//---------------------------



class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void setCoalition(Coalition * col);
    Coalition * getCoalition(); 
    void setConnections(vector<int> * vec) ;
    vector<int> * getConnections(); 
    void choose(vector<int> * connections,vector<Party *> aviableToOffer) ;


    //SelectionPolicy getSelectionPolicy();

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    Coalition *  coal;
    vector<int> * connections;
};
