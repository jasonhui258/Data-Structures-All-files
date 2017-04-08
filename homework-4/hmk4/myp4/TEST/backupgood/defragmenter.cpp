
#include "defragmenter.h"
#include "mynew.h"
using namespace std;
Defragmenter::Defragmenter(DiskDrive *diskDrive)
{
	storage= new int[diskDrive->getCapacity()];
	drive = diskDrive;
	for(int i = 0 ; i < drive->getCapacity(); i++)
	{
		drive->FAT[i] = false;
		storage[i] = 0;
	}
	organizer();
	/*for(int i = 0; i < drive->getCapacity(); i++)
	{
		cout<<i<<" "<<storage[i]<<endl;
	}*/
	preSwap();
	for(int i=0; i<drive->getNumFiles();i++)
	{
		drive->directory[i].setFirstBlockID(storage[drive->directory[i].getFirstBlockID()] ); 
	}
	//cout<<"Hi"<<endl;
}

void Defragmenter::organizer()
{   

	DiskBlock* blockone=NULL; 
	int count=2;
	int next;
	for(int i=0; i<drive->getNumFiles(); i++)
	{

		for(int k=0, size = drive->directory[i].getSize(); k < size; k++)
		{

			if(k==0)
			{
				storage[drive->directory[i].getFirstBlockID()]= count;
            	blockone=drive->readDiskBlock(drive->directory[i].getFirstBlockID());
			}
			else
			{
				storage[blockone->getNext()]= count ;
				next = blockone->getNext();
				delete blockone;
				blockone=drive->readDiskBlock(next); 
			}
			count++;
		}
		delete blockone;
	}	  
}

void Defragmenter::preSwap()
{
	for(int i =2; i<drive->getCapacity(); i++)
	{
		//cout<<i<<endl;
		if(drive->FAT[i] == false)
		{
			if(i == storage[i])
			{
				drive->FAT[i] = true;
				continue;
			}
			currentblock = drive->readDiskBlock(i);
			swap(storage[i]);
		}

	}
}

void Defragmenter::swap(int location)
{
	//check if in storage location if it returns a 0
	//cout<<location<<" "<< storage[location]<<endl;
	nextblock = drive->readDiskBlock(location);
	currentblock->setNext(location+1); 
	drive->writeDiskBlock(currentblock, location);
	drive->FAT[location] = true;
	if(nextblock->getNext() == 0)
	{
		//cout<<"does it ever reach here"<<endl;
		delete nextblock;
		delete currentblock;
		return;
	}
	delete currentblock;
	if(drive->FAT[storage[location]])
	{
		delete nextblock;
		return;
	}
	currentblock = nextblock;
	swap(storage[location]);
}








