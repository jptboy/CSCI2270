//Ayush Khanal
//Instructor: Godley
//Homework 1: Community Garage Sale
#include <iostream>
#include <sstream>
#include <fstream>
#include "CommunicationNetwork.h"
using namespace std;



void mainMenu(string filename)
{
    string option;
    CommunicationNetwork network;
    while(option!="7")//infinite loop until option equal to 7 for bringing people back to the menu
    /*
    The contents of this while loop is just the menu stuff and taking user input, nothing special.
    Just a series of if else if statements over and over until the user presses 7 and quits.
    */
    { 
        cout << "======Main Menu======" << endl; 
        cout << "1. Build Network" << endl; 
        cout << "2. Print Network Path" << endl; 
        cout << "3. Transmit Message Coast-To-Coast-To-Coast" << endl; 
        cout << "4. Add City" << endl; 
        cout << "5. Delete City" << endl; 
        cout << "6. Clear Network" << endl; 
        cout << "7. Quit" << endl;
        
        getline(cin,option);

        if(option=="1")
        {
            network.buildNetwork();
            
            
        }
        else if(option=="2")
        {
            network.printNetwork();
            
        }
        else if(option=="3")
        {
            string msgstr = filename;
            const char* msg = msgstr.c_str();
            network.transmitMsg((char*)msg);
            
        }
        else if(option=="4")
        {
            string cityNewName;
            string cityPreviousName;
            cout << "Enter a city name:" << endl; 
            getline(cin,cityNewName); 
            cout << "Enter a previous city name:" << endl;
            getline(cin,cityPreviousName);

            network.addCity(cityNewName,cityPreviousName);
            
            
        }
        else if(option=="5")
        {
            string citytodel;
            cout << "Enter a city name:" << endl;
            getline(cin,citytodel);
            network.deleteCity(citytodel);
            
        }
        else if(option=="6")
        {
            network.deleteNetwork();
            
        }
        else if(option=="7")
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
        exit(0);
    }
    mainMenu(argv[1]);
    return 0;
}
