#pragma once
#include<iostream>
using namespace std;

class Date {
private:
	int _year;
	int _month;
	int _day;
public:
	//构造函数
	Date(int year=1, int month=1, int day=1)
		:_year(year),
		_month(month),
		_day(day) {

	}
	//获取某一个月的天数
	int GetMonthDay(int year, int month) {
		static int myday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = myday[month];
		//闰年二月份为29天
		if ((month==2)&&((year%4==0)&&(year%100!=0)||(year%400==0))) {
			day += 1;
		}
		return day;
	}
	void Print();
	//运算符重载
	bool operator==(const Date& d);
	bool operator>(const Date& d);
	bool operator>=(const Date& d);
	bool operator<(const Date& d);
	bool operator<=(const Date& d);
	bool operator!=(const Date& d);

	Date& operator++();//前置++
	Date operator++(int);//后置++
	Date& operator--();//前置--
	Date operator--(int);//后置--

	Date operator+(int day);
	Date& operator+=(int day);
	Date operator-(int day);
	Date& operator-=(int day);
	//<< 输出重载
	/*friend ostream& operator <<(ostream& os, const Date& d) {
		os << d._year << "年" << d._month << "月" << d._day << "日" ;
		return os;
	}
	friend istream& operator >>(istream& is, const Date& d) {
		cout << "请输入年份:";
		is >> d._year;
	}*/
	//日期相差天数
	int operator-(const Date& d)const;
};
