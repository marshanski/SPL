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
    void step();
    void initCoalition();
    void stepByParties();
    bool shouldTerminate() const;
    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
    int  getIter() ;
    void stepByAgents();


private:
    Graph mGraph;
    vector <Agent> mAgents;
    vector <Party *> collectingOffers;
    vector <Coalition> coalitions;
    vector<vector<int>> copyMatrix;
    int iter,joined,numberOfPartyies;
    bool hasCoalition;
};