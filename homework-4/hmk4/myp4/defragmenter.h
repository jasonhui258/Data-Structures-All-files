
//Jason Hui
//Marcel Colvin 
// Author Sean Davis

#ifndef defragmenterH
  #define defragmenterH


#include "DefragRunner.h"


class infoWhere
{
public:
    
    infoWhere(int p, int I)
    {
        parentname=p;
        ishouldbe=I;
    }
    infoWhere()
    {
        
    }
    int parentname;
    int ishouldbe;
    
};


class Defragmenter
{
public:
 // Defragmenter(DiskDrive *diskDrive){}
    Defragmenter(DiskDrive *diskDrive);
   infoWhere whereIBelong(DiskDrive *dDrive, unsigned int swapinto,int *GroupName, int *FoundPosition);
   // void swapBlock(DiskBlock *firstBlock, DiskBlock *secondBlock );
    DiskBlock* SWAPKING(int *storage, DiskDrive*, int currentarray,int total);
    int ilivehere(DiskBlock* findmeblock, DiskDrive* disk);//returns parents name;
    int igoherearray(int start, int currentswap,DiskDrive* diskDrive, DiskBlock* seek);
}; // class Defragmenter
#endif

