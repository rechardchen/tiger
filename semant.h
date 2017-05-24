#pragma once
//Keep simple
#include "env.h"
#include "absyn.h"
#include "allocator.h"
#include "temp.h"
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
		//loopExit is the outer loop to break
		ExpTy TransExp(ASTNode,Label=""); //expty.second null if trans failed, else is actualed type
		ExpTy TransDecs(ASTNode);//Declaration list
		ExpTy TransVar(ASTNode);
		Type* TransTy(ASTNode);

		ExpTy TransVarDec(VarDec*); //expty.second != null means success

		//entry function
		void TransProg(ASTNode);

	public:
		inline void SetTranslate(Translate* translator) {
			Translator = translator;
		}

	protected:
		//only used where we must have the actual type
		static Type* actualTy(Type* ty);
		//type equality validation, assume left and right all actual typed
		static bool ValidateTypeCheck(Type* left, Type* right);
		inline void NewScope() { TENV.BeginScope(); VENV.BeginScope(); FENV.BeginScope(); }
		inline void EndScope() { TENV.EndScope(); VENV.EndScope(); FENV.EndScope(); }

		VarEnv VENV;
		FuncEnv FENV;
		TypeEnv TENV;
		Translate* Translator = nullptr;
		BumpPtrAllocator& C; //Allocation Context;
	};
}