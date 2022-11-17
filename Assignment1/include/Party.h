
#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

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

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    Coalition * mCoalition;
    vector <Coalition*> offers;
};

