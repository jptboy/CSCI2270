#include <iostream>
#include <sstream>
#include <fstream>
#include "MovieTree.hpp"
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
void mainMenu(string filename)
{
    MovieTree movies;
    ifstream filein(filename);
    string line="";

    while(getline(filein,line))
    {
        string *lineholder = NULL;
        lineholder = new string[2];
        splitLine(line, lineholder, &lineholder, ',');
        movies.addMovieNode(stoi(lineholder[0]), lineholder[1], stoi(lineholder[2]), stoi(lineholder[3]));
        delete [] lineholder;//PCOF
    }




    string option="";
    while(option!="6")//infinite loop until option equal to 6 for bringing people back to the menu
    /*
    The contents of this while loop is just the menu stuff and taking user input, nothing special.
    Just a series of if else if statements over and over until the user presses 6 and quits.
    */
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Print the inventory" << endl;
        cout << "4. Delete a movie" << endl;
        cout << "5. Count the movies" << endl;
        cout << "6. Quit" << endl;

        getline(cin,option);

        if(option=="1")
        {
            string title="";
            cout << "Enter title:" << endl;
            getline(cin, title);
            movies.findMovie(title);
        }
        else if(option=="2")
        {

        }
        else if(option=="3")
        {
            movies.printMovieInventory();
        }
        else if(option=="4")
        {



        }
        else if(option=="5")
        {


        }
        else if(option=="6")
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
