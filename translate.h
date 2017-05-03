#pragma once
#include "temp.h"
#include <vector>

namespace tiger {
	struct TExp;
	struct TStm;
	struct TCjump;

	struct TrExp {
		virtual TExp* unEx() = 0;
		virtual TStm* unNx() = 0;
		virtual TStm* unCx(Label t, Label f) = 0;
	};

	struct TrEx : public TrExp {
		virtual TExp* unEx() override { return e; }
		virtual TStm* unNx() override;
		virtual TStm* unCx(Label t, Label f) override;

		TExp* e;
	};

	struct TrNx : public TrExp {
		virtual TExp* unEx() override;
		virtual TStm* unNx() override { return s; }
		virtual TStm* unCx(Label t, Label f) override;
		TStm* s;
	};

	struct TrCx : public TrExp {
		virtual TExp* unEx() override;
		virtual TStm* unNx() override;
		virtual TStm* unCx(Label t, Label f) override;

		TStm* s;
		std::vector<Label*> truelist, falselist;
	};
}