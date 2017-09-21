
#include <iostream>
#include <windows.h>

 _declspec(dllexport) int Add(int a,int b)
 {
	return a+b;
 }

 _declspec(dllexport) int Sub(int a,int b)
 {
	 return a-b;
 }