/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :
****************************************/
//----------INCLUDE----------
#pragma once
//----------USING----------
#include<JoinPolicy.h>
#include <iostream>
using std::cout;
using std::endl;
//---------------------------

void MandatesJoinPolicy::choose(Agent * agent,Party * party)
{
    cout << "MandatesJoinPolicy" << endl;

}

void LastOfferJoinPolicy::choose(Agent * agent,Party * party) 
{
    cout << "MandatesJoinPolicy" << endl;
}