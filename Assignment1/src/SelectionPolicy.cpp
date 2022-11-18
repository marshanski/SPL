/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Coalitaion.h
****************************************/
//----------INCLUDE----------
#pragma once
#include <iostream>
#include "SelectionPolicy.h"

#include <bits/stdc++.h>
using std::cout;
using std::endl;

int EdgeWeightSelectionPolicy::choose(vector <Party *> aviable,vector<int> * connections)
{

    int max = 0, maxIndex = -1, paryId =-1 ;
    for (unsigned i = 0; i < aviable.size(); i++)
    {
        if (connections->at(aviable.at(i)->getId()) >max)
        {
            max      = connections->at(aviable.at(i)->getId());
            maxIndex = aviable.at(i)->getId();
            paryId   = i;
        }
    }
    if (max == 0 ){return maxIndex;}
    
    connections->at(maxIndex) = 0;
    auto iter = std::remove(aviable.begin(),aviable.end(),aviable[paryId]);
    aviable.erase(iter,aviable.end());   
    //for (unsigned i = 0; i < connections->size(); i++){cout << connections->at(i)<< endl;};
    return maxIndex;
}

int MandatesSelectionPolicy::choose(vector <Party *> aviable,vector<int> * connections)
{
    int max = 0, maxIndex = -1, paryId =-1 ;
    for (unsigned i = 0; i < aviable.size(); i++)
    {
        if (connections->at(aviable.at(i)->getId()) >0 && aviable.at(i)->getMandates() > max )
        {
            max      = aviable.at(i)->getMandates();
            maxIndex = aviable.at(i)->getId();
            paryId   = i;
        }
    }
    if (max == 0 ){return maxIndex;}
    
    connections->at(maxIndex) = 0;
    auto iter = std::remove(aviable.begin(),aviable.end(),aviable[paryId]);
    aviable.erase(iter,aviable.end());   
    //for (unsigned i = 0; i < connections->size(); i++){cout << connections->at(i)<< endl;};
    return maxIndex;
}
