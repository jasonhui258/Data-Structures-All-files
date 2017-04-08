//Jason Hui
//Marcel Colvin


// Author Sean Davis
#ifndef defragmenterH
  #define defragmenterH

#include "DefragRunner.h"

class Defragmenter
{
public:
	int* storage;
    Defragmenter(DiskDrive *diskDrive);
    void organizer();
    void preSwap();
    void swap(int location);
    DiskDrive* drive;
    DiskBlock* currentblock;
    DiskBlock* nextblock;
}; // class Defragmenter
#endif
