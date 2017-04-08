//Jason Hui Marcel Colvin
//COMPLETED VERSION! Marcel final tested it. fri jan 15th 336pm
#include <iostream>
#include <fstream>
#include "QueueAr.h"
#include "StackAr.h"


using namespace std;

class Person
{public:
    Person(int rn, char let)
    {
        letter=let;
        rownumber=rn;
    }
    char letter;
    int rownumber;
    char getletter()
    {
        return letter;
    }
    int getrownumber()
    {
        return rownumber;
    }
    
};


enum state

{
    EMPTY, NOT_EMPTY, WAITING_TO_MOVE, LUGGAGE1, LUGGAGE2, FIVE, FOUR, THREE, TWO, ONE  //evnetuallyAC_OUT etc etc

};
enum statechair
{
    ADOWN, BDOWN, CDOWN,HOLE, DDOWN,EDOWN,FDOWN  //evnetuallyAC_OUT etc etc
};

class Rowings
{
public:
    StackAr<Person*> left;
    StackAr<Person*> right;
    Person *aisle; //for person to sit in the aisle when it is waiting to board.
    StackAr<Person*> exchanging;
    int rownumbering;
    state statues;
    statechair chaira,chairb,chairc,chaird,chaire,chairf;
    Rowings(int aislenumber )
    {
        chaira=HOLE,chairb=HOLE,chairc=HOLE,chaird=HOLE,chaire=HOLE,chairf=HOLE;
        left=StackAr<Person*>(3); //try
        right=StackAr<Person*>(3);//so whne youg et frunt it gets the real thing
        exchanging=StackAr<Person*>(3);
        rownumbering=aislenumber;
        statues=EMPTY;
    }
};


int boardplane(ifstream& fileread)
{
    Queue<Person*> Qboard(288);//to pop people into the planes
    Queue<Rowings*> Qplane(48);
    
    int seatnumber;
    char letter;
    int count_empty=0;
    int clock=0;
    Rowings *rowbefore=0;
    ///NUMBERCHANGER ////////////////////////////////////
    for (int i= 0; i <288; i++)  //288//$$$$$$$$$ 1
    {//start file read eof
        fileread>>seatnumber>>letter;
        Person *temp=new Person(seatnumber, letter);
        Qboard.enqueue(temp);
        
    }
    ///NUMBERCHANGER ////////////////////////////////////
    for(int i=48;i>0; i--)//would read 48 first    48//$$$$$$$$$ 2
    {
        Qplane.enqueue( new Rowings(i));
    }
    
    while( 1) //when all rows become empty(the aisle part is empty) and second when the queue is empty so everyone made it to the plane.
    {
        count_empty=0; //starts at zero, and counts through all the rows
        ///NUMBERCHANGER ////////////////////////////////////
for( int i=1; i<=48; i++) //still counts front back to front, 48//$$$$$$$$$ 2.9
        {
            Rowings *rowpoint=Qplane.getFront(); //so get front at the start is 48
            Qplane.dequeue();
        if(rowpoint->statues==EMPTY) //changing states;
            {
                if(rowpoint->rownumbering==1 )
                {
                    if(Qboard.isEmpty()==false) //this is to make sure that the QBoard is completely empty, so it doesn't grab "Empty" people, Dequeue "empty" people
                    {
                        Person *human=Qboard.getFront();
                        Qboard.dequeue();
                        rowpoint->aisle=human;// already stuck him in aisle 1
                        rowpoint->statues=NOT_EMPTY ;//stick human in the aisle   ///////
                    }
                    else
                    {  //when number  1 is empty
                        count_empty++;
                    }
                }
                else//else (rowpoint->rownumbering==1 )
                {
                    count_empty++; //count is added if you are not 1,
                }
            } //do nothing
            
if(rowpoint->statues==NOT_EMPTY)
            {//NOT_EMPTY CHECK FIRST STATUES
                if(rowpoint->aisle->rownumber==rowpoint->rownumbering )
                {//0
                    if(rowpoint->aisle->letter=='A' && rowpoint->chairb==HOLE && rowpoint->chairc==HOLE)
                    {
                        rowpoint->left.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=LUGGAGE1;
                        rowpoint->chaira=ADOWN;
                    }
                    else if(rowpoint->aisle->letter=='A' && rowpoint->chairb==BDOWN && rowpoint->chairc==HOLE)
                    {
                        rowpoint->left.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=THREE;
                        rowpoint->chaira=ADOWN;
                        
                    }
                    else if(rowpoint->aisle->letter=='A' && rowpoint->chairb==BDOWN && rowpoint->chairc==CDOWN)
                    {
                        rowpoint->left.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=FIVE;
                        rowpoint->chaira=ADOWN;
                    }
                    else if(rowpoint->aisle->letter=='A' && rowpoint->chairb==HOLE && rowpoint->chairc==CDOWN)
                    {
                        rowpoint->left.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=THREE;
                        rowpoint->chaira=ADOWN;
                    }
                    else if(rowpoint->aisle->letter=='B' && rowpoint->chaira==HOLE && rowpoint->chairc==HOLE)
                    {
                        rowpoint->left.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=LUGGAGE1;
                        rowpoint->chairb=BDOWN;
                    }
                    else if(rowpoint->aisle->letter=='B' && rowpoint->chaira==ADOWN && rowpoint->chairc==HOLE)
                    {
                        rowpoint->left.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=LUGGAGE1;
                        rowpoint->chairb=BDOWN;
                    }
                    else if(rowpoint->aisle->letter=='B' && rowpoint->chaira==ADOWN && rowpoint->chairc==CDOWN)
                    {
                        rowpoint->left.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=THREE;
                        rowpoint->chairb=BDOWN;
                    }
                    else if(rowpoint->aisle->letter=='B' && rowpoint->chaira==HOLE && rowpoint->chairc==CDOWN)
                    {
                        rowpoint->left.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=THREE;
                        rowpoint->chairb=BDOWN;
                    }
                    else if(rowpoint->aisle->letter=='C' )
                    {
                        rowpoint->left.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=LUGGAGE1;
                        rowpoint->chairc=CDOWN;
                    }
else if(rowpoint->aisle->letter=='F' && rowpoint->chaire==HOLE && rowpoint->chaird==HOLE)///////doing other side now
                    {
                        rowpoint->right.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=LUGGAGE1;
                        rowpoint->chairf=FDOWN;
                    }
                    else if(rowpoint->aisle->letter=='F' && rowpoint->chaire==EDOWN && rowpoint->chaird==HOLE)
                    {
                        rowpoint->right.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=THREE;
                        rowpoint->chairf=FDOWN;
                    }
                    else if(rowpoint->aisle->letter=='F' && rowpoint->chaire==EDOWN && rowpoint->chaird==DDOWN)
                    {
                        rowpoint->right.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=FIVE;
                        rowpoint->chairf=FDOWN;
                    }
                    else if(rowpoint->aisle->letter=='F' && rowpoint->chaire==HOLE && rowpoint->chaird==DDOWN)
                    {
                        rowpoint->right.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=THREE;
                        rowpoint->chairf=FDOWN;
                    }
                    else if(rowpoint->aisle->letter=='E' && rowpoint->chairf==HOLE && rowpoint->chaird==HOLE)
                    {
                        rowpoint->right.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=LUGGAGE1;
                        rowpoint->chaire=EDOWN;
                    }
                    else if(rowpoint->aisle->letter=='E' && rowpoint->chairf==FDOWN && rowpoint->chaird==HOLE)
                    {
                        rowpoint->right.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=LUGGAGE1;
                        rowpoint->chaire=EDOWN;
                    }
                    else if(rowpoint->aisle->letter=='E' && rowpoint->chairf==FDOWN && rowpoint->chaird==DDOWN)
                    {
                        rowpoint->right.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=THREE;
                        rowpoint->chaire=EDOWN;
                    }
                    else if(rowpoint->aisle->letter=='E' && rowpoint->chairf==HOLE && rowpoint->chaird==DDOWN)
                    {
                        rowpoint->right.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=THREE;
                        rowpoint->chaire=EDOWN;
                    }
                else if(rowpoint->aisle->letter=='D' )
                    {
                        rowpoint->right.push(rowpoint->aisle); //.push on to the stack
                        rowpoint->aisle=NULL; //to empty the aisle or say 0
                        rowpoint->statues=LUGGAGE1;
                        rowpoint->chaird=DDOWN;
                    }
    }//0
                
                else if(rowpoint->aisle->rownumber!=rowpoint->rownumbering )
                {
                    if(rowbefore->statues==EMPTY)
                    {
                        rowbefore->aisle=rowpoint->aisle ;
                        rowbefore->statues=NOT_EMPTY;
                        rowpoint->aisle=0; // need to clear it and make it empty, cause you still have his old copy
                        rowpoint->statues=EMPTY;
                    }
                }
                
}//NOT_EMPTY CHECK FIRST
            else if (rowpoint->statues==FIVE)
            {
                rowpoint->statues=FOUR;
            }
            else if (rowpoint->statues==FOUR)
            {
            rowpoint->statues=THREE;
            }
            else if (rowpoint->statues==THREE)
            {
                rowpoint->statues=TWO;
            }
            
            else if (rowpoint->statues==TWO)
            {
            rowpoint->statues=LUGGAGE1;
            }
            else if (rowpoint->statues==ONE)
            {
            rowpoint->statues=LUGGAGE1; // 843pm use to be Luggage 1 now is empty
            }
            else if (rowpoint->statues==LUGGAGE1)
            {
            rowpoint->statues=LUGGAGE2;   //set to empty for now taking l
            }
            else if (rowpoint->statues==LUGGAGE2)
            {
                rowpoint->statues=EMPTY;
            }
            
            rowbefore=rowpoint; //saving current one to the before thingy
            Qplane.enqueue(rowpoint);
    }//end big 48 for looping thru all the rows

        clock++;
///NUMBERCHANGER ////////////////////////////////////
        if (count_empty==48 && Qboard.isEmpty()) //48 //$$$$$$$$$ 3
        {
            break; //or keepgoing=false;
        }
//if soemthing sets keep going false
}
return clock*5;
}//end function

int main(int argc ,char** argv)

{
            ifstream ifstr(argv[1]);
            cout<<"Back to front: "<<boardplane(ifstr)<<endl;
            cout<<"Random: "<<boardplane(ifstr)<<endl;
            cout<<"Outside in: "<<boardplane(ifstr)<<endl;
      //        }//end argc else
}//end int main i think

