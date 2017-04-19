
// Generated from ../tiger.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "tigerVisitor.h"


/**
 * This class provides an empty implementation of tigerVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  tigerBaseVisitor : public tigerVisitor {
public:

  virtual antlrcpp::Any visitProg(tigerParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStringExp(tigerParser::StringExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRecordExp(tigerParser::RecordExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBreakExp(tigerParser::BreakExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelOpExp(tigerParser::RelOpExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayExp(tigerParser::ArrayExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileExp(tigerParser::WhileExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitForExp(tigerParser::ForExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignExp(tigerParser::AssignExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNegExp(tigerParser::NegExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfExp(tigerParser::IfExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLetExp(tigerParser::LetExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulDivExp(tigerParser::MulDivExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExplistExp(tigerParser::ExplistExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncCallExp(tigerParser::FuncCallExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogicExp(tigerParser::LogicExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntExp(tigerParser::IntExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLvalueExp(tigerParser::LvalueExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddSubExp(tigerParser::AddSubExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNewExp(tigerParser::NewExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMethodCallExp(tigerParser::MethodCallExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNilExp(tigerParser::NilExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSimpleVar(tigerParser::SimpleVarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFieldVar(tigerParser::FieldVarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubScriptVar(tigerParser::SubScriptVarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprList(tigerParser::ExprListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecList(tigerParser::DecListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeDec(tigerParser::TypeDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassDec(tigerParser::ClassDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecVarDec(tigerParser::DecVarDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunDec(tigerParser::FunDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImportDec(tigerParser::ImportDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNameTy(tigerParser::NameTyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRecordTy(tigerParser::RecordTyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayTy(tigerParser::ArrayTyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassTy(tigerParser::ClassTyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTyfields(tigerParser::TyfieldsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassVarDec(tigerParser::ClassVarDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMethodDec(tigerParser::MethodDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDec(tigerParser::VarDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType_id(tigerParser::Type_idContext *ctx) override {
    return visitChildren(ctx);
  }


};

