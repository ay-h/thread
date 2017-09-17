
//使用事件进行线程同步

#include<iostream>
#include <windows.h>

using namespace std;

CRITICAL_SECTION g_csVar;
HANDLE g_event;
const int THREAD_NUM=10;
int g_Num=0;

DWORD WINAPI  Func(LPVOID);


int main()
{
	g_event=CreateEvent(NULL,false,false,NULL);	//init event
	InitializeCriticalSection(&g_csVar);
	DWORD  ThreadId[THREAD_NUM];
	HANDLE handle[THREAD_NUM];
	int i=0;
	while (i<THREAD_NUM)
	{
		handle[i]=CreateThread(NULL,0,Func,&i,0,&ThreadId[i]);
		WaitForSingleObject(g_event,INFINITE);	//等待事件被触发
		i++;
	}
	WaitForMultipleObjects(THREAD_NUM,handle,TRUE,INFINITE);

	CloseHandle(g_event);
	DeleteCriticalSection(&g_csVar);
	return 0;
}


DWORD WINAPI Func(LPVOID p)
{
	int nThreadNum= *(int*)p;
	SetEvent(g_event);	//触发事件
	Sleep(50);

	EnterCriticalSection(&g_csVar);
	cout<<"线程编号为："<<nThreadNum<<"全局资源值为："<<++g_Num<<endl;
	LeaveCriticalSection(&g_csVar);

	return 0;
}