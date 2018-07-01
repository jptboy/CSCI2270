#include <iostream>
#include "CommunicationNetwork.h"
using namespace std;

CommunicationNetwork::CommunicationNetwork()
{
    
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
    if(head==NULL)//if there is nothing in the linkedlist we always want to do this
    {
        City* newCity=new City(newCityName,NULL,NULL,"NULL");
        head= newCity;
        return;
    }
    else if(prev=="First" && head!=NULL)//if there is something in the linkedlist and we want to replace the first city
    {
        City* newCity=new City(newCityName,head,NULL,"NULL");
        head=newCity;
        return;
    }
    else if(tail==NULL && (prev=="" || prev==head->cityName) && head!=NULL)//if there is one thing in the linkedlist and we want to add to the tail
    {
        City* newCity=new City(newCityName,head,NULL,"NULL");
        tail=newCity;
        return;
    }
    else if(tail!=NULL && head!=NULL)//adding at the tail if there are more than 2 things in the linkedlist
    {
        if(prev==tail->cityName)
        {
            City* newCity=new City(newCityName,tail,NULL,"NULL");
            tail = newCity;
            return;
        }
    }
    else
    {
        City* temp;
        temp=head;

        while(temp->cityName != prev && temp!=NULL)
        {
            temp=temp->next;
        }
        if(temp!=NULL)
        {
            City* newCity=new City(newCityName,temp,temp->next,"NULL");
            temp->next->previous=newCity;
            temp->next=newCity;
            return;
        }
        else
        {
            cout << "Error" << endl;
            return;
        }
            
    }
}
void CommunicationNetwork::buildNetwork()
{
    head=NULL;
    tail=NULL;

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
    
    City* temp=head;
    while(temp!=NULL)
    {
        cout << temp->cityName << endl;
        temp=temp->next;
    }
}
void CommunicationNetwork::transmitMsg(char * msg)
{

}
void CommunicationNetwork::printNetwork()
{
    cout << "===CURRENT PATH===" << endl; 
    cout<<"NULL <-";
    
    City* temp=head;
    while(temp!=NULL)
    {
        cout << temp->cityName << endl;
        temp=temp->next;
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