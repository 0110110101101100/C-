#define _CRT_SECURE_NO_WARNINGS 1 
#include"string.h"
using namespace mystring;
char& string::operator[](size_t i) {
	//����� ȷ���±�Ϸ�
	assert(i < _size);
	return _str[i];
}
//ֻ��
const char& string::operator[](size_t i)const {
	assert(i < _size);
	return _str[i];
}
//������С���
size_t string::size()const {
	return _size;
}
size_t string::length()const {
	return _size;
}
size_t string::capacity()const {
	return _capacity;
}
/*Ŀ�ģ���̬�����ڴ棬������ڴ�ʹ�õ�Ч��->�൱������
������
1 ���n<=_capacity����ô�������
2 ���n>_capacity�Ļ�����Ҫ��һ���µ��ڴ�ռ������·����ڴ�*/
void string::reserve(size_t n) {
	if (n > _capacity) {
		//���
		//1����һ���µĿռ�
		char* tmp = new char[n + 1];//�࿪��һ���ռ��������\0�����ַ�
		//2��ԭ���ռ�����ݿ�����ȥ
		strncpy(tmp, _str, _size + 1);
		//3����ԭ�ռ�
		delete[]_str;
		//4�ı�ָ���capacity
		_str = tmp;
		_capacity = n;
	}
}
/*
����
1 ��n<=_size��ʱ����С_size
2 ��n>_size��ʱ������_size(ע������),��������Ӧ���ַ�,Ĭ��Ϊ\0
*/
void string::resize(size_t n, char c) {
	//1����
	if (n <= _size) {
		_size = n;
		//ע�����������������δ������ڴ�
		_str[_size] = '\0';
	}
	else {
		//����
		if (n > _capacity) {
			reserve(n);
		}
		//����ַ�
		for (size_t i = _size; i < n; i++) {
			_str[i] = c;
		}
		
		//����_size
		_size = n;
		//�����֮�����\0
		_str[_size] = '\0';
	}
}
void string::clear() {
	_size = 0;
	_str[0] = '\0';
	//��ѡ �������´β��ô��� ����ֱ������ 
	//������ٵĻ�����������Ϊ֮ǰ�ռ��˷ѣ�ʵ���ϲ�����Ҫ��ô��ռ�
	delete[]_str;
	_str = nullptr;
}
bool string::empty()const { 
	return _size == 0;
}
//�ɶ���д

//���붼��Ҫ���������ļ��
void string::push_back(char c) {
	if (_size == _capacity) {
		reserve(_capacity==0?4:2*_capacity);
	}
	_str[_size] = c;
	_str[_size + 1] = '\0';
	_size++;
}
void string::append(const char* str) {
	insert(_size, str);
}
void string::append(size_t n, char c) {
	/*if (_size + n > _capacity) {
		reserve(_capacity == 0 ? 4 : 2 * _capacity);
	}
	for (size_t i = _size; i < _size + n; i++) {
		_str[i] = c;
	}
	_str[_size + n + 1] = '\0';
	_size++;*/
	//����
	while(n--)
	insert(_size, c);

}
string& string::operator+=(char c) {
	push_back(c);
	return *this;
}
string& string::operator+=(const char* str) {
	append(str);
	return *this;
}
string& string::insert(size_t pos, char ch) {
	assert(pos >= 0 && pos <=_size);
	if (_size == _capacity) {
		reserve(_capacity == 0 ? 4 : 2 * _capacity);
	}

	for (size_t i = _size; i >= pos; i--) {
		_str[i+1] = _str[i];
	}
	_str[pos] = ch;
	_size++;
	return *this;
}
string& string::insert(size_t pos, const char* str) {
	assert(pos >= 0 && pos <= _size);
	size_t len = strlen(str);
	if (_size+len > _capacity) {
		reserve(_size+len);
	}
	
	char* end = _str + _size;
	while (end >= _str + pos) {
		*(end + len) = *end;
		end--;
	}
	strncpy(_str + pos, str, len);
	_size += len;
	return *this;
}
/*
1 ɾ�����ַ����ȴ�����Ч�ַ����ȣ�ȫ��ɾ�� ���\0����
2 ɾ���ĳ���С����Ч�ַ����ȣ�����ɾ�� strcpy
*/
string& string::erase(size_t pos, size_t len) {
	assert(pos >= 0 && pos <= _size);
	size_t n = _size - pos;
	if (len >= n) {
		_size = pos;
		_str[_size] = '\0';
	}
	else {
		strcpy(_str + pos, _str + pos + len);
		_size -= len;
	}
	return *this;
}
void string::pop_back() {
	assert(_size);
	_size--;
	_str[_size] = '\0';
}
/*
Ŀ�ģ���ֹ����Ŀ��� �������std��׼��� 
�����string�Ŀ������캯���͸�ֵ��������ڴ��в���Ҫ�Ŀ���
�Լ�ʵ��ֱ�ӽ�������
*/
void string::swap(string& str) {
	std::swap(_size, str._size);
	std::swap(_capacity, str._capacity);
	std::swap(_str, str._str);
}
/*
Ŀ�ģ���֤��C���Եļ�����
*/
const char* string::c_str()const {
	return _str;
}

string::iterator string::begin() {
	return _str;
}
string::const_iterator string::begin()const {
	return _str;
}
string::iterator string::end() {
	return _str + _size;
}
string::const_iterator string::end()const {
	return _str + _size;
}
//��������� ������Ӧ��ָ�����������һ��Ԫ�ص���һ��λ�ã������ǳ���������ĩβ��
string::iterator string::rbegin() {
	return (_size > 0) ? (_str + _size - 1) : _str;
}
string::const_iterator string::rbegin()const {
	return (_size > 0) ? (_str + _size - 1) : _str;

}
string::iterator string::rend() {
	return _str;
}
string::const_iterator string::rend()const {
	return _str;
}
//���������
size_t string::find(char ch, size_t pos)const {
	assert(pos < _size);

	for (size_t i = pos; i < _size; i++) {
		if (_str[i] == ch) return i;
	}
	return npos;
}
size_t string::find(const char* str, size_t pos)const {
	assert(pos < _size);

	const char* ret = strstr(_str + pos, str);
	if (ret) {
		return ret - _str;
	}
	else {
		return npos;
	}
}

//��ϵ���������
bool string::operator>(const string& str)const {
	return strcmp(_str, str._str) > 0;
}
bool string::operator==(const string& str)const {
	return strcmp(_str, str._str) == 0;
}
bool string::operator>=(const string& str)const {
	return (*this > str) || (*this == str);
}
bool string::operator<(const string& str)const {
	return !(*this >= str);
}
bool string::operator<=(const string& str)const {
	return (*this == str) || (*this < str);
}
bool string::operator!=(const string& str)const {
	return !(*this == str);
}
istream& operator>>(istream& is, string& s) {
	//1 ����ַ��� ���û�иò��������ܻ���append ���Ǹ���
	s.clear();
	// 2��is�л�ȡһ���ַ���ѭ��������ӵ�s����Ҫ������ַ�������ĩβ
	char ch = is.get();
	//��ע�� �����\n���ߡ� ������ֹͣ����
	while (ch != ' ' && ch != '\n') {
		s += ch;
		ch = is.get();//ע�����ch
	}
	return is;//�Ա�֧��������ֵ
}
istream& getline(istream& is, string& s) {
	s.clear();

	char ch = is.get();
	while (ch != '\n') {
		s += ch;
		ch = is.get();
	}

	return is;
}
ostream& operator<<(ostream& os, const string& s) {
	for (auto e : s) {
		std::cout << e;
	}

	return os;
}

