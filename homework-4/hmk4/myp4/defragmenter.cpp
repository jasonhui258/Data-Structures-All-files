//Jason Hui Marcel Colvin


//so it takes in a deframenter type
// this should run the deframenter thingy,
//taking a Diskdrive type


//this is the defragmente


#include "defragmenter.h"
#include "mynew.h"

class TERRIBLE
{
public:
    int originalposition;
    int DEST;
};


int Defragmenter::ilivehere(DiskBlock* findmeblock, DiskDrive* disk)
{  int atthisarray;
    DiskBlock *compareblock;
    DiskBlock *beforecompare;
    int firstpoint;
    for(int i=0; i<disk->getNumFiles(); i++)
    {
        
        
        for(int j=0; j<disk->directory[i].getSize(); j++)
        {
            if(j==0)
            {
                
            compareblock=disk->readDiskBlock(disk->directory[i].getFirstBlockID());
            firstpoint=disk->directory[i].getFileID();
           
            }
            else
                
            {   beforecompare=compareblock;
                compareblock=disk->readDiskBlock(beforecompare->getNext());
                
                
                
             //   cout<<"hereee"<<firstpoint<<endl;
            }
            
            if(compareblock->getFileBlockNum()==findmeblock->getFileBlockNum() && compareblock->getNext()==findmeblock->getNext())
            {
             //   cout<<"                                       file directory parent is " <<firstpoint<<" "<<i<<endl;
                atthisarray=i;
                break;
            }
        }
    }
            
    
    return atthisarray;
}

int Defragmenter::igoherearray( int start, int currentswap , DiskDrive* diskDrive, DiskBlock* seeker  )
{
int leftalready=currentswap;
//int starter=start;
//DiskBlock* seeker=seek;
bool outofthisworld=false;
int posfromstart=2;
if(start==1)
{
    for(int j=0; j<diskDrive->getNumFiles(); j++)
    {//for j start
        if(outofthisworld==true)
        {break;}
                 if(j!=0)
                {
                            posfromstart+=diskDrive->directory[j-1].getSize();
                            cout<<"get size is "<<diskDrive->directory[j-1].getSize()<<endl;
                        }
             for(int k=0; k<diskDrive->directory[j].getSize(); k++)
            {
                
                if(k==0)
                {
                    seeker=diskDrive->readDiskBlock(diskDrive->directory[j].getFirstBlockID());
                    cout<<"starter seeker: "<<seeker->FILENAME()<<"_"<<seeker->getFileBlockNum()<<"_"<<seeker->getNext()<<endl;
                    DiskBlock* seeker2=diskDrive->readDiskBlock(seeker->getNext());
                    //  cout<<"starter second: "<<seeker2->FILENAME()<<"_"<<seeker2->getFileBlockNum()<<"_"<<seeker2->getNext()<<endl;
                  
                 if(diskDrive->directory[j].getFirstBlockID()==leftalready)
                  {   seeker=diskDrive->readDiskBlock(diskDrive->directory[j].getFirstBlockID());
                      outofthisworld=true;
                      break;
                  }
                }
                
                
                seeker=diskDrive->readDiskBlock(seeker->getNext());
                cout<<"seeker get's next is "<<seeker->FILENAME()<<"_"<<seeker->getFileBlockNum()<<"_"<<seeker->getNext()<<endl;
                if(seeker->getNext()==leftalready)
                {
                    posfromstart+=seeker->getFileBlockNum();
                    cout<<" &&&&&&&&&&&&&&&&&&&&&&&&&&&matches, belongs at "<<posfromstart<<endl;//correct
                    outofthisworld=true;
                    break;
                }
                
            }
         }//for j end
}
else
    if(start==0)
    {
        posfromstart=2;
    }
return posfromstart;
}//end where I SHOULD BE in array function




DiskBlock* Defragmenter::SWAPKING(int *storage, DiskDrive* diskDrive, int current, int total)
{
    int static danceoff=0;
 //int wheretogo=storage[currentarray];
    
    int currentarray=current;
 
  if(storage[currentarray]==0)
  { currentarray=2;

      while(storage[currentarray]==0)
      {
          currentarray+=1;
      //    cout<<"looking: "<<currentarray<<" "<<storage[currentarray]<<endl;
          
      }
    }
    
    
    int wheretogo=storage[currentarray];

    DiskBlock* Blockone= diskDrive->readDiskBlock(currentarray);
    //DiskBlock* Native= diskDrive->readDiskBlock(wheretogo);
    
   // cout<< currentarray<<" Blockone"<<Blockone->FILENAME()<<" "<<Blockone->getFileBlockNum()<<" "<<Blockone->getNext();
   // cout<<"going here:"<< wheretogo<<endl;
    
    
    storage[currentarray]=0;
    danceoff++;
    int totalfiles=total;
    if(danceoff!= totalfiles)
    {
        
        SWAPKING(storage, diskDrive, wheretogo,totalfiles);
    }
    
 //   DiskBlock* zeroblock=readDiskBlock(0);
    //storage[currentarray]=0;
    diskDrive->writeDiskBlock(Blockone, wheretogo);
    delete Blockone;
    
    

}







Defragmenter::Defragmenter(DiskDrive *diskDrive)
{
    
   
    
int capsize=diskDrive->getCapacity();
    
    int blockstart=0;
    int numberoffiles=diskDrive->getNumFiles();
    int nextBlocktemp=0;
    static int danceoff=0;
  
 
    
    
    unsigned int total=diskDrive->getCapacity();
    DiskBlock* listofblock[500002];
    int listofzeros[10000];
    int chunks=2;
    int ALLTOTAL=0;
    
    for(int i=0;i<diskDrive->getNumFiles(); i++)
    {
        ALLTOTAL+=diskDrive->directory[i].getSize();
    }
    
    
    int zeros=diskDrive->getCapacity()-2-ALLTOTAL;
    
  // cout<<"ALLTOTAL IS"<<ALLTOTAL<<endl;
    
  //  cout<<"zeros are "<<zeros<<endl;
    
    
    //Zeros CHECK
    int zerocount=0;
    DiskBlock* zerocurrent;
    
    
    for(int i=2; i<diskDrive->getCapacity();i++)
    { //cout<<"here?"<<i<<endl;
        
        zerocurrent=diskDrive->readDiskBlock(i);
        if (zerocurrent->getFileBlockNum()==0)
        {
            listofzeros[zerocount]=i;
            zerocount++;
            cout<< zerocount<<endl;
        }
            
        
    }
    /*
    for(int i=0; i< zeros; i++)
    {
       // cout<<"zerosColected "<<listofzeros[i]<<endl;
    
    }
    */
    ////ZERO's Checker
    DiskBlock* zeroblock=diskDrive->readDiskBlock(1);
    //now to move zeros to end and swap with last two,
    
    int zerosadness=0;
    
    for(int i=diskDrive->getCapacity()-zeros; i<diskDrive->getCapacity(); i++)
    {
        DiskBlock* switchingzero;
       switchingzero= diskDrive->readDiskBlock(i);
        int currentplace;
        int posfromstart=2;
       // cout<<" I being used is : "<<i <<endl;
        
        for(int j=0; j<diskDrive->getNumFiles(); j++)
        {
            if(j!=0)
            {
            posfromstart+=diskDrive->directory[j-1].getSize()-2;
            }
            for(int k=0; k<diskDrive->directory[j].getSize(); k++)
            {
                DiskBlock *poo;
                DiskBlock *prepoo;
                
                if( i==diskDrive->directory[j].getFirstBlockID())
                {
                    diskDrive->directory[j].setFirstBlockID(i);
                    
                    
                }else if(k==0)
                {
                    poo=diskDrive->readDiskBlock(diskDrive->directory[j].getFirstBlockID());
                    prepoo=diskDrive->readDiskBlock(diskDrive->directory[j].getFirstBlockID());
                    
                }
                else
                {
                    prepoo=poo;
                    poo=diskDrive->readDiskBlock(poo->getNext());
                    
                }
                
               // cout<<"poo gets next is "<<poo->getNext()<<endl;
                
                if(poo->getNext()==i)
                {
                   // cout<<"poo "<<i<<endl;
                    DiskBlock* target=diskDrive->readDiskBlock(poo->getNext());
                    
                 //   cout<<"target's currentblk num is "<<target->getFileBlockNum()<<endl;
                    
                   int gohere= listofzeros[zerosadness];
                 //   cout<<" poos set next is =============="<<poo->getNext()<<endl;
                    
                     poo->setNext(gohere);
                 //    cout<<" poos set next is =============="<<poo->getNext()<<endl;
                    diskDrive->writeDiskBlock(target, gohere );
                    
                    
              //      cout<< i <<" "<<poo->FILENAME()<< " "<<poo->getFileBlockNum()<<" "<<poo->getNext()<<endl;
                   
                    posfromstart=prepoo->getNext();
                 //   cout<<"pos from start"<<posfromstart<<endl;
                    diskDrive->writeDiskBlock(poo, posfromstart);
                    zerosadness++;
                }
            }
    
    }
     
        
        
        diskDrive->writeDiskBlock( zeroblock, i);
       // cout<<"writing zeros into i"<<i<<endl;
        
        
    }
    
    
    
    
   
    DiskBlock* printer;
    
    
    int *storage;
    storage=new int[diskDrive->getCapacity()];
   /*
    for(int i=0; i<diskDrive->getCapacity(); i++)
    {
        printer=diskDrive->readDiskBlock(i);
        
        
        
       // cout<< i <<" "<<printer->FILENAME()<< " "<<printer->getFileBlockNum()<<" "<<printer->getNext()<<endl;
        //int parentname=ilivehere(printer);
        
    }
    */
   // cout<<"-------2-2-2-2--23-2-32-32-3-23-23-2-<<"<<endl;
    
    
    
    ////setting first block ID's
    
    
    
    
    
    ////
    
    
    int starterfiles=2;
    int* parentstarters= new int [diskDrive->getNumFiles()];
    
    for(int i=0; i<diskDrive->getNumFiles(); i++)
    {
        if(i==0)
        {
            parentstarters[0]=2;
        }
        if(i!=0)
        {
            starterfiles+=diskDrive->directory[i-1].getSize();
        }
            parentstarters[i]=starterfiles;
        
       
        
        
    }
    
    //printing out parent starters
    for(int i=0; i<diskDrive->getNumFiles(); i++)
    {
       // cout<<" parentstarters"<<i<<" "<<parentstarters[i]<<endl;
    }
    

    
   
    for(int i=2; i<diskDrive->getCapacity(); i++)
    {
        printer=diskDrive->readDiskBlock(i);
        
        
        
      //  cout<< i <<" "<<printer->FILENAME()<< " "<<printer->getFileBlockNum()<<" "<<printer->getNext()<<endl;
      int parentsdirectory= ilivehere(printer,diskDrive); //lets say parents directory is 2
        int posfromstart;
        //diskDrive->directory[parentsdirectory].getSize();
       /* if (parentsdirectory==0)
        {
            posfromstart=2;
        }
        if(parentsdirectory==1)
        {
            posfromstart=9;
        }
        if(parentsdirectory==2)
        {
            posfromstart=15;
        }
        */
        
        
        posfromstart=parentstarters[parentsdirectory];
        
        
       // cout<<" parents directory is:"<<parentsdirectory<<endl;
        storage[i]=posfromstart+printer->getFileBlockNum()-1;
       // cout<<"posfromstartis------------>"<<posfromstart+printer->getFileBlockNum()-1<<endl;
        
    }
    for(int i=0; i<diskDrive->getCapacity(); i++)
    {
       // cout<<i<<" "<<storage[i]<<endl;
    }
    
    

    
     SWAPKING(storage, diskDrive, 15, diskDrive->getCapacity()-zeros);
    
    
    
    int starterfilesID=2;
    for(int i=0; i<diskDrive->getNumFiles(); i++)
    {
        if(i!=0)
        starterfilesID+=diskDrive->directory[i-1].getSize();
        
      //  cout<<" i: "<<"starfilestarts at"<< starterfilesID<<endl;
        diskDrive->directory[i].setFirstBlockID(starterfilesID );
        
    }
    
    
    
  /*
    for(int i=0; i<diskDrive->getCapacity(); i++)
    {
        printer=diskDrive->readDiskBlock(i);
        
        
        
       // cout<< i <<" "<<printer->FILENAME()<< " "<<printer->getFileBlockNum()<<" "<<printer->getNext()<<endl;
    }
    
    
    */
    
    
    
    /*
    
    
    for(int i=0; i<diskDrive->getNumFiles();i++) //i counts to 3
    {
        int starter=diskDrive->directory[i].getFirstBlockID();
        int currentname;
        DiskBlock* gettingBlock;
        DiskBlock* beingSwapped;
        DiskBlock* nextBlock;
       
   
        if(i==0)
        {
            chunks=2;
              }
      
        if(i!=0)
        {
            chunks+=diskDrive->directory[i-1].getSize();
  
        }
        
    
        
        for(int j=0; j<diskDrive->directory[i].getSize(); j++) //j goes through each individual files
        {
           
                      if(j==0)
            {
                gettingBlock=diskDrive->readDiskBlock(starter);
            }
            else
            {
                int next;
                int filename;
                
                next=gettingBlock->getNext();
                
                
                //nextBlock=
                gettingBlock=diskDrive->readDiskBlock(gettingBlock->getNext());
            }
           
            listofblock[j+chunks]=gettingBlock;
            
            
         
        }
    }
    
  
    int startfirst=0;
  
       DiskBlock* zeroBock=diskDrive->readDiskBlock(1);
    */
    /*
    for(int y=0; y<zeros; y++)
    {
        diskDrive->writeDiskBlock(zeroBock, diskDrive->getCapacity()-1-y);
        //cout<<" zeros are position: "<<diskDrive->getCapacity()-1-y<<endl;
    }
    */
    
    /*
    for(int l=2; l<diskDrive->getCapacity()-zeros-1; l++)
    {
        
        DiskBlock* printer=listofblock[l];
        //cout<< l <<" "<<printer->FILENAME()<< " "<<printer->getFileBlockNum()<<" "<<printer->getNext()<<endl;
       
             diskDrive->writeDiskBlock(printer, l);
              delete printer;
       // delete listofblock[l];
        
    }
    
        DiskBlock* lastblock=listofblock[diskDrive->getCapacity()-zeros-1];
    diskDrive->writeDiskBlock(lastblock, diskDrive->getCapacity()-zeros-1);
    delete lastblock;

   
    
    startfirst=0;
    
   
    
          for(int i=0; i<diskDrive->getNumFiles();i++)
      {
             if(i==0)
              {
                  startfirst+=2;
              }
              else
              {
                  
                   startfirst+=diskDrive->directory[i-1].getSize();
            }
              
              diskDrive->directory[i].setFirstBlockID(startfirst);
             // cout<<" 1st block id is "<<diskDrive->directory[i].getFirstBlockID()<<endl;
        
      }
    
    delete *listofblock;
     */
    
   }//END INT-MAIN










