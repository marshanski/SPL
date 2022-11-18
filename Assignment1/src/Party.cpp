/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Party.cpp
****************************************/
//----------INCLUDE----------
#pragma once
#include <vector>
#include "Party.h"
#include "JoinPolicy.h"
#include <iostream>
#include <Simulation.h>


//---------------------------

//----------USING----------
using std::vector;
using std::cout;
using std::endl;
//---------------------------
Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) ,timer(0), bestOffer(-1), bestAgent(-1)
{


}
State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

void Party::setBestCoal(Coalition * c)
{
    coal = c;
}

int Party::getbestOffer() 
{
    return bestOffer;
}

int Party::getTimer() 
{
    return timer;
}

void Party::setbestOffer(int mandates)
{
    bestOffer = mandates;
}

int Party::getbestAgent() 
{
    return bestAgent ;
}

void Party::setbestAgent(int agentIndex)
{
    bestAgent = agentIndex;
}


int Party::getMandates() const
{
    return mMandates;
}
int Party::getId() 
{
    return mId;
}

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation & s)
{
    Agent * agent = s.addAgent(s.getNumberOfAgents(),mId,sp,coal,s.getConnectionsOfParty(mId));
    //coal->addPartyToCoalition(this,agent);
    int r=0;

}
void Party::setSP(SelectionPolicy * SelectP)
{
    sp = SelectP;
    
}

void Party::choose(Party * party,int iter,Coalition * coal,SelectionPolicy * sp)
{
    this->setState(State(1));
    if (timer!=0)
    {
        timer = iter;
    }
    mJoinPolicy->choose(party,this,coal,sp);
}


