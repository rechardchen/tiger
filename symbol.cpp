#include "symbol.h"
#include "allocator.h"
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

	static BumpPtrAllocator s_symbolPool;

	const char* Symbol::intern(const char* str) {
		size_t n = strlen(str);
		if (n != 0) {
			auto iter = s_symbols.find(str);
			if (iter == s_symbols.end()) {
				auto tmp = s_symbolPool.Allocate<char>(n + 1);
				memcpy(tmp, str, n);
				tmp[n] = '\0';
				s_symbols.insert(tmp);
				return tmp;
			}
			else {
				return *iter;
			}
		}
		return nullptr;
	}

}