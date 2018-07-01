#include <iostream>
#include <sstream>
#include <fstream>
#include "CommunicationNetwork.h"
using namespace std;



void mainMenu(string filename)
{
    
    string option;
    CommunicationNetwork network;
    while(option!="7")
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
            cout << endl;
            
        }
        else if(option=="2")
        {
            network.printNetwork();
            cout << endl;
        }
        else if(option=="3")
        {
            string msgstr = filename;
            const char* msg = msgstr.c_str();
            network.transmitMsg((char*)msg);
            cout << endl;
        }
        else if(option=="4")
        {
            string cityNewName;
            string cityPreviousName;
            cout << "Enter a city name: " << endl; 
            getline(cin,cityNewName); 
            cout << "Enter a previous city name: " << endl;
            getline(cin,cityPreviousName);

            network.addCity(cityNewName,cityPreviousName);
            cout << endl;
            
        }
        else if(option=="5")
        {
            cout << endl;
            
        }
        else if(option=="6")
        {
            cout << endl;
            
        }
        else if(option=="7")
        {
        }
        else
        {
            cout << "Error please enter a valid option" << endl;
        }
    }

}
int main(int argc, char const *argv[])
{
    mainMenu(argv[1]);




    return 0;
}
