
//  ������������������

#include<iostream>
#include <windows.h>

using namespace std;

int main()
{
	HANDLE hMutex=CreateMutex(NULL,true,L"My_Mutex");
	cout<<"�������Ѿ����������ڰ����������������!"<<endl;
	getchar();
	//exit(0);
	ReleaseMutex(hMutex);
	cout<<"�������Ѿ�����!"<<endl;
	CloseHandle(hMutex);

	return 0;
}