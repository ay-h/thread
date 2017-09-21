
#pragma comment(lib,"Mydll.lib")
#include <iostream>
using namespace std;


extern int Add(int,int);
extern int Sub(int,int);


int main()
{
	int a,b;
	cout<<"ÊäÈëa:";
	cin>>a;
	cout<<"ÊäÈëb:";
	cin>>b;
	cout<<"run Mydll add. a+b is:"<<Add(a,b)<<endl;
	cout<<"run Mydll Sub. a-b is:"<<Sub(a,b)<<endl;

	return 0;
}