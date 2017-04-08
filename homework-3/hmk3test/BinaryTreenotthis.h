//Jason Hui
//BinaryTree.h



template <class Object>
class Binary;     // Incomplete declaration.

//;    // Incomplete declaration.

// STICK THIS INTO CPP NOT HERE
template <class Object>
class BinaryNode
{
public:
    BinaryNode( const Object & theElement = Object( ) )
    : element( theElement ) { }
    
    Object element;
   // BinaryNode *next;
    BinaryNode<Object> *leftchild;
    BinaryNode<Object> *rightchild;
    
    friend class Binary<Object>;
    //friend class ListItr<Object>;
};


template <class Object>
class Binary
{
public:
    Binary( );
  
    void merge(){};
    void print(){};
    void setroot(){};
    
private:
    BinaryNode<Object> *root;
};














/*
<template
class BinaryTree
{
 
public:
 
    Node *root;
 
    BinaryTree();
    void insert(string s, Node *noding);//
    void insert(string s); //done          for root insert
    Node *search(string s, Node *noding);//       after root seart
    Node *search (string s); //done            node search root
    
    
    
    
};
void BinaryTree::insert(string s) //root inseart
{
    //maybe root transfer
  //  Node* rooting=root;
    if(root!=NUll)
    {
        insert(s, root);
    }
    else
    {
        root = new Node(s);
        root->leftchild=NULL;
        
        root->rightchild= NULL;
    }
    
}

void BinaryTree::insert(string s, Node *noding)
{
    if( s>= noding->stuff
       )
    {
        if(noding->rightchild != NULL)
        {  insert( s, noding->stuff
                  ); }
        else
        {
            noding->rightchild=new Node(s);
            noding->rightchild->rightchild= NULL;
            noding->rightchild->leftchild= NULL;
        }
        
        
    }
        else if( s < noding->stuff
                )
        {
            insert(s ,noding->stuff);
        }
            
    }
}

Node* BinaryTree::search(string s) //root search
{
    
    return search(s, root);
}





//move toHuffman.cpp
class Node
{
public:
    
    string name;
    int stuff; //stuff is count now
   // int count; // count for
    Node *leftchild;
    Node *rightchild;
    Node(string s)
    {
        stuff=s;
        leftchild=NUll;
        rightchild=NUll;
    }
};

*/
