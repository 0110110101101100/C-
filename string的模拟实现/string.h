#pragma once
# include<iostream>
#include<assert.h>
using std::istream;
using std::ostream;
//先实现一个基本的，后续再添加
namespace mystring {
	class string {
	public:
		typedef char* iterator;//string的迭代器实际上是一个指针
		typedef const char* const_iterator;
		//构造函数
		string(const char* str = "") {
			_size = strlen(str);//不算上\n
			_capacity = 2*_size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}//字符串构造
		//拷贝构造
		string(const string& str)
		{
			_size = str._size;
			_capacity = str._capacity;
			_str = new char[_capacity + 1];
			strcpy(_str, str._str);
		}
		//赋值运算符重载
		string& operator=(const string& s) {
			//防止自赋值
			if (this != &s) {
				//释放旧空间开辟新空间并且拷贝
				delete _str;
				_str = new char[s._capacity + 1];
				strcpy(_str, s._str);

				_size = s._size;
				_capacity = s._capacity;
			}
			return *this;//支持连续赋值
		}
		//析构函数
		~string() {
			delete _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//迭代器相关
		iterator begin();
		const_iterator begin()const;
		iterator end();
		const_iterator end()const;
		//反向迭代器
		iterator rbegin();
		const_iterator rbegin()const;
		iterator rend();
		const_iterator rend()const;

		//容量大小相关
		size_t size()const;
		size_t length()const;
		size_t capacity()const;

		void reserve(size_t n=0);
		void resize(size_t n, char c = '\0');
		void clear();
		bool empty()const;//判空

		
		//操作相关
		//插入
		void push_back(char c);//插入字符
		void append(const char* str);//追加字符串
		void append(size_t n, char c);//n个c
		string& operator+=(const char* str);
		string& operator+=(char c);
		string& insert(size_t pos, char ch);//插入字符
		string& insert(size_t pos, const char* str);//插入字符串
		//删除
		string& erase(size_t pos, size_t len=npos);//从pos位置开始删除len个
		void pop_back();
		//访问
		char& operator[](size_t i);
		const char& operator[](size_t i)const;
		size_t find(char ch, size_t pos = 0)const;
		size_t find(const char* str, size_t pos = 0)const;

		//关系运算符重载
		bool operator>(const string& str)const;
		bool operator==(const string& str)const;
		bool operator>=(const string& str)const;
		bool operator<(const string& str)const;
		bool operator<=(const string & str)const;
		bool operator!=(const string& str)const;


		//其他
		void swap(string& str);
		const char* c_str()const;//c++转换成c风格


	private:
		size_t _size;//实际存储个数
		size_t _capacity;//容量大小
		char* _str;//字符串
		static const size_t npos=-1;//有些操作的默认值

	};
	
	//const size_t string::npos = -1;

	
}
//重载流操作运算符
istream& operator>>(istream& is, mystring::string& s);
istream& getline(istream& is, mystring::string& s);
ostream& operator<<(ostream& os, const mystring::string& s);