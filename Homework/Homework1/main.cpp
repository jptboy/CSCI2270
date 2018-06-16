//Ayush Khanal
//Instructor: Godley
//Homework 1: Community Garage Sale
#include <iostream>
#include <fstream>
#include "Item.h"
int Split(std::string s, char a, std::string word[], int size)//split function from cs1300
{
    int ctilchar = 0;//counts the number of chars until the seperator character
    int arrayindex = 0;//keeps position in the string
    int initseprs = 0;// the initial amount of seperators
    int subs = 0;// used to count the number of substrings
    int seprs = 0;// if there is actually a seperator then we increment initseprs by 1 to get seprs otherwise seprs stays 0
    int ctilcharreal = 0;//is used to see if we are at the end of the string 
    
    for(int i=0; i<s.length();i++)
    {
        if(s[i] == a)
        {
            initseprs++;//if there are seperators then increment init seprs by that amount
        }
    }

    if(initseprs > 0)
    {
        seprs = initseprs + 1;//if init seprs is more than 0 than the real amount of seperators needs to be one more than that for my algorithim
    }



    if(initseprs == 0 && s.length() > 0)//if init seprs is 0 and the string has a length then we just put the string into the 0th index of the  array so we return one subsection
    {
        word[0] = s;
        return 1;
    }
    else
    {
        for(int o = 0; o < seprs; o++)//repeat the outer for loop until the number of seperators is reached
        {
                for(int i = arrayindex; i <= s.length(); i++)
                    {
                        if(s[i] != a)
                        {
                            ctilchar++;//if the ith char of the string isnt the seperator increase the count till char value because thats the purpose of that var
                            ctilcharreal++;//we always increase this to determine our position in the string
                        }
                        
                        if(ctilcharreal==s.length())
                        {
                            word[o] = s.substr(arrayindex, ctilcharreal-arrayindex);//if we reach the end of the string then we put whatever was before that into the array
                            subs++;//increment the number of substrings put into the array
                            break;
                        }
                        
                        if(s[i] == a)
                        {
                            word[o] = s.substr(arrayindex, ctilchar);//if the ith character is the seperator then we make whatever was before that a substring and put it into the array
                            subs++;//increment the amount of substrings put into the array
                            arrayindex += ctilchar + 1;//increment this; its like the cutters arm that would hold your arm while the cutters other arm used a sword to cut it idk how else to explain this
                            ctilchar = 0;//reset the counter till the seperator to 0
                            ctilcharreal++;//we always increase this
                            break;
                        }
                    }
        }
    }
    return subs;// return the number of substrings put into the array
}
bool findMatch(Item itemarr[],int arraylength,Item newItem)//this function is used to find if there is a matched item existing in the array
{
    if(newItem.name=="NULL")//if the item given has the name null we dont care about the item so we return false
        return false;

    if(newItem.state==" wanted")//if its wanted we check to see if there is a for sale item that has a lower price than the wanted price and return true
    {
        for(int i=0; i<arraylength;i++)
        {
            if((itemarr[i].name==newItem.name && itemarr[i].price<= newItem.price) && itemarr[i].state!=newItem.state)
            {
                return true;
            }
        }
    }
    else if(newItem.state==" for sale")//we do the same thing as we did for the wanted item in this case except we want the other item to be wanted for higher than the for sale price
    {
       for(int i=0; i<arraylength;i++)
        {
            if(itemarr[i].name==newItem.name && itemarr[i].price>= newItem.price && itemarr[i].state!=newItem.state)
            {
                return true;
            }
        } 
    }
    return false;
       
}
int indexFound(Item itemarr[],int arraylength,Item newItem)//this function does the samething as the match finding function except it returns the index where the match was found in the array rather than a boolean value
{
    int index=-1;
    if(newItem.state==" wanted")
    {
        for(int i=0; i<arraylength;i++)
        {
            if(itemarr[i].name==newItem.name && itemarr[i].price<= newItem.price && itemarr[i].state!=newItem.state)
            {
                 index = i;
                 break;
            }
        }
    }
    else if(newItem.state==" for sale")
    {
       for(int i=0; i<arraylength;i++)
        {
            if(itemarr[i].name==newItem.name && itemarr[i].price>= newItem.price && itemarr[i].state!=newItem.state)
            {
                index=i;
                break;
            }
        } 
    }
    return index;
    
}
int main(int argc, char const *argv[])
{
    std::string fileName=argv[1];
    std::ifstream filein(fileName);//declarations
    std::string line;

    std::string lineholder[3];//array to hold contents of splitted string


    Item allItems[100];
    int allitemsindex=0;
    int itemssold=0;
    int itemsremaining=0;


    /*std::cout
        <<"Items sold: \n";*/

    while(getline(filein,line))
    {
        Split(line,',',lineholder,3);//while we can get a line from the filein filestream we put that line into the line variable and split it

        Item newItem(lineholder[0],lineholder[1],std::stod(lineholder[2]));//we construct a new item from each line of the file
        
        bool found = findMatch(allItems,100,newItem);//we see if the items match was found by calling found match
        if(!found)
        {
            allItems[allitemsindex] = newItem;
            allitemsindex++;//if we did not find the items match we add it to the end of the array
        }
        else if(found)
        {
           int indexfound=indexFound(allItems,100,newItem);
           Item defaultItem;//otherwise we find where the item was found in the array
           itemssold++;
           if(newItem.state==" wanted")//in the next if and else if statement we are just printing the transaction
           {
               std::cout
                    << newItem.name
                    <<" "
                    << allItems[indexfound].price
                    << std::endl;
           }
           else if(newItem.state==" for sale")
           {
               std::cout
                    << newItem.name
                    <<" "
                    << newItem.price
                    << std::endl;
           }
           allItems[indexfound]=defaultItem;//to delete the items match from the array we set that index in the array to the default struct with default values

        }
            

    }
    std::cout
        << itemssold
        << std::endl;
    /*std::cout
        <<"Items remaining in the message board: "
        << std::endl;*/
    for(int i=0; i<100; i++)
    {
        if(allItems[i].name!="NULL")
        {
            if(allItems[i].state==" wanted")
            {
                std::cout
                    <<allItems[i].name
                    <<", "
                    <<"wanted"
                    <<", "
                    <<allItems[i].price
                    <<std::endl;
            }
            else if(allItems[i].state==" for sale")//for loop to print out the remanining items in the message board
            {
                std::cout
                    <<allItems[i].name//we only print out the item if its name is not NULL, doing this allows us to save time complexity by not shifting the array
                    <<", "
                    <<"for sale"
                    <<", "
                    <<allItems[i].price
                    <<std::endl;
            }

            itemsremaining++;
        }

    }
    std::cout
        << itemsremaining
        << std::endl;
    filein.close();
    
    return 0;
}
