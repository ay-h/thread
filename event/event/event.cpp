
/*    event demo     */


#include <iostream>
#include<windows.h>

using namespace std;

const int THREAD_NUM=10;
CRITICAL_SECTION g_csVar,g_csThread;
int g_nNum=0;

DWORD WINAPI  Func(LPVOID);

int main()
{
	InitializeCriticalSection(&g_csVar);
	InitializeCriticalSection(&g_csThread);
	HANDLE handle[THREAD_NUM];
	DWORD threadid[THREAD_NUM];
	int i=0;
	while (i<THREAD_NUM)
	{
		EnterCriticalSection(&g_csThread);
		handle[i]=CreateThread(NULL,0,Func,&i,0,&threadid[i]);
		i++;

	}

	WaitForMultipleObjects(THREAD_NUM,handle,TRUE,INFINITE);
	//getchar();
	DeleteCriticalSection(&g_csVar);
	DeleteCriticalSection(&g_csThread);
	return 0;
}

DWORD WINAPI  Func(LPVOID p)
{
	int *nThreadNUm= (int*)p;
	LeaveCriticalSection(&g_csThread);
	Sleep(50);
	EnterCriticalSection(&g_csVar);
	cout<<"线程编号为："<<*nThreadNUm<<"全局资源值为："<<++g_nNum<<endl;
	LeaveCriticalSection(&g_csVar);

	return 0;
}