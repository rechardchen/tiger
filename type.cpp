#include "type.h"

namespace tiger {
	static Type nilType(Ty_Nil);
	static Type intType(Ty_Int);
	static Type voidType(Ty_Void);
	static Type strType(Ty_String);

	Type* NilType() {
		return &nilType;
	}

	Type* VoidType() {
		return &voidType;
	}

	Type* IntType() {
		return &intType;
	}

	Type* StringType() {
		return &strType;
	}
}