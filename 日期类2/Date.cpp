#define _CRT_SECURE_NO_WARNINGS 1 
#include"Date.h"

bool Date::operator==(const Date& d) const {
	return _year == d._year &&
		_month == d._month &&
		_day == d._day;
}
bool Date::operator>(const Date& d) const {
	return (_year > d._year) ||
		(_year == d._year && _month > d._month) ||
		(_year == d._year && _month == d._month && _day > d._day);
}
bool Date::operator>=(const Date& d)const {
	return (*this == d) || (*this > d);
}
bool Date::operator!=(const Date& d)const {
	return !(*this == d);
}
bool Date::operator<(const Date& d)const {
	return !(*this >= d);
}
bool Date::operator<=(const Date& d)const {
	return (*this < d) || (*this) == d;
}

Date& Date::operator+=(int day) {
	if (day < 0) return *this -= -day;
	_day += day;
	while (_day>GetMonthDay(_year,_month)){
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month == 13) {
			_year += 1;
			_month = 1;
		}
	}
	return *this;
}
Date& Date::operator-=(int day) {
	if (day < 0) return *this += -day;

	_day -= day;
	while (_day < 0) {
		_month--;
		_day += GetMonthDay(_year, _month);
		if (_month == 0) {
			_year -= 1;
			_month = 12;
		}
	}

	return *this;
}

Date& Date::operator+(int day) {
	Date ret(*this);
	ret += day;
	return ret;
}

Date& Date::operator-(int day) {
	Date ret(*this);
	ret -= day;
	return ret;
}
int Date::operator-(const Date& d) {
	int flag = 1;//符号正负 默认是正
	Date max = *this;
	Date min = d;
	if (*this < d) {
		max = d;
		min = *this;
		flag = -1;
	}
	int count = 0;
	while (min != max) {
		count++;
		min+=1;
	}
	return count*(flag);
}

Date& Date::operator ++() {
	return *this += 1;
}
Date& Date::operator ++(int) {
	Date ret(*this);
	ret += 1;
	return ret;
}
Date& Date::operator--() {
	return *this -= 1;
}
Date& Date::operator--(int) {
	Date ret(*this);
	ret -= 1;
	return ret;
}