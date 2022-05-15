#include <bits/stdc++.h>
using namespace std;

//Util to check cut vertex using DFS in recursive way
//visited keeps track of visited node
//adj contains adjacency list of the graph
// parent - parent of the given vertex
// discoveryTime - keeps track of discovery time of each vertex
// isCutVertex - bool to check if that node is cut vertex or not
void CheckForCutVertices(vector<int> adj[], int vertex, int& time, int parent, bool visited[], bool isCutVertex[],
            int discoveryTime[], int low[])
{
    //Counts the no of children of the vertex
    int numChild = 0;
    //Update the discovery time
    low[vertex] = discoveryTime[vertex] = ++time;
    //Set the current vertex to visited
    visited[vertex] = true;
    //Iterate all the adjaceny vertex of current vertex
    for (auto av : adj[vertex])
    {
        //If the av is not visited already, then do recursive DFS search for av to find cut vertex
        if (visited[av] == false)
        {
            //Increase the child count
            numChild++;
            //Make a recurive call to the adjacency vertex
            CheckForCutVertices(adj, av, time, vertex, visited, isCutVertex, discoveryTime, low);
            //Checks if there is back edge from the root to ancestors
            low[vertex] = min(low[av], low[vertex]);
            if (parent != -1)
            {
                if(discoveryTime[vertex] <= low[av])
                {
                    isCutVertex[vertex] = true;
                }
            }
        }
        else if (av != parent)
        {
            //Store low value
            low[vertex] = min(discoveryTime[av], low[vertex]);
        }
    }
 
    //If the current vertex is the roor and it has mmore than 2 child
    if (parent == -1)
    {
        if(numChild > 1)
        {
            isCutVertex[vertex] = true;
        }
    }
}

//Program to find the cut vertices 
void FindCutVertices(vector<int> adj[], int noVert)
{
    int time, parent;
    int discoveryTime[noVert], low[noVert];
    bool visited[noVert], isCutVertex[noVert];

    //Initialize
    parent =-1;
    time=0;

    for(int i=0; i<noVert; i++)
    {
        discoveryTime[i] = low[i] =  0;
        visited[i] = isCutVertex[i] = false;
    }
 
    //This loop will make sure that the program will work for disconnected graph
    for (int i = 0; i < noVert; i++)
    {
        if (!visited[i])
        {
            CheckForCutVertices(adj, i, time, parent, visited, isCutVertex, discoveryTime, low);
        }
    }
 
    //Print the cut vertices
    for (int i = 0; i < noVert; i++)
    {
        if (isCutVertex[i] == true)
        {
            printf("\n\t%d", i);
        }
    }
}

int main()
{
    //No of vertex, edge
    int noVert, noEdge;

    printf("\nEnter the number of vertex\n");
    scanf("%d", &noVert);
    printf("\nEnter the number of edge\n");
    scanf("%d", &noEdge);

    std::vector<int> adj[noVert];

    printf("\nEnter the Edge in space seperated way 5 10\n");
    for (int i = 0; i < noEdge; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    printf("\nFor the given graph, cut vertices found is");
    FindCutVertices(adj, noVert);
    return 0;
}