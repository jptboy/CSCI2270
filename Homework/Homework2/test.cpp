#include <iostream>
#include <sstream>
using namespace std;
int splitLine(string line, string *splitLineArrayptr,string **memaddressofptrtoarray)
{
    stringstream splitter(line);
    string word;
    int arrayitemcount=0;
    int arraysize=2;
    while(getline(splitter,word,' '))
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
int main(int argc, char const *argv[])
{
    string *splitarray= new string[2];
    string line = "zebras are gay animals";
    int arraysize= splitLine(line,splitarray,&splitarray);
    for(int i=0; i<arraysize;i++)
    {
        cout << splitarray[i] << endl;
    }
    return 0;
}
