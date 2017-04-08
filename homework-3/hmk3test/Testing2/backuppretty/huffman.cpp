//jason hui
//marcel colvin
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
    
   friend ostream& operator<<(ostream& os, const holdstuff& dt)
    {
        os<<dt.letter<<"    "<<dt.count<<" ";
        return os;
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




void outsidemerge(BinaryHeap<holdpoint> *heapmaster,BinaryNode<holdstuff> *left, BinaryNode<holdstuff> *right);

int main(int argc, char *argv[])
{ ifstream filein(argv[1]);
 filein.unsetf(ios_base::skipws);   
    holdstuff pockets[256];
    BinaryHeap<holdpoint> heaping(256);
    BinaryHeap<holdpoint> testheaping(256);
    
    BinaryHeap<holdpoint> heapmin(256);
    BinaryHeap<holdpoint> heapmom(256); //put everyone in heapking go two rounds in testheaping after pairing and print heapking out.
    Binary<holdstuff> oak;
    
    
    int counting=0;
     char test;
    bool founded;
    while(filein)
    {
        filein>>test;


char transfer=test; 


if(test=='\n')
{
cout<<" did it get to endlnes? "<<endl; 
 transfer=' ';

}

        founded=false;
        for(int i=0; i<counting; i++)
        {
            if(pockets[i].letter==transfer)
            {
                pockets[i].count+=1;
                founded=true;
                break;
            }
        }
        if(!founded)
        {
            pockets[counting].letter=transfer;
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
    /*
    for(int i=0; i<counting; i++)
    {
        cout<<testheaping.findMin().superpoint->element.letter<<" "<<testheaping.findMin().superpoint->element.count<<endl;
        testheaping.deleteMin();
        
    }
     */

    
    
    BinaryNode<holdstuff> *firstmin;
    BinaryNode<holdstuff> *secondmin;
   while (!heaping.isEmpty())
    {//while start
        
      
        firstmin=heaping.findMin().superpoint; //first min points to superpoint(Binarynode<holdstuff>) which is inside Holdpoint
        heaping.deleteMin();
        
        if(heaping.isEmpty())
        {
            break;
        }
                       secondmin= heaping.findMin().superpoint;
            heaping.deleteMin();
        
        
            int parentage=0;
            char parentname='Z';
            parentage=firstmin->element.count+ secondmin->element.count;
            BinaryNode<holdstuff> *potato=new BinaryNode<holdstuff>(parentname );
            potato->element.count=parentage;
            holdpoint cabbage(potato);
        
            cabbage.superpoint->leftchild=firstmin;//after getting parent sets left child,
            cabbage.superpoint->rightchild=secondmin;//after getting parent sets the right child;
            //inserting parent back in
            
            heaping.insert(cabbage);
         heapmom.insert(cabbage);
        
        
    }//while end
    
    
    //setting root
    //firstmin contains the only top parent
oak.root=firstmin;
    
   // oak.print();
    
    /*
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
    
    oak.print();
    

    
    
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
