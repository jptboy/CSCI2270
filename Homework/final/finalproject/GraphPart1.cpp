//Ayush Khanal
//Instructor: Godley
//Homework 4: Final Project
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
    newAdjVertex->weight = weight;//we set the weight
    newAdjVertex->v = &(vertices[cityIndex]);// all we are doing in this function is adding an adjacnet vertex

    unsigned int startingIdx=0;
    bool found = false;
    for(unsigned int i=0; i<vertices.size(); i++)//we find the vertex to add to
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
        vertices[startingIdx].adj.push_back(*newAdjVertex);//we add it to the vector
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
    vertex *newVertex = new vertex;//here we just push a new vertex into the vector
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
            for(unsigned int j=0; j<vertices[i].adj.size(); j++)//iterating through the vecotrs adjacent vertex
            {
                if(vertices[i].adj[j].v->name==v2)
                {
                    return 1;//if we find it we return 1 or break
                }
            }
            break;
        }
    }
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        if(vertices[i].name==v2)
        {
            for(unsigned int j=0; j<vertices[i].adj.size(); j++)//we do the same thing as the above for loop
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
        for(unsigned int j=0; j<(vertices[i].adj.size()); j++)//we just display the vertex and its edges with iteration
        {
            cout << vertices[i].adj[j].v->name;
            if(j!=vertices[i].adj.size()-1)
                cout << "***";
        }
        cout << endl;
    }
}
