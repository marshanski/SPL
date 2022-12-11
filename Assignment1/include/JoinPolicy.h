/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :
****************************************/
//----------INCLUDE----------
//----------USING----------
#include <vector>
using std::vector;
#include <Party.h>
#include <Agent.h>
//---------------------------

class JoinPolicy 
{
public:
    virtual void choose(Agent * agent,Party * party,int mandates)=0;
    virtual JoinPolicy* clone()=0;
    virtual ~JoinPolicy()=default;
    virtual void update(Agent * agent,Party * party,int mandates)=0;
};


class MandatesJoinPolicy: public JoinPolicy
{ 
public:
    void choose(Agent * agent,Party * party,int mandates);
    virtual MandatesJoinPolicy* clone() override;
    virtual ~MandatesJoinPolicy() = default;
    void update(Agent * agent,Party * party,int mandates);
};


class LastOfferJoinPolicy : public JoinPolicy 
{
    void choose(Agent * agent,Party * party,int mandates);
    virtual LastOfferJoinPolicy* clone() override;
    virtual ~LastOfferJoinPolicy() =default;
    void update(Agent * agent,Party * party,int mandates);
};