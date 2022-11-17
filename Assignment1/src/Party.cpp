/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Party.cpp
****************************************/
//----------INCLUDE----------
#pragma once
#include <vector>
#include "Party.h"
#include <iostream>
//---------------------------

//----------USING----------
using std::vector;
using std::cout;
using std::endl;
//---------------------------
Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) 
{
    timer = 0;
    mCoalition = nullptr;
    vector<Coalition *> offers;
    cout << & offers << endl;
    cout << & timer << endl;
    
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

void Party::step(Simulation &s)
{
    // TODO: implement this method
    if(this->getState() == 1) // the party is collecting offers.
    {
        if(timer > 2)
        {
            //this.mCoalition = JoinPolicy:: join();
        }
    
    }
}
