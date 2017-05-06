#pragma once
#include "temp.h"
#include <vector>

//TODO:
//support single and double precision floating numbers
//support variable-len integers

//IR-tree
namespace tiger {
	struct TStm;
	struct TExp {};

	//CONST(i): integer constant
	struct TConst : public TExp {
		TConst(int i) : cv(i) {}
		const int cv;
	};

	//NAME(n): symbolic constant n(corresponding to assembly language labels)
	struct TName : public TExp {
		TName(Label l) :label(l) {}
		const Label label;
	};

	//TEMP(t): Temporary t(virtual machine register)
	struct TTemp : public TExp {
		TTemp(Temp _t): t(_t) {}
		const Temp t;
	};

	//BINOP(o, e1, e2)
	enum T_binOp { T_plus, T_minus, T_mul, T_div, T_and, T_or, T_lshift, T_rshift, T_arshift, T_xor };
	struct TBinOp : public TExp {
		TBinOp(T_binOp op, TExp* lhs, TExp* rhs) : op(op), lhs(lhs), rhs(rhs) {}
		T_binOp op;
		TExp *lhs, *rhs;
	};

	//MEM(e): Contents of wordSize bytes of memory starting at address e;
	//Note: when MEM is used as left child of a MOVE, it means "STORE", but anywhere else it means "LOAD"
	struct TMem : public TExp {
		TMem(TExp* e) : addr(e) {}
		TExp* addr;
	};

	//CALL(f,l): Procedure call
	struct TCall : public TExp {
		TCall(TExp* f, const std::vector<TExp*>& l) : callee(f), params(l) {}
		TExp* callee;
		std::vector<TExp*> params;
	};

	//ESEQ(s,e): statement s in evaluated for side effects, then e is evaluated for a result
	struct TEseq : public TExp {
		TEseq(TStm* s, TExp* e) : stm(s), exp(e) {}
		TStm* stm;
		TExp* exp;
	};

	
	struct TStm {};
	//MOVE(TEMP(t), e)
	//MOVE(MEM(e1), e2)
	struct TMove : public TStm {
		TMove(TExp* dst, TExp* src) : dst(dst), src(src) {}
		TExp *dst, *src;
	};

	//EXP(e): evaluate e and discard result
	struct TEval : public TStm {
		TEval(TExp* e) : exp(e) {}
		TExp* exp;
	};

	//JUMP(e, labs): Transfer control to address e
	struct TJump : public TStm {
		TJump(TExp* e, const std::vector<TExp*>& ll) : exp(e), labels(ll) {}
		TExp* exp;
		std::vector<TExp*> labels;
	};

	//CJUMP(o, e1, e2, t, f): conditional jump
	enum T_relOp { T_eq, T_ne, T_lt, T_gt, T_le, T_ge, T_ult, T_ule, T_ugt, T_uge };
	struct TCjump : public TStm {
		TCjump(T_relOp op, TExp* e1, TExp* e2, Label t, Label f) :
			op(op), e1(e1), e2(e2), t(t), f(f) {}
		T_relOp op;
		TExp *e1, *e2;
		Label t, f;
	};

	//SEQ(s1,s2): statement s1 followed by s2
	struct TSeq : public TStm {
		TSeq(TStm* s1, TStm* s2) : s1(s1), s2(s2) {}
		TStm *s1, *s2;
	};

	//LABEL(n): Like a label definition in assembly language
	struct TLabel : public TStm {
		TLabel(Label l) : l(l) {}
		Label l;
	};
}