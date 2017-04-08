#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int value, int last)
{
  leftSibling->insert(values[0]);

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  values[count - 1] = last;
  if(parent)
    parent->resetMinimum(this);
} // LeafNode::ToLeft()

void LeafNode::addToRight(int value, int last)
{
  rightSibling->insert(last);

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToRight()

void LeafNode::addToThis(int value)
{
  int i;

  for(i = count - 1; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];

  values[i + 1] = value;
  count++;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToThis()


void LeafNode::addValue(int value, int &last)
{
  int i;

  if(value > values[count - 1])
    last = value;
  else
  {
    last = values[count - 1];

    for(i = count - 2; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];
    // i may end up at -1
    values[i + 1] = value;
  }
} // LeafNode:: addValue()


int LeafNode::getMaximum()const
{
  if(count > 0)  // should always be the case
    return values[count - 1];
  else
    return INT_MAX;
} // getMaximum()


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int last;

  if(count < leafSize)
  {
    addToThis(value);
    return NULL;
  } // if room for value

  addValue(value, last);

  if(leftSibling && leftSibling->getCount() < leafSize)
  {
    addToLeft(value, last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < leafSize)
    {
      addToRight(value, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(value, last);
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';

   // cout<<" address is: "<<this;
  cout << endl;
} // LeafNode::print()


LeafNode* LeafNode::remove(int value)
{   // To be written by students
    
  // cout<<" this value to be deleted "<<value<<endl;
   for(int i = 0; i< count; i++)
   {
      if(values[i] == value)
      {
      //    cout<<"found value "<<value<<endl;
        for(int j = i; j < count-1; j++)
        {
          values[j] = values[j+1];
        }
        count--;
       //   cout<<" 18??? "<<value<<endl;
        break;
      }
   }
   int halfleaf = 0;
   if(leafSize %2 == 0)
   {
      halfleaf = leafSize/2;
  //  cout<<"even leaf"<<endl;
   }
   else
   {
      halfleaf = (leafSize/2)+1;
   //   cout<<"odd leaf"<<endl;
   }
    
    
    if(count<halfleaf && !parent)
    {
        //this->remove(value);
    }
    
    else if(count <halfleaf && parent) //less than <= was the old one
      {//
        if(leftSibling != NULL && leftSibling->getCount()-1 >= halfleaf)
        {
         // cout<<"fun 1"<<endl;
          int max = leftSibling->getMaximum();
          ((LeafNode*)leftSibling)->specialDelete(max);
          this->addToThis(max);
          this->parent->resetMinimum(this);
            this->parent->resetMinimum(leftSibling);
             this->parent->resetMinimum(rightSibling);
        }
        else if(leftSibling != NULL && leftSibling->getCount()+count <= leafSize && count!=0)
        {
       // cout<<"fun 2"<<endl;
          for(int i=0; i < count; i++)
          {
            this->addToLeft(values[i], this->getMaximum());
          }
            if(rightSibling!=NULL)
            {
            this->rightSibling->setLeftSibling(leftSibling);
            }
            this->leftSibling->setRightSibling(rightSibling);
            
            this->parent->resetMinimum(leftSibling);
            this->parent->resetMinimum(rightSibling);
      /// cout<<"thethte"<<endl;
            return this;
           // cout<<"thethte"<<endl;
         // this->parent->deleteChild(this);
        //  count = 0;
        }
        else if(rightSibling!=NULL && rightSibling->getCount()-1>=halfleaf)
        {
       // cout<<"fun 3"<<endl;
          int min=rightSibling->getMinimum();
              
          ((LeafNode*)rightSibling)->specialDelete(min);
          this->addToThis(min);
          this->parent->resetMinimum(rightSibling);
            this->parent->resetMinimum(leftSibling);
            this->parent->resetMinimum(rightSibling);
        }//borrow
        else if(rightSibling!=NULL && (rightSibling->getCount()+count)<=leafSize && count!=0)
        {
        // cout<<"fun 4"<<endl;
          for(int i=0; i<count; i++)
          {
             this->addToRight(values[i],this->getMaximum ());
          }
            
          this->parent->resetMinimum(rightSibling);
          this->rightSibling->setLeftSibling(leftSibling);
            if(leftSibling!=NULL)
            {
         this->leftSibling->setRightSibling(rightSibling);
            }
            
            this->parent->resetMinimum(leftSibling);
            this->parent->resetMinimum(rightSibling);
          //   cout<<"thethte right"<<endl;
            
            return this;
            //this->parent->deleteChild(this);
        //  count = 0;
        }//merge
   
        
else if(count==0)
{
   // cout<<"HI"<<endl;
    return this;
    }
          
    
      }
    else if(parent)//parent reset
    {
        parent->resetMinimum(this);
        for(int t=0; t<parent->getCount(); t++)
        {
           // parent->resetMinimum(parent->children[t]);
        }
    }
  // this->parent->updateKeys();
    return NULL;

}  // LeafNode::remove()



void LeafNode::specialDelete(int value)
{
  for(int i = 0; i< count; i++)
  {
    if(values[i] == value)
    {
      for(int j = i; j <count-1; j++)
      {
        values[j] = values[j+1];
      }
      count--;
      break;
    }
  }
}




LeafNode* LeafNode::split(int value, int last)
{
  LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(ptr);

  rightSibling = ptr;

  for(int i = (leafSize + 1) / 2; i < leafSize; i++)
    ptr->values[ptr->count++] = values[i];

  ptr->values[ptr->count++] = last;
  count = (leafSize + 1) / 2;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
  return ptr;
} // LeafNode::split()

