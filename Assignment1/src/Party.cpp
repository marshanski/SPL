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
    // TODO: implement this method

}
void Party::step(Simulation & s,int iter)
{
    // TODO: implement this method

    if(timer+3 == iter) // the party is collecting offers.
    {
        //return maxAgent;
    }
}
void Party::choose(Agent * agent)
{
    int a=0;
    mJoinPolicy->choose(agent,this);
}


