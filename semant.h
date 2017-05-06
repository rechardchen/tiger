#pragma once
#include "env.h"
#include "absyn.h"
#include "allocator.h"
#include <utility>

namespace tiger {
	struct Type;
	class TrExp;
	class Translate;


	class Semant {
	public:
		typedef std::pair<TrExp*, Type*> ExpTy;

	public:
		//TODO: delete this member, use TU-Context instead
		Semant(BumpPtrAllocator& allocator);

		ExpTy TransExp(ASTNode);
		ExpTy TransDecs(ASTNode);	//Declarations
		ExpTy TransVar(ASTNode);
		Type* TransTy(ASTNode);

	protected:
		//return null means not exists
		//return nameRef means recursion
		static Type* actualTy(Type* ty);
		bool ValidateTypeCheck(Type* left, Type* right);

		VarEnv VENV;
		FuncEnv FENV;
		TypeEnv TENV;
		Translate* Translator = nullptr;
		BumpPtrAllocator& C; //Allocation Context;
	};
}