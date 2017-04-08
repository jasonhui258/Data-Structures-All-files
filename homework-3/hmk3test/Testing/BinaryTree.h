//Jason Hui
//BinaryTree.h

#include <iostream>

using namespace std;

template <class Object>
class Binary;     // Incomplete declaration.

//;    // Incomplete declaration.

// STICK THIS INTO CPP NOT HERE
template <class Object>
class BinaryNode
{
public:
    BinaryNode( const Object & theElement = Object( ) )
    : element( theElement ) { leftchild=NULL; rightchild=NULL; }
    
    BinaryNode () {leftchild=NULL; rightchild=NULL; } ;
    
    Object element;
   // BinaryNode *next;
    BinaryNode<Object> *leftchild;
    BinaryNode<Object> *rightchild;
    
    //print
    void print(char *x, int count)
    {
        
        /*
        cout<<endl<<endl;
        if(this)
        {
            cout<<" we exist"<<endl;
        }
        
        
        //cannot access left of right check why
        
        if(leftchild==NULL)
        {
            cout<<"left child is null"<<endl;
        }
        else
        {
            cout<<" left is not null"<<endl;
        }
        
        if(rightchild==NULL)
        {
            cout<<"right child is null"<<endl;
        }
        else
        {
            cout<<"right is not null"<<endl;
        }
        
        cout<<"did it print"<<endl;
        */
        
        if(leftchild==NULL && rightchild==NULL)
            {
              
               // cout<<"hit here? "<<endl;
               cout<<element;
            
                for(int i=0; i<count; i++)
                {    //x holds 1s and zeros
                    cout<<x[i];
                    
                }
                cout<<endl;
               
                return;
               
            
        }
       // cout<<" did it even get here"<<endl;
        
        //traversal function
        
        //count is traversal distance,
        //starting at root;
        
        //count++ and then insert the 1 or zero depending on which child
        //this count will be at the end of the leaf, and thats the total distance from the root
        
        
        
        
        if(leftchild!=NULL)
        { //cout<<"get left?"<<endl;
        x[count]='0';
        leftchild->print(x, count+1);
        }
        if(rightchild!=NULL)
        {
            //cout<<"get right?"<<endl;
        x[count]='1';
        rightchild->print(x, count +1);
        }
        
        
    }
    
friend class Binary<Object>;
    //friend class ListItr<Object>;
};


template <class Object>
class Binary
{
public:
    Binary(){};
  
    void merge(){}; //creates parent, sets children to the parent
    
void print()
    {
        char ink[1000];
        root->print(ink, 0);
        
        
    };
    void setroot(){};
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
