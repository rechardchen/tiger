#include "translate.h"
#include "type.h"
#include "tree.h"


namespace tiger {

	class TrEx : public TrExp {
	public:
		TrEx(TExp* e, BumpPtrAllocator&C) : e(e), C(C) {}

		virtual TExp* unEx() override { return e; }
		virtual TStm* unNx() override { return new(C)TEval(e); }
		virtual TStm* unCx(Label t, Label f) override {
			if (e->type == T_Const) //optimize for integer constants
			{
				TConst* c = static_cast<TConst*>(e);
				if (c->cv)
					return new(C)TJump(t, { t });
				else
					return new(C)TJump(f, { f });
			}
			else {
				return new(C)TCjump(T_ne, new(C)TConst(0), e, t, f);
			}
		}
	protected:
		TExp* e;
		BumpPtrAllocator& C;
	};

	class TrNx : public TrExp {
	public:
		TrNx(TStm* s, BumpPtrAllocator&C) :s(s), C(C) {}

		virtual TExp* unEx() override {
			return new(C)TEseq(s, new(C)TConst(0));
		}
		virtual TStm* unNx() override { return s; }
		virtual TStm* unCx(Label t, Label f) override {
			return new(C)TSeq(s, new(C)TJump(f, { f }));
		}
	protected:
		TStm* s;
		BumpPtrAllocator&C;
	};

	class TrCx : public TrExp {
	public:
		TrCx(BumpPtrAllocator&C) :C(C) {}

		virtual TExp* unEx() override {
			auto reg = temp::newTemp();
			auto tlabel = temp::newLabel();
			auto flabel = temp::newLabel();

			return new(C)TEseq(
				new(C)TSeq(
					new(C)TMove(new(C)TTemp(reg), new(C)TConst(0)),
					new(C)TSeq(
						unCx(tlabel,flabel),
						new(C)TSeq(
							new(C)TLabel(tlabel),
							new(C)TSeq(
								new(C)TMove(new(C)TTemp(reg), new(C)TConst(1)),
								new(C)TLabel(flabel)
							)
						)
					)
				),
				new(C)TTemp(reg)
			);
		}

		virtual TStm* unNx() override {
			return new(C)TEval(unEx());
		}

		virtual TStm* unCx(Label t, Label f) override {
			//derived class must provide its own unCx
			assert(0);
			return nullptr;
		}

		/*virtual TStm* unCx(Label t, Label f) override {
			return new(C)TCjump(T_ne, new(C)TConst(0), unEx(), t, f);
		}*/
	
		//virtual TExp* unEx() override;
		//virtual TStm* unNx() override;
	//public:
	//	//TrCx(TStm* s, const std::vector<Label*>& truelist, const std::vector<Label*>& falselist)
	//	//	:s(s), truelist(truelist), falselist(falselist) {}
	//	virtual TExp* unEx() override;
	//	virtual TStm* unNx() override;
	//	virtual TStm* unCx(Label* t, Label* f) override;
	//protected:
	//	//TStm* s;
	//	//std::vector<Label*> truelist, falselist;
	protected:
		BumpPtrAllocator& C;
	};

	class TrRelCx : public TrCx {
	public:
		TrRelCx(TrRelOp op, TrExp* lhs, TrExp* rhs, BumpPtrAllocator& C) 
			:TrCx(C), OP(op), lhs(lhs), rhs(rhs) {}

		virtual TStm* unCx(Label t, Label f) override {
			static const T_relOp OP_MAP[] = { T_eq, T_ne, T_lt, T_gt, T_le, T_ge };
			return new(C)TCjump(OP_MAP[OP], lhs->unEx(), rhs->unEx(), t, f);
		}
	protected:
		TrRelOp OP;
		TrExp *lhs, *rhs;
	};
	
	class TrLogicCx : public TrCx {
	public:
		TrLogicCx(TrLogicOp op, TrExp* lhs, TrExp* rhs, BumpPtrAllocator& C) 
			:TrCx(C), OP(op), lhs(lhs), rhs(rhs) {}

		virtual TStm* unCx(Label t, Label f) override {
			auto label = temp::newLabel();
			TStm* labDef = new(C)TLabel(label);
			TStm* left, *right;
			if (OP == Tr_LogicAnd) { //AND
				left = lhs->unCx(label, f);
				right = rhs->unCx(t, f);
			}
			else { //OR
				left = lhs->unCx(t, label);
				right = rhs->unCx(t, f);
			}
			return new(C)TSeq(
				left,
				new(C)TSeq(
					labDef, right
					)
				);
		}
	protected:
		TrLogicOp OP;
		TrExp *lhs, *rhs;
	};
	
	class TrIf : public TrCx {
	public:
		TrIf(TrExp* test, TrExp* then, TrExp* elsee, BumpPtrAllocator& C)
			:TrCx(C), test(test), then(then), elsee(elsee) {}
		
		virtual TExp* unEx() override {
			assert(elsee != nullptr);
			auto reg = temp::newTemp();
			auto tlabel = temp::newLabel();
			auto flabel = temp::newLabel();
			auto joinlab = temp::newLabel();

			return new(C)TEseq(
				new(C)TSeq(
					test->unCx(tlabel,flabel),
					new(C)TSeq(
						new(C)TLabel(tlabel),
						new(C)TSeq(
							new(C)TMove(new(C)TTemp(reg), then->unEx()),
							new(C)TSeq(
								new(C)TJump(joinlab, { joinlab }),
								new(C)TSeq(
									new(C)TLabel(flabel),
									new(C)TSeq(
										new(C)TMove(new(C)TTemp(reg), elsee->unEx()),
										new(C)TLabel(joinlab)
									)
								)
							)
						)
					)
				),
				new(C)TTemp(reg)
			);
		}

		virtual TStm* unNx() override {
			if (elsee == nullptr) {
				auto tlabel = temp::newLabel(); //true label
				auto jlabel = temp::newLabel(); //join label
				return new(C)TSeq(
					test->unCx(tlabel, jlabel),
					new(C)TSeq(
						new(C)TLabel(tlabel),
						new(C)TSeq(
							then->unNx(),
							new(C)TLabel(jlabel)
						)
					)
				);
			}
			else {
				auto tlabel = temp::newLabel();
				auto flabel = temp::newLabel();
				auto jlabel = temp::newLabel();
				return new(C)TSeq(
					test->unCx(tlabel, flabel),
					new(C)TSeq(
						new(C)TLabel(tlabel),
						new(C)TSeq(
							then->unNx(),
							new(C)TSeq(
								new(C)TJump(jlabel, { jlabel }),
								new(C)TSeq(
									new(C)TLabel(flabel),
									new(C)TSeq(
										elsee->unNx(),
										new(C)TLabel(jlabel)
									)
								)
							)
						)
					)
				);
			}
		}

		virtual TStm* unCx(Label t, Label f) override {
			return new(C)TCjump(T_ne, new(C)TConst(0), unEx(), t, f);
		}
	protected:
		TrExp* test, *then, *elsee;
	};

	Translate::Translate(BumpPtrAllocator& allocator)
		: C(allocator)
	{
		InitLevel = new (C)TrLevel(C);
		CurrentLevel = InitLevel;
	}

	TrLevel* Translate::NewLevel(TrLevel* parent, Label name, const std::vector<bool>& formals)
	{
		auto level = new (C) TrLevel(C);
		level->Name = name;
		level->Parent = parent;
		level->Formals = formals;
		//TODO

		return level;
	}

	void Translate::ExitLevel(TrExp* body)
	{
		//TODO
		TrLevel* curLevel = CurLevel();
		CurrentLevel = curLevel->Parent;

	}

	TrExp* Translate::CombineStm(TrExp* s1, TrExp* s2)
	{
		assert(s1 != nullptr && s2 != nullptr);
		return new(C)TrNx(
			new(C)TSeq(
				s1->unNx(), 
				s2->unNx()
			), C
		);
	}

	TrExp* Translate::TransSimpleVar(TrAccess vAccess)
	{
		if (vAccess.level != InitLevel) { //not global variable
			if (vAccess.access.t == FAccess::InReg) { //in register
				return new (C) TrEx(new(C)TTemp(vAccess.access.u.reg), C);
			}
			else { // in frame
				auto level = CurLevel();
				if (level == vAccess.level) { //in this frame
					return new(C)TrEx(new(C)TMem(
						new(C)TBinOp(
							T_plus,
							new(C)TTemp(level->Frame->FramePtr().u.reg),
							new(C)TConst(vAccess.access.u.offset)
						)
					),C);
				}
				else { //upvalue, use static link to search
					TExp* start = new(C)TMem(new(C)TBinOp(T_plus,
						new(C)TTemp(level->Frame->FramePtr().u.reg),
						new(C)TConst(level->Frame->StaticLink().u.offset)
					));
					level = level->Parent;
					while (level != vAccess.level) {
						start = new(C)TMem(new(C)TBinOp(T_plus,
							start,
							new(C)TConst(level->Frame->StaticLink().u.offset)
						));
						level = level->Parent;
					}
					//now we have reached the level
					start = new(C)TMem(new(C)TBinOp(T_plus,
						start,
						new(C)TConst(vAccess.access.u.offset)
					));
					return new(C)TrEx(start,C);
				}
			}
		}
		else { //TODO: multi-module if it is global variable
			assert(0);
			return nullptr;
		}
	}

	TrExp* Translate::TransFieldVar(TrExp* var, RecordType* type, Symbol field) {
		int idx = -1;
		for (size_t i = 0; i < type->fieldList.size(); ++i) {
			if (field == type->fieldList[i].first) {
				idx = i;
				break;
			}
		}
		assert(idx >= 0);
		if (idx >= 0)
			return new(C)TrEx(new(C)TMem(new(C)TBinOp(T_plus,
				var->unEx(), new(C)TConst(idx*TIGER_WORD_SIZE)
			)),C);
		else
			return nullptr;
	}

	TrExp* Translate::TransSubscriptVar(TrExp* var, TrExp* exp) {
		auto offset = new(C)TBinOp(T_mul, exp->unEx(), new(C)TConst(TIGER_WORD_SIZE));
		return new(C)TrEx(new(C)TMem(new(C)TBinOp(T_plus,
			var->unEx(), offset		
		)),C);
	}

	TrExp* Translate::TransConst(int i) {
		//TODO: optimize Const_0 and Const_1
		return new(C)TrEx(new(C)TConst(i),C);
	}

	TrExp* Translate::TransStrConst(Symbol s) {
		int idx = -1;
		for (size_t i = 0; i < StringFrags.size(); ++i) {
			if (s == StringFrags[i]) {
				idx = (int)i;
				break;
			}
		}
		if (idx == -1) {
			StringFrags.push_back(s);
			idx = (int)StringFrags.size() - 1;
		}
		//TODO: global link label
		return new(C)TrEx(new(C)TName("S" + std::to_string(idx)),C);
	}

	TrExp* Translate::TransArrayInit(TrExp* size, TrExp* init)
	{
		auto regSiz = temp::newTemp();
		auto regInit = temp::newTemp();
		auto regArr = temp::newTemp();

		return new(C)TrEx(new(C)TEseq(
			new(C)TSeq(
				new(C)TMove(new(C)TTemp(regSiz), size->unEx()),
				new(C)TSeq(
					new(C)TMove(new(C)TTemp(regInit), init->unEx()),
					new(C)TMove(
						new(C)TTemp(regArr), 
						ExternelCall("initArray", {
							new(C)TTemp(regSiz),
							new(C)TTemp(regInit)
						})
					)
				)
			),
			new(C)TTemp(regArr)
		),C);
	}

	TrExp* Translate::TransRecordInit(RecordType* type, 
		const std::vector<Symbol>& fnames, const std::vector<TrExp*>& fexps)
	{
		auto regRec = temp::newTemp();
		TStm* init = new(C)TMove(new(C)TTemp(regRec),
			ExternelCall("initRec", { new(C)TConst(type->GetMemberNum()*TIGER_WORD_SIZE) }));
		for (size_t i = 0; i < fnames.size(); i++) {
			init = new(C)TSeq(init, new(C)TMove(
				new(C)TMem(new(C)TBinOp(T_plus, new(C)TTemp(regRec), new(C)TConst(type->GetMemberOffset(fnames[i])*TIGER_WORD_SIZE))),
				fexps[i]->unEx()
			));
		}
		return new(C)TrEx(new(C)TEseq(init, new(C)TTemp(regRec)),C);
	}

	TrExp* Translate::TransCall(Label f, const std::vector<TrExp*>& exps)
	{
		std::vector<TExp*> params;
		for (auto e : exps) params.push_back(e->unEx());
		return new(C)TrEx(new(C)TCall(
			new(C)TName(f),
			params
		),C);
	}

	TrExp* Translate::TransAssign(TrExp* target, TrExp* exp) {
		return new(C)TrNx(new(C)TMove(
			target->unEx(), 
			exp->unEx()),C
		);
	}

	TrExp* Translate::TransBinarySub(TrExp* lhs, TrExp* rhs)
	{
		TExp* l = lhs->unEx();
		TExp* r = rhs->unEx();

		//constant-folding
		if (l->type == T_Const && r->type == T_Const) {
			return new(C)TrEx(new(C)TConst(
				static_cast<TConst*>(l)->cv - static_cast<TConst*>(r)->cv
			),C);
		}
		else {
			return new(C)TrEx(new(C)TBinOp(T_minus, l, r),C);
		}
	}

	TrExp* Translate::TransBinaryMul(TrExp* lhs, TrExp* rhs) {
		TExp* l = lhs->unEx(), *r = rhs->unEx();
		if (l->type == T_Const && r->type == T_Const) {
			return new(C)TrEx(new(C)TConst(
				static_cast<TConst*>(l)->cv * static_cast<TConst*>(r)->cv
			),C);
		}
		else {
			return new(C)TrEx(new(C)TBinOp(T_mul, l, r),C);
		}
	}

	TrExp* Translate::TransBinaryDiv(TrExp* lhs, TrExp* rhs)
	{
		TExp* l = lhs->unEx(), *r = rhs->unEx();
		//Zero-divide error
		if (r->type == T_Const && static_cast<TConst*>(r)->cv == 0)
			return nullptr;
		if (l->type == T_Const && r->type == T_Const) {
			return new(C)TrEx(new(C)TConst(
				static_cast<TConst*>(l)->cv / static_cast<TConst*>(r)->cv
			),C);
		}
		else {
			return new(C)TrEx(new(C)TBinOp(T_div, l, r),C);
		}
	}

	TrExp* Translate::TransBinaryAdd(TrExp* lhs, TrExp* rhs)
	{
		TExp* l = lhs->unEx(), *r = rhs->unEx();
		if (l->type == T_Const && r->type == T_Const) {
			return new(C)TrEx(new(C)TConst(
				static_cast<TConst*>(l)->cv + static_cast<TConst*>(r)->cv
			),C);
		}
		else {
			return new(C)TrEx(new(C)TBinOp(T_plus, l, r),C);
		}
	}

	TrExp* Translate::TransStrConcat(TrExp* lhs, TrExp* rhs)
	{
		return new(C)TrEx(ExternelCall("concatStr", {
			lhs->unEx(), rhs->unEx()
		}),C);
	}

	tiger::TrExp* Translate::TransRelOp(TrRelOp op, TrExp* lhs, TrExp* rhs, bool strOprand) {
		if (!strOprand) {
			return new(C)TrRelCx(op, lhs, rhs, C);
		}
		else {
			return new(C)TrRelCx(op, 
				new(C)TrEx(ExternelCall("compareStr", { lhs->unEx(), rhs->unEx() }),C),
				new(C)TrEx(new(C)TConst(0),C),C
			);
		}
	}

	tiger::TrExp* Translate::TransLogicOp(TrLogicOp op, TrExp* lhs, TrExp* rhs) {
		return new(C)TrLogicCx(op, lhs, rhs, C);
	}

	TrExp* Translate::TransIf(TrExp* test, TrExp* then, TrExp* elsee)
	{
		return new(C)TrIf(test, then, elsee, C);
	}

	/*TrExp* Translate::TransFor(TrExp* lo, TrExp* hi, TrExp* body)
	{

	}
*/
}