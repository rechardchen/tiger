#pragma once
#include "temp.h"

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
}