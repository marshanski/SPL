/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : SelectionPolicy.h
****************************************/
//----------INCLUDE----------------------------------------
#pragma once
#include <string>
#include <vector>
#include <vector>
//----------USING------------------------------------------
using std::string;
using std::vector;
//---------------------------------------------------------
class Agent;
class JoinPolicy;
class SelectionPolicy;
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
    const string &getName() const;
    int getId() ;
    void step(Simulation & s);
    void choose(Party * party,int iter,Coalition * coal,SelectionPolicy * sp);
    void setbestOffer(int mandates);
    int getbestOffer() ;
    void setbestAgent(int agentIndex);
    void setBestCoal(Coalition * c);
    void setSP(SelectionPolicy * SelectP);
    int getbestAgent();
    int getTimer() ;


private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    int bestOffer;
    int bestAgent;
    Coalition * coal;
    SelectionPolicy * sp;
};

