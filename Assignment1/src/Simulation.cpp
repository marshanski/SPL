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
//---------USING----------
class Coalition;
using std::vector;
using std::cout;
using std::endl;
//---------------------------

Simulation::Simulation(Graph graph, vector<Agent> agents):mGraph(graph),mAgents(agents),parties(vector <Party>()),coalitions(vector <Coalition>()),copyMatrix(vector<vector<int>>()), iter (0), joined(0),numberOfPartyies(0),hasCoalition(false),colByNum(vector<vector<int>>())
{
    for (unsigned int i = 0; i < agents.size(); i++)
    {
        Coalition c;
        vector <int> a;
        coalitions.push_back(c);
        colByNum.push_back(a);
    }
    copyMatrix               = mGraph.getMatrix();
    parties                  = mGraph.getParties();
    numberOfPartyies         = parties.size();
    vector<int> aviable;

    for (int i=0; i <numberOfPartyies; i++){aviable.push_back(i);}
    for (unsigned int i=0; i<mAgents.size();i++)
    {
        auto iter = std::remove(aviable.begin(),aviable.end(),mAgents[i].getPartyId());
        aviable.erase(iter,aviable.end());    
    }

    for (unsigned int i=0; i<mAgents.size();i++)
    {
        coalitions.at(i).setCoalition(parties, &mAgents.at(i),aviable,i);
        colByNum.at(i).push_back(mAgents[i].getPartyId());
        joined++;
        mAgents[i].setCoalition(i);
        if (coalitions[i].getMandates() >= 61){hasCoalition = true;}
    }
    return;
    
}

void Simulation::step()
{
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
        p = mAgents[i].choose(parties,coalitions.at(mAgents.at(i).getColId()).getAviable(),copyMatrix.at(mAgents.at(i).getPartyId()));
        partyToOffer = p.first;
        partyId      = p.second;

        if(partyToOffer != -1)
        {
            if (parties.at(partyToOffer).getState() != 2)
            {
                parties.at(partyToOffer).choose(&mAgents[i],coalitions.at(mAgents[i].getColId()).getMandates(),iter);
                mGraph.getParty(partyToOffer).setState(State(1));
                parties.at(partyToOffer).setState(State(1));
                coalitions.at(mAgents[i].getColId()).deleteFromCoalition(partyId);
                copyMatrix[mAgents.at(i).getPartyId()][partyToOffer]=0;
            }
        }
    }
    
}

void Simulation::stepByParties()
{
    for (int i=0; i <numberOfPartyies; i++)
    {
        if (parties.at(i).getState()== 1 && parties.at(i).getTimer()+3 == iter)
        {
            parties.at(i).step(*this);
            joined++;
            mGraph.getParty(i).setState(State(2));
            parties.at(i).setState(State(2));
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
Agent& Simulation::getAgent(int id) 
{
    return mAgents[id];
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

void Simulation::addAgent(int mAgentId,int mPartyId,Agent agent,int  coal)
{
    Agent nAgent = Agent(agent);
    nAgent.setCoalition(coal);
    nAgent.setId(mAgentId);
    nAgent.setPartyId(mPartyId);
    mAgents.push_back(nAgent);
    coalitions.at(coal).addPartyToCoalition(&parties.at(mPartyId),&mAgents[mAgents.size()-1]);
    colByNum.at(coal).push_back(mPartyId);
    if (coalitions.at(coal).getMandates()>=61)
    {
        hasCoalition = true;
    }
    
}

