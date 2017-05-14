#include "translate.h"
#include "type.h"
#include "tree.h"


namespace tiger {

	class TrEx : public TrExp {
	public:
		TrEx(TExp* e) : e(e) {}

		virtual TExp* unEx() override { return e; }
		virtual TStm* unNx() override;
		virtual TStm* unCx(Label t, Label f) override;
	protected:
		TExp* e;
	};

	class TrNx : public TrExp {
	public:
		TrNx(TStm* s) :s(s) {}

		virtual TExp* unEx() override;
		virtual TStm* unNx() override { return s; }
		virtual TStm* unCx(Label t, Label f) override;
	protected:
		TStm* s;
	};

	class TrCx : public TrExp {
	public:
		virtual TExp* unEx() override;
		virtual TStm* unNx() override;
		virtual TStm* unCx(Label t, Label f) override;
	protected:
		TStm* s;
		std::vector<Label*> truelist, falselist;
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
			)
		);
	}

	TrExp* Translate::TransSimpleVar(TrAccess vAccess)
	{
		if (vAccess.level != InitLevel) { //not global variable
			if (vAccess.access.t == FAccess::InReg) { //in register
				return new (C) TrEx(new(C)TTemp(vAccess.access.u.reg));
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
					));
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
					return new(C)TrEx(start);
				}
			}
		}
		else { //TODO: if it is global variable
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
			)));
		else
			return nullptr;
	}

	TrExp* Translate::TransSubscriptVar(TrExp* var, TrExp* exp) {
		auto offset = new(C)TBinOp(T_mul, exp->unEx(), new(C)TConst(TIGER_WORD_SIZE));
		return new(C)TrEx(new(C)TMem(new(C)TBinOp(T_plus,
			var->unEx(), offset		
		)));
	}

	TrExp* Translate::TransConst(int i) {
		//TODO: optimize Const_0 and Const_1
		return new(C)TrEx(new(C)TConst(i));
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
		return new(C)TrEx(new(C)TName("S" + std::to_string(idx)));
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
		));
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
		return new(C)TrEx(new(C)TEseq(init, new(C)TTemp(regRec)));
	}

	TrExp* Translate::TransCall(Label f, const std::vector<TrExp*>& exps)
	{
		std::vector<TExp*> params;
		for (auto e : exps) params.push_back(e->unEx());
		return new(C)TrEx(new(C)TCall(
			new(C)TName(f),
			params
		));
	}

	TrExp* Translate::TransAssign(TrExp* target, TrExp* exp) {
		return new(C)TrNx(new(C)TMove(
			target->unEx(), 
			exp->unEx())
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
			));
		}
		else {
			return new(C)TrEx(new(C)TBinOp(T_minus, l, r));
		}
	}

	TrExp* Translate::TransBinaryMul(TrExp* lhs, TrExp* rhs) {
		TExp* l = lhs->unEx(), *r = rhs->unEx();
		if (l->type == T_Const && r->type == T_Const) {
			return new(C)TrEx(new(C)TConst(
				static_cast<TConst*>(l)->cv * static_cast<TConst*>(r)->cv
			));
		}
		else {
			return new(C)TrEx(new(C)TBinOp(T_mul, l, r));
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
			));
		}
		else {
			return new(C)TrEx(new(C)TBinOp(T_div, l, r));
		}
	}

	TrExp* Translate::TransBinaryAdd(TrExp* lhs, TrExp* rhs)
	{
		TExp* l = lhs->unEx(), *r = rhs->unEx();
		if (l->type == T_Const && r->type == T_Const) {
			return new(C)TrEx(new(C)TConst(
				static_cast<TConst*>(l)->cv + static_cast<TConst*>(r)->cv
			));
		}
		else {
			return new(C)TrEx(new(C)TBinOp(T_plus, l, r));
		}
	}

	TrExp* Translate::TransStrConcat(TrExp* lhs, TrExp* rhs)
	{
		return new(C)TrEx(ExternelCall("concat_str", {
			lhs->unEx(), rhs->unEx()
		}));
	}

	/*TrExp* Translate::TransFor(TrExp* lo, TrExp* hi, TrExp* body)
	{

	}
*/
}