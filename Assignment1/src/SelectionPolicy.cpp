/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Coalitaion.h
****************************************/
//----------INCLUDE----------
#pragma once
#include <iostream>
#include "SelectionPolicy.h"
#include <utility>

#include <bits/stdc++.h>
using std::cout;
using std::endl;

std::pair<int,int> EdgeWeightSelectionPolicy::choose(vector <Party *> aviable,vector<int> * connections)
{

    int max = 0, maxIndex = -1, partyId =-1 ;
    for (unsigned i = 0; i < aviable.size(); i++)
    {
        if (connections->at(aviable.at(i)->getId()) >max)
        {
            max      = connections->at(aviable.at(i)->getId());
            maxIndex = aviable.at(i)->getId();
            partyId   = i;
        }
    }
    return(std::make_pair(maxIndex,partyId));
}

std::pair<int,int>  MandatesSelectionPolicy::choose(vector <Party *> aviable,vector<int> * connections)
{
    int max = 0, maxIndex = -1, partyId =-1 ;
    for (unsigned i = 0; i < aviable.size(); i++)
    {
        if (connections->at(aviable.at(i)->getId()) >0 && aviable.at(i)->getMandates() > max )
        {
            max      = aviable.at(i)->getMandates();
            maxIndex = aviable.at(i)->getId();
            partyId   = i;
        }
    }
    return(std::make_pair(maxIndex,partyId));
}
