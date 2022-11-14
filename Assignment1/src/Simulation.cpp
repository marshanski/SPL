/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :
****************************************/
//----------INCLUDE----------
#include "Party.h"
#include "Coalition.h"
#include "Simulation.h"
#include <vector>
#include <iostream>
//---------------------------
//----------USING----------
using std::vector;
using std::cout;

//---------------------------



Simulation::Simulation(Graph graph, vector<Agent> agents): mGraph(graph), mAgents(agents) , iter (0), joined(0)
{
    //mGraph           = Graph(graph);
    //mAgents          = agents;
    //iter             = 0;
    
    //joined           = 0;
    

    // You can change the implementation of the constructor, but not the signature!
}

void Simulation::raz()
{
    //cout << mGraph.getParties()[0].getMandates();
    Coalition c = Coalition(mGraph.getParties(), &mAgents[1]);
    cout << c.getMandates();
    return;
}


void Simulation::step()
{
    return ;
    //step of all the parties in the collecting offers
    //step of all the agents
    // TODO: implement this method
}

bool Simulation::shouldTerminate() const
{
    // TODO implement this method
    return true;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return vector<vector<int>>();
}
