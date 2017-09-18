
//  mutex demo   

/*  互斥量可以解决线程间的互斥问题，无法解决线程同步问题   */

#include <iostream>
#include <windows.h>

using namespace std;

const int THREAD_NUM=10;
int g_Num=0;
CRITICAL_SECTION g_csVar;
HANDLE g_mutex;

DWORD WINAPI  Func(LPVOID);


int main()
{
	InitializeCriticalSection(&g_csVar);
	g_mutex=CreateMutex(NULL,false,NULL);
	DWORD ThreadID[THREAD_NUM];
	HANDLE handle[THREAD_NUM];
	int i=0;
	while (i<THREAD_NUM)
	{
		handle[i]=CreateThread(NULL,0,Func,&i,0,&ThreadID[i]);
		WaitForSingleObject(g_mutex,INFINITE);
		i++;
	}
	WaitForMultipleObjects(THREAD_NUM,handle,true,INFINITE);
	CloseHandle(g_mutex);
	DeleteCriticalSection(&g_csVar);
	for (i = 0; i < THREAD_NUM; i++)
		CloseHandle(handle[i]);
	return 0;
}

DWORD WINAPI  Func(LPVOID p)
{
	int nThreadNum=*(int*)p;
	ReleaseMutex(g_mutex);
	Sleep(50);
	EnterCriticalSection(&g_csVar);
	cout<<"线程编号为："<<nThreadNum<<" 全局资源值为："<<++g_Num<<endl;
	LeaveCriticalSection(&g_csVar);
	return 0;
}