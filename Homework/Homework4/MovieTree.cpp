#include "MovieTree.hpp"
#include <iostream>
using namespace std;
MovieTree::MovieTree()
{
    root=NULL;
};

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
    if(root==NULL)
    {
        root = new MovieNodeBST(title[0]);
        root->head = new MovieNodeLL(ranking,title,releaseYear,quantity);
        return;
    }
    MovieNodeBST* temp = NULL;
    temp = root;
    while(1)
    {
        if(title[0] < temp->letter)
        {
            if(temp->leftChild==NULL)
            {
                temp->leftChild = new MovieNodeBST(title[0]);
                temp->leftChild->head = new MovieNodeLL(ranking,title,releaseYear,quantity);
                break;
            }
            temp = temp->leftChild;
        }
        else if(title[0] > temp->letter)
        {
            if(temp->rightChild==NULL)
            {
                temp->rightChild = new MovieNodeBST(title[0]);
                temp->rightChild->head = new MovieNodeLL(ranking,title,releaseYear,quantity);
                break;
            }
            temp = temp->rightChild;
        }
        else if(temp->letter==title[0])
        {
            //!PCOME: Inserting into a sorted linkedList will probably be the cause of many bugs
            if(temp->head==NULL)
            {
                temp->head = new MovieNodeLL(ranking,title,releaseYear,quantity);
                break;//or return
            }
            else if(temp->head->title>title)
            {
                MovieNodeLL* temp3 = new MovieNodeLL(ranking,title,releaseYear,quantity);
                temp3->next= temp->head;
                temp->head = temp3;
                break;
            }
            MovieNodeLL* tempLLNode = NULL;
            tempLLNode = temp->head;

            while(tempLLNode->next!=NULL && tempLLNode->next->title<title)
            {
                tempLLNode=tempLLNode->next;
                //cout << tempLLNode->title << endl;
            }
            if(tempLLNode->next==NULL)
            {
                tempLLNode->next = new MovieNodeLL(ranking,title,releaseYear,quantity);
                break;
            }
            else
            {
                MovieNodeLL* temp4 = NULL;
                temp4 = tempLLNode->next;
                tempLLNode->next = new MovieNodeLL(ranking,title,releaseYear,quantity);
                tempLLNode->next->next=temp4;
                break;
            }

        }
        else
        {
            cout << "Horrible Error! " << endl;
        }
    }
}


void MovieTree::printMovieInventory()
{
    printMovieInventory(root);
}
int MovieTree::countMovieNodes()
{
    int count=0;
    countMovieNodes(root,&count);
    return count;
}

MovieNodeBST* treeMin(MovieNodeBST* node)
{
    while(node->leftChild!=NULL)
        node = node->leftChild;
    return node;
}
MovieNodeBST* deleteBSTNodeHelper(MovieNodeBST* node, char letter)
{
    if(node==NULL)
        return node;
    else if(letter<node->letter)
    {
        node->leftChild = deleteBSTNodeHelper(node->leftChild, letter);
    }
    else if(letter > node->letter)
    {

        node->rightChild = deleteBSTNodeHelper(node->rightChild, letter);
    }
    else
    {
        if(node->leftChild == NULL && node->rightChild == NULL)
        {
            delete node;
            node = NULL;
        }
        else if(node->leftChild == NULL)
        {
            MovieNodeBST* tempDel = node;
            node = node->rightChild;
            delete tempDel;
            tempDel = NULL;
        }
        else if(node->rightChild == NULL)
        {
            MovieNodeBST* tempDel = node;
            node = node->leftChild;
            delete tempDel;
            tempDel = NULL;
        }
        else
        {
            MovieNodeBST* tempDel = treeMin(node->rightChild);
            node->letter = tempDel->letter;
            node->head = tempDel->head;
            node->rightChild = deleteBSTNodeHelper(node->rightChild, tempDel->letter);
        }
    }
    return node;
}
void MovieTree::deleteMovieNode(std::string title)
{
    MovieNodeBST* temp = NULL;
    temp = searchBST(root, title);
    if(temp==NULL)
    {
        cout << "Movie not found." << endl;
        return;
    }
    if(temp->head==NULL)
    {
        cout << "Horrible Error" << endl;
        return;
    }

    if(temp->head->title==title && temp->head->next==NULL)
    {
        delete temp->head;
        temp->head = NULL;


        root = deleteBSTNodeHelper(root, title[0]);
        return;
    }
    else if(temp->head->title==title && temp->head->next!=NULL)
    {
        MovieNodeLL* headReplace = NULL;
        headReplace = temp->head->next;
        delete temp->head;
        temp->head = headReplace;
        return;
    }

    MovieNodeLL* tempLL = NULL;
    tempLL = temp->head;

    while(tempLL->next!=NULL && tempLL->next->title!=title)
    {
        tempLL=tempLL->next;
    }

    if(tempLL->next==NULL)
    {
        cout << "Movie not found." << endl;
        return;
    }
    else
    {
        MovieNodeLL* phony = NULL;
        phony = tempLL->next->next;
        delete tempLL->next;//PCOF
        tempLL->next = phony;
        return;
    }
}

void MovieTree::findMovie(std::string title)
{
    //check bst for letter
    MovieNodeBST* checkBST = NULL;
    checkBST = searchBST(root, title);

    if(checkBST==NULL)
    {
        cout << "Movie not found." << endl;
        return;
    }
    if(checkBST->head==NULL)
    {
        cout << "Horrible Error" << endl;
        return;
    }
    MovieNodeLL* foundMovie = NULL;
    foundMovie = searchLL(checkBST->head, title);
    if(foundMovie==NULL)
    {
        cout << "Movie not found." << endl;
        return;
    }
    cout << "Movie Info:" << endl;
    cout << "===========" << endl;
    cout << "Ranking:" << foundMovie->ranking << endl;
    cout << "Title:" << foundMovie->title << endl;
    cout << "Year:" << foundMovie->year << endl;
    cout << "Quantity:" << foundMovie->quantity << endl;
    return;
    //otherwise check the linkedlist for that specific movies
    //if linkedlist search comes back NULL return

    //otherwise derefrence the pointer returned and yeah
}
void MovieTree::rentMovie(std::string title)
{
    MovieNodeBST* checkBST = NULL;
    checkBST = searchBST(root, title);

    if(checkBST==NULL)
    {
        cout << "Movie not found." << endl;
        return;
    }
    if(checkBST->head==NULL)
    {
        cout << "Horrible Error" << endl;
        return;
    }
    MovieNodeLL* foundMovie = NULL;
    foundMovie = searchLL(checkBST->head, title);
    if(foundMovie==NULL)
    {
        cout << "Movie not found." << endl;
        return;
    }

    foundMovie->quantity=((foundMovie->quantity) - 1);

    cout << "Movie has been rented." << endl;
    cout << "Movie Info:" << endl;
    cout << "===========" << endl;
    cout << "Ranking:" << foundMovie->ranking << endl;
    cout << "Title:" << foundMovie->title << endl;
    cout << "Year:" << foundMovie->year << endl;
    cout << "Quantity:" << foundMovie->quantity << endl;
    if(foundMovie->quantity==0)
    {
        deleteMovieNode(foundMovie->title);
    }
    return;
}
void del(MovieNodeLL* node)
{
    if(node==NULL)
        return;
    cout << "Deleting: " << node->title << endl;
    delete node;
    del(node->next);
}
void MovieTree::DeleteAll(MovieNodeBST * node)
{
    if(node==NULL)
        return;
    DeleteAll(node->leftChild);
    DeleteAll(node->rightChild);
    del(node->head);
    delete node;
    node=NULL;//PCOF
} //use this for the post-order traversal deletion of the tree
void MovieTree::printMovieInventory(MovieNodeBST * node)
{
    if(node==NULL)
        return;
    printMovieInventory(node->leftChild);
    //cout << "------\n";
    //cout <<"Movies with letter: " <<node-> letter << endl;
    if(node->head==NULL)
    {
        cout <<"Error on node: " << node->letter << endl;
    }
    else
    {
        MovieNodeLL* temp = NULL;
        temp = node->head;
        while(temp!=NULL)
        {
            cout <<"Movie: " <<temp->title <<" " << temp->quantity << endl;
            temp=temp->next;
        }
    }
    printMovieInventory(node->rightChild);

}
void countLL(MovieNodeLL* head, int* c)
{
    if(head==NULL)
        return;
    MovieNodeLL* temp = head;
    while(temp!=NULL)
    {
        (*c)++;
        temp=temp->next;
    }
}
void MovieTree::countMovieNodes(MovieNodeBST *node, int *c)
{
    if(node==NULL)
        return;
    countMovieNodes(node->leftChild,c);
    /*cout << "------\n";
    cout <<"Movies with letter: " <<node-> letter << endl;*/
    countLL(node->head, c);
    countMovieNodes(node->rightChild,c);
}
MovieNodeBST* MovieTree::searchBST(MovieNodeBST *node, std::string title)
{
    if(node==NULL)
        return NULL;
    MovieNodeBST* temp = NULL;
    temp = node;
    while(1)
    {
        if(title[0]<temp->letter)
        {
            if(temp->leftChild==NULL)
            {
                return NULL;
            }
            temp = temp->leftChild;
        }
        else if(title[0]>temp->letter)
        {
            if(temp->rightChild==NULL)
            {
                return NULL;
            }
            temp = temp->rightChild;
        }
        else if(title[0]==temp->letter)
        {
            return temp;
        }
    }
} //use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE
MovieNodeLL* MovieTree::searchLL(MovieNodeLL* head, std::string title)
{
    MovieNodeLL* temporary = NULL;
    temporary = head;

    while(temporary!=NULL)
    {
        if(temporary->title==title)
        {
            break;
        }
        temporary=temporary->next;
    }
    return temporary;
} //use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
MovieNodeBST* MovieTree::treeMinimum(MovieNodeBST *node)
{
    return NULL;
}  //use this to find the left most leaf node of the BST, you'll need this in the delete function

MovieTree::~MovieTree()
{
    DeleteAll(root);
    root=NULL;
};
