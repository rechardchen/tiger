
// Generated from ../tiger.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "tigerParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by tigerParser.
 */
class  tigerVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by tigerParser.
   */
    virtual antlrcpp::Any visitProg(tigerParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitStringExp(tigerParser::StringExpContext *context) = 0;

    virtual antlrcpp::Any visitRecordExp(tigerParser::RecordExpContext *context) = 0;

    virtual antlrcpp::Any visitBreakExp(tigerParser::BreakExpContext *context) = 0;

    virtual antlrcpp::Any visitRelOpExp(tigerParser::RelOpExpContext *context) = 0;

    virtual antlrcpp::Any visitArrayExp(tigerParser::ArrayExpContext *context) = 0;

    virtual antlrcpp::Any visitWhileExp(tigerParser::WhileExpContext *context) = 0;

    virtual antlrcpp::Any visitForExp(tigerParser::ForExpContext *context) = 0;

    virtual antlrcpp::Any visitAssignExp(tigerParser::AssignExpContext *context) = 0;

    virtual antlrcpp::Any visitNegExp(tigerParser::NegExpContext *context) = 0;

    virtual antlrcpp::Any visitIfExp(tigerParser::IfExpContext *context) = 0;

    virtual antlrcpp::Any visitLetExp(tigerParser::LetExpContext *context) = 0;

    virtual antlrcpp::Any visitMulDivExp(tigerParser::MulDivExpContext *context) = 0;

    virtual antlrcpp::Any visitExplistExp(tigerParser::ExplistExpContext *context) = 0;

    virtual antlrcpp::Any visitFuncCallExp(tigerParser::FuncCallExpContext *context) = 0;

    virtual antlrcpp::Any visitLogicExp(tigerParser::LogicExpContext *context) = 0;

    virtual antlrcpp::Any visitIntExp(tigerParser::IntExpContext *context) = 0;

    virtual antlrcpp::Any visitLvalueExp(tigerParser::LvalueExpContext *context) = 0;

    virtual antlrcpp::Any visitAddSubExp(tigerParser::AddSubExpContext *context) = 0;

    virtual antlrcpp::Any visitNewExp(tigerParser::NewExpContext *context) = 0;

    virtual antlrcpp::Any visitMethodCallExp(tigerParser::MethodCallExpContext *context) = 0;

    virtual antlrcpp::Any visitNilExp(tigerParser::NilExpContext *context) = 0;

    virtual antlrcpp::Any visitSimpleVar(tigerParser::SimpleVarContext *context) = 0;

    virtual antlrcpp::Any visitFieldVar(tigerParser::FieldVarContext *context) = 0;

    virtual antlrcpp::Any visitSubScriptVar(tigerParser::SubScriptVarContext *context) = 0;

    virtual antlrcpp::Any visitExprList(tigerParser::ExprListContext *context) = 0;

    virtual antlrcpp::Any visitDecList(tigerParser::DecListContext *context) = 0;

    virtual antlrcpp::Any visitTypeDec(tigerParser::TypeDecContext *context) = 0;

    virtual antlrcpp::Any visitClassDec(tigerParser::ClassDecContext *context) = 0;

    virtual antlrcpp::Any visitDecVarDec(tigerParser::DecVarDecContext *context) = 0;

    virtual antlrcpp::Any visitFunDec(tigerParser::FunDecContext *context) = 0;

    virtual antlrcpp::Any visitImportDec(tigerParser::ImportDecContext *context) = 0;

    virtual antlrcpp::Any visitNameTy(tigerParser::NameTyContext *context) = 0;

    virtual antlrcpp::Any visitRecordTy(tigerParser::RecordTyContext *context) = 0;

    virtual antlrcpp::Any visitArrayTy(tigerParser::ArrayTyContext *context) = 0;

    virtual antlrcpp::Any visitClassTy(tigerParser::ClassTyContext *context) = 0;

    virtual antlrcpp::Any visitTyfields(tigerParser::TyfieldsContext *context) = 0;

    virtual antlrcpp::Any visitClassVarDec(tigerParser::ClassVarDecContext *context) = 0;

    virtual antlrcpp::Any visitMethodDec(tigerParser::MethodDecContext *context) = 0;

    virtual antlrcpp::Any visitVarDec(tigerParser::VarDecContext *context) = 0;

    virtual antlrcpp::Any visitType_id(tigerParser::Type_idContext *context) = 0;


};

