#define _CRT_SECURE_NO_WARNINGS 1 
#include "Date.h"

void test() {
	Date d1(2022, 3, 4);
	Date d2(2023, 11, 1);
	Date d3 = d1 + 500;
	cout << d3;

	//cin>>d3;
	//cout <<"�޸ĺ����ڣ�"<< d3<<endl;

	cout << "d1��d2��" << d1 - d2<<"��" << endl;
	cout << "d2��d1���:" << d2 - d1 << "��" << endl;
}

int main() {
	test();
	return 0;
}