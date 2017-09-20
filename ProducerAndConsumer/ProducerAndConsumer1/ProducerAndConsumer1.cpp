
// һ�������ߣ����������ߣ�һ������أ��ĸ���������

#include <iostream>
#include <windows.h>
using namespace std;

DWORD WINAPI ProducerThread(LPVOID);
DWORD WINAPI ConsumerThread(LPVOID);	// ���������ߣ��������߳̾�����



const int PRODUCT_NUM=16;
const int BUFFER_SIZE=4;
int g_Buffer[BUFFER_SIZE];
CRITICAL_SECTION g_csVar;
HANDLE g_hEventBufEmpty,g_hEventBufFull;
int g_i=0,g_j=0;


int main()
{
	InitializeCriticalSection(&g_csVar);
	g_hEventBufEmpty=CreateSemaphore(NULL,4,4,NULL);
	g_hEventBufFull=CreateSemaphore(NULL,0,4,NULL);
	const int THREAD_NUM=3;
	HANDLE handle[THREAD_NUM];
	memset(g_Buffer,0,sizeof(g_Buffer));
	handle[0]=CreateThread(NULL,0,ProducerThread,NULL,0,NULL);
	handle[1]=CreateThread(NULL,0,ConsumerThread,NULL,0,NULL);
	handle[2]=CreateThread(NULL,0,ConsumerThread,NULL,0,NULL);

	WaitForMultipleObjects(THREAD_NUM,handle,true,INFINITE);
	for (int i=0;i<THREAD_NUM;i++)
	{
		CloseHandle(handle[i]);
	}
	CloseHandle(g_hEventBufEmpty);
	CloseHandle(g_hEventBufFull);
	DeleteCriticalSection(&g_csVar);

	return 0;
}


DWORD WINAPI ProducerThread(LPVOID p)
{
	for (int i=1;i<=PRODUCT_NUM;i++)
	{
		WaitForSingleObject(g_hEventBufEmpty,INFINITE);
		EnterCriticalSection(&g_csVar);
		g_Buffer[g_i]=i;		
		cout<<"�������ڵ� "<<g_i<<" ��������з������� "<<g_Buffer[g_i]<<endl;
		g_i=(g_i+1)%BUFFER_SIZE;   //g_i��������ʵ���ڻ������ѭ��
		LeaveCriticalSection(&g_csVar);
		ReleaseSemaphore(g_hEventBufFull,1,NULL);
	}
	cout<<"��������������߳̽�������!"<<endl;
	return 0;
}


DWORD  WINAPI ConsumerThread(LPVOID p)
{
	for (int i=1;i<=PRODUCT_NUM;i++)
	{
		WaitForSingleObject(g_hEventBufFull,INFINITE);
		EnterCriticalSection(&g_csVar);
		g_Buffer[g_i]=i;
		cout<<"\t\t\t���Ϊ "<<GetCurrentThreadId()<<" ���������ڵ� "<<g_j<<" ���������ȡ������ "<<g_Buffer[g_j]<<endl;
	
		if(g_Buffer[g_j]==PRODUCT_NUM)
		{
			LeaveCriticalSection(&g_csVar);
			ReleaseSemaphore(g_hEventBufFull,1,NULL);
			break;
		}
		g_j=(g_j+1)%BUFFER_SIZE;  //g_i��������ʵ���ڻ������ѭ��
		LeaveCriticalSection(&g_csVar);
		ReleaseSemaphore(g_hEventBufEmpty,1,NULL);
	}
	cout<<"���Ϊ "<<GetCurrentThreadId()<<" �������߽������У� "<<endl;
	return 0;
}

