
//����������������,һ�������ߣ�һ�������ߣ�һ����������
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
		WaitForSingleObject(g_hEventBufEmpty,INFINITE);	//�ȴ�������Ϊ��
		EnterCriticalSection(&g_csVar);
		g_Buffer=i;
		cout<<"�����߽����� "<<g_Buffer<<" ���뻺������"<<endl;
		LeaveCriticalSection(&g_csVar);
		SetEvent(g_hEventBufFull);		//�����¼�
	}

	return 0;
}


DWORD WINAPI ConsumerThread(LPVOID p)
{
	for (int i=1;i<=PRODUCT_NUM;i++)
	{
		WaitForSingleObject(g_hEventBufFull,INFINITE);
		EnterCriticalSection(&g_csVar);
		cout<<"\t\t\t\t�����߽����� "<<g_Buffer<<" �ӻ�����ȡ����"<<endl;
		LeaveCriticalSection(&g_csVar);
		SetEvent(g_hEventBufEmpty);
	}


	return 0;
}


