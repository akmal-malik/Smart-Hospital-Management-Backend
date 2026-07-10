#ifndef HOSPITAL_ROUTER_H
#define HOSPITAL_ROUTER_H

#include <vector>
#include <string>

#include "Models.h"

using namespace std;

class HospitalRouter
{
private:

    int numNodes;

    vector<vector<Edge>> graph;

public:


    HospitalRouter(int nodes = 0);
    void initializeGraph(int nodes);

    /*
    |--------------------------------------------------------------------------
    | Map Management
    |--------------------------------------------------------------------------
    */

    void addCorridor(
        int from,
        int to,
        int baseTime
    );

    bool removeCorridor(
        int from,
        int to
    );

    bool blockCorridor(
        int from,
        int to
    );

    bool unblockCorridor(
        int from,
        int to
    );

    void updateTrafficFromAI(
        int from,
        int to,
        int extraDelay
    );

    void resetTraffic();

    /*
    |--------------------------------------------------------------------------
    | Routing
    |--------------------------------------------------------------------------
    */

    vector<int> findFastestRoute(
        int startNode,
        int endNode
    );

    int getRouteTime(
        int startNode,
        int endNode
    );

    /*
    |--------------------------------------------------------------------------
    | Search
    |--------------------------------------------------------------------------
    */

    vector<Edge> getNeighbours(
        int node
    );

    /*
    |--------------------------------------------------------------------------
    | Display
    |--------------------------------------------------------------------------
    */

    void displayMap();

    /*
    |--------------------------------------------------------------------------
    | Persistence
    |--------------------------------------------------------------------------
    */

    void saveMap();

    void loadMap();
};

#endif