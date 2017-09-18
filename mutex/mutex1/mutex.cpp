
//  互斥量被遗弃现象处理

#include<iostream>
#include <windows.h>

using namespace std;

int main()
{
	HANDLE hMutex=CreateMutex(NULL,true,L"My_Mutex");
	cout<<"互斥量已经创建，现在按任意键触发互斥量!"<<endl;
	getchar();
	//exit(0);
	ReleaseMutex(hMutex);
	cout<<"互斥量已经触发!"<<endl;
	CloseHandle(hMutex);

	return 0;
}