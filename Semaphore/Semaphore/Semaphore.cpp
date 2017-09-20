
//  信号量演示

#include<iostream>
#include <windows.h>

using namespace std;

const int THREAD_NUM=10;
int g_Num=0;
CRITICAL_SECTION g_csVar;
HANDLE g_ThreadSema;

DWORD WINAPI  Func(LPVOID);



int main()
{
	InitializeCriticalSection(&g_csVar);
	g_ThreadSema=CreateSemaphore(NULL,0,1,NULL);

	HANDLE handle[THREAD_NUM];
	DWORD ThreadId[THREAD_NUM];
	int i=0;
	while (i<THREAD_NUM)
	{
		handle[i]=CreateThread(NULL,0,Func,&i,0,&ThreadId[i]);
		WaitForSingleObject(g_ThreadSema,INFINITE);
		i++;
	}
	WaitForMultipleObjects(THREAD_NUM,handle,true,INFINITE);
	CloseHandle(g_ThreadSema);
	DeleteCriticalSection(&g_csVar);
	for(i=0;i<THREAD_NUM;i++)
	{
		CloseHandle(handle[i]);
	}
	return 0;
}


DWORD WINAPI Func(LPVOID p)
{
	int nThreadNum= *(int*)p;
	ReleaseSemaphore(g_ThreadSema,1,NULL);
	Sleep(50);
	EnterCriticalSection(&g_csVar);
	cout<<"线程编号为： "<<nThreadNum<<" 全局资源值为："<<++g_Num<<endl;
	LeaveCriticalSection(&g_csVar);
	return 0;
}