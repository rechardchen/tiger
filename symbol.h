#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace tiger
{
	class Symbol
	{
	public:
		Symbol() : mName(nullptr) {}

		Symbol(const std::string& name) {
			mName = intern(name.data());
		}
		Symbol(const char* name) {
			mName = intern(name);
		}
		inline const char* Name() const { 
			return mName; 
		}
		inline bool operator==(const Symbol& rhs) const { 
			return mName == rhs.mName;
		}
		
	public:
		struct Hasher {
			size_t operator() (const Symbol& s) const{
//#if sizeof(size_t) == sizeof(const char*)
//				return size_t(s.mName);
//#else
//				return std::hash<const char*>()(s.mName);
//#endif
				return size_t(s.mName);
				//return std::hash<const char*>()(s.mName);
			}
		};

	protected:
		const char* intern(const char* str);
		const char* mName = nullptr;
	};

	//Symbol Table Implementation(Simple)
	template <typename T>
	class SymbolTable {
		typedef std::unordered_map<Symbol, T*, Symbol::Hasher> TableType;

	public:
		SymbolTable() {
			BeginScope();
		}

		void BeginScope() {
			mTableStack.emplace_back(TableType());
		}

		void EndScope() {
			mTableStack.pop_back();
		}

		void Enter(Symbol sym, T* value) {
			auto& table = mTableStack.back();
			table[sym] = value;
		}

		void Pop(Symbol sym) {
			auto& table = mTableStack.back();
			table.erase(sym);
		}

		T* Look(Symbol sym) {
			T* val = nullptr;
			for (auto iter = mTableStack.rbegin(); iter != mTableStack.rend(); ++iter) {
				auto& t = *iter;
				auto it = t.find(sym);
				if (it != t.end()) return it->second;
			}
			return val;
		}
	protected:
		std::vector<TableType> mTableStack;
	};
}
