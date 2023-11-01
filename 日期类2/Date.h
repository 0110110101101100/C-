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
//��ʼ��
	Date(int year, int month, int day) :
		_year(year=1),
		_month(month=1),
		_day(day=1) {

	}
// ��������� > == ֻ��ʵ���������߼� �������ü���
	bool operator ==(const Date& d) const;
	bool operator >(const Date& d) const;
	bool operator >=(const Date& d) const;
	bool operator != (const Date& d) const;
	bool operator <(const Date& d) const;
	bool operator <=(const Date& d) const;
//����+= -=�����
	Date& operator+=(int day);
	Date& operator-=(int day);
//����+ -����� ����
//- 1ĳһ����X�������� 2��������֮���������� 
	Date& operator+(int day);
	Date& operator-(int day);
	int operator-(const Date& d);
// ����ǰ��++ �ͺ���++
	Date& operator ++();
	Date& operator ++(int);//intռλ
//���� ǰ��-- �ͺ���--
	Date& operator --();
	Date& operator --(int);
// << >>
	friend ostream& operator <<(ostream& os, const Date& d) {
		os << d._year << "��" << d._month << "��" << d._day << "��" << endl;
		return os;
	}
	friend istream& operator >>(istream& is, Date& d) {
		cout << "����������ڵ���ݣ�";
		is >> d._year;

		cout << "����������ڵ��·ݣ�";
		is >> d._month;

		cout << "����������ڵ��գ�";
		is >> d._day;

		return is;
	}
	// ��ȡ��Ӧ��ݶ�Ӧ�·ݵ���������ҪƵ�������� ���ó�inline
	int GetMonthDay(int year, int month) {
		static int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = days[month];
		//���������Ķ��·ݾ���Ҫ+1
		if ((month == 2) && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
			days[month] += 1;
		}
		return day;
	}
};