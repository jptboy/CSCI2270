#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
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
    private:
        Node head;
    public:
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
    while(temp->nextNode!=NULL)//while the memory address of the next node isn't null we set the temp pointer equal to the memory address of the next node
    {
        temp=temp->nextNode;
    }
    temp->nextNode= node;//after the memory address of the next node is null we know that we have reached the end so we set the memory address of the next node equal to the memory address in the argument
}
void LinkedList::traverse()
{
    Node *temp=&head;//set the temp equal to the memory address of the head node at first
    while(temp!=NULL)//while the temp pointer isn't null print the value of each node
    {
        std::cout
            << temp->value
            << std::endl;
        temp=temp->nextNode;//after the value is printed the temp pointer is set to the memory address of the next node
    }
}
int main(int argc, char const *argv[])
{
    Node chicago("chicago",NULL);//make a new node and we dont know the memory address of the next node so we set it equal to NULL
    Node *chicagoptr=  &chicago;
    LinkedList cityList(chicagoptr);//initialize the linked list with this node

    Node atlanta("atlanta",NULL);//insert this node at the end
    cityList.insertNode(&atlanta);
    cityList.traverse();


    return 0;
}
