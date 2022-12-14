/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :Simulation.h
****************************************/
//----------INCLUDE----------
#pragma once
#include <vector>
#include "Graph.h"
#include "Agent.h"
#include "Coalition.h"
//---------------------------
//----------USING----------
using std::string;
using std::vector;
//---------------------------

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);
    //GET
    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions()const;
    Agent& getAgent(int id) ;
    int  getIter() ;
    int getNumberOfAgents();
    vector<int> * getConnectionsOfParty(int party);
    //
    void step();
    void initCoalition();
    void stepByParties();
    bool shouldTerminate() const;
    void stepByAgents();
    void addAgent(int mAgentId,int mPartyId,Agent agent,int  coal);
    void addPartyToCoalition(Party * party, Agent * agent);


private:
    Graph mGraph;
    vector <Agent> mAgents;
    vector <Party> parties;
    vector <Coalition> coalitions;
    vector<vector<int>> copyMatrix;
    int iter,joined,numberOfPartyies;
    bool hasCoalition;
    vector<vector<int>> colByNum;
    vector<vector<int>> offers;
};