#pragma once
#include "temp.h"
#include "allocator.h"
#include "frame.h"
#include <vector>

namespace tiger {
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
		//TODO: delete this member, use a TU-Context instead
		TrLevel(BumpPtrAllocator& context);
		TrAccess AllocLocal(bool escape);
		TrAccess Argument(int i);

	public:
		TrLevel* Parent = nullptr;
		Frame* Frame = nullptr;
		Label Name;
		std::vector<bool> Formals;

	protected:
		BumpPtrAllocator& C;
	};


	//TranslationUnit, IR-tree translator
	class Translate {
	public:
		Translate(BumpPtrAllocator& allocator);

		TrLevel* OutmostLevel() { return InitLevel; }
		TrLevel* NewLevel(TrLevel* parent, Label name, const std::vector<bool>& formals);
		TrLevel* CurLevel() const { return CurrentLevel; }
		void	 ExitLevel(TrExp* body);

		TrExp* CombineStm(TrExp* s1, TrExp* s2);
		TrExp* TransSimpleVar(TrAccess);
		TrExp* TransAssign(TrExp* target, TrExp* exp);
		
	private:
		TrLevel* InitLevel, *CurrentLevel;
		BumpPtrAllocator& C;
	};
}