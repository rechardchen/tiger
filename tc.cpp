#include "allocator.h"
#include "absyn.h"
#include "translate.h"
#include "semant.h"
#include "x86masmframe.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;
using namespace tiger;


int main()
{
	ifstream fin("../samples/test2.tig");
	stringstream ss;
	ss << fin.rdbuf();
	auto tree = parseAST(ss.str());
	dumpAST(tree);
	
	BumpPtrAllocator areana;
	Translate trans(areana);
	trans.SetExternalName([](std::string n) { return n; });
	trans.SetFrameCreator([&](const std::vector<bool>& escape) {
		return new(areana) X86MasmFrame(escape);
	});

	Semant semant(areana);
	semant.SetTranslate(&trans);

	semant.TransProg(tree);

	char _c;
	cin >> _c;

}