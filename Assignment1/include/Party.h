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
    //--------------------Rule of 5-----------------------------------------
    //Constructor
    Party(int id, string name, int mandates, JoinPolicy *); 
    //Copy constructor
    Party(const Party & other);
    //Copy assignment opearator
    Party &operator=(const Party &other);
    //Destructor
    virtual ~Party();
    //Move Constructor
    Party(Party && other) ;
    //Assignment Operator
    Party & operator=(Party && other) ;
    //GET
    int getbestAgent();
    int getTimer() ;
    int getbestOffer() ;
    int getId() ;
    int getMandates() const;
    State getState() const;
    const string &getName() const;
    //SET
    void step(Simulation & s);
    void setState(State state);
    void setbestOffer(int mandates);
    void setBestCoal(int colId);
    void setbestAgent(int agentIndex);
    //
    void choose(Agent * agent,int iter,int mandates);
    void updateMandates(Agent * agent,int mandates);



private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    int bestOffer;
    int bestAgent;
    int coal;
};

