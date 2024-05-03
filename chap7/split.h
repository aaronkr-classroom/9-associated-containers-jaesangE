#pragma once
#ifdef GUARD_split_h
#define GUARD_split_h

// split.cpp
#include <cctype>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
bool space(char);
bool not_space(char);
vector<string>split(const string&);



#endif