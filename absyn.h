//AST module for tiger compiler
#pragma once
#include <string>
#include <memory>
#include <list>

namespace tiger
{
	struct BaseASTNode;
	typedef std::shared_ptr<BaseASTNode> ASTNode;

	enum ASTNodeType
	{
		A_Invalid, A_Nil, A_String, A_Int, A_Array, A_Record, A_New, A_Call, A_MethodCall,
		A_UnaryOp, A_BinOp, A_Assign, A_If, A_While, A_For, A_Break, A_Let,
		A_SimpleVar, A_FieldVar, A_SubscriptVar, A_ExpList, A_DeclareList, A_TypeDec, A_ClassDec, A_VarDec,
		A_TyFields, A_FuncDec, A_ImportDec, A_NameTy, A_RecordTy, A_ArrayTy, A_ClassTy, A_MethodDec
	};
	struct BaseASTNode
	{
		BaseASTNode(int _type=A_Invalid) :type(_type) {}
		const int type;
	};
	struct NilExp : public BaseASTNode { NilExp() :BaseASTNode(A_Nil) {} };
	struct StringExp : public BaseASTNode 
	{ 
		StringExp() :BaseASTNode(A_String) {}
		std::string val; 
	};
	struct IntExp : public BaseASTNode 
	{ 
		IntExp() :BaseASTNode(A_Int) {}
		int val; 
	};
	
	struct Field
	{
		std::string name;
		ASTNode exp;
	};

	struct ArrayExp : public BaseASTNode
	{
		ArrayExp() :BaseASTNode(A_Array) {}
		std::string type;
		ASTNode size, init;
	};
	struct RecordExp : public BaseASTNode
	{
		RecordExp() :BaseASTNode(A_Record) {}
		std::string type;
		std::list<Field> fields;
	};
	struct NewExp : public BaseASTNode
	{
		NewExp() :BaseASTNode(A_New) {}
		std::string type;
	};
	struct CallExp : public BaseASTNode
	{
		CallExp() :BaseASTNode(A_Call) {}
		std::string name;
		std::list<ASTNode> params;
	};
	struct MethodCallExp : public BaseASTNode
	{
		MethodCallExp() :BaseASTNode(A_MethodCall) {}
		ASTNode var;
		std::string method;
		std::list<ASTNode> params;
	};
	struct UnaryOpExp : public BaseASTNode
	{
		UnaryOpExp() :BaseASTNode(A_UnaryOp) {}
		enum { OP_NEG } op;
		ASTNode exp;
	};
	struct BinOpExp : public BaseASTNode
	{
		BinOpExp() :BaseASTNode(A_BinOp) {}
		enum {
			OP_MUL, OP_DIV, OP_ADD, OP_SUB,
			OP_EQ, OP_NE, OP_GE, OP_LE, OP_GT, OP_LT,
			OP_AND, OP_OR
		} op;
		ASTNode lhs, rhs;
	};
	struct AssignExp : public BaseASTNode
	{
		AssignExp() :BaseASTNode(A_Assign) {}
		//var := exp
		ASTNode var, exp;
	};
	struct IfExp : public BaseASTNode
	{
		IfExp() :BaseASTNode(A_If) {}
		//if test then else elsee
		ASTNode test, then, elsee;
	};
	struct WhileExp : public BaseASTNode
	{
		WhileExp() :BaseASTNode(A_While) {}
		//while test do body
		ASTNode test, body;
	};
	struct ForExp : public BaseASTNode
	{
		ForExp() :BaseASTNode(A_For) {}
		//for var := lo to hi do body
		std::string var;
		ASTNode lo, hi, body;
	};
	struct BreakExp : public BaseASTNode
	{
		BreakExp() :BaseASTNode(A_Break) {}
	};
	struct LetExp : public BaseASTNode
	{
		LetExp() :BaseASTNode(A_Let) {}
		ASTNode decs, exps;
	};
	
	struct SimpleVar : public BaseASTNode
	{
		SimpleVar() :BaseASTNode(A_SimpleVar) {}
		std::string name;
	};
	struct FieldVar : public BaseASTNode
	{
		FieldVar() :BaseASTNode(A_FieldVar) {}
		//var.field
		ASTNode var;
		std::string field;
	};
	struct SubscriptVar : public BaseASTNode
	{
		SubscriptVar() :BaseASTNode(A_SubscriptVar) {}
		//var[exp]
		ASTNode var, exp;
	};
	struct ExpList : public BaseASTNode
	{
		ExpList() :BaseASTNode(A_ExpList) {}
		std::list<ASTNode> exps;
	};
	struct DeclareList : public BaseASTNode
	{
		DeclareList() :BaseASTNode(A_DeclareList) {}
		std::list<ASTNode> decs;
	};
	struct TypeDec : public BaseASTNode
	{
		TypeDec() :BaseASTNode(A_TypeDec) {}
		std::string name;
		ASTNode ty;
	};
	struct ClassDec : public BaseASTNode
	{
		ClassDec() :BaseASTNode(A_ClassDec) {}
		std::string name, super;
		std::list<ASTNode> fields;
	};
	struct VarDec : public BaseASTNode
	{
		VarDec() :BaseASTNode(A_VarDec) {}
		std::string name, type;
		ASTNode init;
	};
	struct TyField {
		std::string name;
		std::string type;
		//bool escape = false;
	};
	struct TyFields : public BaseASTNode
	{
		TyFields() :BaseASTNode(A_TyFields) {}
		std::list<TyField> fields;
	};
	struct FuncDec : public BaseASTNode
	{
		FuncDec() :BaseASTNode(A_FuncDec) {}
		std::string name, rtype;
		ASTNode body, params;
	};
	struct ImportDec : public BaseASTNode
	{
		ImportDec() :BaseASTNode(A_ImportDec) {}
		std::string module;
	};
	struct NameTy : public BaseASTNode
	{
		NameTy() :BaseASTNode(A_NameTy) {}
		std::string name;
	};
	struct RecordTy : public BaseASTNode
	{
		RecordTy() :BaseASTNode(A_RecordTy) {}
		ASTNode tyfields;
	};
	struct ArrayTy : public BaseASTNode
	{
		ArrayTy() :BaseASTNode(A_ArrayTy) {}
		std::string type;
	};
	struct ClassTy : public BaseASTNode
	{
		ClassTy() :BaseASTNode(A_ClassTy) {}
		std::string super;
		std::list<ASTNode> fields;
	};
	struct MethodDec : public BaseASTNode
	{
		MethodDec() :BaseASTNode(A_MethodDec) {}
		std::string name, rtype;
		ASTNode body, params;
	};

	class ASTVisitor
	{
	public:
		virtual void visit(ASTNode) final;

	protected:
		virtual void visitNilExp(NilExp*) {}
		virtual void visitIntExp(IntExp*) {}
		virtual void visitStringExp(StringExp*) {}
		virtual void visitArrayExp(ArrayExp*) {}
		virtual void visitRecordExp(RecordExp*) {}
		virtual void visitNewExp(NewExp*) {}
		virtual void visitCallExp(CallExp*) {}
		virtual void visitMethodCallExp(MethodCallExp*) {}
		virtual void visitUnaryOpExp(UnaryOpExp*) {}
		virtual void visitBinaryOpExp(BinOpExp*) {}
		virtual void visitAssignExp(AssignExp*) {}
		virtual void visitIfExp(IfExp*) {}
		virtual void visitWhileExp(WhileExp*) {}
		virtual void visitForExp(ForExp*) {}
		virtual void visitBreakExp(BreakExp*) {}
		virtual void visitLetExp(LetExp*) {}
		virtual void visitSimpleVar(SimpleVar*) {}
		virtual void visitFieldVar(FieldVar*) {}
		virtual void visitSubscriptVar(SubscriptVar*) {}
		virtual void visitExpList(ExpList*) {}
		virtual void visitDeclareList(DeclareList*) {}
		virtual void visitTypeDec(TypeDec*) {}
		virtual void visitClassDec(ClassDec*) {}
		virtual void visitVarDec(VarDec*) {}
		virtual void visitTyFields(TyFields*) {}
		virtual void visitFuncDec(FuncDec*) {}
		virtual void visitImportDec(ImportDec*) {}
		virtual void visitNameTyp(NameTy*) {}
		virtual void visitRecordTy(RecordTy*) {}
		virtual void visitArrayTy(ArrayTy*) {}
		virtual void visitClassTy(ClassTy*) {}
		virtual void visitMethodDec(MethodDec*) {}
	};
	//AST 
	ASTNode parseAST(const std::string& source);
	void dumpAST(ASTNode tree);
}