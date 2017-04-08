#ifndef _NODE_H_
#define _NODE_H_
#include <cstring>
#include "LinkedList.h"
//
//using namespace std; 
class Node;
class edge
{
	public:
		edge(Node* next, int weight)
		{
			this->next = next;
			this->weight = weight;
		}
		Node* next;
		int weight;
		int flow;
};

class Node
{
	public:
		Node();
		Node(char ID[]);
		Node(Node* n);
    
    
		char ID[16];
    int parentCap; 
    
    
		int numedges;
		bool isTerminal;
		List<edge*> edgelist;
		bool isLast;
		bool visited;
		Node* parent;

};
#endif