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
    for (unsigned i = 0; i < agents.size(); i++)
    {
        Coalition c;
        vector <int> a;
        coalitions.push_back(c);
        colByNum.push_back(a);
    }
    
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
        coalitions.at(i).setCoalition(parties, &mAgents.at(i),aviable,i);
        colByNum.at(i).push_back(mAgents[i].getPartyId());
        joined++;
        mAgents[i].setCoalition(& coalitions.at(i));
        mAgents[i].setConnections(& copyMatrix[mAgents[i].getPartyId()]);
        if (coalitions[i].getMandates() >= 61){hasCoalition = true;}
    }
    return;
}

void Simulation::step()
{
    cout << "iter : " << iter << endl;
    this->stepByParties();
    this->stepByAgents();
    iter++;
    return;
}

void Simulation::stepByAgents()
{
    int partyToOffer,partyId;
    std::pair<int,int> p;
    for (unsigned int i=0; i < mAgents.size(); i++)
    {
        p = mAgents[i].choose(coalitions.at(mAgents[i].getCoalition()->getId()).getAviable(),mAgents[i].getConnections());
        partyToOffer = p.first;
        partyId      = p.second;
        cout << "Agent : " << i << endl;
        cout << "choose:" << partyToOffer << endl;
        if(partyToOffer != -1)
        {
            parties.at(partyToOffer).choose(&parties.at(mAgents[i].getPartyId()),iter,mAgents[i].getCoalition(),mAgents[i].getSelectionPolicy());
            mGraph.getParty(partyToOffer).setState(State(1));
            mAgents[i].getCoalition()->getId();
            coalitions.at(mAgents[i].getCoalition()->getId()).deleteFromCoalition(partyId);
            mAgents[i].deleteFromAgent(partyToOffer);
        }
    }
    
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


const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    return colByNum;
}

void Simulation::addAgent(int mAgentId,int mPartyId,SelectionPolicy *mSelectionPolicy,Coalition *  coal,vector<int> * connections)
{
    int a=0;
    mAgents.push_back(Agent(mAgentId,mPartyId,mSelectionPolicy->clone(),coal,connections));
    int coalitionId = coal->getId();
    coalitions.at(coalitionId).addPartyToCoalition(&parties.at(mPartyId),&mAgents[mAgents.size()-1]);
    colByNum.at(coalitionId).push_back(mPartyId);
    if (coalitions.at(coalitionId).getMandates()>61)
    {
        hasCoalition = true;
    }
    
}


