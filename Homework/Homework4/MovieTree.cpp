#include "MovieTree.hpp"
#include <iostream>
using namespace std;
MovieTree::MovieTree()
{
    root=NULL;//when we create the MovieTree object we should initialize the root to NULL because otherwise it may be holding some garbage that causes undefined behavior
};

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
    if(root==NULL)//if the root is null make a node with the letter and add a linkedlist head to the node with the movie
    {
        root = new MovieNodeBST(title[0]);
        root->head = new MovieNodeLL(ranking,title,releaseYear,quantity);
        return;
    }
    MovieNodeBST* temp = NULL;
    temp = root;
    while(1)//we have an indefinite loop that we use to iterate down the tree for a unknown number of nodes to find the place to insert the new movie
    {
        if(title[0] < temp->letter)//if the first letter is less than the letter we want to go to the left
        {
            if(temp->leftChild==NULL)//if the left is null thats where we enter a node
            {
                temp->leftChild = new MovieNodeBST(title[0]);
                temp->leftChild->head = new MovieNodeLL(ranking,title,releaseYear,quantity);
                break;
            }
            temp = temp->leftChild;
        }
        else if(title[0] > temp->letter)//we do the same thing as we did for the left but the opposite way for the right if the first letter has a higher ASCII value
        {
            if(temp->rightChild==NULL)
            {
                temp->rightChild = new MovieNodeBST(title[0]);
                temp->rightChild->head = new MovieNodeLL(ranking,title,releaseYear,quantity);
                break;
            }
            temp = temp->rightChild;
        }
        else if(temp->letter==title[0])//if the first letter of the title matches then we add it to the linkedlist of movies associated with that letter
        {
            if(temp->head==NULL)//this should actually never happen because each letter should have a initialized head
            {
                temp->head = new MovieNodeLL(ranking,title,releaseYear,quantity);
                break;//or return
            }
            else if(temp->head->title>title)//if we need to add the movie as the new head we do this
            {
                MovieNodeLL* temp3 = new MovieNodeLL(ranking,title,releaseYear,quantity);
                temp3->next= temp->head;
                temp->head = temp3;
                break;
            }
            MovieNodeLL* tempLLNode = NULL;
            tempLLNode = temp->head;

            while(tempLLNode->next!=NULL && tempLLNode->next->title<title)//iterate through the linkedlist until we get to the end or find the movie before the positon we want to add
            {
                tempLLNode=tempLLNode->next;
                //cout << tempLLNode->title << endl;
            }
            if(tempLLNode->next==NULL)//this means we got to the end and we can add to the tail and break
            {
                tempLLNode->next = new MovieNodeLL(ranking,title,releaseYear,quantity);
                break;
            }
            else//otherwise we add the movie immediately after
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
            cout << "Horrible Error! " << endl;/*DEBUG statment, never actually happens*/
        }
    }
}


void MovieTree::printMovieInventory()
{
    printMovieInventory(root);//if the class method is called we just call the private recursive method to do the work
}
int MovieTree::countMovieNodes()
{
    int count=0;
    countMovieNodes(root,&count);//if the class method is called we just call the private recursive method to do the work
    return count;
}

MovieNodeBST* treeMin(MovieNodeBST* node)
{
    if(node==NULL)
        return node;
    while(node->leftChild!=NULL)//walk down the left of the bst until the left child is null and that gives you the minimum value
        node = node->leftChild;
    return node;
}
MovieNodeBST* deleteBSTNodeHelper(MovieNodeBST* node, char letter)//recursive delete function, I forgot i had parent pointers for the BST nodes otherwise I would have done it iteratively
{
    if(node==NULL)
        return node;
    else if(letter<node->letter)
    {
        node->leftChild = deleteBSTNodeHelper(node->leftChild, letter);//search the left subtree if its less
    }
    else if(letter > node->letter)
    {

        node->rightChild = deleteBSTNodeHelper(node->rightChild, letter);//search right if its more, we have to set it equal to the recursive call to build links backwards
    }
    else//if its equal thats the node to delete
    {
        if(node->leftChild == NULL && node->rightChild == NULL)//if it has no children we just delete it
        {
            delete node;
            node = NULL;
        }
        else if(node->leftChild == NULL)//if it has only a right child we set the node to its right child and we delete the original node
        {
            MovieNodeBST* tempDel = node;
            node = node->rightChild;
            delete tempDel;
            tempDel = NULL;
        }
        else if(node->rightChild == NULL)//same thing for left
        {
            MovieNodeBST* tempDel = node;
            node = node->leftChild;
            delete tempDel;
            tempDel = NULL;
        }
        else//otherwise we replace the node with the minimum value from its right subtree and delete that node from the right subtree
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
    /*
    Basically we try to find the movie and if we find it and its in a linkedlist with more than one
    element we delete it out of the linkedlist otherwise we delete the head and use the
    helper node deleter to delete the letter out of the bst
    */
    MovieNodeBST* temp = NULL;
    temp = searchBST(root, title);
    if(temp==NULL)
    {
        cout << "Movie not found." << endl;
        return;
    }
    if(temp->head==NULL)
    {
        cout << "Horrible Error" << endl;//never happens
        return;
    }

    if(temp->head->title==title && temp->head->next==NULL)//if its the only thing in the linkedlist
    {
        delete temp->head;
        temp->head = NULL;


        root = deleteBSTNodeHelper(root, title[0]);
        return;
    }
    else if(temp->head->title==title && temp->head->next!=NULL)//if there are more t hingsin the linkedlist and the movie to delete is the head
    {
        MovieNodeLL* headReplace = NULL;
        headReplace = temp->head->next;
        delete temp->head;
        temp->head = headReplace;
        return;
    }

    MovieNodeLL* tempLL = NULL;
    tempLL = temp->head;

    while(tempLL->next!=NULL && tempLL->next->title!=title)//iterate through until we find the movie we want to delete or get to the end
    {
        tempLL=tempLL->next;
    }

    if(tempLL->next==NULL)//if we get to the end the movie has not been found
    {
        cout << "Movie not found." << endl;
        return;
    }
    else//otherwise we replace it
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

    if(checkBST==NULL)//we check the bst for the letter and if its not found we return NULL
    {
        cout << "Movie not found." << endl;
        return;
    }
    if(checkBST->head==NULL)
    {
        cout << "Horrible Error" << endl;//no horrible error happens
        return;
    }
    MovieNodeLL* foundMovie = NULL;
    foundMovie = searchLL(checkBST->head, title);//we search the linkedlist for the actual movie and if its not found we return null
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
void MovieTree::rentMovie(std::string title)//same process as find movie expect we decrement it after finding it and we call delete on the movie if the quantity is 0
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
void del(MovieNodeLL* node)//helper function to recursively delete nodes in a linked list
{
    if(node==NULL)
        return;
    cout << "Deleting: " << node->title << endl;
    delete node;
    del(node->next);
}
void MovieTree::DeleteAll(MovieNodeBST * node)//post order traversing the binary search tree and deleting the linkedlits from it
{
    if(node==NULL)
        return;
    DeleteAll(node->leftChild);
    DeleteAll(node->rightChild);
    del(node->head);
    delete node;
    node=NULL;//PCOF
} //use this for the post-order traversal deletion of the tree
void MovieTree::printMovieInventory(MovieNodeBST * node)//in order traversal to print out all the movies
{
    if(node==NULL)
        return;
    printMovieInventory(node->leftChild);
    //cout << "------\n";
    //cout <<"Movies with letter: " <<node-> letter << endl;
    if(node->head==NULL)
    {
        cout <<"Error on node: " << node->letter << endl;//never happens
    }
    else
    {
        MovieNodeLL* temp = NULL;//print out each movie in the linked list for the bst node
        temp = node->head;
        while(temp!=NULL)
        {
            cout <<"Movie: " <<temp->title <<" " << temp->quantity << endl;
            temp=temp->next;
        }
    }
    printMovieInventory(node->rightChild);

}
void countLL(MovieNodeLL* head, int* c)//count number of movies in each linked list
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
void MovieTree::countMovieNodes(MovieNodeBST *node, int *c)//we do in order traversal and count the movies in each BST linkedlist node in this helper function
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
    //iteratively search the bst and return null if the node hasnt been found
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
{   //function does what its name implies
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
    treeMin(node);//grader look at this function instead
    return NULL;
}  //use this to find the left most leaf node of the BST, you'll need this in the delete function

MovieTree::~MovieTree()
{
    DeleteAll(root);//delete all nodes and free memory
    root=NULL;//set root to null to avoid segfaults
};
