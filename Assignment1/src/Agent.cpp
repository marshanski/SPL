#include "Agent.h"
class SelectionPolicy;


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
}

int Agent::getId() const
{
    return mAgentId;
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

void Agent::choose(vector<int> * connections,vector<Party *> aviableToOffer) 
{
    mSelectionPolicy->choose2(connections,aviableToOffer);
}



