//
#include <iostream>
#include <windows.h>
#define NUM  20

using namespace std;
int g_Products[NUM];
CRITICAL_SECTION cs;
int g_pNum=0,g_gNum=0;
DWORD WINAPI  producter(LPVOID);
DWORD WINAPI  consumer(LPVOID);


int main()
{
	HANDLE hThread,hThread1;
	DWORD threadID,threadID1;
	InitializeCriticalSection(&cs);
	hThread=CreateThread(NULL,0,producter,NULL,0,&threadID);
	hThread1=CreateThread(NULL,0,consumer,NULL,0,&threadID1);

	getchar();
	DeleteCriticalSection(&cs);
	return 0;
}


DWORD WINAPI  producter(LPVOID p)
{
	while (1)
	{
		Sleep(2000);
		EnterCriticalSection(&cs);
		cout<<"now one product  in "<<g_pNum++<<" dsdsf"<<endl;
		g_pNum=g_pNum%NUM;
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD WINAPI  consumer(LPVOID p)
{
	while (1)
	{
		Sleep(2000);
		EnterCriticalSection(&cs);
		cout<<"\t\t\tnow get one product  from "<<g_gNum++<<" dsdsf"<<endl;
		g_gNum=g_gNum%NUM;
		LeaveCriticalSection(&cs);
	}

	return 0;
}



