#define _CRT_SECURE_NO_WARNINGS 1 
#include"Date.h"
void Date::Print() {
	cout << _year << "年" << _month << "月" << _day << "日" << endl;
}
bool Date::operator==(const Date& d) {
	return _year == d._year &&
		_month == d._month &&
		_day == d._day;
}

bool Date::operator>(const Date& d) {
	return (_year>d._year) || 
		((_year==d._year)&&(_month>d._month)) || 
		((_year==d._year)&&(_month==d._month)&&(_day>d._day));
}

bool Date::operator>=(const Date& d) {
	return (*this == d) || (*this) > d;
}

bool Date::operator<(const Date& d) {
	return !(*this >= d);
}

bool Date::operator<=(const Date& d) {
	return (*this == d) || (*this < d);
}

bool Date::operator !=(const Date& d) {
	return !(*this == d);
}
//++d
Date& Date::operator++() {
	return (*this) += 1;
}
//d++
Date Date::operator++(int) {
	Date tmp(*this);
	(*this) +=1;
	return tmp;
}
Date& Date::operator--() {
	return (*this) -= 1;
}
Date Date::operator--(int) {
	Date tmp(*this);
	*this -= 1;
	return tmp;
}
//Date futureDate = currentDate + 7; 
//currentDate不能被修改
Date Date::operator+(int day) {
	Date tmp(*this);
	tmp += day;
	return tmp;
}

Date& Date::operator+=(int day) {
	_day += day;
	while (_day > GetMonthDay(_month, _day)) {
		_month++;
		_day-= GetMonthDay(_month, _day);//进位
		if (_month == 13) {
			_year += 1;
			_month = 1;
		}
	}
	return *this;
}

Date Date::operator-(int day) {
	Date tmp(*this);
	tmp -= day;
	return tmp;

}
Date& Date::operator-=(int day) {
	if (day < 0) return *this = -day;//负数
	_day -= day;
	//借位置
	while (_day <= 0) {
		_month -= 1;
		if (_month == 0) {
			_year -= 1;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

//int Date::operator - (const Date & d)const {
//	int flag = 1;//默认左操作数大于右操作数
//	Date max = *this;
//	Date min = d;
//	if (*this < d) {
//		max = d;
//		min = *this;
//		flag = -1;
//	}
//
//	int count = 0;
//	while (min != max) {
//		count++;
//		min++;
//	}
//	return count;
//
//}