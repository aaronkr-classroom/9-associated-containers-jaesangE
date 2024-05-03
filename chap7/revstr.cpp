//revstr.cpp

#include <iostream>
#include <string>

using namespace std;

void revStr(string& str, int start, int end) {
	if (start >= end)
		return;
	char temp = str[start];
	str[start] = str[end];
	str[end] = temp;

	revStr(str, start + 1, end - 1);
}
int main() {

	string str;
	cout << "Enter a string : ";
	cin >> str;
	revStr(str,0,str.length()-1);
	cout << "Reversed string : " << str << endl;

	return 0;
}