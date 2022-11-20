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
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy,int coal);
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
    int getColId(); 
    SelectionPolicy * getSelectionPolicy();
    //set
    void step(Simulation &);
    void setCoalition(int col);
    std::pair<int,int> choose(vector<Party>parties,vector <int> aviable,vector<int>connections);
    void deleteFromAgent(int partyToOffer);


private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int  coal;
};
