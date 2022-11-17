/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :
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

    void step();
    void initCoalition();
    bool shouldTerminate() const;
    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
    void stepByParties();
    int  getIter() ;

private:
    Graph mGraph;
    vector <Agent> mAgents;
    vector <Party *> collectingOffers;
    vector <Coalition> coalitions;
    int iter,joined,numberOfPartyies;
    bool hasCoalition;
    vector<vector<int>> copyMatrix;

    
};