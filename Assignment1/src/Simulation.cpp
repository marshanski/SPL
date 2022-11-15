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
    copyMatrix               = mGraph.getMatrix();
    vector <Party> parties   = mGraph.getParties();
    numberOfPartyies         = parties.size();
    vector <Party * > aviable;
    for (int i = 0; i <numberOfPartyies; i++){aviable.push_back(& parties[i]);}

    for (unsigned int i=0; i<mAgents.size();i++)
    {
        
        coalitions.push_back(Coalition(parties, &mAgents[i]));
        joined++;
        mAgents[i].setCoalition(& coalitions[i]);
        mAgents[i].setConnections(& copyMatrix[mAgents[i].getPartyId()]);
        if (coalitions[i].getMandates() >= 61){hasCoalition = true;}
        auto iter = std::remove(aviable.begin(),aviable.end(),&parties[mAgents[i].getPartyId()]);
        aviable.erase(iter,aviable.end());    
    }
    
    for (unsigned i = 0; i <coalitions.size(); i++){coalitions[i].setAviable(aviable);}
    vector<int> * v = mAgents[0].getConnections();
    //cout << v->at(0) << endl;
    mAgents[0].choose();
    //v,mAgents[0].getCoalition()->getAviable()
    //for (unsigned i = 0; i < v->size(); i++){cout << v->at(i) << endl;}
    //cout << & copyMatrix << endl;W
    //cout << mGraph.getMatrixAdress() << endl;
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
