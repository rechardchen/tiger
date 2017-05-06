#include "semant.h"
#include "type.h"
#include "translate.h"

namespace tiger {

	Semant::Semant(BumpPtrAllocator& allocator)
		: C(allocator)
		, VENV(env::baseVEnv())
		, FENV(env::baseFEnv())
		, TENV(env::baseTEnv())
	{
		Translator = new (C) Translate(C);
	}

	Semant::ExpTy Semant::TransExp(ASTNode)
	{
		return ExpTy(nullptr, nullptr);
	}

	Semant::ExpTy Semant::TransDecs(ASTNode n)
	{
		//TODO: handle class definitions
		assert(n->type == A_DeclareList);
		DeclareList* dl = static_cast<DeclareList*>(n);
		TrExp* initExp = nullptr;

		//first pass only process type headers
		for (auto dec : dl->decs) {
			if (dec->type == A_TypeDec) {
				auto tydec = static_cast<TypeDec*>(dec);
				switch (tydec->ty->type) {
				case A_NameTy:
				case A_RecordTy:
				case A_ArrayTy:
					TENV.Enter(tydec->name, new(C) NameType(tydec->name, nullptr));
					break;
				default:
					assert(0);
					break;
				}
			}
		}
		for (auto dec : dl->decs) {
			//second pass get the complete type definition
			if (dec->type == A_TypeDec) {
				auto tydec = static_cast<TypeDec*>(dec);
				Symbol typeName = tydec->name;
				auto ty = TENV.Look(typeName);
				assert(ty->tt == Ty_Name);
				auto nt = static_cast<NameType*>(ty);
				nt->type = TransTy(tydec);

				//check: recursive define and incomplete define
				Type* realTy = nt->type;
				while (realTy != nt && realTy->tt == Ty_Name) {
					auto realNT = static_cast<NameType*>(realTy);
					if (realNT->type == nullptr) {
						reportErr("type %s has an incomplete definition!", tydec->name.c_str());
						break;
					}
					else
						realTy = realNT->type;
				}
				if (realTy == nt)
					reportErr("type %s has a recursive definition!", tydec->name.c_str());
			}
			else if (dec->type == A_VarDec) {
				auto vardec = static_cast<VarDec*>(dec);
				Type* ty = nullptr;
				bool needTrans = true;
				if (!vardec->type.empty()) { //if var type not specified, need type induction
					ty = TENV.Look(vardec->type);
					if (ty == nullptr) {
						reportErr("type %s not exists!", vardec->type.c_str());
						needTrans = false;
					}
				}

				if (needTrans) {
					ExpTy expty = TransExp(vardec->init); //TransExp do not return nullptr type
					ty = ty == nullptr ? expty.second : ty;
					if (!ValidateTypeCheck(ty, expty.second)) {
						reportErr("type mismatch!");
					}
					else {
						auto curLevel = Translator->CurLevel();
						auto vAccess = curLevel->AllocLocal(vardec->escape);
						auto entry = new(C) VarEntry;
						entry->access = vAccess;
						entry->type = expty.second;
						VENV.Enter(vardec->name, entry);
						
						//code gen
						TrExp* varExp = Translator->TransSimpleVar(vAccess);
					}
				}
			}
			else if (dec->type == A_FuncDec) {
				//TODO
			}
		}

		return ExpTy(initExp, nullptr);
	}

	Semant::ExpTy Semant::TransVar(ASTNode)
	{
		return ExpTy(nullptr, nullptr);
	}

	Type* Semant::TransTy(ASTNode n)
	{
		switch (n->type) {
		case A_NameTy:
		{
			NameTy* nt = static_cast<NameTy*>(n);
			Type* ty = TENV.Look(nt->name);
			if (ty == nullptr)
				reportErr("type %s not defined!", nt->name.c_str());
			return ty;
		}
			break;

		case A_RecordTy:
		{
			RecordTy* rt = static_cast<RecordTy*>(n);
			std::vector<RecordType::Field> fieldVec;
			for (auto field : rt->tyfields->fields) {
				RecordType::Field tempField;
				tempField.first = field->name;
				Type* ty = TENV.Look(field->type);
				if (ty == nullptr) 
					reportErr("type %s not defined!", field->type.c_str());
				tempField.second = ty;
				fieldVec.push_back(tempField);
			}
			return new (C) RecordType(fieldVec);
		}
			break;

		case A_ArrayTy:
		{
			ArrayTy* at = static_cast<ArrayTy*>(n);
			Type* ty = TENV.Look(at->type);
			if (ty == nullptr)
				reportErr("type %s not defined!", at->type.c_str());
			return new (C) ArrayType(ty);
		}
			break;

		default:
			assert(0);
			break;
		}
		return nullptr;
	}

	Type* actualTy(Type* ty) {
		while (ty->tt == Ty_Name)
			ty = static_cast<NameType*>(ty)->type;
		return ty;
	}
}