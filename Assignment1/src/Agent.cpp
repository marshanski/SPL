#include "Agent.h"
#include "Party.h"
#include "Simulation.h"
#include <vector>
#include "SelectionPolicy.h"
#include <utility>
using std::vector;


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{}

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy,Coalition *  coal,vector<int> * connections):
mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy),coal(coal),connections(connections)
{}

int Agent::getId() const
{
    return mAgentId;
}

SelectionPolicy * Agent::getSelectionPolicy()
{
    return mSelectionPolicy;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    // TODO: implement this method
}

void Agent::setCoalition(Coalition * col)
{
    coal = col;
}

Coalition * Agent::getCoalition() 
{
    return coal;
}

vector<int> * Agent::getConnections() 
{
    return connections;
}
void Agent::setConnections(vector<int> * vec) 
{
    connections = vec;
}

std::pair<int,int> Agent::choose(vector<Party *> aviable, vector<int> * connections)
{
    return mSelectionPolicy->choose(aviable,connections);
}

void Agent::deleteFromAgent(int partyToOffer)
{
    connections->at(partyToOffer) = 0;
}



