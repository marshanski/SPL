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
Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) ,timer(0), bestOffer(-1), bestAgent(-1),coal(-1)
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
void Party::setBestCoal(int colId)
{
    coal = colId;
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
    
    s.addAgent(s.getNumberOfAgents(),mId,s.getAgent(coal).getSelectionPolicy(),coal);
}


void Party::choose(Agent * agent,int mandates,int iter)
{
    if(mState == State(0))
    {
        timer = iter;
    }
    mJoinPolicy->choose(agent,this,mandates);
}


