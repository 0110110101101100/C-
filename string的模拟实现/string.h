#pragma once
# include<iostream>
#include<assert.h>
using std::istream;
using std::ostream;
//��ʵ��һ�������ģ����������
namespace mystring {
	class string {
	public:
		typedef char* iterator;//string�ĵ�����ʵ������һ��ָ��
		typedef const char* const_iterator;
		//���캯��
		string(const char* str = "") {
			_size = strlen(str);//������\n
			_capacity = 2*_size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}//�ַ�������
		//��������
		string(const string& str)
		{
			_size = str._size;
			_capacity = str._capacity;
			_str = new char[_capacity + 1];
			strcpy(_str, str._str);
		}
		//��ֵ���������
		string& operator=(const string& s) {
			//��ֹ�Ը�ֵ
			if (this != &s) {
				//�ͷžɿռ俪���¿ռ䲢�ҿ���
				delete _str;
				_str = new char[s._capacity + 1];
				strcpy(_str, s._str);

				_size = s._size;
				_capacity = s._capacity;
			}
			return *this;//֧��������ֵ
		}
		//��������
		~string() {
			delete _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//���������
		iterator begin();
		const_iterator begin()const;
		iterator end();
		const_iterator end()const;
		//���������
		iterator rbegin();
		const_iterator rbegin()const;
		iterator rend();
		const_iterator rend()const;

		//������С���
		size_t size()const;
		size_t length()const;
		size_t capacity()const;

		void reserve(size_t n=0);
		void resize(size_t n, char c = '\0');
		void clear();
		bool empty()const;//�п�

		
		//�������
		//����
		void push_back(char c);//�����ַ�
		void append(const char* str);//׷���ַ���
		void append(size_t n, char c);//n��c
		string& operator+=(const char* str);
		string& operator+=(char c);
		string& insert(size_t pos, char ch);//�����ַ�
		string& insert(size_t pos, const char* str);//�����ַ���
		//ɾ��
		string& erase(size_t pos, size_t len=npos);//��posλ�ÿ�ʼɾ��len��
		void pop_back();
		//����
		char& operator[](size_t i);
		const char& operator[](size_t i)const;
		size_t find(char ch, size_t pos = 0)const;
		size_t find(const char* str, size_t pos = 0)const;

		//��ϵ���������
		bool operator>(const string& str)const;
		bool operator==(const string& str)const;
		bool operator>=(const string& str)const;
		bool operator<(const string& str)const;
		bool operator<=(const string & str)const;
		bool operator!=(const string& str)const;


		//����
		void swap(string& str);
		const char* c_str()const;//c++ת����c���


	private:
		size_t _size;//ʵ�ʴ洢����
		size_t _capacity;//������С
		char* _str;//�ַ���
		static const size_t npos=-1;//��Щ������Ĭ��ֵ

	};
	
	//const size_t string::npos = -1;

	
}
//���������������
istream& operator>>(istream& is, mystring::string& s);
istream& getline(istream& is, mystring::string& s);
ostream& operator<<(ostream& os, const mystring::string& s);