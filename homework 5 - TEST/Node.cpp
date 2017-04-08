#include "Node.h"
#include "LinkedList.h"

using namespace std;  
Node::Node()
{
	strcpy(ID, "");
	isLast = false;
}

Node::Node(char ID[])
{
	strcpy(ID, this->ID);
	isLast = false;
}
Node::Node(Node* n)
{
	strcpy(this->ID, n->ID);
	isLast = false;




//ListItr<edge*> iterman(n->edgelist.header);  

ListItr<edge*> iterman=n->edgelist.zeroth(); 
while(iterman.retrieve()!=NULL)
{
     
 this->edgelist.insert(iterman.retrieve(),iterman);

 iterman.advance(); 
}



/*
for(list<edge*>::iterator itr=n->edgelist.begin(); itr!=n->edgelist.end(); itr++)
{
 this->edgelist.push_back(itr); 
}
*/

}