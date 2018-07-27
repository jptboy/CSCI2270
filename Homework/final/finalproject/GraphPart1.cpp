//Ayush Khanal
//Instructor: Godley
//Homework 1: Community Garage Sale
//IMPORTANT: Read README for build instructions
#include <iostream>
#include "Graph.h"
using namespace std;
void Graph::addEdge(std::string v1, std::string v2, int weight)
{
    unsigned int cityIndex = stoi(v2);
    /*
    cout
        << "Edge length of: "<< weight <<" between: " << v1
        << " and: " << vertices[cityIndex].name << endl;
    */
    adjVertex *newAdjVertex = new adjVertex;
    newAdjVertex->weight = weight;
    newAdjVertex->v = &(vertices[cityIndex]);

    unsigned int startingIdx=0;
    bool found = false;
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        if(vertices[i].name==v1)
        {
            startingIdx=i;
            found=true;
            break;
        }
    }
    if(found)
    {
        vertices[startingIdx].adj.push_back(*newAdjVertex);
        //cout << "Edge has been added." << endl;
        delete newAdjVertex;
    }
    else
    {
        cout << "Huge error" << endl;
    }

}
void Graph::addVertex(std::string name)
{
    vertex *newVertex = new vertex;
    newVertex->name = name;
    vertices.push_back(*newVertex);
    delete newVertex;
}
int Graph::isAdjacent(std::string v1, std::string v2)
{
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        if(vertices[i].name==v1)
        {
            for(unsigned int j=0; j<vertices[i].adj.size(); j++)
            {
                if(vertices[i].adj[j].v->name==v2)
                {
                    return 1;
                }
            }
            break;
        }
    }
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        if(vertices[i].name==v2)
        {
            for(unsigned int j=0; j<vertices[i].adj.size(); j++)
            {
                if(vertices[i].adj[j].v->name==v1)
                {
                    return 1;
                }
            }
            break;
        }
    }
    return 0;
}
void Graph::displayEdges()
{
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        cout << vertices[i].name << "->";
        /*
        if(vertices[i].adj.size()>0)
        {
            for(unsigned int j=0; j<(vertices[i].adj.size()-1); j++)
            {
                cout << vertices[i].adj[j].v->name << "***";
            }
            cout << vertices[i].adj[vertices[i].adj.size()-1].v->name << endl;
        }
        else
        {
            cout << vertices[i].name << "->" << endl;
        }
        */
        for(unsigned int j=0; j<(vertices[i].adj.size()); j++)
        {
            cout << vertices[i].adj[j].v->name;
            if(j!=vertices[i].adj.size()-1)
                cout << "***";
        }
        cout << endl;
    }
}
