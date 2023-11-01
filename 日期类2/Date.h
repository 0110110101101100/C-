#pragma once
#include<iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;
class Date {
private:
	int _year;
	int _month;
	int _day;
public:
//初始化
	Date(int year, int month, int day) :
		_year(year=1),
		_month(month=1),
		_day(day=1) {

	}
// 运算符重载 > == 只需实现这两个逻辑 其他复用即可
	bool operator ==(const Date& d) const;
	bool operator >(const Date& d) const;
	bool operator >=(const Date& d) const;
	bool operator != (const Date& d) const;
	bool operator <(const Date& d) const;
	bool operator <=(const Date& d) const;
//重载+= -=运算符
	Date& operator+=(int day);
	Date& operator-=(int day);
//重载+ -运算符 复用
//- 1某一日期X天后的日期 2两个日期之间相差的天数 
	Date& operator+(int day);
	Date& operator-(int day);
	int operator-(const Date& d);
// 重载前置++ 和后置++
	Date& operator ++();
	Date& operator ++(int);//int占位
//重载 前置-- 和后置--
	Date& operator --();
	Date& operator --(int);
// << >>
	friend ostream& operator <<(ostream& os, const Date& d) {
		os << d._year << "年" << d._month << "月" << d._day << "日" << endl;
		return os;
	}
	friend istream& operator >>(istream& is, Date& d) {
		cout << "请输入该日期的年份：";
		is >> d._year;

		cout << "请输入该日期的月份：";
		is >> d._month;

		cout << "请输入该日期的日：";
		is >> d._day;

		return is;
	}
	// 获取对应年份对应月份的天数，需要频繁被调用 设置成inline
	int GetMonthDay(int year, int month) {
		static int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = days[month];
		//如果是闰年的二月份就需要+1
		if ((month == 2) && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
			days[month] += 1;
		}
		return day;
	}
};