#include "MovieTree.hpp"
#include <iostream>
using namespace std;
MovieTree::MovieTree()
{

};

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
    cout << ranking << " " << title << " " << releaseYear << " " << quantity << endl;
}


void MovieTree::printMovieInventory()
{

}
int MovieTree::countMovieNodes()
{
    return 0;
}
void MovieTree::deleteMovieNode(std::string title)
{

}

void MovieTree::findMovie(std::string title)
{

}
void MovieTree::rentMovie(std::string title)
{

}



void MovieTree::DeleteAll(MovieNodeBST * node)
{

} //use this for the post-order traversal deletion of the tree
void MovieTree::printMovieInventory(MovieNodeBST * node)
{

}
void MovieTree::countMovieNodes(MovieNodeBST *node, int *c)
{

}
MovieNodeBST* MovieTree::searchBST(MovieNodeBST *node, std::string title)
{
    return NULL;
} //use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE
MovieNodeLL* MovieTree::searchLL(MovieNodeLL* head, std::string title)
{
    return NULL;
} //use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
MovieNodeBST* MovieTree::treeMinimum(MovieNodeBST *node)
{
    return NULL;
}  //use this to find the left most leaf node of the BST, you'll need this in the delete function

MovieTree::~MovieTree()
{

};
