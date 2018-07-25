#include <iostream>
#include <fstream>
#include "Graph.h"
#include <sstream>
#include <string>
using namespace std;
int splitLine(string line, string *splitLineArrayptr,string **memaddressofptrtoarray, char sep)//this function is from homework2 and it  is used to split individual lines in a text file
{
    stringstream splitter(line);
    string word= "";
    int arrayitemcount=0;
    int arraysize=2;
    while(getline(splitter,word, sep))
    {
        if(arrayitemcount==arraysize)//we double the array if the number of elements has matched the size
        {
            arraysize*=2;
            string *temp = NULL;
            temp=new string[arraysize];
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
    string *correctsizearray = NULL;
    correctsizearray=new string[arrayitemcount];
    for(int i=0; i<arrayitemcount; i++)
    {
        correctsizearray[i]=splitLineArrayptr[i];
    }
    delete [] splitLineArrayptr;
    splitLineArrayptr=NULL;
    *memaddressofptrtoarray=correctsizearray;//we derefrence the pointer to the array given and set it equal to the new array with exactly the correct number of split words from the line
    return arrayitemcount;
}
void mainMenu(string fileName)
{
    Graph cities;
    ifstream filein(fileName);
    string line;
    for(int i=0;getline(filein,line);i++)
    {
        string *lineholder = NULL;
        lineholder = new string[2];
        int linelength = splitLine(line, lineholder, &lineholder, ',');
        if(i==0)
        {
            for(int j=1;j<linelength;j++)
            {
                cities.addVertex(lineholder[j]);
            }
        }
        else
        {
            for(int j=1; j<linelength; j++)
            {
                if(lineholder[j]!="0" && lineholder[j]!="-1")
                {
                    cities.addEdge(
                        lineholder[0], to_string(j-1), stoi(lineholder[j])
                    );

                }
            }
        }
        delete [] lineholder;
        lineholder = NULL;
    }



    string option="";
    while(option!="3")//infinite loop until option equal to 3 for bringing people back to the menu

    //The contents of this while loop is just the menu stuff and taking user input, nothing special.
    //Just a series of if else if statements over and over until the user presses 3 and quits.

    {
        cout << "======Main Menu======" << endl;
        cout << "1. Print vertices" << endl;
        cout << "2. Vertex adjacent" << endl;
        cout << "3. Quit" << endl;

        getline(cin,option);

        if(option=="1")
        {
            cities.displayEdges();
        }
        else if(option=="2")
        {
            string first;
            string second;

            cout << "Enter first city:" << endl;
            getline(cin,first);
            cout << "Enter second city:" << endl;
            getline(cin,second);
            if(cities.isAdjacent(first, second))
            {
                cout << "True" << endl;
            }
            else
            {
                cout << "False" << endl;
            }
        }
        else if(option=="3")
        {
            cout << "Goodbye!" << endl;
        }
        else
        {
            cout << "Error please enter a valid option!" << endl;
        }

    }
}
int main(int argc, char const *argv[])
{
    if(argc<2)//to prevent errors if less than number of required command line arguments
    {
        cout << "Please give a proper number of arguments! Program will now exit!" << endl;
        return 1;
    }
    mainMenu(argv[1]);
    return 0;
}
