#include "absyn.h"
#include "symbol.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;
using namespace tiger;

#pragma pack(push, 1)
struct C {
	char c;
	union {
		double d;
		long double ld;
		long long ll;
		void* p;
	}x;
};
#pragma pack(pop)
int main()
{
	/*ifstream in("../samples/test49.tig");
	stringstream ss;
	ss << in.rdbuf();
	dumpAST(parseAST(ss.str()));*/
	//Symbol s("rechardchen"), t("rechardchen");
	cout << sizeof(C) << endl;
	cout << offsetof(C, x) << endl;
	cout << alignof(C) << endl;

	char _c;
	cin >> _c;

}