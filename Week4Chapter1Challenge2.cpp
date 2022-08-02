// Week4Chapter1Challenge2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
    Write an A* implementation that reads coordinates labeled (x,y,cost) 
    where x & y are letters that define a connection, and cost is a number 
    that represents the cost.

    Sample map to traverse:

    (a,b,5) // = (0, 1, 5)
    (b,c,1) // = (1, 2, 1)
    (a,d,7) // = (0, 3, 7)
    (c,d,1) // = (2, 3, 1)

    Sample path request:

    (a,d)

    The program should determine if it's possible to reach a destination given the starting point. 
    It should also find the cheapest path, making sure to output the cost of the path.
*/

#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

#define VERTEX_COUNT 4

bool debug = false;

void HandleInvalidInput()
{
    cout << "Invalid input" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int GetValidInput(int max)
{
    int selection;

    bool retry;

    do
    {
        retry = false;

        cin >> selection;

        if (cin.fail() || selection < 0 || selection > max)
        {
            HandleInvalidInput();

            retry = true;
        }
    } while (retry);

    cout << endl;

    return selection;
}

int GetMinimumDistance(int distance[], bool sptSet[])
{
    if(debug) cout << "Getting minimum distance..." << endl;

    int minimum = INT_MAX;
    int minimumIndex = 0;

    for (int i = 0; i < VERTEX_COUNT; i++)
    {
        if (!sptSet[i] && distance[i] <= minimum)
        {
            minimum = distance[i];
            minimumIndex = i;
        }
    }

    if (debug) cout << "Minimum: " << minimum << ", index: " << minimumIndex << endl << endl;

    return minimumIndex;
}

void DisplayDistances(int distance[], int source, int goal)
{
    //cout << "Vertex, Distance from Source" << endl;

    //for (int i = 0; i < VERTEX_COUNT; i++)
    //{
    //    cout << i << ", " << distance[i] << endl;
    //}

    if (distance[goal] == INT_MAX)
    {
        cout << "No path found.";
    }
    else
    {
        cout << "Distance from " << source << " to " << goal << " is " << distance[goal];
    }

    cout << endl;
}

/*
    Set all elements of distance to INFINITE (or max available for variable type)
    Set all elements of sptSet to false.
*/
void InitializeSets(int distance[VERTEX_COUNT], bool sptSet[VERTEX_COUNT])
{
    if (debug) cout << "Initializing sets.." << endl << endl;

    for (int i = 0; i < VERTEX_COUNT; i++)
    {
        distance[i] = INT_MAX;
        sptSet[i] = false;
    }
}

bool IsNewDistanceSmaller(int u, int v, int vertexGraph[VERTEX_COUNT][VERTEX_COUNT],
    int distance[VERTEX_COUNT],
    bool sptSet[VERTEX_COUNT])
{
    if (debug)
    {
        cout << "Is new distance smaller?" << endl;
        cout << "sptSet[v]: " << sptSet[v] << ", ";
        cout << "vertexGraph[u][v]: " << vertexGraph[u][v] << ", ";
        cout << "distance[u]: " << distance[u] << ", ";
        cout << "distance[v]: " << distance[v] << endl << endl;
    }

    // return true if the path is not finalized, there is a connection, the connection is not MAX,
    // and the new distance is shorter than the old distance
    return !sptSet[v] &&
        vertexGraph[u][v] &&
        distance[u] != INT_MAX &&
        distance[u] + vertexGraph[u][v] < distance[v];
}

void FindShortestPath(int vertexGraph[VERTEX_COUNT][VERTEX_COUNT], 
                        int distance[VERTEX_COUNT], 
                        bool sptSet[VERTEX_COUNT],
                        int goal)
{
    for (int count = 0; count < VERTEX_COUNT - 1; count++)
    {
        int u = GetMinimumDistance(distance, sptSet);

        if(debug) cout << "u = " << u << ", marking sptSet[u] to true" << endl;

        sptSet[u] = true;

        if (debug) cout << "Looping through vertices..." << endl << endl;

        for (int v = 0; v < VERTEX_COUNT; v++)
        {
            if (debug) cout << "Checking v: " << v << "..." << endl;

            if (IsNewDistanceSmaller(u, v, vertexGraph, distance, sptSet))
            {
                if (debug) cout << "Setting new distance: " << distance[u] + vertexGraph[u][v] << endl << endl;
                distance[v] = distance[u] + vertexGraph[u][v];
            }
        }

        // break once this goal is completely processed
        if (sptSet[goal] == true) return;
    }
}

void DijkstrasAlgorithm(int vertexGraph[VERTEX_COUNT][VERTEX_COUNT], int source, int goal)
{
    int distance[VERTEX_COUNT];

    bool sptSet[VERTEX_COUNT]; 

    InitializeSets(distance, sptSet);

    distance[source] = 0;

    if (debug) cout << "dist[source] = 0" << endl << endl;

    FindShortestPath(vertexGraph, distance, sptSet, goal);

    DisplayDistances(distance, source, goal);
}

int main()
{
    int vertexGraph[VERTEX_COUNT][VERTEX_COUNT] =     { { 0, 5, 0, 7},
                                                        { 5, 0, 1, 0},
                                                        { 0, 1, 0, 1},
                                                        { 7, 0, 1, 0} };

    //int vertexGraph[VERTEX_COUNT][VERTEX_COUNT] = { { 0, 0, 0, 0},
    //                                                { 0, 0, 1, 0},
    //                                                { 0, 1, 0, 1},
    //                                                { 0, 0, 1, 0} };

    // set this to where you would like to start
    int source = 0;

    cout << "Set the source: ";
    source = GetValidInput(VERTEX_COUNT - 1);

    int goal = 0;

    cout << "Set the goal: ";
    goal = GetValidInput(VERTEX_COUNT - 1);

    cout << "Would you like debug logs? (0 = n, 1 = y): ";
    debug = GetValidInput(1);

    DijkstrasAlgorithm(vertexGraph, source, goal);

    return 0;
}