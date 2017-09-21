
#include <iostream>
#include<windows.h>
using namespace std;

DWORD WINAPI  FatherThread(LPVOID);
DWORD WINAPI  DaughterThread(LPVOID);
DWORD WINAPI  SonThread(LPVOID);

HANDLE g_Disk,g_Orange,g_Apple;


int main()
{
	g_Disk=CreateSemaphore(NULL,1,1,NULL);
	g_Orange=CreateSemaphore(NULL,0,1,NULL);
	g_Apple=CreateSemaphore(NULL,0,1,NULL);
	const int THREAD_NUM=3;
	HANDLE handle[THREAD_NUM];
	handle[0]=CreateThread(NULL,0,FatherThread,NULL,0,NULL);
	handle[1]=CreateThread(NULL,0,DaughterThread,NULL,0,NULL);
	handle[2]=CreateThread(NULL,0,SonThread,NULL,0,NULL);

	getchar();
	CloseHandle(g_Disk);
	CloseHandle(g_Apple);
	CloseHandle(g_Orange);
	for (int i=0;i<THREAD_NUM;i++)
	{
		CloseHandle(handle[i]);
	}
	return 0;
}


DWORD WINAPI  FatherThread(LPVOID)
{
	while (1)
	{
		WaitForSingleObject(g_Disk,INFINITE);
		Sleep(1000);
		if(rand()%2==0)
		{
			cout<<"盘子中放入了一个橘子！"<<endl;
			ReleaseSemaphore(g_Orange,1,NULL);
		}
		else
		{
			cout<<"盘子中放入了一个苹果！"<<endl;
			ReleaseSemaphore(g_Apple,1,NULL);
		}
	}
	

	return 0;
}

DWORD WINAPI  DaughterThread(LPVOID)
{
	while (1)
	{
		WaitForSingleObject(g_Apple,INFINITE);
		Sleep(1000);
		cout<<"\t\t\t女儿取走了盘子中的苹果！"<<endl;
		ReleaseSemaphore(g_Disk,1,NULL);
	}
	
	return 0;
}

DWORD WINAPI  SonThread(LPVOID)
{
	while(1)
	{
		WaitForSingleObject(g_Orange,INFINITE);
		Sleep(1000);
		cout<<"\t\t\t\t\t\t儿子取走了盘子中的橘子！"<<endl;
		ReleaseSemaphore(g_Disk,1,NULL);
	}
	
	return 0;
}