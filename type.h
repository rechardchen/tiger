#pragma once
#include "symbol.h"
#include <vector>

namespace tiger {
	enum TypeType {Ty_Nil, Ty_Void, Ty_Int, Ty_String, Ty_Array, Ty_Record, Ty_Name};

	struct Type {
		Type(TypeType ty) :tt(ty) {}
		const TypeType tt;
	};

	struct ArrayType: public Type {
		ArrayType(Type* ty) : Type(Ty_Array), arrTy(ty) {}
		Type* arrTy;
	};

	struct NameType : public Type {
		NameType(Symbol sym, Type* ty = nullptr) :Type(Ty_Name), name(sym), type(ty) {}
		Symbol name;
		Type* type;
	};

	struct RecordType : public Type {
		typedef std::pair<Symbol, Type*> Field;
		RecordType(const std::vector<Field>& fields) : Type(Ty_Record), fieldList(fields) {}
		std::vector<Field> fieldList;

		Type* GetMemberTy(Symbol name) {
			for (auto f : fieldList) {
				if (f.first == name) return f.second;
			}
			return nullptr;
		}
		int GetMemberOffset(Symbol name) {
			int offset = -1;
			for (size_t i = 0; i < fieldList.size(); ++i) {
				if (fieldList[i].first == name) {
					offset = (int)i;
					break;
				}
			}
			return offset;
		}
		int GetMemberNum()const {
			return (int)fieldList.size();
		}
	};

	//nil, void, int, string types are static allocated
	Type* NilType();
	Type* VoidType();
	Type* IntType();
	Type* StringType();
}