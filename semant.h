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

		//make sure if ExpTy returned is successful, then ty is actual typed
		ExpTy TransExp(ASTNode); //expty.second null if trans failed, else is actualed type
		ExpTy TransDecs(ASTNode);//Declaration list
		ExpTy TransVar(ASTNode);
		Type* TransTy(ASTNode);

		ExpTy TransVarDec(VarDec*); //expty.second != null means success

	protected:
		//only used where we must have the actual type
		static Type* actualTy(Type* ty);
		//type equality validation
		static bool ValidateTypeCheck(Type* left, Type* right);

		VarEnv VENV;
		FuncEnv FENV;
		TypeEnv TENV;
		Translate* Translator = nullptr;
		BumpPtrAllocator& C; //Allocation Context;
	};
}