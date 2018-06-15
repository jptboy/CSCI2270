#include <iostream>
struct Node
{
    Node(){};
    Node(std::string newValue,Node *newNode)
    {
        value=newValue;
        nextNode=newNode;
    }
    std::string value;
    Node *nextNode;
};
class LinkedList
{
    public:
        Node head;
        LinkedList(Node *firstNode);
        void insertNode(Node *node);
        void traverse();
};
LinkedList::LinkedList(Node *newNode)
{
    head=*newNode;
    head.nextNode=NULL;
};
void LinkedList::insertNode(Node *node)
{
    Node *temp=&head;
    while(temp->nextNode!=NULL)
    {
        temp=temp->nextNode;
    }
    temp->nextNode= node;
}
void LinkedList::traverse()
{
    Node *temp=&head;
    while(temp!=NULL)
    {
        std::cout
            << temp->value
            << std::endl;
        temp=temp->nextNode;
    }
}
int main(int argc, char const *argv[])
{
    Node chicago("chicago",NULL);
    Node *chicagoptr=  &chicago;
    LinkedList cityList(chicagoptr);

    Node atlanta("atlanta",NULL);
    cityList.insertNode(&atlanta);
    cityList.traverse();


    return 0;
}
