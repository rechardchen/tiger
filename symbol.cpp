#include "symbol.h"
#include <cstring>
#include <unordered_set>

using std::unordered_set;
namespace tiger
{
	static size_t hash_string(const char* s) {
		size_t hash = 5381;
		int c;
		while (c = *s++) {
			hash = ((hash << 5) + hash) + c;
		}
		return hash;
	}

	static bool equal_string(const char* s, const char* t) {
		return strcmp(s, t) == 0;
	}

	static unordered_set<const char*,
		size_t(*)(const char*),
		bool(*)(const char*, const char*)> s_symbols(100, &hash_string, &equal_string);

	Symbol::Symbol(const std::string& name) {
		if (!name.empty()) {
			auto iter = s_symbols.find(name.c_str());
			if (iter == s_symbols.end()) {
				auto l = name.length();
				auto tmp = new char[l + 1];
				strncpy(tmp, name.c_str(), l);
				tmp[l] = '\0';

				s_symbols.insert(tmp);
				mName = tmp;
			}
			else {
				mName = *iter;
			}
		}
	}
}