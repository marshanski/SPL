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
#include<bits/stdc++.h>
#include<algorithm>
//---------------------------
//----------USING----------
using std::vector;
using std::cout;
using std::endl;
//---------------------------



Simulation::Simulation(Graph graph, vector<Agent> agents): mGraph(graph), mAgents(agents) , iter (0), joined(0),numberOfPartyies(0),hasCoalition(false)
{

}

void Simulation::initCoalition()
{
    vector <Party> parties   = mGraph.getParties();
    numberOfPartyies         = parties.size();
    vector <Party * > aviable;
    for (int i = 0; i <numberOfPartyies; i++)
    {
        aviable.push_back(& parties[i]);
        cout << &parties[i] << endl;
    }
    for (unsigned int i=0; i<mAgents.size();i++)
    {
        Coalition c = Coalition(parties, &mAgents[i]);
        coalitions.push_back(c);
        joined++;
        if (c.getMandates() >= 61){hasCoalition = true;}

        auto iter = std::remove(aviable.begin(),aviable.end(),&parties[mAgents[i].getPartyId()]);
        aviable.erase(iter,aviable.end());    
    }
    cout << aviable.size() << endl;
    
    for (unsigned i = 0; i <aviable.size(); i++)
    {
        cout << aviable[i]->getMandates() << endl;
        
    }
    return;
}


void Simulation::step()
{
    //
    return;
  
}

bool Simulation::shouldTerminate() const
{
    if ( hasCoalition || numberOfPartyies == joined){return true;}
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
