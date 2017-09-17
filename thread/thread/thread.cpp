#include <iostream>
#include <windows.h>
using namespace std;
int product_num=0;
CRITICAL_SECTION cs;
DWORD  WINAPI   producer(LPVOID);
DWORD  WINAPI   consumer(LPVOID);


int main()
{
	HANDLE hTread,hTread1;
	DWORD  threadid,threadid1;
	InitializeCriticalSection(&cs);
	hTread=CreateThread(NULL,0,producer,NULL,0,&threadid);
	hTread1=CreateThread(NULL,0,consumer,NULL,0,&threadid1);


	getchar();
	DeleteCriticalSection(&cs);
	return 0;
}


DWORD  WINAPI   producer(LPVOID p)
{
	while(1)
	{
		Sleep(1000);
		EnterCriticalSection(&cs);
		cout<<"1.product is  "<<++product_num<<endl;
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD  WINAPI   consumer(LPVOID p1)
{
	while(1)
	{
		Sleep(1500);
		EnterCriticalSection(&cs);
		cout<<"\t\t 2.product is  "<<--product_num<<endl;
		LeaveCriticalSection(&cs);
	}
	return 0;
}
