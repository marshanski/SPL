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
#include <iostream>
#include <utility>
//---------------------------


class SelectionPolicy 
{
public:
    virtual std::pair<int,int> choose(vector<Party *> aviable,vector<int> * connections)=0;
};

class MandatesSelectionPolicy: public SelectionPolicy
{ 
public:
     std::pair<int,int> choose(vector<Party *> aviable,vector<int> * connections);
};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
public:
     std::pair<int,int> choose(vector<Party *> aviable, vector<int> * connections);
};



