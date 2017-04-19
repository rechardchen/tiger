#include "absyn.h"
#include "grammar/tigerBaseVisitor.h"

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
			for (int i = 0; i < values.size(); ++i)
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
			for (auto& e : params) exp->params.push_back(visit(e));
			return ASTNode(exp);
		}
		virtual antlrcpp::Any visitMethodCallExp(tigerParser::MethodCallExpContext *ctx) override {
			auto exp = new MethodCallExp;
			exp->var = visit(ctx->lvalue());
			exp->method = ctx->ID()->getText();
			auto params = ctx->exp();
			for (auto& e : params) exp->params.push_back(visit(e));
			return ASTNode(exp);
		}
	};
}