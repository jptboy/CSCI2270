//Ayush Khanal
//Instructor: Godley
//Homework 1: Community Garage Sale
#include <iostream>
#include "CommunicationNetwork.h"
#include <sstream>
#include <fstream>
using namespace std;
int splitLine(string line, string *splitLineArrayptr,string **memaddressofptrtoarray, char sep)//this function is from homework2 and it  is used to split individual lines in a text file
{
    stringstream splitter(line);
    string word;
    int arrayitemcount=0;
    int arraysize=2;
    while(getline(splitter,word, sep))
    {
        if(arrayitemcount==arraysize)//we double the array if the number of elements has matched the size
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
            temp=NULL;//we do t his to not have dangling pointers
        }
        splitLineArrayptr[arrayitemcount++]=word;//otherwise we keep filling it up
    }
    string *correctsizearray=new string[arrayitemcount];
    for(int i=0; i<arrayitemcount; i++)
    {
        correctsizearray[i]=splitLineArrayptr[i];
    }
    delete [] splitLineArrayptr;
    splitLineArrayptr=NULL;
    *memaddressofptrtoarray=correctsizearray;//we derefrence the pointer to the array given and set it equal to the new array with exactly the correct number of split words from the line
    return arrayitemcount;
}
int loadWordArray(string filename,string **array)//this function is also from homework two and its supposed to utlize the splitline function above to split every word in a text file with a certain delimiter into an array and return how many words were split
{
    ifstream filein(filename);
    string line;
    string *splitLineptr=NULL;//variable declarations
    string *allwords=new string[2];
    int allwordsidx=0;
    int allwordssize=2;
    while(getline(filein,line))
    {
        if(line!=" ")
        {
            splitLineptr=new string[2];
            int linelength= splitLine(line,splitLineptr,&splitLineptr,' ');//here we just use a dynamic array again and split line by line from the file unless its empty

            for(int i=0;i<linelength;i++)
            {
                if(allwordsidx==allwordssize)
                {
                    allwordssize*=2;
                    string *temp=new string[allwordssize];
                    for(int i=0;i<allwordssize;i++)
                    {
                        temp[i]="NULL";//I am just filling it up with default values, this is unneccessary
                    }
                    for(int i=0;i<allwordsidx;i++)
                    {
                        temp[i]=allwords[i];
                    }
                    delete [] allwords;//as we do dynamic array filling we have to make sure to delete the old ones to prevent memory leaks
                    allwords=temp;
                    temp=NULL;
                }

                allwords[allwordsidx++]=splitLineptr[i];
            }
        }
    }
    string *correctsizearray=new string[allwordsidx];
    for(int i=0; i<allwordsidx;i++)
    {
        correctsizearray[i]=allwords[i];//here we make the exact size of array neccessary and we are able to do this because we kept track of the exact number of elements
    }
    delete [] allwords;
    allwords=NULL;
    *array = correctsizearray;
    return allwordsidx;
}
CommunicationNetwork::CommunicationNetwork()//when we construct the communication network nothing should be there so the head and the tail are set to NULL
{
    head=NULL;
    tail=NULL;
};
CommunicationNetwork::~CommunicationNetwork()
{
    deleteNetwork();//when we destroy the communication network we should delete all the nodes
};


/*
This was the first function that I actually did instead of build network, and I 
just made calls to this function in build network in order to construct the network and the function is actually pretty complicated.
*/
void CommunicationNetwork::addCity(std::string newCityName, std::string prev)
{
    if(head==NULL && !(prev=="First" || prev==""))//if the linkedlist is empty and you try to add a city and give it a previous city besides first or empty you are doing something wrong and I dont let you do that
    {
        cout << "That is not how you properly use a doubly linked list!\nThere is nothing in it, so how could there be a previous city with the name you just gave?" << endl;
        return;
    }
    else if(head==NULL && (prev=="First" || prev==""))//if the list is empty and you try to add a city and say that the previous city is First or say it is empty then the new head becomes the city you just added
    {
        City* newCity= new City(newCityName,NULL,NULL,"");
        head=newCity;
        return;
    }
    else if(prev=="First")//if the list isnt empty and you say First as the previous city then:
    {
        City* newCity= new City(newCityName,head,NULL,"");//construct your city and set the next to head
        head->previous=newCity;//set the current heads previous pointer to point to the city you just created
        head = newCity;//we set the new head as the new city you just created
        if(tail==NULL)//if you just keep adding cities with First as the previous city, there wasn't any tail and that was causing the bug, so we are just setting the last city to the tail
        {
            City* temp=head;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            tail=temp;
        }
        return;
    }
    else if(prev=="")//if the list isnt empty and you say prev is empty then we add it to the tail
    {
        if(tail==NULL)//if the tail is null then we just add it after the head and set tail to the new city
        {
            City* newCity= new City(newCityName,NULL,head,"");
            head->next=newCity;
            tail = newCity;
            return;
        }
        else if(tail!=NULL)//if the tail isnt null we say that the previous pointer of the newcity is the current tail instead of the head like in the if statement above
        {
            City* newCity= new City(newCityName,NULL,tail,"");
            tail->next = newCity;
            tail = newCity;
            return;
        }
    }
    else if(tail!=NULL && tail->cityName==prev)//if the tail isnt null and its cityname is prev then we just add at the tail
    {
        
        City* newCity= new City(newCityName,NULL,tail,"");
        tail->next = newCity;
        tail = newCity;
        return;
        
    }
    else if(tail==NULL && head->cityName==prev)//if there is only one thing in the linkedlist then we need to do some stuff to add at the tail because there is no tail
    {
        City* newCity= new City(newCityName,NULL,head,"");//essentially we just make a tail here and set head to point to tail
        head->next=newCity;
        tail = newCity;
        return;
    }
    else//if none of these edge cases happen we find the previous city with the name wanted and add after that
    {
        City* temp=head;
        while(temp!=NULL && temp->cityName!=prev)
        {
            temp=temp->next;
        }
        if(temp!=NULL)//the while loop stops when the previous city is found or temp==NULL and we only want to add if temp!= NULL because if temp==NULL here it means that the previous city doesnt exist
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
    //when we build a new network we want to set head and tail to NULL and we just fill up the network with addCity
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
    printNetwork();
}
void CommunicationNetwork::transmitMsg(char* msg)
{
    if(head==NULL)
    {
        cout << "Empty list" << endl;
        return;
    }
    string* words = new string[2];
    int wordct=loadWordArray(msg,&words);//here we split all of the words in the file into a dynamic array by calling the loadWordArray function and we get the number of words that we split
    City* temp=head;

    for(int i=0; i<wordct;i++)//for each word in the array that we split we relay it across the whole network back and forth
    {
        while(temp!=NULL)//we go forward in this while loop until we reach NULL
        {
            temp->message=words[i];
            cout<<temp->cityName<<" received "<<temp->message<<endl;
            temp->message="";
            temp=temp->next;
        }
        
        if(tail!=NULL)//we only go backwards if there is more than one city
        {
            temp=tail->previous;
            while(temp!=NULL)
            {
                temp->message=words[i];
                cout<<temp->cityName<<" received "<<temp->message<<endl;//we print out everything in a backwards order until temp equals null again
                temp->message="";
                temp=temp->previous;
            }
        }
    }
        
    
}
void CommunicationNetwork::printNetwork()
{
    

    if(head==NULL)//edge case of a empty network
    {
        cout << "===CURRENT PATH===" << endl; 
        cout << "Network is empty!" << endl;
        cout << "==================" << endl;
        return;
    }
    else if(tail==NULL)//edge case of a network with only one thing in it
    {
        cout << "===CURRENT PATH===" << endl; 
        cout <<"NULL <- " << head->cityName << " -> " << "NULL" << endl;
        cout << "==================" << endl;
        return;
    }

    cout << "===CURRENT PATH===" << endl; 
    cout<<"NULL <- ";
    
    City* temp=head;
    while(temp->next!=NULL)//printing out a normal network
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
        temp=temp->next;//we try to find the city that was given to delete and if we cant find it and temp ends up equaling NULL we cout not found
    }
    if(temp==NULL)
    {
        cout << name << " not found" << endl;
    }
    else
    {
        if(temp==head && tail==NULL)//edge case of deleting the head when there is only one thing
        {
            delete temp;
            head=NULL;
        }
        else if(temp==head)//edge case of deleting the head when there is more than one thing
        {
            temp->next->previous=NULL;//we are just trying to make the next thing the head
            head=temp->next;
            delete temp;//PCOE
        }
        else if(temp==tail)//edge case of deleting the tail
        {
            temp->previous->next=NULL;//we are just trying to make the previous thing the tail
            tail=temp->previous;
            delete temp;//PCOE
        }
        else
        {
            temp->previous->next=temp->next;//if we are trying to delete a city normally we  have to do the pointer stuff correctly and set the previouses next to the current next
            temp->next->previous=temp->previous;//set the current nexts previous to the current previous
            delete temp;//and t hen finally delete the node
        }
    }
}
void del(City* node)//I made a recursive helper function to help delete nodes
{
    if(node==NULL)//we stop recursion when the node given is NULL
        return;
    cout << "deleting " << node->cityName<<endl;
    delete node;//we delete the node given
    del(node->next);//we recurse
}
void CommunicationNetwork::deleteNetwork()
{
    del(head);//delete network just relies on the del(City*) helpher function to delete and free all the memory and then it sets the head and the tail pointers to NULL
    head=NULL;
    tail=NULL;
}
