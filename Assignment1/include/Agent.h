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
    //Copy constructor
    Agent(const Agent & other);
    //Copy assignment opearator
    Agent &operator=(const Agent &other);
    //Destructor
    virtual ~Agent();
    //Move Constructor
    Agent(Agent && other) ;
    //Assignment Operator
    Agent & operator=(Agent && other);
    //-------------------------------------------------------------
    //GET
    int getPartyId() const;
    int getId() const;
    int getColId(); 
    SelectionPolicy * getSelectionPolicy();
    //set
    void step(Simulation &);
    void setCoalition(int col);
    void setPartyId(int index) ;
    void setId(int index) ;

    std::pair<int,int> choose(vector<Party>parties,vector <int> aviable,vector<int>connections);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int  coal;
};
