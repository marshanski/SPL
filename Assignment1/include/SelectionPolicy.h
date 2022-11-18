/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : SelectionPolicy.h
****************************************/
//----------INCLUDE----------
//----------USING----------
#pragma once
#include <vector>
using std::vector;
#include <Party.h>
//---------------------------


class SelectionPolicy 
{
public:
    virtual int choose(vector<Party *> aviable,vector<int> * connections)=0;
};

class MandatesSelectionPolicy: public SelectionPolicy
{ 
public:
    int choose(vector<Party *> aviable,vector<int> * connections);
};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
public:
    int choose(vector<Party *> aviable, vector<int> * connections);
};



