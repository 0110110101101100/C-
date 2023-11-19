#pragma once
#include<iostream>
#include<assert.h>

namespace mystring {
	class string {
	private:
		size_t _capacity;
		size_t _size;
		char* _str;
	public:
		const static size_t npos = -1;
		/*
		* 迭代器相关实现：统一遍历
		* 暂时实现迭代器和常量迭代器
		*/
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin() {
			return _str;
		}
		iterator end() {
			return _str + _size;
		}
		const_iterator begin() const {
			return _str;
		}
		const_iterator end() const {
			return _str + _size;
		}

		/*
		* 初始化：
		* 默认初始化
		* 拷贝构造初始化
		* 赋值初始化
		*/
		string() :
			_size(0),
			_capacity(0),
			_str(new char[1]) {
			_str[0] = '\0';
		}
		//拷贝构造函数1 string s("hello world")
		//用字符串初始化
		string(const char* str) :
			_capacity(strlen(str)),
			_size(strlen(str)),
			_str(new char[_capacity + 1]) {
			strcpy(_str, str);
		}
		//拷贝构造函数2 string s2(s1);
		//用string初始化
		void swap(string& str) {
			std::swap(_capacity, str._capacity);
			std::swap(_size, str._size);
			std::swap(_str, str._str);
		}
		string(const string& str)
			:_capacity(0),
			_size(0),
			_str(nullptr) {
			string tmp(str._str);
			swap(tmp);
		}
		string& operator=(string str) {
			swap(str);
			return *this;
		}

		~string() {
			delete[]_str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		/*
		访问相关
		*/
		char operator[](size_t i) {
			return _str[i];
		}
		const char operator[](size_t i)const {
			return _str[i];
		}
		size_t find(char c,size_t pos=0) {
			assert(pos >= 0 && pos < _size);

			for (size_t i = pos; i < _size; i++) {
				if (c == _str[i]) {
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* str,size_t pos=0) {
			assert(pos>=0&&pos<_size);

			const char* ret = strstr(_str + pos, str);
			if (ret != NULL) return ret-_str;
			else return npos;
		}
		/*
		容量相关
		*/
		size_t size()const {
			return _size;
		}
		size_t capacity()const {
			return _capacity;
		}
		bool empty() {
			return _size == 0;
		}
		void reserve(size_t n) {
			if (n > _capacity) {
				
				char* tmp = new char[n+1];
				strcpy(tmp, _str);
				delete[]_str;

				_str = tmp;
				_capacity = n;
			}
		}
		void resize(size_t n,char c='\0') {
			if (n > _size) {
				if (n > _capacity) {
					reserve(n);
				}
				for (size_t i = _size; i < n; i++) {
					_str[i] = c;
				}
				_str[n] = '\0';
				_size = n;
			}
			else {
				_str[n] = '\0';
				_size = n;
			}
		}
		//操作相关
		//插入
		//插入单词
		string& insert(size_t pos, char c) {
			assert(pos >= 0 && pos <= _size);
			if (_size == _capacity) {
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}

			size_t end = _size + 1;
			while (end > pos) {
				_str[end] = _str[end-1];
				end--;
			}
			
			
			_str[pos] = c;
			_size++;

			return *this;
		}
		//插入字符串
		string& insert(size_t pos, const char* str) {
			assert(pos >= 0 && pos <= _size);

			if (_size + strlen(str) > _capacity) {
				reserve(_size + strlen(str));
			}

			size_t end = _size + strlen(str);
			while (end >= pos+strlen(str)) {
				_str[end] = _str[end - strlen(str)];
				end--;
			}
			
			strncpy(_str + pos, str,strlen(str));
			_size += strlen(str);

			return *this;
		}
		void push_back(char c) {
			insert(_size, c);
		}
		void append(const char* str) {
			insert(_size, str);
		}
		string& operator+=(char c) {
			push_back(c);
			return *this;
		}
		string& operator+=(const char* str) {
			append(str);
			return*this;
		}
		void erase(size_t pos, size_t len=npos) {
			assert(pos >= 0 && pos < _size);

			size_t ret = _size - pos;
			if (len >= ret||len==npos) {
				_str[pos] = '\0';
				_size =pos;
			}
			else {
				strncpy(_str + pos, _str+pos+len, len);
				_size -= len;
			}
			
		}
		void clear() {
			_str[0] = '\0';
			_size = 0;
		}

		//重载比较运算符
		bool operator==(const string& str) {
			return strcmp(_str,str._str) == 0;
		}
		bool operator>(const string& str) {
			return strcmp(_str, str._str) > 0;
		}
		bool operator>=(const string& str) {
			return (*this == str) || (*this > str);
		}
		bool operator<(const string& str) {
			return !(*this >= str);
		}
		bool operator<=(const string& str) {
			return !(*this > str);
		}
		bool operator!=(const string& str) {
			return !(*this == str);
		}
		//其他
		const char* c_str()const{
			return _str;
		}
	};
	//重载输入输出操作符
	std::istream& operator >>(std::istream& is,string& str) {
		str.clear();
		//定义缓冲区
		const size_t N = 32;
		char buffer[N];
		size_t i = 0;

		char c = is.get();
		while (c != ' ' && c != '\n') {
			buffer[i] = c;
			i++;
			if (i == N - 1) {
				buffer[i] = '\0';
				str += buffer;
				i = 0;
			}
			c = is.get();
		}

		buffer[i] = '\0';
		str += buffer;

		return is;

	}
	std::istream& getline(std::istream& is, string& str) {
		str.clear();

		char c = is.get();
		while (c != '\n') {
			str += c;
			c = is.get();
		}
		return is;
	}
	std::ostream& operator << (std::ostream & os, const string & str) {
		for (auto e : str) {
			os << e;
		}
		return os;
	}
	
	void test1() {
		string s;
		string s1("hello world");
		string s3 = s1;
	}

	void test2() {
		string s = "hello world";
		std::cout << s << std::endl;
		s.insert(3,'*');
		std::cout << s << std::endl;
		s.insert(0,'*');
		std::cout << s << std::endl;

		s.push_back('c');
		s.push_back('c');
		s.push_back('c');
		s.push_back('c');
		s.push_back('c');
		s.push_back('c');
		s.push_back('c');
		s.push_back('c');
		s.push_back('c');
		s.push_back('c');
		s.push_back('c');
		s.push_back('c');
		std::cout << s << std::endl;

		s.append("hhhhhhhhhhhhhhh");
		std::cout << s << std::endl;

	}

	void test3() {
		string s;
		std::cout << "请输入：";
		std::cin >> s ;
		std::cout << s << std::endl;
	}
}

