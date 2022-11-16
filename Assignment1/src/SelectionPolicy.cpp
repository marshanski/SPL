/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Coalitaion.h
****************************************/
//----------INCLUDE----------
#pragma once
#include "SelectionPolicy.h"



int EdgeWeightSelectionPolicy::choose(vector <Party *> aviable,vector<int> * connections)
{
    return 2;
}

int MandatesSelectionPolicy::choose(vector <Party *> aviable,vector<int> * connections)
{
    return 1;
}
