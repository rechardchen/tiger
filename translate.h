#pragma once
#include "temp.h"
#include "allocator.h"
#include "frame.h"
#include <vector>
#include <functional>

namespace tiger {
	struct RecordType;
	struct TExp;
	struct TStm;
	class Frame;

	class TrExp {
	public:
		virtual TExp* unEx() = 0;
		virtual TStm* unNx() = 0;
		virtual TStm* unCx(Label t, Label f) = 0;
	};


	class TrLevel;
	struct TrAccess {
		TrLevel* level = nullptr;
		FAccess access;
	};

	class TrLevel {
	public:
		//TrLevel(BumpPtrAllocator& context) :C(context) {}
		TrAccess AllocLocal(bool escape) {
			TrAccess access;
			access.level = this;
			access.access = Frame->AllocLocal(escape);
			return access;
		}
		TrAccess Argument(int i) {
			TrAccess access;
			access.level = this;
			access.access = Frame->Argument(i + 1);
			return access;
		}

	public:
		TrLevel* Parent = nullptr;//parent == null means global scope
		Frame* Frame = nullptr;//Frame == null means not a function
		Label Name;
		std::vector<bool> Formals;
	};

	enum TrRelOp { Tr_EQ, Tr_NE, Tr_LT, Tr_GT, Tr_LE, Tr_GE };
	enum TrLogicOp { Tr_LogicAnd, Tr_LogicOr };
	//TranslationUnit, IR-tree translator
	class Translate {
	public:
		Translate(BumpPtrAllocator& allocator);

		TrLevel* OutmostLevel() { return InitLevel; }
		TrLevel* NewLevel(TrLevel* parent, Label name, const std::vector<bool>& formals);
		TrLevel* CurLevel() const { return CurrentLevel; }
		void	 ExitLevel(TrExp* body);

		TrExp* CombineStm(TrExp* s1, TrExp* s2);
		TrExp* CombineESeq(TrExp* s, TrExp* e);

		TrExp* TransSimpleVar(TrAccess);
		TrExp* TransFieldVar(TrExp* var, RecordType* type, Symbol field);
		TrExp* TransSubscriptVar(TrExp* var, TrExp* exp);

		TrExp* TransConst(int i);
		TrExp* TransStrConst(Symbol s);
		TrExp* TransArrayInit(TrExp* size, TrExp* init); //A[x] = init
		TrExp* TransRecordInit(RecordType* type, const std::vector<Symbol>& fnames, const std::vector<TrExp*>& fexps);
		TrExp* TransCall(Label f, const std::vector<TrExp*>&, TrLevel* callee);
		TrExp* TransAssign(TrExp* target, TrExp* exp);
		TrExp* TransBinarySub(TrExp* lhs, TrExp* rhs);
		TrExp* TransBinaryMul(TrExp* lhs, TrExp* rhs);
		TrExp* TransBinaryDiv(TrExp* lhs, TrExp* rhs);
		TrExp* TransBinaryAdd(TrExp* lhs, TrExp* rhs);
		TrExp* TransStrConcat(TrExp* lhs, TrExp* rhs);
		TrExp* TransRelOp(TrRelOp op, TrExp* lhs, TrExp* rhs, bool strOprand=false);
		TrExp* TransLogicOp(TrLogicOp op, TrExp* lhs, TrExp* rhs);
		TrExp* TransIf(TrExp* test, TrExp* then, TrExp* elsee);
		TrExp* TransWhile(TrExp* test, TrExp* body, Label end);
		TrExp* TransFor(TrAccess i, TrExp* lo, TrExp* hi, TrExp* body, Label end);
		TrExp* TransBreak(Label);
		TrExp* TransExplist(const std::vector<TrExp*>& exps);
		
	private:
		TrLevel* InitLevel, *CurrentLevel;
		BumpPtrAllocator& C;

		//TODO: global link labels = module + f/s-index
		std::vector<Symbol> StringFrags;
		std::vector<std::pair<TStm*, Frame*>> FuncFrags;

		//frame-specific
		FExternalCall ExternelCall;
		std::function<Frame*(const std::vector<bool>&)> FrameCreator;
	};
}