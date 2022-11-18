/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : SelectionPolicy.h
****************************************/
//----------INCLUDE----------------------------------------
#pragma once
#include <string>
#include <vector>


//----------USING------------------------------------------
using std::string;
using std::vector;
//---------------------------------------------------------
class Agent;
class JoinPolicy;
class Simulation;
class Coalition;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    int getId() ;
    void step(Simulation & s,int iter);
    void choose(Agent * agent);

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    int bestOffer;
    int bestAgent;
};

