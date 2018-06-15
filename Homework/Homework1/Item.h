#ifndef ITEM_H
#define ITEM_H
#include <iostream>

struct Item
{
    std::string name;
    std::string state;
    double price;

    
    Item()
    {
        name="NULL";
        state="NULL";
        price=-1; 
    };
    Item(std::string newName,std::string newState,double newPrice)
    {
        name=newName;
        state=newState;
        price=newPrice;
    };
};
#endif //ITEM_H