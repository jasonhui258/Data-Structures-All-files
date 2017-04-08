#include <iostream>
#include <climits>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


BTreeNode* InternalNode::addPtr(BTreeNode *ptr, int pos)
{ // called when original was full, pos is where the node belongs.
  if(pos == internalSize)
    return ptr;

  BTreeNode *last = children[count - 1];

  for(int i = count - 2; i >= pos; i--)
  {
    children[i + 1] = children[i];
    keys[i + 1] = keys[i];
  } // shift things to right to make room for ptr, i can be -1!

  children[pos] = ptr;  // i will end up being the position that it is inserted
  keys[pos] = ptr->getMinimum();
  ptr->setParent(this);
  return last;
} // InternalNode:: addPtr()


void InternalNode::addToLeft(BTreeNode *last)
{
  ((InternalNode*)leftSibling)->insert(children[0]);

  for(int i = 0; i < count - 1; i++)
  {
    children[i] = children[i + 1];
    keys[i] = keys[i + 1];
  }

  children[count - 1] = last;
  keys[count - 1] = last->getMinimum();
  last->setParent(this);
  if(parent)
    parent->resetMinimum(this);
} // InternalNode::ToLeft()


void InternalNode::addToRight(BTreeNode *ptr, BTreeNode *last)
{
  ((InternalNode*) rightSibling)->insert(last);
  if(ptr == children[0] && parent)
    parent->resetMinimum(this);
} // InternalNode::addToRight()



void InternalNode::addToThis(BTreeNode *ptr, int pos)
{  // pos is where the ptr should go, guaranteed count < internalSize at start
  int i;

  for(i = count - 1; i >= pos; i--)
  {
      children[i + 1] = children[i];
      keys[i + 1] = keys[i];
  } // shift to the right to make room at pos

  children[pos] = ptr;
  keys[pos] = ptr->getMinimum();
  count++;
  ptr->setParent(this);

  if(pos == 0 && parent)
    parent->resetMinimum(this);
} // InternalNode::addToThis()



int InternalNode::getMaximum() const
{
  if(count > 0) // should always be the case
    return children[count - 1]->getMaximum();
  else
    return INT_MAX;
}  // getMaximum();


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{  // count must always be >= 2 for an internal node
  int pos; // will be where value belongs

  for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);

  BTreeNode *last, *ptr = children[pos]->insert(value);
  if(!ptr)  // child had room.
    return NULL;

  if(count < internalSize)
  {
    addToThis(ptr, pos + 1);
    return NULL;
  } // if room for value

  last = addPtr(ptr, pos + 1);

  if(leftSibling && leftSibling->getCount() < internalSize)
  {
    addToLeft(last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < internalSize)
    {
      addToRight(ptr, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(last);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  children[0] = oldRoot;
  children[1] = node2;
  keys[0] = oldRoot->getMinimum();
  keys[1] = node2->getMinimum();
  count = 2;
  children[0]->setLeftSibling(NULL);
  children[0]->setRightSibling(children[1]);
  children[1]->setLeftSibling(children[0]);
  children[1]->setRightSibling(NULL);
  oldRoot->setParent(this);
  node2->setParent(this);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *newNode)
{ // called by sibling so either at beginning or end
  int pos;

  if(newNode->getMinimum() <= keys[0]) // from left sibling
    pos = 0;
  else // from right sibling
    pos = count;

  addToThis(newNode, pos);
} // InternalNode::insert(BTreeNode *newNode)


void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


BTreeNode* InternalNode::remove(int value)
{  // to be written by students
  
  //  cout<<" did it even get to internalNOde"<<endl;
BTreeNode *goat=NULL;
    
    
    
    
    

for(int i =count-1; i >=0; i--)
  {
    if(keys[i] <=value)
    {
    goat=children[i]->remove(value);
        
      break;
    }
  }
    
if(goat!=NULL)
    {//0
     //   cout<<"goatin"<<endl;
        removeChild(goat);
        
        if(parent)
        {
            this->parent->resetMinimum(this);
        }
        
        int halfnode;
        
        
        if(internalSize %2 == 0)
        {
            halfnode = internalSize/2;
     //     cout<<"even"<<endl;
        }
        else
        {
            halfnode = (internalSize/2)+1;
      //  cout<<"odd"<<endl;
        }
    
    
        if(this->count ==1 && leftSibling==NULL && rightSibling==NULL)
        {
             //cout<<" happenis?"<<children[0]<<endl<<endl<<endl;
            BTreeNode* tempslap=children[0];
            return tempslap;
        }
        
        else if(count<halfnode)
       {//01
        if(leftSibling != NULL && leftSibling->getCount()-1 >= halfnode)
        {
      //      cout<<" inside 1"<<endl;
           
            BTreeNode* tempnode=  ((InternalNode*)leftSibling)->getChild(leftSibling->getCount()-1);
            
            this->addToThis(tempnode, 0);
           
              ((InternalNode*)leftSibling)->removeChild(tempnode);
              ((InternalNode*)leftSibling)->parent->resetMinimum(leftSibling);
            this->resetMinimum(tempnode);
            
        }
        else if(leftSibling != NULL && leftSibling->getCount()+count <= internalSize && count!=0)
        {
        //   cout<<"inside2"<<endl;
            for(int i=0; i < count; i++)
            {
                this->addToLeft(children[i]);
            }
          leftSibling->setRightSibling(rightSibling);
            if( rightSibling!=NULL)
            {
                rightSibling->setLeftSibling(leftSibling);
            }
            
            
            return this;
            //((InternalNode*)leftSibling)->updateKeys();
           // count = 0;
        }
        else if(rightSibling!=NULL && rightSibling->getCount()-1>=halfnode)
        {
      //     cout<<"inside3"<<endl;
            
            BTreeNode* tempnode=  ((InternalNode*)rightSibling)->getChild(0);
            
            this->addToThis(tempnode, count);
            
           ((InternalNode*)rightSibling)->removeChild(tempnode);
            ((InternalNode*)rightSibling)->parent->resetMinimum(rightSibling);
            
            this->resetMinimum(tempnode);
        }//borrow
        else if(rightSibling!=NULL && (rightSibling->getCount()+count)<=internalSize && count!=0)
        {
         //  cout<<"merge to right inside 4"<<endl;
            for(int i=0; i<count; i++)
            {
                this->addToRight(children[i], this->getChild(0));
            }
            
            this->rightSibling->setLeftSibling(leftSibling);
            if( leftSibling!=NULL)
            {
                leftSibling->setRightSibling(rightSibling);
            }
            
            
            return this;
       
        }//merge

       }//01
      
        
    }//0
    
    this->resetMyself();
    
   
    

    return NULL;
    
    cout<<"end of internal"<<endl;
}//end function

    
    void InternalNode::removeChild(BTreeNode* target)
    {
        for(int i=0; i<count; i++)
        {
            if(children[i]==target)
            {
                for(int k=i; k<count-1; k++)
                {
                    children[k]=children[k+1];
                    keys[k]=keys[k+1];
                }
                count--;
                break;
            }
            
            
        }
    }


    
    BTreeNode* InternalNode::getChild( int hobo)
    {
        
        return children[hobo];
    }
    
    
    
      /*if(count < halfnode) //maybe half node like that?  trying to fix delet 5 and 6
      {
        if(leftSibling != NULL && leftSibling->getCount()-1 >= halfnode)
        {
          cout<<"faggot inside 1"<<endl;
           BTreeNode* max = ((InternalNode*)leftSibling)->children[((InternalNode*)leftSibling)->count-1];
          ((InternalNode*)leftSibling)->specialD(max);
          this->addToThis(max,0);

          this->parent->resetMinimum(this);
        }
        else if(leftSibling != NULL && leftSibling->getCount()+count <= internalSize)
        {
          cout<<"faggot inside2"<<endl;
          for(int i=0; i < count; i++)
          {
            this->addToLeft(children[i]);
          }
          this->parent->deleteChild(this);
            ((InternalNode*)leftSibling)->updateKeys();
          count = 0;
        }
        else if(rightSibling!=NULL && rightSibling->getCount()-1>=halfnode)
        {
          cout<<"faggot inside3"<<endl;
          BTreeNode* min=((InternalNode*)rightSibling)->children[((InternalNode*)rightSibling)->count-1];
              
          ((InternalNode*)rightSibling)->specialD(min);
          this->addToThis(min, count);
          this->parent->resetMinimum(((InternalNode*)rightSibling));
        }//borrow
        else if(rightSibling!=NULL && (rightSibling->getCount()+count)<=internalSize)
        {
          cout<<"faggot inside 4"<<endl;
          for(int i=0; i<count; i++)
          {
             this->addToRight(children[i], children[i]);
          }
          this->parent->resetMinimum(((InternalNode*)rightSibling));
        ((InternalNode*)rightSibling)->updateKeys();
          count = 0;
        }//merge
      }
       
       
  if(this->getCount() == 1 && this->rightSibling == NULL && this->leftSibling == NULL)
  {
    return this->children[0];
  }
    
    updateKeys();
*/
     //  nternalNode::remove(int value)

void InternalNode::specialD(BTreeNode* balls)
{
  for(int i = 0; i< count; i++)
  {
    if(children[i] == balls)
    {
      for(int j = i; j <count-1; j++)
      {
        children[j] = children[j+1];
      }
      count--;
      break;
    }
  }
    
    updateKeys();
}


void InternalNode::resetMyself()
{
    for(int i = 0; i < count; i++)
    {
         keys[i] = children[i]->getMinimum();
    }
}
void InternalNode::resetMinimum(const BTreeNode* child)
{
  for(int i = 0; i < count; i++)
    if(children[i] == child)
    {
      keys[i] = children[i]->getMinimum();
      if(i == 0 && parent)
        parent->resetMinimum(this);
      break;
    }
} // InternalNode::resetMinimum()


InternalNode* InternalNode::split(BTreeNode *last)
{
  InternalNode *newptr = new InternalNode(internalSize, leafSize,
    parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(newptr);

  rightSibling = newptr;

  for(int i = (internalSize + 1) / 2; i < internalSize; i++)
  {
    newptr->children[newptr->count] = children[i];
    newptr->keys[newptr->count++] = keys[i];
    children[i]->setParent(newptr);
  }

  newptr->children[newptr->count] = last;
  newptr->keys[newptr->count++] = last->getMinimum();
  last->setParent(newptr);
  count = (internalSize + 1) / 2;
  return newptr;
} // split()
/*
void InternalNode::deleteChild(BTreeNode* node)
{
  for(int i = 0; i < this->getCount(); i++)
  {
    if(this->children[i] == node)
    {
      cout<<"deleting child"<<endl;
      for(int j = i; j < this->getCount()-1; j++)
      {
        children[j] = children[j+1];
      }
      count--;
      break;
    }
  }

}
*/

void InternalNode::updateKeys()
{
  for(int i =0; i < this->getCount(); i++)
  {
    keys[i] = children[i]->getMinimum();
  }
}
