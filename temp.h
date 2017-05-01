#pragma once
#include "symbol.h"

namespace tiger {
	typedef int Temp;
	typedef Symbol Label;

	namespace temp {
		Temp newTemp();
		Label newLabel();
		Label newNamedLabel(const char* l);
	}

}