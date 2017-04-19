
// Generated from ../tiger.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  tigerParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, STRING = 46, ID = 47, INT = 48, COMMENT = 49, WS = 50
  };

  enum {
    RuleProg = 0, RuleExp = 1, RuleLvalue = 2, RuleExps = 3, RuleDecs = 4, 
    RuleDec = 5, RuleTy = 6, RuleTyfields = 7, RuleClassfields = 8, RuleVardec = 9, 
    RuleType_id = 10
  };

  tigerParser(antlr4::TokenStream *input);
  ~tigerParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ProgContext;
  class ExpContext;
  class LvalueContext;
  class ExpsContext;
  class DecsContext;
  class DecContext;
  class TyContext;
  class TyfieldsContext;
  class ClassfieldsContext;
  class VardecContext;
  class Type_idContext; 

  class  ProgContext : public antlr4::ParserRuleContext {
  public:
    ProgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpContext *exp();
    DecsContext *decs();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgContext* prog();

  class  ExpContext : public antlr4::ParserRuleContext {
  public:
    ExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpContext() : antlr4::ParserRuleContext() { }
    void copyFrom(ExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  StringExpContext : public ExpContext {
  public:
    StringExpContext(ExpContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RecordExpContext : public ExpContext {
  public:
    RecordExpContext(ExpContext *ctx);

    Type_idContext *type_id();
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BreakExpContext : public ExpContext {
  public:
    BreakExpContext(ExpContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RelOpExpContext : public ExpContext {
  public:
    RelOpExpContext(ExpContext *ctx);

    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayExpContext : public ExpContext {
  public:
    ArrayExpContext(ExpContext *ctx);

    Type_idContext *type_id();
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WhileExpContext : public ExpContext {
  public:
    WhileExpContext(ExpContext *ctx);

    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ForExpContext : public ExpContext {
  public:
    ForExpContext(ExpContext *ctx);

    antlr4::tree::TerminalNode *ID();
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignExpContext : public ExpContext {
  public:
    AssignExpContext(ExpContext *ctx);

    LvalueContext *lvalue();
    ExpContext *exp();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NegExpContext : public ExpContext {
  public:
    NegExpContext(ExpContext *ctx);

    ExpContext *exp();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfExpContext : public ExpContext {
  public:
    IfExpContext(ExpContext *ctx);

    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LetExpContext : public ExpContext {
  public:
    LetExpContext(ExpContext *ctx);

    DecsContext *decs();
    ExpsContext *exps();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MulDivExpContext : public ExpContext {
  public:
    MulDivExpContext(ExpContext *ctx);

    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExplistExpContext : public ExpContext {
  public:
    ExplistExpContext(ExpContext *ctx);

    ExpsContext *exps();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FuncCallExpContext : public ExpContext {
  public:
    FuncCallExpContext(ExpContext *ctx);

    antlr4::tree::TerminalNode *ID();
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogicExpContext : public ExpContext {
  public:
    LogicExpContext(ExpContext *ctx);

    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntExpContext : public ExpContext {
  public:
    IntExpContext(ExpContext *ctx);

    antlr4::tree::TerminalNode *INT();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LvalueExpContext : public ExpContext {
  public:
    LvalueExpContext(ExpContext *ctx);

    LvalueContext *lvalue();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddSubExpContext : public ExpContext {
  public:
    AddSubExpContext(ExpContext *ctx);

    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NewExpContext : public ExpContext {
  public:
    NewExpContext(ExpContext *ctx);

    Type_idContext *type_id();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MethodCallExpContext : public ExpContext {
  public:
    MethodCallExpContext(ExpContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ID();
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NilExpContext : public ExpContext {
  public:
    NilExpContext(ExpContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpContext* exp();
  ExpContext* exp(int precedence);
  class  LvalueContext : public antlr4::ParserRuleContext {
  public:
    LvalueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LvalueContext() : antlr4::ParserRuleContext() { }
    void copyFrom(LvalueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SimpleVarContext : public LvalueContext {
  public:
    SimpleVarContext(LvalueContext *ctx);

    antlr4::tree::TerminalNode *ID();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FieldVarContext : public LvalueContext {
  public:
    FieldVarContext(LvalueContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ID();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SubScriptVarContext : public LvalueContext {
  public:
    SubScriptVarContext(LvalueContext *ctx);

    LvalueContext *lvalue();
    ExpContext *exp();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LvalueContext* lvalue();
  LvalueContext* lvalue(int precedence);
  class  ExpsContext : public antlr4::ParserRuleContext {
  public:
    ExpsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpsContext() : antlr4::ParserRuleContext() { }
    void copyFrom(ExpsContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExprListContext : public ExpsContext {
  public:
    ExprListContext(ExpsContext *ctx);

    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpsContext* exps();

  class  DecsContext : public antlr4::ParserRuleContext {
  public:
    DecsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    DecsContext() : antlr4::ParserRuleContext() { }
    void copyFrom(DecsContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DecListContext : public DecsContext {
  public:
    DecListContext(DecsContext *ctx);

    std::vector<DecContext *> dec();
    DecContext* dec(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  DecsContext* decs();

  class  DecContext : public antlr4::ParserRuleContext {
  public:
    DecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    DecContext() : antlr4::ParserRuleContext() { }
    void copyFrom(DecContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DecVarDecContext : public DecContext {
  public:
    DecVarDecContext(DecContext *ctx);

    VardecContext *vardec();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunDecContext : public DecContext {
  public:
    FunDecContext(DecContext *ctx);

    antlr4::tree::TerminalNode *ID();
    TyfieldsContext *tyfields();
    ExpContext *exp();
    Type_idContext *type_id();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ClassDecContext : public DecContext {
  public:
    ClassDecContext(DecContext *ctx);

    antlr4::tree::TerminalNode *ID();
    ClassfieldsContext *classfields();
    Type_idContext *type_id();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeDecContext : public DecContext {
  public:
    TypeDecContext(DecContext *ctx);

    antlr4::tree::TerminalNode *ID();
    TyContext *ty();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ImportDecContext : public DecContext {
  public:
    ImportDecContext(DecContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  DecContext* dec();

  class  TyContext : public antlr4::ParserRuleContext {
  public:
    TyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TyContext() : antlr4::ParserRuleContext() { }
    void copyFrom(TyContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  RecordTyContext : public TyContext {
  public:
    RecordTyContext(TyContext *ctx);

    TyfieldsContext *tyfields();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NameTyContext : public TyContext {
  public:
    NameTyContext(TyContext *ctx);

    Type_idContext *type_id();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ClassTyContext : public TyContext {
  public:
    ClassTyContext(TyContext *ctx);

    ClassfieldsContext *classfields();
    Type_idContext *type_id();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayTyContext : public TyContext {
  public:
    ArrayTyContext(TyContext *ctx);

    Type_idContext *type_id();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TyContext* ty();

  class  TyfieldsContext : public antlr4::ParserRuleContext {
  public:
    TyfieldsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<Type_idContext *> type_id();
    Type_idContext* type_id(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TyfieldsContext* tyfields();

  class  ClassfieldsContext : public antlr4::ParserRuleContext {
  public:
    ClassfieldsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ClassfieldsContext() : antlr4::ParserRuleContext() { }
    void copyFrom(ClassfieldsContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MethodDecContext : public ClassfieldsContext {
  public:
    MethodDecContext(ClassfieldsContext *ctx);

    antlr4::tree::TerminalNode *ID();
    TyfieldsContext *tyfields();
    ExpContext *exp();
    Type_idContext *type_id();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ClassVarDecContext : public ClassfieldsContext {
  public:
    ClassVarDecContext(ClassfieldsContext *ctx);

    VardecContext *vardec();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ClassfieldsContext* classfields();

  class  VardecContext : public antlr4::ParserRuleContext {
  public:
    VardecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    VardecContext() : antlr4::ParserRuleContext() { }
    void copyFrom(VardecContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  VarDecContext : public VardecContext {
  public:
    VarDecContext(VardecContext *ctx);

    antlr4::tree::TerminalNode *ID();
    ExpContext *exp();
    Type_idContext *type_id();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  VardecContext* vardec();

  class  Type_idContext : public antlr4::ParserRuleContext {
  public:
    Type_idContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_idContext* type_id();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool expSempred(ExpContext *_localctx, size_t predicateIndex);
  bool lvalueSempred(LvalueContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

