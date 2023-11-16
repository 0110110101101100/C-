#pragma once
#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<assert.h>
//�������Ե�
#include<iostream>
namespace mystring {
	class string {
	public:
		//���������
		/* ʵ���˳�����ǳ����ĵ����� 
		������ͳһ�ķ�ʽ����STL
		ʵ���ϣ�string�ĵ���������ָ��
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
		//��ʼ��������
		//Ĭ�Ϲ���
		/*string()
			:_size(0)
			, _capacity(0)
			, _str(new char[1]) {
			_str[0] = '\0';
		}*/
		
		/*
		�������죺���ڿ���������ʹ��һ���Ѿ����ڵĶ���ȥ
		��ʼ��һ�������ڵĶ���
		�����ϣ�����Ҫ�����ȣ�ֱ�ӿ�������
		*/
		//����һ����ͳд��
		string(const char* str = "")
			:_size(strlen(str)),
			_capacity(_size),
			_str(new char[_capacity + 1]) {
			strcpy(_str, str);
		}

		////���������ִ�д��
		//string(const string& str)
		//	:_size(0),
		//	_capacity(0),
		//	_str(new char[1]) {
		//	
		//	string tmp(str);
		//	swap(tmp);
		//}

		/*
		=�����أ���ʹ��һ���Ѿ����ڵĶ���ֵ����һ���Ѿ����ڵĶ���
		��ʱ��Ҫ���ͷ�֮ǰ���ٵ��ڴ棬�����Ͽռ䲻�ͷŻ�����ڴ�й©����
		����һ���µĿռ䣬��ԭ���ݿ����������ٸ���������Ա������
		Ҫ��ֹ�Ը�ֵ
		�����ϣ�ע���ֹ�Ը�ֵ��delete�ɿռ� new�¿ռ�
		*/
		//����һ����ͳд��
		//string& operator=(const string& str) {
		//	//��ֹ�Ը�ֵ
		//	if (this != &str) {
		//		//�ͷžɿռ�
		//		delete[]_str;

		//		//����һ���¿ռ䣬���Ҹı�֮ǰ��ָ��
		//		char* tmp = new char[str._capacity + 1];
		//		strcpy(tmp,str._str);

		//		//���¶Գ�Ա�����޸�
		//		_size = str._size;
		//		_capacity = str._capacity;
		//		_str = tmp;
		//	}
		//	//֧��������ֵ
		//	return *this;
		//}

		//���������ִ�д��
		/*
		�ִ�д����Ҫ��ͨ��swap������ʵ�ֵġ�
		1 Ϊʲôʹ��swap������ֱ�����ñ�׼���е�swap�������Ż���
		�п��ܿ���ʹ���ƶ���ֵ��������ǵ����Ŀ���������Ч��
		2 ���ʵ�ֵģ�����һ����ʱ����tmp���Ƚ����õ��������ÿ������캯��
		������tmp��ȥ�����������Ҫ���ˡ�֮������swap����*this�����ݺ�tmp������
		��ʱ�������ݱ�������tmp����tmp����*this���õ�����
		���ڳ���������֮��tmp�ᱻ���٣����Խ�������tmp����ν

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
		* ��ֵ��������Ż���д���ϸ���� 
		* ������ֵ���ݣ����Դ�ʱstr���Ƕ����һ�ݿ�����
		* �ֿ��Գ䵱tmp�Ĺ���
		* ����������֮��Ӱ��ԭ����
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

		//�������
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
		* ���ݺ���������ָ����һ��n���ı�capacity�Ĵ�СΪn
		* ���ݺ���������ֻ�е�n����capacity��ʱ�����Ҫ���ݡ�
		* ��ʱ��Ҫ�ͷžɵ��ڴ�飬�����µ��ڴ�飬���ҿ��������ݵ��¿ռ�
		
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
		* resize�Ĺ��ܣ��޸�_size,�����󣬿���С��Ĭ����������'\0'
		��Ҫ�������ݻ���
		�����
		1 n>size 1.1n>capacity 1.2 n<=capacity ����size
		2 n<=size ��Сsize
		*/
		void resize(size_t n,char c = '\0') {
			if (n > _size) {
				//�ж��Ƿ���Ҫ����
				if (n > _capacity) {
					reserve(n);
				}
				//�������
				for (size_t i = _size; i < n; i++) {
					_str[i] = c;
				}

				//����ĩβ���޸�size
				_str[n] = '\0';
				_size = n;
			}
			else {
				_str[n] = '\0';
				_size = n;
			}
		}
		//�������
		char operator[](size_t i) {
			return _str[i];
		}
		char operator[](size_t i)const {
			return _str[i];
		}
		/*
		* �����ض��ַ��Ƿ����ַ����� Ĭ�ϴӵ�һ��λ�ÿ�ʼѰ��
		* ����ҵ���ô���ص�һ��λ���±꣬û�ҵ��ͷ������ε����ֵ
		*/
		size_t find(char ch, size_t pos = 0) {
			assert(pos >= 0 && pos <= _size);

			for (size_t i = 0; i < _size; i++) {
				if (ch == _str[i]) return i;
			}

			return npos;
		}/*
		 �����ַ������Ƿ����ض��Ӵ� ����strstr����
		 ͨ������ֵ����һ�γ��ָ�λ�õ�ָ�룩�ж�-��ָ�����������λ��
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

		//�ַ���������صĺ���
		//������أ�ʵ��insert ֮��ʵ��append��push_back ������ʵ��+=
		/*
		* ����һ���ַ� ֻ��Ҫ��pos���Ԫ�����������ƶ�һ��λ��
		*/
		string& insert(size_t pos, char c) {
			//�жϣ������
			assert(pos >= 0 && pos <= _size);
			//�������
			if (_size == _capacity) reserve(_capacity == 0 ? 4 : 2 * _capacity);
			//�ƶ����Ӻ���ǰ�ƶ� ��ǰһ��λ�õ�Ԫ���ƶ�����һ��λ��
			size_t end = _size + 1;
			while (end > pos) {
				_str[end] = _str[end - 1];
				end--;
			}
			//����
			_str[pos] = c;
			_size++;
			//֧����ʽ����
			return *this;
		}
		/*
		����һ���ַ�����˼·��ֻ࣬�����ƶ��Ӵ����len����λ
		*/
		string& insert(size_t pos, const char* str) {
			//�����
			assert(pos >= 0 && pos <= _size);
			size_t len = strlen(str);
			//���� ����һ�ο϶����� ����Ƶ������
			if(_size+len>_capacity) reserve(_size+len);
			//�ƶ�
			size_t end = _size + len;
			while (end >= pos + len) {
				_str[end] = _str[end - len];
				end--;
			}
			strcpy(_str + pos, str);

			_size += len;
			return *this;

		}

		/*����һ���ַ���ĩβ*/
		void push_back(char c) {
			insert(_size, c);
		}
		/*��ĩβ׷���ַ���*/
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

		//ɾ�����
		void erase(size_t pos, size_t len = npos) {
			assert(pos >= 0 && pos <= _size);
			//pos��ʼ��_sizeλ�ã�ĩβ����len�Ĵ�С���бȽ�
			size_t n = _size - pos;
			//1 len>n ˵��ȫ��ɾ��
			if (len >= n || n == npos) {
				_str[pos] = '\0';
				_size = pos;
			}//ɾ��һ����
			else {
				//����
				strncpy(_str + pos, _str + pos + len, len);
				_size -= len;
			}
		}
		void clear() {
			_str[0] = '\0';
			_size = 0;
		}
		//��������� ��ϵ���������
		bool operator>(const string& str)const {
			return strcmp(_str, str._str) > 0;
		}
		bool operator==(const string& str)const {
			return strcmp(_str, str._str) == 0;
		}
		//����ʵ�������߼�
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
		
		//����
		//c++ 2 c string to char* ����
		const char* c_str() const {
			return _str;
		}
		
	private:
		int _size;
		int _capacity;
		char* _str;

	};

	//�����������
	std::istream& operator>>(std::istream& is, string& str) {
		const size_t N = 32;//���û�������С
		char buffer[N];//���û�����
		size_t i = 0;//�±����ڷ��ʻ�����

		str.clear();//��� ��ֹ>>֮ǰ�����ݵĸ���

		char c = is.get();
		while (c != ' ' || c != '\n') {
			buffer[i++] = c;
			//������������� ��������������ȡ
			if (i == N - 1) {
				buffer[i] = '\0';
				str += buffer;
				i = 0;
			}
			c = is.get();
		}
		//�����˲��ܶ�ȡ�ľ�ˢ�³�ȥ
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

	//���Գ�ʼ������������
	void test1() {
		string s1 = "hello world";
		string s2("world");
		s1 = s2;
		//�������Σ��������ˣ��δ���
	}
	//���Ե�������صĺ���
	void test2() {
		string s1 = "hello wolrd";
		for (auto e : s1) {
			std::cout << e;
		}
		std::cout << std::endl;
	}
	//����������غ���
	void test3() {
		string s1("hello world");
		std::cout << "reserve֮ǰ��s��size�� " << s1.size() << " s��capacity:" << s1.capacity() << std::endl;
		s1.reserve(20);
		std::cout << "reserve֮��s��size�� " << s1.size() << " s��capacity:" << s1.capacity() << std::endl;

		s1.resize(20, 'c');
		std::cout << "resize֮ǰ��s��size�� " << s1.size() << " s��capacity:" << s1.capacity() << std::endl;
		std::cout << "���ַ���Ϊ:";
		for (auto e : s1) std::cout << e;
		std::cout << std::endl;

		s1.resize(5);
		std::cout << "resize֮��s��size�� " << s1.size() << " s��capacity:" << s1.capacity() << std::endl;
		std::cout << "���ַ���Ϊ:";
		for (auto e : s1) std::cout << e;
		std::cout << std::endl;
	}
	// ���Է������
	void test4() {
		string s = "hello world";
		for (size_t i = 0; i < s.size(); i++) {
			std::cout << s[i];
		}
		std::cout << std::endl;

		std::cout << "s��h���±�Ϊ��" << s.find('h') << std::endl;
		std::cout << "����world�Ӵ������һ�γ��ֵ�λ���ǣ�" << s.find("world") << std::endl;
		std::cout << "����wosdd�Ӵ������һ�γ��ֵ�λ���ǣ�" << s.find("wossd") << std::endl;

	}
	// �������
	void test5() {
		string s = "hello world";
		s.insert(s.size(), '*');
		std::cout << "������һ���ַ���sΪ:";
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		s.insert(3, "#########################");
		std::cout << "insert֮��s��size�� " << s.size() << " s��capacity:" << s.capacity() << std::endl;
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		s.push_back('!');
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		s.append("��������");
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		s += '@';
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		s += "�ұ�����������";
		for (auto e : s) std::cout << e;
		std::cout << std::endl;

		std::cout << "erase֮ǰ,sΪ:" << s << std::endl;
		std::cout << "erase֮ǰ��s��size�� " << s.size() << " s��capacity:" << s.capacity() << std::endl;
		s.erase(3);
		std::cout << "erase֮��,sΪ:" << s << std::endl;
		std::cout << "erase֮��s��size�� " << s.size() << " s��capacity:" << s.capacity() << std::endl;
		
		std::cout << "clear֮ǰ��s��size�� " << s.size() << " s��capacity:" << s.capacity() << std::endl;
		s.clear();
		std::cout << "clear֮��,sΪ:" << s;
		std::cout << "clear֮��s��size�� " << s.size() << " s��capacity:" << s.capacity() << std::endl;

	}
	//�������������������
	void test6() {
		string s;
		std::cout << "�����룺";
		std::cin >> s;
		std::cout << "sΪ��" << s << std::endl;
	}
}
