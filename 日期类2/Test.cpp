#define _CRT_SECURE_NO_WARNINGS 1 
#include "Date.h"

void test() {
	Date d1(2022, 3, 4);
	Date d2(2023, 11, 1);
	Date d3 = d1 + 500;
	cout << d3;

	//cin>>d3;
	//cout <<"修改后日期："<< d3<<endl;

	cout << "d1和d2相差：" << d1 - d2<<"天" << endl;
	cout << "d2和d1相差:" << d2 - d1 << "天" << endl;
}

int main() {
	test();
	return 0;
}