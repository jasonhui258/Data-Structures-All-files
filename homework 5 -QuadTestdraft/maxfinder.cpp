// Authors: Marcel Colvin Jason Hui
#include "QuadraticProbing.h"
#include "NetDriver.h"
#include "maxfinder.h"
#include "QueueLL.h"
#include "LinkedList.h"


MaxFinder::MaxFinder(const Computer *computers, int numComputers, int numTerminals) 
{
    Node empty = new Node();
    //hash = new QuadraticHashTable(numComputers);
    graph = new Node*[numComputers];
    /*char temp[16];
    for(int i = 0; i < numComputers; i++)
    {
    	strcpy(temp, computers[i].address);
    	hash->insert(new Node(temp));
    }*/
    
    
    char temp[16];
    
    source=new Node();

 
    
    graphsize = 0;
       	for(int i = 0 ;i<numTerminals; i++)
   	{
//   		strcpy(temp, computers[i].address);
     
   		graph[i] = new Node();

        strcpy(graph[i]->ID,computers[i].address);
      
    
        this->source->edgelist.insert(new edge(graph[i],2147483647), this->source->edgelist.zeroth());
        graphsize++;

        Node* pointing=graph[i];
      this->hash->insert(pointing);
        
        
        //iterman.advance();
   	}

    for(int i = numTerminals; i < numComputers; i++)
    {
//    	strcpy(temp, computers[i+1].address);
    	graph[i] = new Node();

        strcpy(graph[i]->ID,computers[i].address);
    	graphsize++;
         Node* pointing=graph[i];
        this->hash->insert(pointing);
     
    }
    
    graph[numComputers-1]->isLast = true;
    
    //ORange
   Node* pointing= this->hash->find( graph[numComputers-1]->ID );
    pointing->isLast=true;
    
} // MaxFinder()

int MaxFinder::calcMaxFlow(Edge *edges, int numEdges)
{
    
    
    
	Node* source;
	Node* dest;
	for(int i = 0; i < numEdges; i++)
	{
        
        /* Orange
		for(int j = 0; j < graphsize; j++)
		{
            
            //cout<<"grpa"<< graph[j]->ID<<endl;
           
           // cout<<"edges[i].src "<<edges[i].src<<"__ "<<graph[j]->ID<<endl;
            
            
            
			if(strcmp(edges[i].src,graph[j]->ID)==0)
			{
                //cout<<"source exist"<<endl;
				source = graph[j];
                
				break;
               
			}
           
        }
            *///Orange
        
           source= this->hash->find(edges[i].src);
            
            
            
		
        //cout<<"get here?"<<endl;
        /*
		for(int k = 0; k < graphsize; k++)
		{
			if(strcmp(edges[i].dest,graph[k]->ID)==0)
			{
//                cout<<"dest exist"<<endl;
				dest = graph[k];
				break;
			}
         }
            */
        dest=this->hash->find(edges[i].dest);
            
		
        
        
		//ListItr<edge*> iterman=source->edgelist.zeroth();

        
//        cout<<"this121   "<< edges[i].capacity<<" "<<endl;
//        cout<<"source is "<<source->ID<<endl;
//        cout<<"dest is "<<dest->ID<<endl<<endl;
    
		source->edgelist.insert(new edge(dest, edges[i].capacity),source->edgelist.zeroth());
        
		dest->edgelist.insert(new edge(source, 0),  dest->edgelist.zeroth());
        
        
       
		//iterman.advance();
	}
    
    return fordFulkerson();
} // calcMaxFlow()

int MaxFinder::fordFulkerson()
{
	int pathflow = 2147483647;
	int maxflow = 0;
	while(bfs())
	{
		//follow path back, looking for minimum capacity
		Node* u = graph[graphsize-1];
     
        Node* uparent;
		while(u != this->source)
		{
			uparent = u->parent;
           // cout<<"check u id "<<u->ID<<" "<<u->parentCap<<endl;
            if(pathflow > u->parentCap)
                pathflow = u->parentCap;

			u = uparent;
 //cout<<"maxflow "<<pathflow<<endl;
		}
        
        
        //cout<<pathflow<<endl;
		u = graph[graphsize-1];
        
		while(u != this->source)
		{
			uparent = u->parent;
          
            
            for(ListItr<edge*> iterman=uparent->edgelist.first(); !iterman.isPastEnd(); iterman.advance())
            {
                if(strcmp(iterman.retrieve()->next->ID, u->ID) == 0)
                {
                    iterman.retrieve()->weight -= pathflow;
                    break;
                }
            }
            for(ListItr<edge*> iterman=u->edgelist.first(); !iterman.isPastEnd(); iterman.advance())
            {
                if(strcmp(iterman.retrieve()->next->ID,uparent->ID) == 0)
                {
                     iterman.retrieve()->weight += pathflow;
                    break;
                }
            }
    
            u = uparent;
   
        
         }
        
        maxflow += pathflow;


		//goes back subtract from real edge, add to inverse edge

		//give a hash, takes in a node and finds an edge
	}
return maxflow;
}


    
    
    

bool MaxFinder::bfs()
{
    // Create a visited array and mark all vertices as not visited
    for(int i = 0; i < graphsize; i++)
    {
    	graph[i]->visited = false;
        
    }

    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    QueueLL <Node*> q;
    q.enqueue(this->source);
    this->source->visited = true;
    this->source->parent = NULL;

    // Standard BFS Loop
    while (!q.isEmpty())
    {
        Node* u = q.getFront();
        q.dequeue();

     
        for(ListItr<edge*> boy=u->edgelist.first(); !boy.isPastEnd(); boy.advance()){
            if(boy.retrieve()->next->visited ==false && boy.retrieve()->weight > 0)
            {
                q.enqueue(boy.retrieve()->next);
                boy.retrieve()->next->parent = u;
                boy.retrieve()->next->parentCap = boy.retrieve()->weight;
                boy.retrieve()->next->visited = true;
            }
         }
        
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (graph[graphsize-1]->visited == true);
}
