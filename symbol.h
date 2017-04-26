#pragma once
#include <string>

namespace tiger
{
	class Symbol
	{
	public:
		Symbol(const std::string& name);
		const char* name() const { return mName; }
		bool operator==(const Symbol& rhs) const { return mName == rhs.mName;}

	protected:
		const char* mName = nullptr;
	};
}
