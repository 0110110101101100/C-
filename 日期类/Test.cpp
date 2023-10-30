#define _CRT_SECURE_NO_WARNINGS 1 
#include"Date.h"

void test() {
	Date d1(2023, 10, 30);
	Date d2(2023, 10, 30);
	Date d3(2023, 10, 29);
	Date d4(2023, 10, 31);

	if (d1 == d2) {
		cout << "d1和d2相等" << endl;
	}
	if (d1 >= d3) {
		cout << "d1大于等于d3" << endl;
	}
	cout << "d1过100天后是:" << d1+100 << endl;
}

int main() {
	test();
	return 0;
}
