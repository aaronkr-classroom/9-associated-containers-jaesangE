//grannar.cpp
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include "split.h"
#include <map>

using namespace std;
// 주어진 입력 스트림으로 문법 테이블을 읽음

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;


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


	//불변성 :지금까지 원래의 i,현재의 i 범위에 있는 
	//문자들을 처리
	while (i != s.end()) {

		i = find_if(i, s.end(), not_space);
		iter  j = find_if(i, s.end(), space);
		if (i != s.end())
			ret.push_back(string(i, j));
		i = j;
	}

	return ret;
}


Grammar read_grammar(istream& in) {
	Grammar ret;
	string line;
	//입력 데이터를 읽음

	while (getline(in, line)) {
		
		vector<string>entry = split(line);
		if (!entry.empty()) {
			ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
		}
	}
	return ret;
}
bool bracketed(const string& s) {
	//<...>?=true
	return s.size() > 1
		&& s[0] == '<' && s[s.size() - 1] == '>';
}
vector<string> gen_sent(const Grammar & g) {
	vector<string> ret;
	gen_aux(g, "<sentence>", ret);
	return ret;
}
int nrand(int n)
{
	if (n <= 0 || n > RAND_MAX) {
		throw domain_error("Argument to nrand is out of range");
	}
	const int bucket_size = RAND_MAX / n;
	int r;
	do r = rand() / bucket_size;
	while (r >= n);

	return r;
}
void gen_aux(const Grammar& g, const string& word, vector<string>& ret)
{
	if (!bracketed(word)) {
		ret.push_back(word);
	}
	else {
		Grammar::const_iterator it = g.find(word);
		if (it == g.end())
			throw logic_error("empty rule");
		const Rule_collection& c = it->second;

		const Rule& r = c[nrand(c.size())];

		for (Rule::const_iterator i = r.begin(); i != r.end(); ++i) {
			gen_aux(g, *i, ret);
		}
	}
}
int main()
{
	vector<string> sentence = gen_sent(read_grammar(cin));

	vector<string>::const_iterator it = sentence.begin();
	if (!sentence.empty()) {
		cout << *it;
		++it;
	}
	while (it != sentence.end()) {
		cout << " " << *it;
		++it;
	}
	cout << endl;
	return 0;
}