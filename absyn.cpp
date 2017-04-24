#include "absyn.h"
#include "grammar/tigerLexer.h"
#include "grammar/tigerParser.h"
#include "grammar/tigerBaseVisitor.h"
#include "antlr4-runtime.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

namespace tiger
{
	void ASTVisitor::visit(ASTNode node) {
		switch (node->type)
		{
#define DISPATCH(E, T, V) \
		case E: return V((T*)node.get());

		DISPATCH(A_Nil, NilExp, visitNilExp);
		DISPATCH(A_String, StringExp, visitStringExp);
		DISPATCH(A_Int, IntExp, visitIntExp);
		DISPATCH(A_Array, ArrayExp, visitArrayExp);
		DISPATCH(A_Record, RecordExp, visitRecordExp);
		DISPATCH(A_New, NewExp, visitNewExp);
		DISPATCH(A_Call, CallExp, visitCallExp);
		DISPATCH(A_MethodCall, MethodCallExp, visitMethodCallExp);
		DISPATCH(A_UnaryOp, UnaryOpExp, visitUnaryOpExp);
		DISPATCH(A_BinOp, BinOpExp, visitBinaryOpExp);
		DISPATCH(A_Assign, AssignExp, visitAssignExp);
		DISPATCH(A_If, IfExp, visitIfExp);
		DISPATCH(A_While, WhileExp, visitWhileExp);
		DISPATCH(A_For, ForExp, visitForExp);
		DISPATCH(A_Break, BreakExp, visitBreakExp);
		DISPATCH(A_Let, LetExp, visitLetExp);
		DISPATCH(A_SimpleVar, SimpleVar, visitSimpleVar);
		DISPATCH(A_FieldVar, FieldVar, visitFieldVar);
		DISPATCH(A_SubscriptVar, SubscriptVar, visitSubscriptVar);
		DISPATCH(A_ExpList, ExpList, visitExpList);
		DISPATCH(A_DeclareList, DeclareList, visitDeclareList);
		DISPATCH(A_TypeDec, TypeDec, visitTypeDec);
		DISPATCH(A_ClassDec, ClassDec, visitClassDec);
		DISPATCH(A_VarDec, VarDec, visitVarDec);
		DISPATCH(A_TyFields, TyFields, visitTyFields);
		DISPATCH(A_FuncDec, FuncDec, visitFuncDec);
		DISPATCH(A_ImportDec, ImportDec, visitImportDec);
		DISPATCH(A_NameTy, NameTy, visitNameTy);
		DISPATCH(A_RecordTy, RecordTy, visitRecordTy);
		DISPATCH(A_ArrayTy, ArrayTy, visitArrayTy);
		DISPATCH(A_ClassTy, ClassTy, visitClassTy);
		DISPATCH(A_MethodDec, MethodDec, visitMethodDec);
		DISPATCH(A_Field, Field, visitField);
		DISPATCH(A_EField, EField, visitEField);

#undef DISPATCH
		}
		return;
	}
	class AbsynVisitor : public tigerBaseVisitor
	{
	public:
		virtual antlrcpp::Any visitNilExp(tigerParser::NilExpContext *ctx) override {
			return ASTNode(new NilExp);
		}
		virtual antlrcpp::Any visitIntExp(tigerParser::IntExpContext *ctx) override {
			auto exp = new IntExp;
			exp->val = std::stoi(ctx->INT()->getText());
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitStringExp(tigerParser::StringExpContext *ctx) override {
			auto exp = new StringExp;
			exp->val = ctx->STRING()->getText();
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitArrayExp(tigerParser::ArrayExpContext *ctx) override {
			auto exp = new ArrayExp;
			exp->type = ctx->type_id()->getText();
			exp->size = visit(ctx->exp(0));
			exp->init = visit(ctx->exp(1));
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitRecordExp(tigerParser::RecordExpContext *ctx) override {
			auto exp = new RecordExp;
			exp->type = ctx->type_id()->getText();
			
			auto ids = ctx->ID();
			auto values = ctx->exp();
			for (size_t i = 0; i < values.size(); ++i)
			{
				auto efield = new EField;
				efield->name = ids[i]->getText();
				efield->exp = visit(values[i]);
				exp->fields.push_back(ASTNode(efield));
			}
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitNewExp(tigerParser::NewExpContext *ctx) override {
			auto exp = new NewExp;
			exp->type = ctx->type_id()->getText();
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitLvalueExp(tigerParser::LvalueExpContext *ctx) override {
			return visit(ctx->lvalue());
		}
		virtual antlrcpp::Any visitFuncCallExp(tigerParser::FuncCallExpContext *ctx) override {
			auto exp = new CallExp;
			exp->name = ctx->ID()->getText();
			auto params = ctx->exp();
			for (auto e : params) exp->params.push_back(visit(e));
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitMethodCallExp(tigerParser::MethodCallExpContext *ctx) override {
			auto exp = new MethodCallExp;
			exp->var = visit(ctx->lvalue());
			exp->method = ctx->ID()->getText();
			auto params = ctx->exp();
			for (auto e : params) exp->params.push_back(visit(e));
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitNegExp(tigerParser::NegExpContext *ctx) override {
			auto exp = new UnaryOpExp;
			exp->op = UnaryOpExp::OP_NEG;
			exp->exp = visit(ctx->exp());
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitMulDivExp(tigerParser::MulDivExpContext *ctx) override {
			auto exp = new BinOpExp;
			auto opTxt = ctx->op->getText();
			exp->op = opTxt == "*" ? BinOpExp::OP_MUL : BinOpExp::OP_DIV;
			exp->lhs = visit(ctx->exp(0));
			exp->rhs = visit(ctx->exp(1));
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitAddSubExp(tigerParser::AddSubExpContext *ctx) override {
			auto exp = new BinOpExp;
			auto opTxt = ctx->op->getText();
			exp->op = opTxt == "+" ? BinOpExp::OP_ADD : BinOpExp::OP_SUB;
			exp->lhs = visit(ctx->exp(0));
			exp->rhs = visit(ctx->exp(1));
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitRelOpExp(tigerParser::RelOpExpContext *ctx) override {
			auto exp = new BinOpExp;
			auto opTxt = ctx->op->getText();
			if (opTxt == "=")
				exp->op = BinOpExp::OP_EQ;
			else if (opTxt == "<>")
				exp->op = BinOpExp::OP_NE;
			else if (opTxt == ">=")
				exp->op = BinOpExp::OP_GE;
			else if (opTxt == "<=")
				exp->op = BinOpExp::OP_LE;
			else if (opTxt == ">")
				exp->op = BinOpExp::OP_GT;
			else if (opTxt == "<")
				exp->op = BinOpExp::OP_LT;
			exp->lhs = visit(ctx->exp(0));
			exp->rhs = visit(ctx->exp(1));
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitLogicExp(tigerParser::LogicExpContext *ctx) override {
			auto exp = new BinOpExp;
			auto opTxt = ctx->op->getText();
			exp->op = opTxt == "&" ? BinOpExp::OP_AND : BinOpExp::OP_OR;
			exp->lhs = visit(ctx->exp(0));
			exp->rhs = visit(ctx->exp(1));
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitExplistExp(tigerParser::ExplistExpContext *ctx) override {
			return visit(ctx->exps());
		}
		virtual antlrcpp::Any visitAssignExp(tigerParser::AssignExpContext *ctx) override {
			auto exp = new AssignExp;
			exp->var = visit(ctx->lvalue());
			exp->exp = visit(ctx->exp());
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitIfExp(tigerParser::IfExpContext *ctx) override {
			auto exp = new IfExp;
			exp->test = visit(ctx->exp(0));
			exp->then = visit(ctx->exp(1));
			auto elsee = ctx->exp(2);
			if (elsee)
				exp->elsee = visit(elsee);
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitWhileExp(tigerParser::WhileExpContext *ctx) override {
			auto exp = new WhileExp;
			exp->test = visit(ctx->exp(0));
			exp->body = visit(ctx->exp(1));
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitForExp(tigerParser::ForExpContext *ctx) override {
			auto exp = new ForExp;
			exp->var = ctx->ID()->getText();
			exp->lo = visit(ctx->exp(0));
			exp->hi = visit(ctx->exp(1));
			exp->body = visit(ctx->exp(2));
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitBreakExp(tigerParser::BreakExpContext *ctx) override {
			return ASTNode(new BreakExp);
		}
		virtual antlrcpp::Any visitLetExp(tigerParser::LetExpContext *ctx) override {
			auto exp = new LetExp;
			exp->decs = visit(ctx->decs());
			exp->exps = visit(ctx->exps());
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitSimpleVar(tigerParser::SimpleVarContext *ctx) override {
			auto var = new SimpleVar;
			var->name = ctx->ID()->getText();
			return ASTNode(var);
		}
		virtual antlrcpp::Any visitFieldVar(tigerParser::FieldVarContext *ctx) override {
			auto var = new FieldVar;
			var->var = visit(ctx->lvalue());
			var->field = ctx->ID()->getText();
			return ASTNode(var);
		}
		virtual antlrcpp::Any visitSubScriptVar(tigerParser::SubScriptVarContext *ctx) override {
			auto var = new SubscriptVar;
			var->var = visit(ctx->lvalue());
			var->exp = visit(ctx->exp());
			return ASTNode(var);
		}
		virtual antlrcpp::Any visitExprList(tigerParser::ExprListContext *ctx) override {
			auto explist = new ExpList;
			for (auto e : ctx->exp())
				explist->exps.push_back(visit(e));
			return ASTNode(explist);
		}
		virtual antlrcpp::Any visitDecList(tigerParser::DecListContext *ctx) override {
			auto declist = new DeclareList;
			for (auto d : ctx->dec())
			{
				declist->decs.push_back(visit(d));
			}
			return ASTNode(declist);
		}
		virtual antlrcpp::Any visitTypeDec(tigerParser::TypeDecContext *ctx) override {
			auto typedec = new TypeDec;
			typedec->name = ctx->ID()->getText();
			typedec->ty = visit(ctx->ty());
			return ASTNode(typedec);
		}
		virtual antlrcpp::Any visitClassDec(tigerParser::ClassDecContext *ctx) override {
			auto classdec = new ClassDec;
			classdec->name = ctx->ID()->getText();
			auto super = ctx->type_id();
			classdec->super = super ? super->getText() : "";
			for (auto f : ctx->classfields())
			{
				classdec->fields.push_back(visit(f));
			}
			return ASTNode(classdec);
		}
		virtual antlrcpp::Any visitDecVarDec(tigerParser::DecVarDecContext *ctx) override {
			return visit(ctx->vardec());
		}
		virtual antlrcpp::Any visitFunDec(tigerParser::FunDecContext *ctx) override {
			auto fundec = new FuncDec;
			fundec->name = ctx->ID()->getText();
			fundec->params = visit(ctx->tyfields());
			auto rtype = ctx->type_id();
			fundec->rtype = rtype ? rtype->getText() : "";
			fundec->body = visit(ctx->exp());
			return ASTNode(fundec);
		}
		virtual antlrcpp::Any visitImportDec(tigerParser::ImportDecContext *ctx) override {
			auto imp = new ImportDec;
			imp->module = ctx->STRING()->getText();
			return ASTNode(imp);
		}
		virtual antlrcpp::Any visitNameTy(tigerParser::NameTyContext *ctx) override {
			auto nameTy = new NameTy;
			nameTy->name = ctx->type_id()->getText();
			return ASTNode(nameTy);
		}
		virtual antlrcpp::Any visitRecordTy(tigerParser::RecordTyContext *ctx) override {
			auto recordTy = new RecordTy;
			recordTy->tyfields = visit(ctx->tyfields());
			return ASTNode(recordTy);
		}
		virtual antlrcpp::Any visitArrayTy(tigerParser::ArrayTyContext *ctx) override {
			auto arrayTy = new ArrayTy;
			arrayTy->type = ctx->type_id()->getText();
			return ASTNode(arrayTy);
		}
		virtual antlrcpp::Any visitClassTy(tigerParser::ClassTyContext *ctx) override {
			auto classTy = new ClassTy;
			auto super = ctx->type_id();
			classTy->super = super ? super->getText() : "";
			for (auto f : ctx->classfields()) classTy->fields.push_back(visit(f));
			return ASTNode(classTy);
		}
		virtual antlrcpp::Any visitTyFields(tigerParser::TyFieldsContext *ctx) override {
			auto tyfields = new TyFields;
			auto ids = ctx->ID();
			auto typeids = ctx->type_id();
			for (size_t i = 0; i < ids.size(); ++i)
			{
				auto field = new Field;
				field->name = ids[i]->getText();
				field->type = typeids[i]->getText();
				tyfields->fields.push_back(ASTNode(field));
			}
			return ASTNode(tyfields);
		}
		virtual antlrcpp::Any visitClassVarDec(tigerParser::ClassVarDecContext *ctx) override {
			return visit(ctx->vardec());
		}
		virtual antlrcpp::Any visitMethodDec(tigerParser::MethodDecContext *ctx) override {
			auto method = new MethodDec;
			method->name = ctx->ID()->getText();
			method->params = visit(ctx->tyfields());
			auto rtype = ctx->type_id();
			method->rtype = rtype ? rtype->getText() : "";
			method->body = visit(ctx->exp());
			return ASTNode(method);
		}
		virtual antlrcpp::Any visitVarDec(tigerParser::VarDecContext *ctx) override {
			auto var = new VarDec;
			var->name = ctx->ID()->getText();
			auto _type = ctx->type_id();
			var->type = _type ? _type->getText() : "";
			var->init = visit(ctx->exp());
			return ASTNode(var);
		}
	};

	tiger::ASTNode parseAST(const std::string& source) {
		using namespace antlr4;

		std::stringstream ss(source);
		ANTLRInputStream input(ss);
		tigerLexer lexer(&input);
		CommonTokenStream tokens(&lexer);
		tigerParser parser(&tokens);

		auto tree = parser.prog();
		AbsynVisitor visitor;
		return visitor.visit(tree);
	}


	//TODO: dump ast after type-induction
	class ASTDumper:public ASTVisitor
	{
	protected:
		void dumpIndents() {
			for (size_t i = 0; i < indents.size(); ++i) {
				if (!indents[i])
					cout << "|-";
				else if (i + 1 == indents.size())
					cout << "`-";
				else
					cout << "  ";
			}
		}

		template<typename Iter>
		Iter next(Iter iter) {
			return ++iter;
		}

		virtual void visitNilExp(NilExp* nil) override {
			dumpIndents();
			cout << "NilLiteral " << this << endl;
		}
		virtual void visitIntExp(IntExp* i) override{
			dumpIndents();
			cout << "IntLiteral " << this << " " << i->val << endl;
		}
		virtual void visitStringExp(StringExp* s) override{
			dumpIndents();
			cout << "StringLiteral " << this << " " << s->val << endl;
		}
		virtual void visitArrayExp(ArrayExp* arr) override{
			dumpIndents();

			cout << "ArrayInit " << this << " " << arr->type << "[]" << endl;
			indents.push_back(false);
			visit(arr->size);
			indents.back() = true;
			visit(arr->init);
			indents.pop_back();
		}
		virtual void visitRecordExp(RecordExp* record) override {
			dumpIndents();

			cout << "RecordInit " << this << " " << record->type << "{}" << endl;
			if (!record->fields.empty()) {
				indents.push_back(false);
				for (auto iter = record->fields.begin(); iter != record->fields.end(); ++iter) {
					if (next(iter) == record->fields.end()) {
						indents.back() = true;
					}
					visit(*iter);
				}
				indents.pop_back();
			}
		}
		virtual void visitNewExp(NewExp* new_) override{
			dumpIndents();

			cout << "NewExp " << this << " " << new_->type << endl;
		}
		virtual void visitCallExp(CallExp* call) override {
			dumpIndents();

			cout << "CallExp " << this << " " << call->name << endl;
			if (!call->params.empty()) {
				indents.push_back(false);
				for (auto iter = call->params.begin(); iter != call->params.end(); ++iter) {
					if (next(iter) == call->params.end()) {
						indents.back() = true;
					}
					visit(*iter);
				}
				indents.pop_back();
			}
		}
		virtual void visitMethodCallExp(MethodCallExp* call) override {
			dumpIndents();

			cout << "MethodCallExp " << this << " " << call->method << endl;
			indents.push_back(call->params.empty() ? true : false);
			visit(call->var);
			for (auto iter = call->params.begin(); iter != call->params.end(); ++iter) {
				if (next(iter) == call->params.end()) {
					indents.back() = true;
				}
				visit(*iter);
			}
			indents.pop_back();
		}
		virtual void visitUnaryOpExp(UnaryOpExp* op) override {
			dumpIndents();

			cout << "UnaryOpExp " << this << " '-'" << endl;
			indents.push_back(true);
			visit(op->exp);
			indents.pop_back();
		}
		virtual void visitBinaryOpExp(BinOpExp* op) override {
			dumpIndents();
			static char* opsymbols[] = { 
				"*","/","+","-","=","<>",">=","<=",">","<","&","|" 
			};
			cout << "BinaryOpExp " << this << " " << opsymbols[op->op] << endl;
			indents.push_back(false);
			visit(op->lhs);
			indents.back() = true;
			visit(op->rhs);
			indents.pop_back();
		}
		virtual void visitAssignExp(AssignExp* assign) override {
			dumpIndents();
			cout << "AssignExp " << this << endl;
			indents.push_back(false);
			visit(assign->var);
			indents.back() = true;
			visit(assign->exp);
			indents.pop_back();
		}
		virtual void visitIfExp(IfExp* iff) override {
			dumpIndents();
			cout << "IfExp " << this << endl;
			indents.push_back(false);
			visit(iff->test);
			if (!iff->elsee) {
				indents.back() = true;
				visit(iff->then);
			}
			else {
				visit(iff->then);
				indents.back() = true;
				visit(iff->elsee);
			}
			indents.pop_back();
		}
		virtual void visitWhileExp(WhileExp* while_) override {
			dumpIndents();
			cout << "WhileExp " << this << endl;
			indents.push_back(false);
			visit(while_->test);
			indents.back() = true;
			visit(while_->body);
			indents.pop_back();
		}
		virtual void visitForExp(ForExp* for_) override {
			dumpIndents();
			cout << "ForExp " << this << " " << for_->var << endl;
			indents.push_back(false);
			visit(for_->lo);
			visit(for_->hi);
			indents.back() = true;
			visit(for_->body);
			indents.pop_back();
		}
		virtual void visitBreakExp(BreakExp*) override {
			dumpIndents();
			cout << "BreakExp " << this << endl;
		}
		virtual void visitLetExp(LetExp* let) override {
			dumpIndents();
			cout << "LetExp " << this << endl;
			indents.push_back(false);
			visit(let->decs);
			indents.back() = true;
			visit(let->exps);
			indents.pop_back();
		}
		virtual void visitSimpleVar(SimpleVar* sv) override {
			dumpIndents();
			cout << "SimpleVarRef " << this << " " << sv->name << endl;
		}
		virtual void visitFieldVar(FieldVar* fv) override {
			dumpIndents();
			cout << "FieldVarRef " << this << " ." << fv->field << endl;
			indents.push_back(true);
			visit(fv->var);
			indents.pop_back();
		}
		virtual void visitSubscriptVar(SubscriptVar* sv) override {
			dumpIndents();
			cout << "SubscriptVarRef " << this << endl;
			indents.push_back(false);
			visit(sv->var);
			indents.back() = true;
			visit(sv->exp);
			indents.pop_back();
		}
		virtual void visitExpList(ExpList* el) override {
			dumpIndents();
			cout << "ExpList " << this << endl;
			
			if (!el->exps.empty()) {
				indents.push_back(false);
				for (auto iter = el->exps.begin(); iter != el->exps.end(); ++iter) {
					if (next(iter) == el->exps.end()) {
						indents.back() = true;
					}
					visit(*iter);
				}
				indents.pop_back();
			}
		}
		virtual void visitDeclareList(DeclareList* dl) override {
			dumpIndents();
			cout << "DeclarationList " << this << endl;
			if (!dl->decs.empty()) {
				indents.push_back(false);
				for (auto iter = dl->decs.begin(); iter != dl->decs.end(); ++iter) {
					if (next(iter) == dl->decs.end()) {
						indents.back() = true;
					}
					visit(*iter);
				}
				indents.pop_back();
			}
		}
		virtual void visitTypeDec(TypeDec* td) override {
			dumpIndents();
			cout << "TypeDeclaration " << this << " " << td->name << endl;
			indents.push_back(true);
			visit(td->ty);
			indents.pop_back();
		}
		virtual void visitClassDec(ClassDec* cd) override {
			dumpIndents();
			cout << "ClassDeclaration " << this << " " << cd->name;
			if (!cd->super.empty()) {
				cout << "(extends " << cd->super << ")";
			}
			cout << endl;
			if (!cd->fields.empty()) {
				indents.push_back(false);
				for (auto iter = cd->fields.begin(); iter != cd->fields.end(); ++iter) {
					if (next(iter) == cd->fields.end()) {
						indents.back() = true;
					}
					visit(*iter);
				}
				indents.pop_back();
			}
		}
		virtual void visitVarDec(VarDec* vd) override {
			dumpIndents();
			cout << "VarDeclaration " << this << " " << vd->name;
			if (!vd->type.empty()) {
				cout << " of type " << vd->type;
			}
			cout << endl;
			indents.push_back(true);
			visit(vd->init);
			indents.pop_back();
		}
		virtual void visitFuncDec(FuncDec* fd) override {
			dumpIndents();
			cout << "FuncDeclaration " << this << " " << fd->name 
				<< "(" << fd->rtype << ")" << endl;
			indents.push_back(false);
			TyFields* tfields = (TyFields*)fd->params.get();
			for (auto field : tfields->fields)
				visit(field);
			indents.back() = true;
			visit(fd->body);
			indents.pop_back();
		}
		virtual void visitImportDec(ImportDec* id) override {
			dumpIndents();
			cout << "ImportDeclaration " << this << " " << id->module << endl;
		}
		virtual void visitNameTy(NameTy* nt) override {
			dumpIndents();
			cout << "TypeAlias " << this << " " << nt->name << endl;
		}
		virtual void visitRecordTy(RecordTy* rt) override {
			dumpIndents();
			cout << "RecordTypeDef " << this << endl;
			indents.push_back(false);
			TyFields* tfields = (TyFields*)rt->tyfields.get();
			for (auto iter = tfields->fields.begin(); iter != tfields->fields.end(); ++iter) {
				if (next(iter) == tfields->fields.end()) {
					indents.back() = true;
				}
				visit(*iter);
			}
			indents.pop_back();
		}
		virtual void visitArrayTy(ArrayTy* at) override {
			dumpIndents();
			cout << "ArrayTypeDef " << this << " " << at->type << "[]" << endl;
		}
		virtual void visitClassTy(ClassTy* ct) override {
			dumpIndents();
			cout << "ClassTypeDef " << this << " ";
			if (!ct->super.empty())
				cout << "extends " << ct->super << endl;
			indents.push_back(false);
			for (auto iter = ct->fields.begin(); iter != ct->fields.end(); ++iter) {
				if (next(iter) == ct->fields.end()) {
					indents.back() = true;
				}
				visit(*iter);
			}
			indents.pop_back();
		}
		virtual void visitMethodDec(MethodDec* md) override {
			dumpIndents();
			cout << "MethodDeclaration " << this << " " << md->name
				<< "(" << md->rtype << ")" << endl;
			indents.push_back(false);
			TyFields* tfields = (TyFields*)md->params.get();
			for (auto field : tfields->fields) visit(field);
			indents.back() = true;
			visit(md->body);
			indents.pop_back();
		}
		virtual void visitField(Field* f) override {
			dumpIndents();
			cout << "FieldDec " << this << " "
				<< f->name << ":" << f->type << endl;
		}
		virtual void visitEField(EField* e) override {
			dumpIndents();
			cout << "EFieldDec " << this << " " << e->name << endl;
			indents.push_back(true);
			visit(e->exp);
			indents.pop_back();
		}
		std::vector<bool> indents; //right
	};

	void dumpAST(ASTNode tree) {
		ASTDumper dumper;
		dumper.visit(tree);
	}

}
