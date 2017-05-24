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
		};
	};

	inline FAccess InFrame(int offset) {
		FAccess access;
		access.t = FAccess::InFrame;
		access.offset = offset;
		return access;
	}

	inline FAccess InReg(Temp reg) {
		FAccess access;
		access.t = FAccess::InReg;
		access.reg = reg;
		return access;
	}

	class Frame {
	public:
		//virtual FAccess StaticLink() = 0;
		virtual FAccess FramePtr() = 0;
		virtual FAccess Argument(int i) = 0;
		virtual FAccess ReturnAddress() = 0;
		virtual FAccess ReturnValue() = 0;

		virtual FAccess AllocLocal(bool escape) = 0;
	};
}