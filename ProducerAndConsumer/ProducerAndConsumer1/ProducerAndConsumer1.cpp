
// 一个生产者，两个消费者，一个缓冲池（四个缓冲区）

#include <iostream>
#include <windows.h>
using namespace std;

DWORD WINAPI ProducerThread(LPVOID);
DWORD WINAPI ConsumerThread(LPVOID);	// 两个消费者，开两个线程就行了



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
		cout<<"生产者在第 "<<g_i<<" 个缓冲池中放入数据 "<<g_Buffer[g_i]<<endl;
		g_i=(g_i+1)%BUFFER_SIZE;   //g_i自增，并实现在缓冲池中循环
		LeaveCriticalSection(&g_csVar);
		ReleaseSemaphore(g_hEventBufFull,1,NULL);
	}
	cout<<"生产者完成任务，线程结束运行!"<<endl;
	return 0;
}


DWORD  WINAPI ConsumerThread(LPVOID p)
{
	for (int i=1;i<=PRODUCT_NUM;i++)
	{
		WaitForSingleObject(g_hEventBufFull,INFINITE);
		EnterCriticalSection(&g_csVar);
		g_Buffer[g_i]=i;
		cout<<"\t\t\t编号为 "<<GetCurrentThreadId()<<" 的消费者在第 "<<g_j<<" 个缓冲池中取走数据 "<<g_Buffer[g_j]<<endl;
	
		if(g_Buffer[g_j]==PRODUCT_NUM)
		{
			LeaveCriticalSection(&g_csVar);
			ReleaseSemaphore(g_hEventBufFull,1,NULL);
			break;
		}
		g_j=(g_j+1)%BUFFER_SIZE;  //g_i自增，并实现在缓冲池中循环
		LeaveCriticalSection(&g_csVar);
		ReleaseSemaphore(g_hEventBufEmpty,1,NULL);
	}
	cout<<"编号为 "<<GetCurrentThreadId()<<" 的消费者结束运行！ "<<endl;
	return 0;
}

