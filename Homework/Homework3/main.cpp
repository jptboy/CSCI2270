#include <iostream>
#include "CommunicationNetwork.h"
using namespace std;



void mainMenu()
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
        cout << option << endl;

        if(option=="1")
        {
            network.buildNetwork();
            cout << endl;
            
        }
        else if(option=="2")
        {
            network.printNetwork();
            
        }
        else if(option=="3")
        {
            cout << endl;
            
        }
        else if(option=="4")
        {
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
    mainMenu();




    return 0;
}
