#include "HospitalRouter.h"

#include <queue>
#include <climits>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/*
|--------------------------------------------------------------------------
| Constructor
|--------------------------------------------------------------------------
*/

HospitalRouter::HospitalRouter(int nodes)
{
    numNodes = nodes;
    graph.resize(nodes);
}

/*
|--------------------------------------------------------------------------
| Initialize Graph
|--------------------------------------------------------------------------
*/

void HospitalRouter::initializeGraph(int nodes)
{
    numNodes = nodes;

    graph.clear();

    graph.resize(nodes);
}

/*
|--------------------------------------------------------------------------
| Add Corridor
|--------------------------------------------------------------------------
*/

void HospitalRouter::addCorridor(
    int from,
    int to,
    int baseTime)
{
    // Validate input
    if (from < 0 || to < 0 || baseTime <= 0)
    {
        cout << "[ERROR] Invalid corridor data.\n";
        return;
    }

    // Dynamically expand graph if necessary
    int requiredNodes = max(from, to) + 1;

    if (requiredNodes > numNodes)
    {
        numNodes = requiredNodes;
        graph.resize(numNodes);
    }

    // Prevent duplicate corridor
    for (const auto& edge : graph[from])
    {
        if (edge.to == to)
        {
            cout << "[WARNING] Corridor already exists.\n";
            return;
        }
    }

    Edge edge;

    edge.to = to;
    edge.baseWeight = baseTime;
    edge.trafficDelay = 0;
    edge.isBlocked = false;

    graph[from].push_back(edge);

    cout << "[SUCCESS] Corridor added.\n";
}

/*
|--------------------------------------------------------------------------
| Remove Corridor
|--------------------------------------------------------------------------
*/

bool HospitalRouter::removeCorridor(
    int from,
    int to)
{
    if (from < 0 || from >= numNodes ||
        to < 0 || to >= numNodes)
    {
        return false;
    }

    auto& edges = graph[from];

    auto it = remove_if(
        edges.begin(),
        edges.end(),
        [to](const Edge& edge)
        {
            return edge.to == to;
        });

    if (it == edges.end())
        return false;

    edges.erase(it, edges.end());

    return true;
}


/*
|--------------------------------------------------------------------------
| Block Corridor
|--------------------------------------------------------------------------
*/

bool HospitalRouter::blockCorridor(
    int from,
    int to)
{
    if (from < 0 || from >= numNodes ||
        to < 0 || to >= numNodes)
    {
        return false;
    }

    for (auto& edge : graph[from])
    {
        if (edge.to == to)
        {
            edge.isBlocked = true;
            return true;
        }
    }

    return false;
}

/*
|--------------------------------------------------------------------------
| Unblock Corridor
|--------------------------------------------------------------------------
*/

bool HospitalRouter::unblockCorridor(
    int from,
    int to)
{
    if (from < 0 || from >= numNodes ||
        to < 0 || to >= numNodes)
    {
        return false;
    }

    for (auto& edge : graph[from])
    {
        if (edge.to == to)
        {
            edge.isBlocked = false;
            return true;
        }
    }

    return false;
}

/*
|--------------------------------------------------------------------------
| AI Traffic Update
|--------------------------------------------------------------------------
*/

void HospitalRouter::updateTrafficFromAI(
    int from,
    int to,
    int extraDelay)
{
    if (from < 0 || from >= numNodes ||
        to < 0 || to >= numNodes)
    {
        cout << "[ERROR] Invalid node number.\n";
        return;
    }

    if (extraDelay < 0)
    {
        cout << "[ERROR] Traffic delay cannot be negative.\n";
        return;
    }

    for (auto& edge : graph[from])
    {
        if (edge.to == to)
        {
            edge.trafficDelay = extraDelay;

            cout << "[SUCCESS] Traffic Updated.\n";

            return;
        }
    }

    cout << "[ERROR] Corridor not found.\n";
}

/*
|--------------------------------------------------------------------------
| Reset All Traffic Delays
|--------------------------------------------------------------------------
*/

void HospitalRouter::resetTraffic()
{
    for (auto& node : graph)
    {
        for (auto& edge : node)
        {
            edge.trafficDelay = 0;
        }
    }
    cout << "[SUCCESS] Traffic Reset.\n";
}

/*
|--------------------------------------------------------------------------
| Find Fastest Route
|--------------------------------------------------------------------------
*/

vector<int> HospitalRouter::findFastestRoute(
    int startNode,
    int endNode)
    
{

    if (startNode < 0 || startNode >= numNodes ||
    endNode < 0 || endNode >= numNodes)
{
    return {};
}
    vector<int> distance(
        numNodes,
        INT_MAX
    );

    vector<int> parent(
        numNodes,
        -1
    );

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    distance[startNode] = 0;

    pq.push({
        0,
        startNode
    });

    while(!pq.empty())
    {
        int currentDistance = pq.top().first;
        int currentNode = pq.top().second;

        pq.pop();

        if(currentDistance > distance[currentNode])
            continue;

        for(const auto &edge : graph[currentNode])
        {
            if(edge.isBlocked)
            continue;
            int neighbour = edge.to;

            int weight = edge.getTotalWeight();

            if(distance[currentNode] + weight < distance[neighbour])
            {
                distance[neighbour] =
                    distance[currentNode] + weight;

                parent[neighbour] = currentNode;

                pq.push({
                    distance[neighbour],
                    neighbour
                });
            }
        }
    }

    vector<int> path;

    if(distance[endNode] == INT_MAX)
        return path;

    for(
        int at = endNode;
        at != -1;
        at = parent[at]
    )
    {
        path.push_back(at);
    }

    reverse(
        path.begin(),
        path.end()
    );

    return path;
}

/*
|--------------------------------------------------------------------------
| Route Time
|--------------------------------------------------------------------------
*/

int HospitalRouter::getRouteTime(
    int startNode,
    int endNode)
{

    if (startNode < 0 || startNode >= numNodes ||
    endNode < 0 || endNode >= numNodes)
{
    return -1;
}
    vector<int> distance(
        numNodes,
        INT_MAX
    );

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    distance[startNode]=0;

    pq.push({
        0,
        startNode
    });

    while(!pq.empty())
    {
        auto current = pq.top();

        pq.pop();

        int node = current.second;

        if(current.first > distance[node])
            continue;

        for(const auto &edge : graph[node])
        {
            if(edge.isBlocked)
            continue;
            int next = edge.to;

            int weight = edge.getTotalWeight();

            if(distance[node]+weight<distance[next])
            {
                distance[next]=
                    distance[node]+weight;

                pq.push({
                    distance[next],
                    next
                });
            }
        }
    }

    return distance[endNode];
}

/*
|--------------------------------------------------------------------------
| Display Hospital Map
|--------------------------------------------------------------------------
*/

void HospitalRouter::displayMap()
{
    cout << "\n========== HOSPITAL MAP ==========\n";

    for (int from = 0; from < numNodes; from++)
    {
        cout << "\nLocation " << from << ":\n";

        if (graph[from].empty())
        {
            cout << "  No connected corridors.\n";
            continue;
        }

        for (const auto& edge : graph[from])
        {
            cout << "  --> "
     << edge.to
     << " | Base Time: "
     << edge.baseWeight
     << " sec"
     << " | Traffic Delay: "
     << edge.trafficDelay
     << " sec"
     << " | Status: "
     << (edge.isBlocked ? "Blocked" : "Open")
     << endl;
        }
    }

    cout << "==================================\n";
}

/*
|--------------------------------------------------------------------------
| Get Neighbouring Locations
|--------------------------------------------------------------------------
*/

vector<Edge> HospitalRouter::getNeighbours(
    int node)
{
    if (node < 0 || node >= numNodes)
    {
        return {};
    }

    return graph[node];
}

/*
|--------------------------------------------------------------------------
| Save Hospital Map
|--------------------------------------------------------------------------
*/

void HospitalRouter::saveMap()
{
    ofstream file("database/hospital_map.txt");

    if (!file.is_open())
    {
        cout << "[ERROR] Unable to save hospital map.\n";
        return;
    }

    file << numNodes << endl;

    for (int from = 0; from < numNodes; from++)
    {
        for (const auto& edge : graph[from])
        {
            file << from << " "
                 << edge.to << " "
                 << edge.baseWeight << " "
                 << edge.trafficDelay << " "
                 << edge.isBlocked
                 << endl;
        }
    }

    file.close();

    cout << "[SUCCESS] Hospital map saved.\n";
}

/*
|--------------------------------------------------------------------------
| Load Hospital Map
|--------------------------------------------------------------------------
*/

void HospitalRouter::loadMap()
{

    
    ifstream file("database/hospital_map.txt");

    if (!file.is_open())
    {
        cout << "[INFO] No saved hospital map found.\n";
        return;
    }

    file >> numNodes;

    graph.clear();
    graph.resize(numNodes);

    int from;

    while (file >> from)
    {
        Edge edge;

        file >> edge.to;
        file >> edge.baseWeight;
        file >> edge.trafficDelay;
        file >> edge.isBlocked;


        if (from < 0 || from >= numNodes)
{
    continue;
}

       if (edge.to >= 0 && edge.to < numNodes)
{
    graph[from].push_back(edge);
}
    }

    file.close();

    cout << "[SUCCESS] Hospital map loaded.\n";
}