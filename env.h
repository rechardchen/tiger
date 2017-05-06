#pragma once
#include "symbol.h"
#include "translate.h"
#include <vector>

namespace tiger {
	struct Type;

	struct VarEntry {
		TrAccess access;
		Type* type;
	};

	struct FuncEntry {
		TrLevel*	level;
		Type*		resultType;

		std::vector<Type*>	paramTypes;
	};

	typedef SymbolTable<VarEntry>	VarEnv;
	typedef SymbolTable<FuncEntry>	FuncEnv;
	typedef SymbolTable<Type>		TypeEnv;

	namespace env {
		//built-in variables
		VarEnv baseVEnv();
		//built-in functions
		FuncEnv baseFEnv();
		//built-in types
		TypeEnv baseTEnv();
	}
}