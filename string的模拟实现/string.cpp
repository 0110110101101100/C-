#define _CRT_SECURE_NO_WARNINGS 1 
#include"string.h"
using namespace mystring;
char& string::operator[](size_t i) {
	//差错检测 确保下标合法
	assert(i < _size);
	return _str[i];
}
//只读
const char& string::operator[](size_t i)const {
	assert(i < _size);
	return _str[i];
}
//容量大小相关
size_t string::size()const {
	return _size;
}
size_t string::length()const {
	return _size;
}
size_t string::capacity()const {
	return _capacity;
}
/*目的：动态分配内存，以提高内存使用的效率->相当于扩容
操作：
1 如果n<=_capacity，那么无需操作
2 如果n>_capacity的话，需要在一块新的内存空间上重新分配内存*/
void string::reserve(size_t n) {
	if (n > _capacity) {
		//深拷贝
		//1开辟一块新的空间
		char* tmp = new char[n + 1];//多开辟一个空间用来存放\0结束字符
		//2把原来空间的内容拷贝过去
		strncpy(tmp, _str, _size + 1);
		//3销毁原空间
		delete[]_str;
		//4改变指向和capacity
		_str = tmp;
		_capacity = n;
	}
}
/*
规则：
1 当n<=_size的时候，缩小_size
2 当n>_size的时候，扩大_size(注意扩容),并且填充对应的字符,默认为\0
*/
void string::resize(size_t n, char c) {
	//1缩容
	if (n <= _size) {
		_size = n;
		//注意结束符，否则会出现未分配的内存
		_str[_size] = '\0';
	}
	else {
		//扩容
		if (n > _capacity) {
			reserve(n);
		}
		//填充字符
		for (size_t i = _size; i < n; i++) {
			_str[i] = c;
		}
		
		//更新_size
		_size = n;
		//填充完之后添加\0
		_str[_size] = '\0';
	}
}
void string::clear() {
	_size = 0;
	_str[0] = '\0';
	//可选 不销毁下次不用创建 可以直接利用 
	//如果销毁的话，可能是因为之前空间浪费，实际上并不需要那么大空间
	delete[]_str;
	_str = nullptr;
}
bool string::empty()const { 
	return _size == 0;
}
//可读可写

//插入都需要进行容量的检测
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
	//复用
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
1 删除的字符长度大于有效字符长度：全部删除 添加\0即可
2 删除的长度小于有效字符长度：部分删除 strcpy
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
目的：防止额外的开销 如果利用std标准库的 
会调用string的拷贝构造函数和赋值运算符，内存有不必要的开销
自己实现直接交换即可
*/
void string::swap(string& str) {
	std::swap(_size, str._size);
	std::swap(_capacity, str._capacity);
	std::swap(_str, str._str);
}
/*
目的：保证与C语言的兼容性
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
//反向迭代器 迭代器应该指向容器的最后一个元素的下一个位置，而不是超过容器的末尾。
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
//迭代器相关
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

//关系运算符重载
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
	//1 清空字符串 如果没有该操作，可能会是append 而非覆盖
	s.clear();
	// 2从is中获取一个字符，循环遍历添加到s（需要输入的字符串）的末尾
	char ch = is.get();
	//请注意 如果是\n或者‘ ’将会停止输入
	while (ch != ' ' && ch != '\n') {
		s += ch;
		ch = is.get();//注意更新ch
	}
	return is;//以便支持连续赋值
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

