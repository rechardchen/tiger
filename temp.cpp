#include "temp.h"

//TODO: refactor this c-style code
namespace tiger {
	namespace temp {
		static int regStart = 100;
		static int labelStart = 0;

		Temp newTemp() {
			return Temp(regStart++);
		}

		Label newLabel() {
			char label[100] = { 0 };
			sprintf(label, "L%d", labelStart++);
			return Label(label);
		}

		Label newNamedLabel(const char* l) {
			return Label(l);
		}
	}
}