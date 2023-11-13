#define _CRT_SECURE_NO_WARNINGS 1 
#include"string.h"
using namespace mystring;
using std::cout;
using std::cin;
using std::endl;
/*
1 反向迭代器最后一个被吞了
2 resize的实现有点问题
3 重载流操作运算符为什么显示没重载（）
*/
void test() {
	/*mystring::string s1("hello world");
	mystring::string s2(s1);
	mystring::string s3("mmmmmmm");
	s1 = s3;*/

	

	//mystring::string mystr2 = "aaaaaaaa";
	//? 报错 当前运算符未重载
	//mystr2 >> mystr;
	//
	//迭代器遍历
	//for (string::iterator it = mystr.begin(); it != mystr.end(); it++) {
	//	cout << *it;
	//}
	//cout << endl;

	//反向? 为什么输出不了h
	//for (string::iterator rit = mystr.rbegin(); rit != mystr.rend(); --rit) {
	//	cout << *rit;
	//}
	//cout << endl;
	//11
	//cout << mystr.size() << endl;
	//cout << mystr.length() << endl;
	//
	//cout <<"mystr的capacity： "<< mystr.capacity() << endl;
	//mystr.reserve(10);
	//cout << "mystr的capacity： " << mystr.capacity() << endl;
	//mystr.reserve(40);
	//cout << "mystr的capacity： " << mystr.capacity() << endl;
	//
	//mystr.resize(10);
	//cout << "mystr的size： " << mystr.size() << endl;
	//cout << "mystr的capacity： " << mystr.capacity() << endl;
	//resize的最后一个d被吞了
	//mystr.resize(20, 'a');
	//cout << "mystr的size： " << mystr.size() << endl;
	//cout << "mystr的capacity： " << mystr.capacity() << endl;
	//cout << mystr << endl;

	//mystr.clear();
	//cout << "mystr的size： " << mystr.size() << endl;
	//cout << "mystr的capacity： " << mystr.capacity() << endl;
	//cout << mystr << endl;

	//cout << mystr.empty() << endl;

	mystring::string mystr = "hello world";

	cout << mystr << endl;
	cout << "测试push_back:" << endl;
	mystr.push_back('a');
	cout << mystr << endl;
	cout << "mystr的size： " << mystr.size() << endl;
	cout << "mystr的capacity： " << mystr.capacity() << endl;
	cout << endl;

	cout << "测试append" << endl;
	mystr.append("hello ");
	cout << mystr << endl;
	cout << "mystr的size： " << mystr.size() << endl;
	cout << "mystr的capacity： " << mystr.capacity() << endl;
	cout << endl;

	cout << "测试append" << endl;
	mystr.append(10, '1');
	cout << mystr << endl;
	cout << "mystr的size： " << mystr.size() << endl;
	cout << "mystr的capacity： " << mystr.capacity() << endl;
	cout << endl;

	cout << "测试+=" << endl;
	mystr += "world";
	mystr += "*";
	cout << mystr << endl;
	cout << "mystr的size： " << mystr.size() << endl;
	cout << "mystr的capacity： " << mystr.capacity() << endl;
	cout << endl;

	cout << "测试insert" << endl;
	mystr.insert(5, "M");
	mystr.insert(5, "Momo");
	cout << mystr << endl;
	cout << "mystr的size： " << mystr.size() << endl;
	cout << "mystr的capacity： " << mystr.capacity() << endl;
	cout << endl;

	cout << "测试erase" << endl;
	mystr.erase(5);
	mystr.erase(2,2);
	cout << mystr << endl;
	cout << "mystr的size： " << mystr.size() << endl;
	cout << "mystr的capacity： " << mystr.capacity() << endl;
	cout << endl;

	cout << "测试pop_back" << endl;
	mystr.pop_back();
	cout << mystr << endl;
	cout << "mystr的size： " << mystr.size() << endl;
	cout << "mystr的capacity： " << mystr.capacity() << endl;
	cout << endl;

	cout << "测试[]" << endl;
	for (size_t i = 0; i < mystr.size(); i++)
	cout << mystr[i] << endl;

	cout << "测试find" << endl;
	cout << mystr.find("h")<<endl;
	cout << mystr.find("he") << endl;


}

int main() {
	test();
	return 0;
}