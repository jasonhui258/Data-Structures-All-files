//jason hui
#include <iostream>
#include <fstream>
#include "BinaryTree.h"
#include "BinaryHeap.h"


using namespace std;
//makes heaps that store holdpoint, and holdpoint stores BinaryNodes of type Hold stuff

//hold-point is to store children versions of BinaryNode-Holdstuff
class holdstuff
{
public:
    int count;
    char letter;
    holdstuff() {};
    holdstuff( char z)
    {
        letter=z;
        count=1;
    };
};




class holdpoint
{
public:
    BinaryNode<holdstuff> *superpoint;
    holdpoint(){};
    holdpoint(BinaryNode<holdstuff> *super )
    {
        superpoint=super;
    };
     friend bool operator<(const holdpoint& left, const holdpoint& right)
    {
       if( left.superpoint->element.count < right.superpoint->element.count)
       {
           return true;
       }else
       {
           return false;
       }
    }
    
    
};

void outsidemerge(BinaryHeap<holdpoint> *heapmaster,BinaryNode<holdstuff> *left, BinaryNode<holdstuff> *right)
{
    int parentage=0;
    char parentname='Z';
    parentage=left->element.count+right->element.count;
    BinaryNode<holdstuff> *cake=new BinaryNode<holdstuff>(parentname );
    cake->element.count=parentage;
    holdpoint transport(cake);
    heapmaster->insert(transport);
                      
                      
}
/*
class holdparent
{
public:
    BinaryNode<holdstuff> *superpoint;
    holdparent(){};
    holdparent(BinaryNode<holdstuff> *super)
    {
        superpoint=super;
    };
    friend bool operator<(const holdparent &left, const holdparent& right)
    {
        if( left.superpoint->element.count < right.superpoint->element.count)
        {
            return true;
        }else
        {
            return false;
        }
    }
    
    
};
void outsidemerge(BinaryHeap<holdparent> *heapmaster,BinaryNode<holdstuff> *left, BinaryNode<holdstuff> *right)
{
    int parentage=0;
    char parentname='Z';
    parentage=left->element.count+right->element.count;
    holdparent
    heapmaster.insert(
    
    
}
                      
*/

void outsidemerge(BinaryHeap<holdpoint> *heapmaster,BinaryNode<holdstuff> *left, BinaryNode<holdstuff> *right);

int main(int argc, char *argv[])
{
    
   
    ifstream filein(argv[1]);
    
    holdstuff pockets[256];
    BinaryHeap<holdpoint> heaping(256);
    BinaryHeap<holdpoint> testheaping(256);
    BinaryHeap<holdpoint> heapmom(256); //put everyone in heapking go two rounds in testheaping after pairing and print heapking out.
    int counting=0;
     char test;
    bool founded;
    while(filein)
    {
        filein>>test;
        
        founded=false;
        for(int i=0; i<counting; i++)
        {
            if(pockets[i].letter==test)
            {
                pockets[i].count+=1;
                founded=true;
                break;
            }
        }
        if(!founded)
        {
            pockets[counting].letter=test;
            pockets[counting].count=1;
            counting++;
        }
        
    }
    
    //this stores all the raw letters into a heap queue thingy,
    for(int i=0; i<counting; i++)
    {
        BinaryNode<holdstuff> *potato=new BinaryNode<holdstuff>(pockets[i] );
        holdpoint cabbage( potato );
        
        heaping.insert(cabbage);
        testheaping.insert(cabbage);
    }
    
    for(int i=0; i<counting; i++)
    {
        cout<<testheaping.findMin().superpoint->element.letter<<" "<<testheaping.findMin().superpoint->element.count<<endl;
        testheaping.deleteMin();
        
    }
  //  cout<<"\n \n \n "<<endl;
    
    //for finding ->two mins, ->merging them creating a parent, -> parentHoldPoint -> ParentholdPoint points to these two children ->
    // ->stick them back in the same queue,
    
   // int twomins=2;
    
    int countshrink=counting;
    int countmom=0;
    
    /*
    for(int i=0; i<countshrink; i++)
    {
        //cout<<"get here"<<endl;
        BinaryNode<holdstuff> *firstmin;
        BinaryNode<holdstuff> *secondmin;
        int twomins=2;
        for(int j=1; j<twomins; j++)
        {
        
        cout<< j <<"....... "<<heaping.findMin().superpoint->element.count<<"....."<<endl;
        firstmin=  heaping.findMin().superpoint; //first min points to superpoint(Binarynode<holdstuff>) which is inside Holdpoint
        heaping.deleteMin();
          twomins++;
            cout<< j <<"....... "<<heaping.findMin().superpoint->element.count<<"....."<<endl;
            secondmin=  heaping.findMin().superpoint; //first min points to superpoint(Binarynode<holdstuff>) which is inside Holdpoint
            heaping.deleteMin();
            twomins--;
            //same stuff as outsidemerge here
            int parentage=0;
            char parentname='Z';
            parentage=firstmin->element.count+ secondmin->element.count;
            BinaryNode<holdstuff> *potato=new BinaryNode<holdstuff>(parentname );
            potato->element.count=parentage;
            
            holdpoint cabbage(potato);
        
            cabbage.superpoint->leftchild=firstmin;//after getting parent sets left child,
            cabbage.superpoint->rightchild=secondmin;//after getting parent sets the right child;
            heapmom.insert(cabbage);
            
            countshrink--;
            countshrink--;
            countmom++;
              //this compasantes for shrinking as the heaping is getting smaller.
            //need to store firstmin and secondmin into special hold
        }
        
        cout<<"min of i:"<<i<<" firstmincount: "<<firstmin->element.count<<" secondmincount: "<<secondmin->element.count<<" "<<endl;
        
        twomins=0;
        
       
    }
    
    
   while(!heapmom.isEmpty())
   {
      // cout<<" here???"<<endl;
    cout<<"heapparent: "<<heapmom.findMin().superpoint->element.letter<<" heapparent count: "<<heapmom.findMin().superpoint->element.count<<" "<<endl;
       cout<<"parent-left: "<<heapmom.findMin().superpoint->leftchild->element.letter<<heapmom.findMin().superpoint->leftchild->element.count<<" ";
   cout<<"parent-right: "<<heapmom.findMin().superpoint->rightchild->element.letter<<heapmom.findMin().superpoint->rightchild->element.count<<" ";
       cout<<endl<<endl;
    heapmom.deleteMin();
   }
    */

    
    
    //while not empty, find two elements
    // merge them together, get their Parent, and add counts together, and then use some letter or number to be the parent as a character
    // create another holdpoint to hold PARENTS
    //and insert that parent back in the binary heap
    //
    /*
   for(int i=0; i<30; i++)
    {
        cout<<" pockets "<< pockets[i].letter<<".,.,"<<pockets[i].count<<endl;
    }
     */
    
    
    
    
    
}//end int main












///
