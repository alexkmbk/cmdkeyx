#pragma once 

#include <string>
#include <vector>
#include <algorithm>

using std::wstring;
using std::vector;
using std::pair;


namespace args {
	vector<pair<wstring, wstring>> parse(int argc, wchar_t* argv[]);
	wstring find(const vector<pair<wstring, wstring>>& params, const wstring& paramName);
}
