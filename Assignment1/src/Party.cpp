/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Party.cpp
****************************************/
//----------INCLUDE----------
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

 
Party::Party(const Party & other): mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState) ,timer(other.timer), bestOffer(other.bestOffer), bestAgent(other.bestAgent),coal(other.coal)
{}

Party& Party:: operator=(const Party &other)
{
    if (this != &other)
    {
        if (mJoinPolicy){delete mJoinPolicy;}

        mId           = other.mId;
        mName         = other.mName;
        mJoinPolicy   = other.mJoinPolicy->clone();
        mMandates     = other.mMandates;
        mState        = other.mState;
        timer         = other.timer;
        bestOffer     = other.bestOffer;
        bestAgent     = other.bestAgent;
        coal          = other.coal;

    }
    return *this;
}


Party::~Party()
{
    if (mJoinPolicy){delete mJoinPolicy;}
}

Party::Party(Party && other) :mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState) ,timer(other.timer), bestOffer(other.bestOffer), bestAgent(other.bestAgent),coal(other.coal)
{

    other.mJoinPolicy = nullptr;
}
Party& Party::operator=(Party && other) 
{
    if(this != &other)
    {
        if (mJoinPolicy){delete mJoinPolicy;}

        mId               = other.mId;
        mName             = other.mName;
        mJoinPolicy       = other.mJoinPolicy;
        mMandates         = other.mMandates;
        mState            = other.mState;
        timer             = other.timer;
        bestOffer         = other.bestOffer;
        bestAgent         = other.bestAgent;
        coal              = other.coal;
        other.mJoinPolicy =nullptr;
    }
    return *this;
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

    s.addAgent(s.getNumberOfAgents(),mId,s.getAgent(coal),coal);
}


void Party::choose(Agent * agent,int mandates,int iter)
{
    if(mState == State(0))
    {
        timer = iter;
    }
    mJoinPolicy->choose(agent,this,mandates);
}

void Party::updateMandates(Agent * agent,int mandates)
{
    mJoinPolicy->update(agent,this,mandates);
}


