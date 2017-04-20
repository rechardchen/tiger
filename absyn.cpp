#include "absyn.h"
#include "grammar/tigerLexer.h"
#include "grammar/tigerParser.h"
#include "grammar/tigerBaseVisitor.h"
#include "antlr4-runtime.h"

namespace tiger
{
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
				exp->fields.push_back({
					ids[i]->getText(),
					visit(values[i])
				});
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
			exp->elsee = elsee ? visit(elsee) : nullptr;
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
			fundec->rtype = ctx->type_id()->getText();
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
				tyfields->fields.push_back(std::make_pair(
					ids[i]->getText(), typeids[i]->getText()
					));
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

	tiger::ASTNode parseAST(const std::string& source)
	{
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

	class ASTDumper
	{

	};
}