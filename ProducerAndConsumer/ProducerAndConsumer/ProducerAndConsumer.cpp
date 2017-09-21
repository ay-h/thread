
//生产者消费者问题,一个生产者，一个消费者，一个缓冲区。
#include <iostream>
#include <windows.h>

using namespace std;

DWORD WINAPI ProducerThread(LPVOID);
DWORD WINAPI ConsumerThread(LPVOID);

const int PRODUCT_NUM=10;
int g_Buffer=0;
CRITICAL_SECTION g_csVar;
HANDLE g_hEventBufEmpty,g_hEventBufFull;


int main()
{
	InitializeCriticalSection(&g_csVar);
	g_hEventBufEmpty=CreateEvent(NULL,false,true,NULL);
	g_hEventBufFull=CreateEvent(NULL,false,false,NULL);

	const int THREAD_NUM=2;
	HANDLE handle[THREAD_NUM];
	handle[0]=CreateThread(NULL,0,ProducerThread,NULL,0,NULL);
	handle[1]=CreateThread(NULL,0,ConsumerThread,NULL,0,NULL);
	WaitForMultipleObjects(THREAD_NUM,handle,true,INFINITE);

	DeleteCriticalSection(&g_csVar);
	CloseHandle(handle[0]);
	CloseHandle(handle[1]);
	CloseHandle(g_hEventBufEmpty);
	CloseHandle(g_hEventBufFull);
	return 0;
}


DWORD WINAPI ProducerThread(LPVOID p)
{
	for (int i=1;i<=PRODUCT_NUM;i++)
	{
		WaitForSingleObject(g_hEventBufEmpty,INFINITE);	//等待缓冲区为空
		EnterCriticalSection(&g_csVar);
		g_Buffer=i;
		cout<<"生产者将数据 "<<g_Buffer<<" 放入缓冲区！"<<endl;
		LeaveCriticalSection(&g_csVar);
		SetEvent(g_hEventBufFull);		//触发事件
	}

	return 0;
}


DWORD WINAPI ConsumerThread(LPVOID p)
{
	for (int i=1;i<=PRODUCT_NUM;i++)
	{
		WaitForSingleObject(g_hEventBufFull,INFINITE);
		EnterCriticalSection(&g_csVar);
		cout<<"\t\t\t\t消费者将数据 "<<g_Buffer<<" 从缓冲区取出！"<<endl;
		LeaveCriticalSection(&g_csVar);
		SetEvent(g_hEventBufEmpty);
	}


	return 0;
}


