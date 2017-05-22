#pragma once
#include "frame.h"

namespace tiger {
	class X86MasmFrame : public Frame {
	public:
		X86MasmFrame(const std::vector<bool>& escape);

		//virtual FAccess StaticLink() override;
		virtual FAccess FramePtr() override;
		virtual FAccess Argument(int i) override;
		virtual FAccess ReturnAddress() override;
		virtual FAccess ReturnValue() override;

		virtual FAccess AllocLocal(bool escape)override;

		//static Frame* Create(const std::vector<bool>&);

	protected:
		int StackSize = 0;
		int NArgs = 0;
	};
}