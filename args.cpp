#include "args.h"

namespace args {
	vector<pair<wstring, wstring>> parse(int argc, wchar_t* argv[]) {
		std::vector<pair<wstring, wstring>> res;

		for (int i = 1; i < argc; ++i) {
			wstring arg(argv[i]);

			if (!arg.empty() && arg[0] == '/') {
				auto pos = arg.find(':');
				if (pos == wstring::npos) {
					res.emplace_back(arg.substr(1), L"");
				}
				else
				{
					res.emplace_back(arg.substr(1, pos - 1), arg.substr(pos + 1));
				}								
			}
		}
		return res;
	}

	wstring find(const vector<pair<wstring, wstring>>& params, const wstring& paramName) {
		wstring res;
		auto foundItem = std::find_if(params.begin(), params.end(), [paramName](const pair<wstring, wstring>& m) -> bool { return m.first == paramName; });
		if (foundItem != params.end())
		{
			res = foundItem->second;
		}
		return res;

	}
}
