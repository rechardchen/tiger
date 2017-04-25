#include "antlr4-runtime.h"
#include "absyn.h"
#include <fstream>

using namespace std;
using namespace tiger;
int main()
{
	ifstream in("../samples/test49.tig");
	stringstream ss;
	ss << in.rdbuf();
	dumpAST(parseAST(ss.str()));
	char c;
	cin >> c;

}