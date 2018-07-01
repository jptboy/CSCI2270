#include <iostream>
#include "CommunicationNetwork.h"
using namespace std;

CommunicationNetwork::CommunicationNetwork()
{
    head=NULL;
    tail=NULL;
};
CommunicationNetwork::~CommunicationNetwork()
{

};
/*
struct City{
    std::string cityName;
    std::string message;
    City *next;
    City *previous;

    City(){}; // default constructor

    City(std::string initName, City *initNext, City *initPrevious, std::string initMessage)
    {
        cityName = initName;
        next = initNext;
        previous = initPrevious;
        message = initMessage;
    }
};
*/
void CommunicationNetwork::addCity(std::string newCityName, std::string prev)
{
    if(head==NULL)
    {
        City* newCity= new City(newCityName,NULL,NULL,"");
        head=newCity;
        return;
    }
    else if(prev=="First")
    {
        City* newCity= new City(newCityName,head,NULL,"");
        head->previous=newCity;
        head = newCity;
        return;
    }
    else if(prev=="")
    {
        if(tail==NULL)
        {
            City* newCity= new City(newCityName,NULL,head,"");
            head->next=newCity;
            tail = newCity;
            return;
        }
        else if(tail!=NULL)
        {
            City* newCity= new City(newCityName,NULL,tail,"");
            tail->next = newCity;
            tail = newCity;
            return;
        }
    }
    else if(tail!=NULL && tail->cityName==prev)
    {
        
        City* newCity= new City(newCityName,NULL,tail,"");
        tail->next = newCity;
        tail = newCity;
        return;
        
    }
    else if(tail==NULL && head->cityName==prev)
    {
        City* newCity= new City(newCityName,NULL,head,"");
        head->next=newCity;
        tail = newCity;
        return;
    }
    else
    {
        City* temp;
        while(temp!=NULL && temp->cityName!=prev)
        {
            temp=temp->next;
            return;
        }
        if(temp!=NULL)
        {
            City* newCity= new City(newCityName,temp->next,temp,"");
            temp->next->previous=newCity;
            temp->next=newCity;
            return;
        }
        else
        {
            cout << "That city must not exist!" << endl;
            return;
        }
    }
}
void CommunicationNetwork::buildNetwork()
{
    addCity("Los Angeles","First");
    addCity("Phoenix","");
    
    addCity("Denver","");
    addCity("Dallas","");
    addCity("St. Louis","");
    addCity("Chicago","");
    addCity("Atlanta","");
    addCity("Washington, D.C","");
    addCity("New York","");
    addCity("Boston","");
    
}
void CommunicationNetwork::transmitMsg(char * msg)
{

}
void CommunicationNetwork::printNetwork()
{
    cout << "===CURRENT PATH===" << endl; 
    cout<<"NULL <- ";
    
    City* temp=head;
    while(temp->next!=NULL)
    {
        cout << temp->cityName << " <-> ";
        temp=temp->next;
    }
    if(tail!=NULL)
    {
        cout << tail->cityName << " -> ";
    }
    cout << "NULL" << endl; 
    cout << "==================" << endl;
    
}
void CommunicationNetwork::deleteCity(std::string name)
{

}
void CommunicationNetwork::deleteNetwork()
{

}