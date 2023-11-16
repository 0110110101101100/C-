#pragma once
#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<assert.h>
//用来测试的
#include<iostream>
namespace mystring {
	class string {
	public:
		//迭代器相关
		/* 实现了常量与非常量的迭代器 
		用于以统一的方式遍历STL
		实际上，string的迭代器就是指针
		*/
		typedef char* iterator;
		typedef const char* const_iterator;
		const static size_t npos = -1;
		iterator begin() {
			return _str;
		}
		const_iterator begin()const {
			return _str;
		}
		iterator end() {
			return _str + _size;
		}
		const_iterator end() const {
			return _str + _size;
		}
		//初始化与析构
		//默认构造
		/*string()
			:_size(0)
			, _capacity(0)
			, _str(new char[1]) {
			_str[0] = '\0';
		}*/
		
		/*
		拷贝构造：由于拷贝构造是使用一个已经存在的对象去
		初始化一个不存在的对象
		操作上：不需要析构等，直接拷贝即可
		*/
		//方法一：传统写法
		string(const char* str = "")
			:_size(strlen(str)),
			_capacity(_size),
			_str(new char[_capacity + 1]) {
			strcpy(_str, str);
		}

		////方法二：现代写法
		//string(const string& str)
		//	:_size(0),
		//	_capacity(0),
		//	_str(new char[1]) {
		//	
		//	string tmp(str);
		//	swap(tmp);
		//}

		/*
		=的重载：是使用一个已经存在的对象赋值给另一个已经存在的对象，
		此时需要先释放之前开辟的内存，（堆上空间不释放会造成内存泄漏），
		开辟一块新的空间，将原数据拷贝过来，再更新其他成员函数。
		要防止自赋值
		操作上：注意防止自赋值，delete旧空间 new新空间
		*/
		//方法一：传统写法
		//string& operator=(const string& str) {
		//	//防止自赋值
		//	if (this != &str) {
		//		//释放旧空间
		//		delete[]_str;

		//		//开辟一块新空间，并且改变之前的指向
		//		char* tmp = new char[str._capacity + 1];
		//		strcpy(tmp,str._str);

		//		//重新对成员函数修改
		//		_size = str._size;
		//		_capacity = str._capacity;
		//		_str = tmp;
		//	}
		//	//支持连续赋值
		//	return *this;
		//}

		//方法二：现代写法
		/*
		现代写法主要是通过swap函数来实现的。
		1 为什么使用swap而不是直接利用标准库中的swap？性能优化，
		有可能可以使用移动赋值运算符而非单纯的拷贝，提升效率
		2 如何实现的？创建一个临时对象tmp，先将有用的数据利用拷贝构造函数
		拷贝到tmp中去这就是我们需要的了。之后利用swap，将*this的数据和tmp交换，
		此时无用数据被给到了tmp，而tmp给了*this有用的数据
		由于出了作用域之后，tmp会被销毁，所以将垃圾给tmp无所谓

		*/
		/*void swap(string& tmp)
		{
			std::swap(_str, tmp._str);
			std::swap(_size, tmp._size);
			std::swap(_capacity, tmp._capacity);
		}
		string& operator=(const string& str) {
			if (this != &str) {
				string tmp(str);
				swap(tmp);
			}
			return *this;
		}*/
		/*
		* 赋值运算符的优化：写法上更简便 
		* 由于是值传递，所以此时str既是对象的一份拷贝，
		* 又可以充当tmp的功能
		* 出了作用域之后不影响原数据
		*
		*/
		void swap(string& tmp) {
			std::swap(_str, tmp._str);
			std::swap(_size, tmp._size);
			std::swap(_capacity, tmp._capacity);
		}
		string& operator=(string str) {
			if (this != &str) {
				swap(str);
			}
			return *this;
		}
		~string() {
			delete[]_str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//容量相关
		size_t size()const {
			return _size;
		}
		size_t capacity()const {
			return _capacity;
		}
		bool empty() {
			return _size == 0;
		}
		/*
		* 扩容函数：给定指定的一个n，改变capacity的大小为n
		* 扩容函数操作：只有当n大于capacity的时候才需要扩容。
		* 此时需要释放旧的内存块，开辟新的内存块，并且拷贝旧数据到新空间
		
		*/
		void reserve(size_t n) {
			if (n > _capacity) {
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[]_str;
				_str = tmp;

				_capacity = n;
			}
		}
		/*
		* resize的功能：修改_size,可扩大，可缩小。默认扩大后填充'\0'
		需要考虑扩容机制
		情况：
		1 n>size 1.1n>capacity 1.2 n<=capacity 扩大size
		2 n<=size 缩小size
		*/
		void resize(size_t n,char c = '\0') {
			if (n > _size) {
				//判断是否需要扩容
				if (n > _capacity) {
					reserve(n);
				}
				//填充数据
				for (size_t i = _size; i < n; i++) {
					_str[i] = c;
				}

				//处理末尾和修改size
				_str[n] = '\0';
				_size = n;
			}
			else {
				_str[n] = '\0';
				_size = n;
			}
		}
		//访问相关
		char operator[](size_t i) {
			return _str[i];
		}
		char operator[](size_t i)const {
			return _str[i];
		}
		/*
		* 查找特定字符是否在字符串中 默认从第一个位置开始寻找
		* 如果找到那么返回第一个位置下标，没找到就返回整形的最大值
		*/
		size_t find(char ch, size_t pos = 0) {
			assert(pos >= 0 && pos <= _size);

			for (size_t i = 0; i < _size; i++) {
				if (ch == _str[i]) return i;
			}

			return npos;
		}/*
		 查找字符串中是否有特定子串 调用strstr函数
		 通过返回值（第一次出现该位置的指针）判断-》指针相减算出相对位置
		 */
		size_t find(const char* str, size_t pos = 0) {
			assert(pos >= 0 && pos <= _size);
			assert(str);

			const char* ret = strstr(_str + pos, str);
			if (ret) {
				return ret - _str;
			}
			else {
				return npos;
			}
		}

		//字符串访问相关的函数
		//插入相关：实现insert 之后实现append和push_back 复用再实现+=
		/*
		* 插入一个字符 只需要将pos后的元素整体往后移动一个位置
		*/
		string& insert(size_t pos, char c) {
			//判断：差错处理
			assert(pos >= 0 && pos <= _size);
			//容量检测
			if (_size == _capacity) reserve(_capacity == 0 ? 4 : 2 * _capacity);
			//移动：从后往前移动 将前一个位置的元素移动到后一个位置
			size_t end = _size + 1;
			while (end > pos) {
				_str[end] = _str[end - 1];
				end--;
			}
			//插入
			_str[pos] = c;
			_size++;
			//支持链式操作
			return *this;
		}
		/*
		插入一个字符串，思路差不多，只不过移动子串向后len个单位
		*/
		string& insert(size_t pos, const char* str) {
			//差错处理
			assert(pos >= 0 && pos <= _size);
			size_t len = strlen(str);
			//扩容 开辟一次肯定够了 避免频繁扩容
			if(_size+len>_capacity) reserve(_size+len);
			//移动
			size_t end = _size + len;
			while (end >= pos + len) {
				_str[end] = _str[end - len];
				end--;
			}
			strcpy(_str + pos, str);

			_size += len;
			return *this;

		}

		/*插入一个字符到末尾*/
		void push_back(char c) {
			insert(_size, c);
		}
		/*在末尾追加字符串*/
		void append(const char* str) {
			insert(_size, str);
		}
		
		string& operator+=(const char* str) {
			append(str);
			return *this;
		}
		string& operator+=(char c) {
			push_back(c);
			return *this;
		}

		//删除相关
		void erase(size_t pos, size_t len = npos) {
			assert(pos >= 0 && pos <= _size);
			//pos开始到_size位置（末尾）和len的大小进行比较
			size_t n = _size - pos;
			//1 len>n 说明全部删除
			if (len >= n || n == npos) {
				_str[pos] = '\0';
				_size = pos;
			}//删除一部分
			else {
				//覆盖
				strncpy(_str + pos, _str + pos + len, len);
				_size -= len;
			}
		}
		void clear() {
			_str[0] = '\0';
			_size = 0;
		}
		//运算符重载 关系运算符重载
		bool operator>(const string& str)const {
			return strcmp(_str, str._str) > 0;
		}
		bool operator==(const string& str)const {
			return strcmp(_str, str._str) == 0;
		}
		//复用实现其他逻辑
		bool operator>=(const string& str)const {
			return (*this > str) || (*this == str);
		}
		bool operator<(const string& str)const {
			return !(*this >= str);
		}
		bool operator<=(const string& str)const {
			return (*this == str) || (*this < str);
		}
		bool operator!=(const string& str)const {
			return !(*this == str);
		}
		
		//其他
		//c++ 2 c string to char* 兼容
		const char* c_str() const {
			return _str;
		}
		
	private:
		int _size;
		int _capacity;
		char* _str;

	};

	//重载流运算符
	std::istream& operator>>(std::istream& is, string& str) {
		const size_t N = 32;//设置缓冲区大小
		char buffer[N];//设置缓冲区
		size_t i = 0;//下标用于访问缓冲区

		str.clear();//清除 防止>>之前的数据的干扰

		char c = is.get();
		while (c != ' ' || c != '\n') {
			buffer[i++] = c;
			//如果缓冲区满了 将缓冲区数据提取
			if (i == N - 1) {
				buffer[i] = '\0';
				str += buffer;
				i = 0;
			}
			c = is.get();
		}
		//碰到了不能读取的就刷新出去
		buffer[i] = '\0';
		str += buffer;

		return is;
	}

	std::ostream& operator<<(std::ostream& os, const string& str) {
		for (auto e : str) {
			os << e;
		}
		return os;
	}

	//测试初始化和析构函数
	void test1() {
		string s1 = "hello world";
		string s2("world");
		s1 = s2;
		//析构两次？吹错误了？段错误？
	}
	//测试迭代器相关的函数
	void test2() {
		string s1 = "hello wolrd";
		for (auto e : s1) {
			std::cout << e;
		}
		std::cout << std::endl;
	}
	//测试容量相关函数
	void test3() {
		string s1("hello world");
		std::cout << "reserve之前，s的size： " << s1.size() << " s的capacity:" << s1.capacity() << std::endl;
		s1.reserve(20);
		std::cout << "reserve之后，s的size： " << s1.size() << " s的capacity:" << s1.capacity() << std::endl;

		s1.resize(20, 'c');
		std::cout << "resize之前，s的size： " << s1.size() << " s的capacity:" << s1.capacity() << std::endl;
		std::cout << "该字符串为:";
		for (auto e : s1) std::cout << e;
		std::cout << std::endl;

		s1.resize(5);
		std::cout << "resize之后，s的size： " << s1.size() << " s的capacity:" << s1.capacity() << std::endl;
		std::cout << "该字符串为:";
		for (auto e : s1) std::cout << e;
		std::cout << std::endl;
	}
	// 测试访问相关
	void test4() {
		string s = "hello world";
		for (size_t i = 0; i < s.size(); i++) {
			std::cout << s[i];
		}
		std::cout << std::endl;

		std::cout << "s中h的下标为：" << s.find('h') << std::endl;
		std::cout << "若有world子串，则第一次出现的位置是：" << s.find("world") << std::endl;
		std::cout << "若有wosdd子串，则第一次出现的位置是：" << s.find("wossd") << std::endl;

	}
	// 操作相关
	void test5() {
		string s = "hello world";
		s.insert(s.size(), '*');
		std::cout << "插入了一个字符后，s为:";
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		s.insert(3, "#########################");
		std::cout << "insert之后，s的size： " << s.size() << " s的capacity:" << s.capacity() << std::endl;
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		s.push_back('!');
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		s.append("阳光明媚");
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		s += '@';
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		s += "我辈岂是蓬蒿人";
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		std::cout << "erase之前,s为:" << s << std::endl;
		std::cout << "erase之前，s的size： " << s.size() << " s的capacity:" << s.capacity() << std::endl;
		s.erase(3);
		std::cout << "erase之后,s为:" << s << std::endl;
		std::cout << "erase之后，s的size： " << s.size() << " s的capacity:" << s.capacity() << std::endl;
		
		std::cout << "clear之前，s的size： " << s.size() << " s的capacity:" << s.capacity() << std::endl;
		s.clear();
		std::cout << "clear之后,s为:" << s;
		std::cout << "clear之后，s的size： " << s.size() << " s的capacity:" << s.capacity() << std::endl;

	}
	//测试流操作运算符重载
	void test6() {
		string s;
		std::cout << "请输入：";
		std::cin >> s;
		std::cout << "s为：" << s << std::endl;
	}
}
