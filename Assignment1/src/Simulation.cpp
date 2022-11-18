/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :
****************************************/
//----------INCLUDE----------
#include "Coalition.h"
#include "Simulation.h"
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <Party.h>
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
    parties                  = mGraph.getParties();
    numberOfPartyies         = parties.size();
    vector<Party *> aviable;

    for (unsigned int i=0; i <numberOfPartyies; i++){aviable.push_back(& parties[i]);}
    for (unsigned int i=0; i<mAgents.size();i++)
    {
        auto iter = std::remove(aviable.begin(),aviable.end(),&parties[mAgents[i].getPartyId()]);
        aviable.erase(iter,aviable.end());    
    }

    for (unsigned int i=0; i<mAgents.size();i++)
    {
        Coalition *c = new Coalition();
        c->setCoalition(parties, &mAgents.at(i),aviable,i);
        coalitions.push_back(*c);
        joined++;
        mAgents[i].setCoalition(c);
        mAgents[i].setConnections(& copyMatrix[mAgents[i].getPartyId()]);
        if (coalitions[i].getMandates() >= 61){hasCoalition = true;}
    }
    return;
}

void Simulation::step()
{
    this->stepByParties();
    cout <<"---------------------------------------------" << endl;
    cout <<"iter: " << iter << endl; 
    this->stepByAgents();
    iter++;
    return;
}

void Simulation::stepByAgents()
{
    int partyToOffer;
    for (unsigned int i=0; i < mAgents.size(); i++)
    {
        partyToOffer = mAgents[i].choose(mAgents[i].getCoalition()->getAviable(),mAgents[i].getConnections());
        cout << "Agent "  << i << endl;
        cout << "Choose " << partyToOffer << endl;
        if(partyToOffer != -1)
        {
            parties.at(partyToOffer).choose(&parties.at(mAgents[i].getPartyId()),iter,mAgents[i].getCoalition(),mAgents[i].getSelectionPolicy());
            mGraph.getParty(partyToOffer).setState(State(1));
        }
    }
    int a=0;
    
}

void Simulation::stepByParties()
{
    int bestAgent;
    //vector <Party> parties   = mGraph.getParties();
    for (unsigned int i=0; i <numberOfPartyies; i++)
    {
        if (parties.at(i).getState()== 1 && parties.at(i).getTimer()+3 == iter)
        {
            parties.at(i).step(*this);
            joined++;
            mGraph.getParty(i).setState(State(2));
        }
    }
    
}

int Simulation::getIter() 
{
    return iter;
}


bool Simulation::shouldTerminate() const
{
    if ( hasCoalition || numberOfPartyies == joined){return true;}
    return false;    
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


int Simulation::getNumberOfAgents()
{
    return mAgents.size();
    
}

vector<int> * Simulation::getConnectionsOfParty(int party)
{
    return &copyMatrix[party];

} 

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return vector<vector<int>>();
}

Agent * Simulation::addAgent(int mAgentId,int mPartyId,SelectionPolicy *mSelectionPolicy,Coalition *  coal,vector<int> * connections)
{
    Agent * agent = new Agent(mAgentId,mPartyId,mSelectionPolicy,coal,connections);
    mAgents.push_back(* agent);
    int coalitionId = coal->getId();
    coalitions.at(coalitionId).addPartyToCoalition(&parties.at(mPartyId),agent);
    if (coalitions.at(coalitionId).getMandates()>61)
    {
        hasCoalition = true;
    }
    
    return agent;
}

void Simulation::addPartyToCoalition(Party * party, Agent * agent)
{
    //partiesInCoalition.push_back(party);
    //mandates += party->getMandates();
    //agentInCoalition.push_back(agent);
}