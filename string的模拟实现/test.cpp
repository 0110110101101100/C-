#define _CRT_SECURE_NO_WARNINGS 1 
#include"string.h"
using namespace mystring;
using std::cout;
using std::cin;
using std::endl;
/*
1 ������������һ��������
2 resize��ʵ���е�����
3 ���������������Ϊʲô��ʾû���أ���
*/
void test() {
	/*mystring::string s1("hello world");
	mystring::string s2(s1);
	mystring::string s3("mmmmmmm");
	s1 = s3;*/

	

	//mystring::string mystr2 = "aaaaaaaa";
	//? ���� ��ǰ�����δ����
	//mystr2 >> mystr;
	//
	//����������
	//for (string::iterator it = mystr.begin(); it != mystr.end(); it++) {
	//	cout << *it;
	//}
	//cout << endl;

	//����? Ϊʲô�������h
	//for (string::iterator rit = mystr.rbegin(); rit != mystr.rend(); --rit) {
	//	cout << *rit;
	//}
	//cout << endl;
	//11
	//cout << mystr.size() << endl;
	//cout << mystr.length() << endl;
	//
	//cout <<"mystr��capacity�� "<< mystr.capacity() << endl;
	//mystr.reserve(10);
	//cout << "mystr��capacity�� " << mystr.capacity() << endl;
	//mystr.reserve(40);
	//cout << "mystr��capacity�� " << mystr.capacity() << endl;
	//
	//mystr.resize(10);
	//cout << "mystr��size�� " << mystr.size() << endl;
	//cout << "mystr��capacity�� " << mystr.capacity() << endl;
	//resize�����һ��d������
	//mystr.resize(20, 'a');
	//cout << "mystr��size�� " << mystr.size() << endl;
	//cout << "mystr��capacity�� " << mystr.capacity() << endl;
	//cout << mystr << endl;

	//mystr.clear();
	//cout << "mystr��size�� " << mystr.size() << endl;
	//cout << "mystr��capacity�� " << mystr.capacity() << endl;
	//cout << mystr << endl;

	//cout << mystr.empty() << endl;

	mystring::string mystr = "hello world";

	cout << mystr << endl;
	cout << "����push_back:" << endl;
	mystr.push_back('a');
	cout << mystr << endl;
	cout << "mystr��size�� " << mystr.size() << endl;
	cout << "mystr��capacity�� " << mystr.capacity() << endl;
	cout << endl;

	cout << "����append" << endl;
	mystr.append("hello ");
	cout << mystr << endl;
	cout << "mystr��size�� " << mystr.size() << endl;
	cout << "mystr��capacity�� " << mystr.capacity() << endl;
	cout << endl;

	cout << "����append" << endl;
	mystr.append(10, '1');
	cout << mystr << endl;
	cout << "mystr��size�� " << mystr.size() << endl;
	cout << "mystr��capacity�� " << mystr.capacity() << endl;
	cout << endl;

	cout << "����+=" << endl;
	mystr += "world";
	mystr += "*";
	cout << mystr << endl;
	cout << "mystr��size�� " << mystr.size() << endl;
	cout << "mystr��capacity�� " << mystr.capacity() << endl;
	cout << endl;

	cout << "����insert" << endl;
	mystr.insert(5, "M");
	mystr.insert(5, "Momo");
	cout << mystr << endl;
	cout << "mystr��size�� " << mystr.size() << endl;
	cout << "mystr��capacity�� " << mystr.capacity() << endl;
	cout << endl;

	cout << "����erase" << endl;
	mystr.erase(5);
	mystr.erase(2,2);
	cout << mystr << endl;
	cout << "mystr��size�� " << mystr.size() << endl;
	cout << "mystr��capacity�� " << mystr.capacity() << endl;
	cout << endl;

	cout << "����pop_back" << endl;
	mystr.pop_back();
	cout << mystr << endl;
	cout << "mystr��size�� " << mystr.size() << endl;
	cout << "mystr��capacity�� " << mystr.capacity() << endl;
	cout << endl;

	cout << "����[]" << endl;
	for (size_t i = 0; i < mystr.size(); i++)
	cout << mystr[i] << endl;

	cout << "����find" << endl;
	cout << mystr.find("h")<<endl;
	cout << mystr.find("he") << endl;


}

int main() {
	test();
	return 0;
}