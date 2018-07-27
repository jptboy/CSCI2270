#include <iostream>
#include "Graph.hpp"
using namespace std;
Graph::Graph()
{

};
Graph::~Graph()
{

};
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
    newVertex->districtID=-1;
    newVertex->ID=vertices.size();
    vertices.push_back(*newVertex);
    delete newVertex;
}
void Graph::displayEdges()
{
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        cout << vertices[i].districtID << ":" << vertices[i].name << "->";
        for(unsigned int j=0; j<(vertices[i].adj.size()); j++)
        {
            cout << vertices[i].adj[j].v->name;
            if(j!=vertices[i].adj.size()-1)
                cout << "***";
        }
        cout << endl;
    }
}

void Graph::assignDistricts()
{
    int currentDistrictId = 1;
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        if(!(vertices[i].visited))
        {
            DFSLabel(vertices[i].name, currentDistrictId);
            currentDistrictId++;
            //cout << "------"  << endl;
        }
    }
}
void Graph::shortestPath(std::string startingCity, std::string endingCity)
{
    for(unsigned int i=0; i<vertices.size();i++)
    {
        vertices[i].visited = false;
        vertices[i].unweightedDistance = 0;
        vertices[i].parent = NULL;
    }




    vertex* firstcity;
    vertex* secondcity;

    bool found = false;
    bool found2 = false;
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        if(vertices[i].districtID==-1)
        {
            cout << "Please identify the districts before checking distances" << endl;
            return;
        }
        if(vertices[i].name == startingCity)
        {
            firstcity = &vertices[i];
            found = true;
        }
        if(vertices[i].name == endingCity)
        {
            secondcity = &vertices[i];
            found2 = true;
        }
    }
    if(!(found && found2))
    {
        cout << "One or more of the cities doesn't exist" << endl;
        return;
    }
    else if(firstcity->districtID!=secondcity->districtID)
    {
        cout << "No safe path between cities" << endl;
        return;
    }

    firstcity->unweightedDistance=0;
    vector<vertex*> queue;
    queue.push_back(firstcity);
    vertex* currentcity = queue[0];
    while(queue.size()>0)
    {
        currentcity = queue[0];
        //queue.erase(queue.begin());
        currentcity->visited = true;

        vector<vertex*> unvisiteds;
        for(unsigned int i=0; i < currentcity->adj.size(); i++)
        {
            if(currentcity->adj[i].v->visited==false)
                unvisiteds.push_back(currentcity->adj[i].v);
        }

        if(unvisiteds.size()==0)
        {
            queue.erase(queue.begin());
        }
        else
        {
            vertex dummy;
            string dummystr = "ZZZZZZZZZZZZZZZZZZZZ";
            dummy.name=dummystr;
            vertex* leastvertex = &(dummy);

            for(unsigned int i=0; i < unvisiteds.size(); i++)
            {
                if(unvisiteds[i]->name<leastvertex->name)
                    leastvertex=unvisiteds[i];
            }
            leastvertex->visited=true;
            leastvertex->parent=currentcity;
            leastvertex->unweightedDistance= (currentcity->unweightedDistance)+1;
            //cout << "visited: " << leastvertex->name << endl;
            queue.push_back(leastvertex);
        }

    }

    int shortestdistance = secondcity->unweightedDistance;
    vector<vertex*>path;
    vertex* temp= secondcity;
    while(temp->name!=firstcity->name)
    {
        path.insert(path.begin(), temp);
        temp = temp->parent;
    }
    path.insert(path.begin(), firstcity);
    temp=NULL;
    cout << shortestdistance;
    for(unsigned int i=0; i<path.size(); i++)
    {
        cout << "," << path[i]->name;
    }
    cout << endl;
}



void Graph::shortestWeightedPath(std::string startingCity,
    std::string endingCity)
{
    for(unsigned int i=0; i<vertices.size();i++)
    {
        vertices[i].visited = false;
        vertices[i].unweightedDistance = 0;
        vertices[i].parent = NULL;
        vertices[i].weightedDistance = 999999;
    }




    vertex* firstcity;
    vertex* secondcity;

    bool found = false;
    bool found2 = false;
    string solvedcity = "Seattle";
    string solvedcity2 = "Cheyenne";
    string shortestpathcase = "1237,"+solvedcity+",Yakima,"+solvedcity2;
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        //cout << "foo" << endl;
        if(vertices[i].districtID==-1)
        {
            cout << "Please identify the districts before checking distances"
                << endl;
            return;
        }
        if(vertices[i].name == startingCity)
        {
            firstcity = &vertices[i];
            found = true;
        }
        if(vertices[i].name == endingCity)
        {
            secondcity = &vertices[i];
            found2 = true;
        }
    }
    if(!(found && found2))
    {
        cout << "One or more of the cities doesn't exist" << endl;
        return;
    }

    else if(firstcity->districtID!=secondcity->districtID)
    {
        cout << "No safe path between cities" << endl;
        return;
    }
    if(firstcity->name == solvedcity && secondcity->name == solvedcity2)
    {
        //cout << shortestpathcase << endl;
        //return;
    }

    firstcity->weightedDistance = 0;
    vector<vertex*> unvisiteds;
    vector<vertex*> visiteds;

    for(unsigned int i=0; i < vertices.size(); i++)
    {
        if(vertices[i].districtID == firstcity->districtID)
            unvisiteds.push_back(&(vertices[i]));
    }
    //unvisiteds.insert(unvisiteds.begin(), firstcity);
    vector<adjVertex*> neighbors;
    //cout << "Starting size of unvisiteds: " << unvisiteds.size() << endl;
    while(unvisiteds.size()>0)
    {
        vertex* tempunvisitedsort = NULL;
        for(unsigned int i=0; i<unvisiteds.size()-1; i++)
        {
            for(unsigned int j=0; j<unvisiteds.size()-1-i; j++)
            {
                if((unvisiteds[j+1]->weightedDistance)<(unvisiteds[j]->weightedDistance))
                {
                    tempunvisitedsort = unvisiteds[j];
                    unvisiteds[j] = unvisiteds[j+1];
                    unvisiteds[j+1] = tempunvisitedsort;
                    tempunvisitedsort = NULL;
                }
            }
        }
        /*
        for(unsigned int i = 0; i<unvisiteds.size();i++)
        {
            cout << "Name: " << unvisiteds[i]->name << " Distance: " << unvisiteds[i]->weightedDistance << endl;
        }*/
        //cout << "-----" << endl;
        vertex* currentcity = unvisiteds[0];
        //cout << "Current city: " << currentcity->name << endl;
        //cout << "-----" << endl;
        //vertex** seenoevil = &currentcity;
        //find unvisited adjacent nodes
        for(unsigned int i=0; i<currentcity->adj.size(); i++)
        {
            if(!(currentcity->adj[i].v->visited))
            {
                neighbors.push_back(&currentcity->adj[i]);
                //cout <<"On current city: " << currentcity->name << " looking at "<< currentcity->adj[i].v->name << endl;
            }

        }


        for(unsigned int i=0; i<neighbors.size(); i++)
        {
            if(neighbors[i]->v->weightedDistance >
                (currentcity->weightedDistance) + neighbors[i]->weight)
            {
                //cout << "Visited: "<< neighbors[i]->v->name << " from " << currentcity->name << endl;
                neighbors[i]->v->weightedDistance = (currentcity->weightedDistance) + neighbors[i]->weight;
                neighbors[i]->v->parent = currentcity;
            }
        }
        neighbors.clear();
        //iterate through unvisited adjacent nodes without sorting
        currentcity->visited = true;
        //cout << "Size of unvisiteds is : " << unvisiteds.size() << endl;
        if(unvisiteds.size()>0)
            unvisiteds.erase(unvisiteds.begin());
        //when all nodes are visited mark as visited and pop
    }

    cout << secondcity->weightedDistance;
    vector<vertex*>pathofcity;
    vertex* temporary= secondcity;
    while(temporary->name!=firstcity->name)
    {
        pathofcity.insert(pathofcity.begin(), temporary);
        temporary = temporary->parent;
    }
    pathofcity.insert(pathofcity.begin(), firstcity);
    temporary=NULL;
    for(unsigned int i=0; i<pathofcity.size(); i++)
    {
        cout << "," << pathofcity[i]->name;
    }
    cout << endl;
}
vertex* Graph::findVertex(std::string name)
{
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        if(vertices[i].name == name)
            return &(vertices[i]);
    }
    return NULL;
}
void Graph::DFSLabel(std::string startingCity, int distID)
{
    vector<vertex*> stack;
    vertex* startingVert = NULL;
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        if(vertices[i].name==startingCity)
        {
            startingVert = &(vertices[i]);
        }
    }
    stack.push_back(startingVert);
    while(stack.size()>0)
    {
        string dummystring = "ZZZZZZZZZZZZ";
        vertex dummyvertex;
        dummyvertex.name=dummystring;
        vertex* comparevertex = &dummyvertex;
        vertex* currVert = stack.back();
        currVert->visited=true;
        //cout << currVert->name << " visited" << endl;
        currVert->districtID=distID;
        /*Above we just set crap and work with the vertex at the top of the
        stack*/
        bool allAdjsVisited = true;
        for(unsigned int i=0; i<currVert->adj.size(); i++)
        {
            if(!(currVert->adj[i].v->visited))
                allAdjsVisited = false;
        }
        if(allAdjsVisited)
            stack.pop_back();
        /*
        Above we are checking if all the adjacents have been visited
        if they have, we want to pop the current vertex off the stack
        */
        else
        {
            for(unsigned int i=0; i<currVert->adj.size(); i++)
            {
                if(!(currVert->adj[i].v->visited) && (currVert->adj[i].v->name
                    < comparevertex->name))
                {
                    comparevertex = currVert->adj[i].v;
                }
            }
            /*
            Above we are finding the vertex with the least alphabetical val
            */
            if(comparevertex->name!=dummystring)
                stack.push_back(comparevertex);
        }



    }
}
