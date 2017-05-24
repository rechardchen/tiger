#pragma once
#include "frame.h"
#include <vector>

namespace tiger {
	struct TExp;
	class X86MasmFrame : public Frame {
	public:
		X86MasmFrame(const std::vector<bool>& escape);

		virtual FAccess FramePtr() override;
		virtual FAccess Argument(int i) override;
		virtual FAccess ReturnAddress() override;
		virtual FAccess ReturnValue() override;

		virtual FAccess AllocLocal(bool escape)override;


	protected:
		int StackSize = 0;
		int NArgs = 0;
	};
}