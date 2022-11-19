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
    //--------------------Rule of 5-----------------------------------------
    //Constructor
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy,Coalition *coal,vector<int> * connections);
    //Copy constructor
    Agent(const Agent & other);
    //
    Agent &operator=(const Agent &other);
    virtual ~Agent();
    Agent(Agent && other) ;
    Agent & operator=(Agent && other) ;
    //-------------------------------------------------------------
    //GET
    int getPartyId() const;
    int getId() const;
    Coalition * getCoalition(); 
    SelectionPolicy * getSelectionPolicy();
    vector<int> * getConnections(); 
    //set
    void step(Simulation &);
    void setCoalition(Coalition * col);
    void setConnections(vector<int> * vec) ;
    std::pair<int,int> choose(vector<Party *> aviable ,vector<int> * connections) ;
    void deleteFromAgent(int partyToOffer);




private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    Coalition *  coal;
    vector<int> * connections;
};
