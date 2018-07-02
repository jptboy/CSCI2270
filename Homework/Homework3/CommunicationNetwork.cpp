#include <iostream>
#include "CommunicationNetwork.h"
#include <sstream>
#include <fstream>
using namespace std;
int splitLine(string line, string *splitLineArrayptr,string **memaddressofptrtoarray, char sep)
{
    stringstream splitter(line);
    string word;
    int arrayitemcount=0;
    int arraysize=2;
    while(getline(splitter,word, sep))
    {
        if(arrayitemcount==arraysize)
        {
            arraysize*=2;
            string *temp=new string[arraysize];
            for(int i=0; i<arraysize;i++)
            {
                temp[i]="NULL";
            }
            for(int i=0; i<arrayitemcount; i++)
            {
                temp[i]=splitLineArrayptr[i];
            }
            delete [] splitLineArrayptr;
            splitLineArrayptr=temp;
            temp=NULL;
        }
        splitLineArrayptr[arrayitemcount++]=word;
    }
    string *correctsizearray=new string[arrayitemcount];
    for(int i=0; i<arrayitemcount; i++)
    {
        correctsizearray[i]=splitLineArrayptr[i];
    }
    delete [] splitLineArrayptr;
    splitLineArrayptr=NULL;
    *memaddressofptrtoarray=correctsizearray;
    return arrayitemcount;
}
CommunicationNetwork::CommunicationNetwork()
{
    head=NULL;
    tail=NULL;
};
CommunicationNetwork::~CommunicationNetwork()
{
    deleteNetwork();//PCOF
};
void CommunicationNetwork::addCity(std::string newCityName, std::string prev)
{
    if(head==NULL && !(prev=="First"))
    {
        cout << "That is not how you properly use a doubly linked list. Make a head first please. It is blasphemous to try to make a tail before a head!" << endl;
        return;
    }
    else if(head==NULL && prev=="First")
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
        City* temp=head;
        while(temp!=NULL && temp->cityName!=prev)
        {
            temp=temp->next;
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
            cout << "Previous City does not exist! New City Not Added!" << endl;
            return;
        }
    }
}
void CommunicationNetwork::buildNetwork()
{
    head=NULL;
    tail=NULL;
    addCity("Los Angeles","First");
    addCity("Phoenix","Los Angeles");
    addCity("Denver","");
    addCity("Dallas","Denver");
    addCity("St. Louis","Dallas");
    addCity("Chicago","");
    addCity("Atlanta","Chicago");
    addCity("Washington, D.C","Atlanta");
    addCity("New York","");
    addCity("Boston","");
}
void CommunicationNetwork::transmitMsg(char* msg)
{
    if(head==NULL)
    {
        cout << "Empty list" << endl;
        return;
    }
    ifstream filein(msg);
    string line;
    string* words = new string[2];
    int wordct=0;
    while(getline(filein,line))
    {
        wordct=splitLine(line,words,&words,' ');
    }
    City* temp=head;

    for(int i=0; i<wordct;i++)
    {
        while(temp!=NULL)
        {
            temp->message=words[i];
            cout<<temp->cityName<<" received "<<temp->message<<endl;
            temp->message="";
            temp=temp->next;
        }
        
        if(tail!=NULL)
        {
            temp=tail->previous;
            while(temp!=NULL)
            {
                temp->message=words[i];
                cout<<temp->cityName<<" received "<<temp->message<<endl;
                temp->message="";
                temp=temp->previous;
            }
        }
    }
        
    
}
void CommunicationNetwork::printNetwork()
{
    

    if(head==NULL)
    {
        cout << "===CURRENT PATH===" << endl; 
        cout << "Network is empty!" << endl;
        cout << "==================" << endl;
        return;
    }
    else if(tail==NULL)
    {
        cout << "===CURRENT PATH===" << endl; 
        cout <<"NULL <- " << head->cityName << " -> " << "NULL" << endl;
        cout << "==================" << endl;
        return;
    }

    cout << "===CURRENT PATH===" << endl; 
    cout<<"NULL <- ";
    
    City* temp=head;
    while(temp->next!=NULL)
    {
        cout << temp->cityName << " <-> ";
        temp=temp->next;
    }
    cout << tail->cityName << " -> ";
    cout << "NULL" << endl; 
    cout << "==================" << endl;
    
    
}
void CommunicationNetwork::deleteCity(std::string name)
{
    City* temp = head;
    while(temp!=NULL && temp->cityName!=name)
    {
        temp=temp->next;
    }
    if(temp==NULL)
    {
        cout << name << " not found" << endl;
    }
    else
    {
        if(temp==head && tail==NULL)
        {
            delete temp;
            head=NULL;
        }
        else if(temp==head)
        {
            temp->next->previous=NULL;
            head=temp->next;
            delete temp;//PCOE
        }
        else if(temp==tail)
        {
            temp->previous->next=NULL;
            tail=temp->previous;
            delete temp;//PCOE
        }
        else
        {
            temp->previous->next=temp->next;
            temp->next->previous=temp->previous;
            delete temp;//PCOE
        }
    }
}
void del(City* node)
{
    if(node==NULL)
        return;
    cout << "deleting " << node->cityName<<endl;
    delete node;
    del(node->next);
}
void CommunicationNetwork::deleteNetwork()
{
    del(head);
    head=NULL;
    tail=NULL;
}
