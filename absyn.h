//AST module for tiger compiler
#pragma once
#include <string>
#include <memory>
#include <list>

namespace tiger
{
	struct BaseASTNode;
	typedef std::shared_ptr<BaseASTNode> ASTNode;

	struct BaseASTNode
	{
		/*BaseASTNode(int _type) :type(_type) {}
		const int type;*/
	};

	struct NilExp : public BaseASTNode {};
	struct StringExp : public BaseASTNode 
	{ 
		std::string val; 
	};
	struct IntExp : public BaseASTNode 
	{ 
		int val; 
	};
	
	struct Field
	{
		std::string name;
		ASTNode exp;
	};

	struct ArrayExp : public BaseASTNode
	{
		std::string type;
		ASTNode size, init;
	};
	struct RecordExp : public BaseASTNode
	{
		std::string type;
		std::list<Field> fields;
	};
	struct NewExp : public BaseASTNode
	{
		std::string type;
	};
	struct CallExp : public BaseASTNode
	{
		std::string name;
		std::list<ASTNode> params;
	};
	struct MethodCallExp : public BaseASTNode
	{
		ASTNode var;
		std::string method;
		std::list<ASTNode> params;
	};
	struct UnaryOpExp : public BaseASTNode
	{
		enum { OP_NEG } op;
		ASTNode exp;
	};
	struct BinOpExp : public BaseASTNode
	{
		enum {
			OP_MUL, OP_DIV, OP_ADD, OP_SUB,
			OP_EQ, OP_NE, OP_GE, OP_LE, OP_GT, OP_LT,
			OP_AND, OP_OR
		} op;
		ASTNode lhs, rhs;
	};
	struct AssignExp : public BaseASTNode
	{
		//var := exp
		ASTNode var, exp;
	};
	struct IfExp : public BaseASTNode
	{
		//if test then else elsee
		ASTNode test, then, elsee;
	};
	struct WhileExp : public BaseASTNode
	{
		//while test do body
		ASTNode test, body;
	};
	struct ForExp : public BaseASTNode
	{
		//for var := lo to hi do body
		std::string var;
		ASTNode lo, hi, body;
	};
	struct BreakExp : public BaseASTNode
	{

	};
	struct LetExp : public BaseASTNode
	{
		ASTNode decs, exps;
	};
	
	struct SimpleVar : public BaseASTNode
	{
		std::string name;
	};
	struct FieldVar : public BaseASTNode
	{
		//var.field
		ASTNode var;
		std::string field;
	};
	struct SubscriptVar : public BaseASTNode
	{
		//var[exp]
		ASTNode var, exp;
	};
	struct ExpList : public BaseASTNode
	{
		std::list<ASTNode> exps;
	};
	struct DeclareList : public BaseASTNode
	{
		std::list<ASTNode> decs;
	};
	struct TypeDec : public BaseASTNode
	{
		std::string name;
		ASTNode ty;
	};
	struct ClassDec : public BaseASTNode
	{
		std::string name, super;
		std::list<ASTNode> fields;
	};
	struct VarDec : public BaseASTNode
	{
		std::string name, type;
		ASTNode init;
	};
	struct TyFields : public BaseASTNode
	{
		std::list<std::pair<std::string, std::string> > fields;
	};
	struct FuncDec : public BaseASTNode
	{
		std::string name, rtype;
		ASTNode body, params;
	};
	struct ImportDec : public BaseASTNode
	{
		std::string module;
	};
	struct NameTy : public BaseASTNode
	{
		std::string name;
	};
	struct RecordTy : public BaseASTNode
	{
		ASTNode tyfields;
	};
	struct ArrayTy : public BaseASTNode
	{
		std::string type;
	};
	struct ClassTy : public BaseASTNode
	{
		std::string super;
		std::list<ASTNode> fields;
	};
	struct MethodDec : public BaseASTNode
	{
		std::string name, rtype;
		ASTNode body, params;
	};

	ASTNode parseAST(const std::string& source);
}