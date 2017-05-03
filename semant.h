#pragma once
#include <utility>

namespace tiger {
	struct TrExp;
	struct Type;

	class Semant {
	public:
		typedef std::pair<TrExp*, Type*> ExpTy;

	};
}