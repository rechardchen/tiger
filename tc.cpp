#include "allocator.h"
#include "absyn.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;
using namespace tiger;


int main()
{
	ifstream fin("../samples/merge.tig");
	stringstream ss;
	ss << fin.rdbuf();
	auto tree = parseAST(ss.str());
	dumpAST(tree);
	char _c;
	cin >> _c;

}