//Jason Hui Marcel Colvin 
// marcel completed
#include <iostream>
#include "CPUTimer.h"
#include <fstream>
#include "CursorList.h"
#include "LinkedList.h"
#include "QueueAr.h"
#include "SkipList.h"
#include "StackAr.h"
#include "StackLi.h"



vector<CursorNode <int> > cursorSpace(500000);

using namespace std;

int getChoice()
{
	int choice;
	cout<<"\n     ADT Menu"<<endl;
	cout<<"0. Quit\n1. LinkedList\n2. CursorList\n3. StackAr\n4. StackLi\n5. QueueAr\n6. SkipList"<<endl;
	cout<<"Your choice >> ";
	cin>>choice;
	while(choice < 0 || choice > 6)
	{
		cout<<"Your choice is not between 0 and 6.\nPlease try again."<<endl;
		cout<<"\n     ADT Menu"<<endl;
		cout<<"0. Quit\n1. LinkedList\n2. CursorList\n3. StackAr\n4. StackLi\n5. QueueAr\n6. SkipList"<<endl;
		cout<<"Your choice >> ";
		cin>>choice;
	}
	return choice;
}

void RunList(char* filename)
{
	List<int> list;
	ListItr<int> listItr = list.zeroth();
	int value;
	ifstream ifstr(filename);
	char comm, s[512];
	ifstr.getline(s, 512);
	while(ifstr>>comm>>value)
	{
		if(comm == 'i')
		{
			list.insert(value, listItr);
		}
		else
		{
			list.remove(value);
		}
	}

}

void RunCursorList(char* filename)
{
	CursorList<int> list(cursorSpace);
	CursorListItr<int> listItr = list.zeroth();
	int value;
	ifstream ifstr(filename);
	char comm, s[512];
	ifstr.getline(s, 512);
	while(ifstr>>comm>>value)
	{
		if(comm == 'i')
		{
			list.insert(value, listItr);
		}
		else
		{
			list.remove(value);
		}
	}
}

void RunStackAr(char* filename)
{
	StackAr<int> list(500000);
	int value;
	ifstream ifstr(filename);
	char comm, s[512];
	ifstr.getline(s, 512);
	while(ifstr>>comm>>value)
	{
		if(comm == 'i')
		{
			list.push(value);
		}
		else
		{
			list.pop();
		}
	}
}

void RunStackLi(char* filename)
{
	StackLi<int> list;
	int value;
	ifstream ifstr(filename);
	char comm, s[512];
	ifstr.getline(s, 512);
	while(ifstr>>comm>>value)
	{
		if(comm == 'i')
		{
			list.push(value);
		}
		else
		{
			list.pop();
		}
	}
}

void RunQueueAr(char* filename)
{
	Queue<int> list(500000);
	int value;
	ifstream ifstr(filename);
	char comm, s[512];
	ifstr.getline(s, 512);
	while(ifstr>>comm>>value)
	{
		if(comm == 'i')
		{
			list.enqueue(value);
		}
		else
		{
			list.dequeue();
		}
	}
}

void RunSkipList(char* filename)
{
	SkipList<int> list(0,500000);
	int value;
	ifstream ifstr(filename);
	char comm, s[512];
	ifstr.getline(s, 512);
	while(ifstr>>comm>>value)
	{
		if(comm == 'i')
		{
			list.insert(value);
		}
		else
		{
			list.deleteNode(value);
		}
	}
}

int main()
{
	CPUTimer ct;
	int choice;
	char filename[100];
	cout<<"Filename >> ";
	cin.getline(filename, 100);
	do
	{
		choice = getChoice();
		ct.reset();
		switch(choice)
		{
			case 1:
				RunList(filename); break;
			case 2:
				RunCursorList(filename); break;
			case 3:
				RunStackAr(filename); break;
			case 4:
				RunStackLi(filename); break;
			case 5:
				RunQueueAr(filename); break;
			case 6:
				RunSkipList(filename); break;
		}
		cout<<"CPU time: "<< ct.cur_CPUTime()<< endl;
	} while(choice > 0);
}


