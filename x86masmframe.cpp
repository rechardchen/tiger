#include "x86masmframe.h"
#include "temp.h"

namespace tiger {
	enum X86_GPR {
		EAX, EBX, ECX, EDX,
		ESI, EDI, EBP, ESP,
	};

	X86MasmFrame::X86MasmFrame(const std::vector<bool>& escape)
	{
		NArgs = (int)escape.size();
	}

	tiger::FAccess X86MasmFrame::FramePtr()
	{
		return InReg(EBP);
	}

	//tiger::FAccess X86MasmFrame::StaticLink()
	//{
	//	return Argument(0);
	//}

	tiger::FAccess X86MasmFrame::Argument(int i)
	{
		//X86 arguments all frame-resident
		return InFrame((i + 2)*TIGER_WORD_SIZE);
	}

	tiger::FAccess X86MasmFrame::ReturnAddress()
	{
		return InFrame(TIGER_WORD_SIZE);
	}

	tiger::FAccess X86MasmFrame::ReturnValue()
	{
		return InReg(EAX);
	}

	tiger::FAccess X86MasmFrame::AllocLocal(bool escape)
	{
		if (!escape)
			return InReg(temp::newTemp());
		else
			return InFrame(StackSize -= TIGER_WORD_SIZE);
	}

}