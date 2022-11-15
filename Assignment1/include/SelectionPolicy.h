/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :
****************************************/
//----------INCLUDE----------
#pragma once

class SelectionPolicy 
{
    public:
        
        virtual int choose2(vector<int> * connections,vector<Party *> aviableToOffer);

};

class MandatesSelectionPolicy : public SelectionPolicy 
{ 
    public:
        MandatesSelectionPolicy();
        virtual int choose2(vector<int> * connections,vector<Party *> aviableToOffer);

};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
    public:
        EdgeWeightSelectionPolicy();
        virtual int choose2(vector<int> * connections,vector<Party *> aviableToOffer);

};