/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Agent.h
****************************************/
//----------INCLUDE----------
#pragma once
#include <vector>
#include "Party.h"
//---------------------------
//----------CLASS----------
using std::vector;
//---------------------------

class Graph
{
public:
    Graph(vector<Party> vertices, vector<vector<int>> edges);
    //GET
    int getMandates(int partyId) const;
    int getEdgeWeight(int v1, int v2) const;
    int getNumVertices() const;
    const Party &getParty(int partyId) const;
    vector <Party>getParties() const;
    vector<vector<int>> getMatrix();
    vector<vector<int>>  * getMatrixAdress();
    Party &getParty(int partyId) ;

private:
    vector<Party> mVertices;
    vector<vector<int>> mEdges;
};
