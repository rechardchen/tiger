#include "tree.h"
#include "translate.h"

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

	TrExp* Translate::CombineStm(TrExp* s1, TrExp* s2)
	{
		assert(s1 != nullptr || s2 != nullptr);
		if (s1 == nullptr) 
			return new(C) TrNx(s2->unNx());
		else if (s2 == nullptr) 
			return new(C) TrNx(s1->unNx());
		else
			return new(C)TrNx(
				new(C)TSeq(
					s1->unNx(), 
					s2->unNx()
				)
			);
	}

	TrExp* Translate::TransSimpleVar(TrAccess vAccess)
	{
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

}