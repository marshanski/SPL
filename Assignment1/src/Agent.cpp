#include "Agent.h"
#include "Party.h"
#include "Simulation.h"
#include <vector>
#include "SelectionPolicy.h"
#include <utility>
using std::vector;


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy),coal(-1)
{}

Agent::Agent(const Agent & other):mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone()),coal(other.coal)
{
    //mAgentId         = other.mAgentId;
    //mPartyId         = other.mPartyId;
    //mSelectionPolicy = other.mSelectionPolicy->clone();
    //coal             = other.coal;
}
Agent& Agent:: operator=(const Agent &other)
{
    if (this != &other)
    {
        if (mSelectionPolicy)
        {
            delete mSelectionPolicy;
        }

        mAgentId         = other.mAgentId;
        mPartyId         = other.mPartyId;
        mSelectionPolicy = other.mSelectionPolicy->clone();
        coal             = other.coal;
    }
    return *this;
}


Agent::~Agent()
{
    if (mSelectionPolicy)
    {
        delete mSelectionPolicy;
    }


}
Agent::Agent(Agent && other) :mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy),coal(other.coal)
{
    //mAgentId         = other.mAgentId;
    //mPartyId         = other.mPartyId;
    //mSelectionPolicy = other.mSelectionPolicy;
    //coal             = other.coal;
    other.mSelectionPolicy       =nullptr;
}
Agent& Agent::operator=(Agent && other) 
{
    if(this != &other)
    {
        if (mSelectionPolicy)
        {
            delete mSelectionPolicy;
        }

        mAgentId         = other.mAgentId;
        mPartyId         = other.mPartyId;
        mSelectionPolicy = other.mSelectionPolicy;
        coal             = other.coal;
        other.mSelectionPolicy       = nullptr;
    }
    return *this;

}

int Agent::getId() const
{
    return mAgentId;
}
void Agent::setId(int index) 
{
    mAgentId = index;
}

SelectionPolicy * Agent::getSelectionPolicy()
{
    return mSelectionPolicy;
}

int Agent::getPartyId() const
{
    return mPartyId;
}
void Agent::setPartyId(int index) 
{
    mPartyId = index;
}

void Agent::step(Simulation &sim)
{
    // TODO: implement this method
}

void Agent::setCoalition(int col)
{
    coal = col;
}

int Agent::getColId() 
{
    return coal;
}


std::pair<int,int> Agent::choose(vector<Party>parties,vector <int> aviable,vector<int>connections)
{
    return mSelectionPolicy->choose(parties,aviable,connections);
}

void Agent::deleteFromAgent(int partyToOffer)
{
    //connections->at(partyToOffer) = 0;
}



