//AST module for tiger compiler
#pragma once
#include <memory>

namespace tiger
{
	struct ABaseNode
	{
		ABaseNode(int _type) :type(_type) {}
		const int type;
	};

	typedef std::shared_ptr<ABaseNode> ASTNode;
}