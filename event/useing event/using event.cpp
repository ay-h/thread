
//ʹ���¼������߳�ͬ��

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
		WaitForSingleObject(g_event,INFINITE);	//�ȴ��¼�������
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
	SetEvent(g_event);	//�����¼�
	Sleep(50);

	EnterCriticalSection(&g_csVar);
	cout<<"�̱߳��Ϊ��"<<nThreadNum<<"ȫ����ԴֵΪ��"<<++g_Num<<endl;
	LeaveCriticalSection(&g_csVar);

	return 0;
}