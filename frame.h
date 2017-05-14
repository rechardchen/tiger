#pragma once
#include "temp.h"
#include "symbol.h"
#include <vector>

//machine-independent module
#define TIGER_WORD_SIZE 4

namespace tiger {

	struct FAccess {
		enum { InFrame, InReg } t;
		union
		{
			int offset;
			Temp reg;
		} u;
	};

	class Frame {
	public:
		virtual FAccess StaticLink();
		virtual FAccess FramePtr();
	};
	
	struct TExp;
	typedef TExp* FExternalCall(Symbol s, const std::vector<TExp*>&);
}