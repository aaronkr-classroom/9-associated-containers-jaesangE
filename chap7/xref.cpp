#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <cctype>
#include <string>

using namespace std;

map<string, vector<int>>xref(istream& in,vector<string> find_words(const string&) = split)
{
	string line;
	int line_number = 0;
	map<string, vector<int>>ret;

	while (getline(in, line)) {
		++line_number;

		vector<string> words = find_words(line);

		for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it)
			ret[*it].push_back(line_number);
	}
	return ret;
}

bool space(char c) {
	return isspace(c);
}
bool not_space(char c) {
	return !isspace(c);
}

vector<string>split(const string& s) {
	typedef string::const_iterator iter;

	vector<string> ret;
	iter i = s.begin();


	//�Һ��� :���ݱ��� ������ i,������ i ������ �ִ� 
	//���ڵ��� ó��
	while (i != s.end()) {

		i = find_if(i, s.end(), not_space);
		iter  j = find_if(i, s.end(), space);
		if (i != s.end())
			ret.push_back(string(i, j));
		i = j;
	}

	return ret;
}


int main()
{
	map<string, vector<int>> ret = xref(cin);

	for (map<string, vector<int>>::const_iterator it = ret.begin(); it != ret.end(); ++it) {
		cout << it->first << "occurs on line(s): ";

		vector<int>::const_iterator line_it = it->second.begin();

		cout << *line_it;
		++line_it;
		while (line_it != it->second.end()) {
			cout << ", " << *line_it;
			++line_it;
		}
		cout << endl;
	}
	return 0;

}
// split.cpp
/*
* ���� ���� : 
* 7-7 , 7-8
* xref.cpp���� �߰�
* �׸��� ���ٿ� �ܾ �� �� �̻� ��Ÿ����
* �ٹ�ȣ�� �ٲپ� 
*/

