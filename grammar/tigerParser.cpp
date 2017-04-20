
// Generated from ../tiger.g4 by ANTLR 4.7


#include "tigerVisitor.h"

#include "tigerParser.h"


using namespace antlrcpp;
using namespace antlr4;

tigerParser::tigerParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

tigerParser::~tigerParser() {
  delete _interpreter;
}

std::string tigerParser::getGrammarFileName() const {
  return "tiger.g4";
}

const std::vector<std::string>& tigerParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& tigerParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

tigerParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tigerParser::ExpContext* tigerParser::ProgContext::exp() {
  return getRuleContext<tigerParser::ExpContext>(0);
}

tigerParser::DecsContext* tigerParser::ProgContext::decs() {
  return getRuleContext<tigerParser::DecsContext>(0);
}


size_t tigerParser::ProgContext::getRuleIndex() const {
  return tigerParser::RuleProg;
}

antlrcpp::Any tigerParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

tigerParser::ProgContext* tigerParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, tigerParser::RuleProg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(24);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case tigerParser::T__0:
      case tigerParser::T__8:
      case tigerParser::T__9:
      case tigerParser::T__12:
      case tigerParser::T__24:
      case tigerParser::T__27:
      case tigerParser::T__29:
      case tigerParser::T__31:
      case tigerParser::T__32:
      case tigerParser::STRING:
      case tigerParser::ID:
      case tigerParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(22);
        exp(0);
        break;
      }

      case tigerParser::EOF:
      case tigerParser::T__36:
      case tigerParser::T__37:
      case tigerParser::T__39:
      case tigerParser::T__41:
      case tigerParser::T__44: {
        enterOuterAlt(_localctx, 2);
        setState(23);
        decs();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

tigerParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t tigerParser::ExpContext::getRuleIndex() const {
  return tigerParser::RuleExp;
}

void tigerParser::ExpContext::copyFrom(ExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StringExpContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::StringExpContext::STRING() {
  return getToken(tigerParser::STRING, 0);
}

tigerParser::StringExpContext::StringExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::StringExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitStringExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RecordExpContext ------------------------------------------------------------------

tigerParser::Type_idContext* tigerParser::RecordExpContext::type_id() {
  return getRuleContext<tigerParser::Type_idContext>(0);
}

std::vector<tree::TerminalNode *> tigerParser::RecordExpContext::ID() {
  return getTokens(tigerParser::ID);
}

tree::TerminalNode* tigerParser::RecordExpContext::ID(size_t i) {
  return getToken(tigerParser::ID, i);
}

std::vector<tigerParser::ExpContext *> tigerParser::RecordExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::RecordExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::RecordExpContext::RecordExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::RecordExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitRecordExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakExpContext ------------------------------------------------------------------

tigerParser::BreakExpContext::BreakExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::BreakExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitBreakExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RelOpExpContext ------------------------------------------------------------------

std::vector<tigerParser::ExpContext *> tigerParser::RelOpExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::RelOpExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::RelOpExpContext::RelOpExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::RelOpExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitRelOpExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayExpContext ------------------------------------------------------------------

tigerParser::Type_idContext* tigerParser::ArrayExpContext::type_id() {
  return getRuleContext<tigerParser::Type_idContext>(0);
}

std::vector<tigerParser::ExpContext *> tigerParser::ArrayExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::ArrayExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::ArrayExpContext::ArrayExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::ArrayExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitArrayExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileExpContext ------------------------------------------------------------------

std::vector<tigerParser::ExpContext *> tigerParser::WhileExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::WhileExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::WhileExpContext::WhileExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::WhileExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitWhileExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForExpContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::ForExpContext::ID() {
  return getToken(tigerParser::ID, 0);
}

std::vector<tigerParser::ExpContext *> tigerParser::ForExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::ForExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::ForExpContext::ForExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::ForExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitForExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignExpContext ------------------------------------------------------------------

tigerParser::LvalueContext* tigerParser::AssignExpContext::lvalue() {
  return getRuleContext<tigerParser::LvalueContext>(0);
}

tigerParser::ExpContext* tigerParser::AssignExpContext::exp() {
  return getRuleContext<tigerParser::ExpContext>(0);
}

tigerParser::AssignExpContext::AssignExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::AssignExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitAssignExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NegExpContext ------------------------------------------------------------------

tigerParser::ExpContext* tigerParser::NegExpContext::exp() {
  return getRuleContext<tigerParser::ExpContext>(0);
}

tigerParser::NegExpContext::NegExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::NegExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitNegExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfExpContext ------------------------------------------------------------------

std::vector<tigerParser::ExpContext *> tigerParser::IfExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::IfExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::IfExpContext::IfExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::IfExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitIfExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LetExpContext ------------------------------------------------------------------

tigerParser::DecsContext* tigerParser::LetExpContext::decs() {
  return getRuleContext<tigerParser::DecsContext>(0);
}

tigerParser::ExpsContext* tigerParser::LetExpContext::exps() {
  return getRuleContext<tigerParser::ExpsContext>(0);
}

tigerParser::LetExpContext::LetExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::LetExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitLetExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulDivExpContext ------------------------------------------------------------------

std::vector<tigerParser::ExpContext *> tigerParser::MulDivExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::MulDivExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::MulDivExpContext::MulDivExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::MulDivExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitMulDivExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExplistExpContext ------------------------------------------------------------------

tigerParser::ExpsContext* tigerParser::ExplistExpContext::exps() {
  return getRuleContext<tigerParser::ExpsContext>(0);
}

tigerParser::ExplistExpContext::ExplistExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::ExplistExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitExplistExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallExpContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::FuncCallExpContext::ID() {
  return getToken(tigerParser::ID, 0);
}

std::vector<tigerParser::ExpContext *> tigerParser::FuncCallExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::FuncCallExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::FuncCallExpContext::FuncCallExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::FuncCallExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitFuncCallExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicExpContext ------------------------------------------------------------------

std::vector<tigerParser::ExpContext *> tigerParser::LogicExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::LogicExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::LogicExpContext::LogicExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::LogicExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitLogicExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntExpContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::IntExpContext::INT() {
  return getToken(tigerParser::INT, 0);
}

tigerParser::IntExpContext::IntExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::IntExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitIntExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LvalueExpContext ------------------------------------------------------------------

tigerParser::LvalueContext* tigerParser::LvalueExpContext::lvalue() {
  return getRuleContext<tigerParser::LvalueContext>(0);
}

tigerParser::LvalueExpContext::LvalueExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::LvalueExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitLvalueExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddSubExpContext ------------------------------------------------------------------

std::vector<tigerParser::ExpContext *> tigerParser::AddSubExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::AddSubExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::AddSubExpContext::AddSubExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::AddSubExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitAddSubExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NewExpContext ------------------------------------------------------------------

tigerParser::Type_idContext* tigerParser::NewExpContext::type_id() {
  return getRuleContext<tigerParser::Type_idContext>(0);
}

tigerParser::NewExpContext::NewExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::NewExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitNewExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MethodCallExpContext ------------------------------------------------------------------

tigerParser::LvalueContext* tigerParser::MethodCallExpContext::lvalue() {
  return getRuleContext<tigerParser::LvalueContext>(0);
}

tree::TerminalNode* tigerParser::MethodCallExpContext::ID() {
  return getToken(tigerParser::ID, 0);
}

std::vector<tigerParser::ExpContext *> tigerParser::MethodCallExpContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::MethodCallExpContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::MethodCallExpContext::MethodCallExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::MethodCallExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitMethodCallExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NilExpContext ------------------------------------------------------------------

tigerParser::NilExpContext::NilExpContext(ExpContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::NilExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitNilExp(this);
  else
    return visitor->visitChildren(this);
}

tigerParser::ExpContext* tigerParser::exp() {
   return exp(0);
}

tigerParser::ExpContext* tigerParser::exp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tigerParser::ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, parentState);
  tigerParser::ExpContext *previousContext = _localctx;
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, tigerParser::RuleExp, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(126);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<NilExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(27);
      match(tigerParser::T__0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<IntExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(28);
      match(tigerParser::INT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<StringExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(29);
      match(tigerParser::STRING);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ArrayExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(30);
      type_id();
      setState(31);
      match(tigerParser::T__1);
      setState(32);
      exp(0);
      setState(33);
      match(tigerParser::T__2);
      setState(34);
      match(tigerParser::T__3);
      setState(35);
      exp(18);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<RecordExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(37);
      type_id();
      setState(38);
      match(tigerParser::T__4);
      setState(51);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == tigerParser::ID) {
        setState(39);
        match(tigerParser::ID);
        setState(40);
        match(tigerParser::T__5);
        setState(41);
        exp(0);
        setState(48);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == tigerParser::T__6) {
          setState(42);
          match(tigerParser::T__6);
          setState(43);
          match(tigerParser::ID);
          setState(44);
          match(tigerParser::T__5);
          setState(45);
          exp(0);
          setState(50);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(53);
      match(tigerParser::T__7);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<NewExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(55);
      match(tigerParser::T__8);
      setState(56);
      type_id();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<LvalueExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(57);
      lvalue(0);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<FuncCallExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(58);
      match(tigerParser::ID);
      setState(59);
      match(tigerParser::T__9);
      setState(68);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << tigerParser::T__0)
        | (1ULL << tigerParser::T__8)
        | (1ULL << tigerParser::T__9)
        | (1ULL << tigerParser::T__12)
        | (1ULL << tigerParser::T__24)
        | (1ULL << tigerParser::T__27)
        | (1ULL << tigerParser::T__29)
        | (1ULL << tigerParser::T__31)
        | (1ULL << tigerParser::T__32)
        | (1ULL << tigerParser::STRING)
        | (1ULL << tigerParser::ID)
        | (1ULL << tigerParser::INT))) != 0)) {
        setState(60);
        exp(0);
        setState(65);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == tigerParser::T__6) {
          setState(61);
          match(tigerParser::T__6);
          setState(62);
          exp(0);
          setState(67);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(70);
      match(tigerParser::T__10);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<MethodCallExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(71);
      lvalue(0);
      setState(72);
      match(tigerParser::T__11);
      setState(73);
      match(tigerParser::ID);
      setState(74);
      match(tigerParser::T__9);
      setState(83);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << tigerParser::T__0)
        | (1ULL << tigerParser::T__8)
        | (1ULL << tigerParser::T__9)
        | (1ULL << tigerParser::T__12)
        | (1ULL << tigerParser::T__24)
        | (1ULL << tigerParser::T__27)
        | (1ULL << tigerParser::T__29)
        | (1ULL << tigerParser::T__31)
        | (1ULL << tigerParser::T__32)
        | (1ULL << tigerParser::STRING)
        | (1ULL << tigerParser::ID)
        | (1ULL << tigerParser::INT))) != 0)) {
        setState(75);
        exp(0);
        setState(80);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == tigerParser::T__6) {
          setState(76);
          match(tigerParser::T__6);
          setState(77);
          exp(0);
          setState(82);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(85);
      match(tigerParser::T__10);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<NegExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(87);
      match(tigerParser::T__12);
      setState(88);
      exp(12);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<ExplistExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(89);
      match(tigerParser::T__9);
      setState(90);
      exps();
      setState(91);
      match(tigerParser::T__10);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<AssignExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(93);
      lvalue(0);
      setState(94);
      match(tigerParser::T__23);
      setState(95);
      exp(6);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<IfExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(97);
      match(tigerParser::T__24);
      setState(98);
      exp(0);
      setState(99);
      match(tigerParser::T__25);
      setState(100);
      exp(0);
      setState(103);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
      case 1: {
        setState(101);
        match(tigerParser::T__26);
        setState(102);
        exp(0);
        break;
      }

      }
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<WhileExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(105);
      match(tigerParser::T__27);
      setState(106);
      exp(0);
      setState(107);
      match(tigerParser::T__28);
      setState(108);
      exp(4);
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<ForExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(110);
      match(tigerParser::T__29);
      setState(111);
      match(tigerParser::ID);
      setState(112);
      match(tigerParser::T__23);
      setState(113);
      exp(0);
      setState(114);
      match(tigerParser::T__30);
      setState(115);
      exp(0);
      setState(116);
      match(tigerParser::T__28);
      setState(117);
      exp(3);
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<BreakExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(119);
      match(tigerParser::T__31);
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<LetExpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(120);
      match(tigerParser::T__32);
      setState(121);
      decs();
      setState(122);
      match(tigerParser::T__33);
      setState(123);
      exps();
      setState(124);
      match(tigerParser::T__34);
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(142);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(140);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulDivExpContext>(_tracker.createInstance<ExpContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExp);
          setState(128);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(129);
          dynamic_cast<MulDivExpContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == tigerParser::T__13

          || _la == tigerParser::T__14)) {
            dynamic_cast<MulDivExpContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(130);
          exp(12);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddSubExpContext>(_tracker.createInstance<ExpContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExp);
          setState(131);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(132);
          dynamic_cast<AddSubExpContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == tigerParser::T__12

          || _la == tigerParser::T__15)) {
            dynamic_cast<AddSubExpContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(133);
          exp(11);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<RelOpExpContext>(_tracker.createInstance<ExpContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExp);
          setState(134);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(135);
          dynamic_cast<RelOpExpContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << tigerParser::T__5)
            | (1ULL << tigerParser::T__16)
            | (1ULL << tigerParser::T__17)
            | (1ULL << tigerParser::T__18)
            | (1ULL << tigerParser::T__19)
            | (1ULL << tigerParser::T__20))) != 0))) {
            dynamic_cast<RelOpExpContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(136);
          exp(10);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<LogicExpContext>(_tracker.createInstance<ExpContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExp);
          setState(137);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(138);
          dynamic_cast<LogicExpContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == tigerParser::T__21

          || _la == tigerParser::T__22)) {
            dynamic_cast<LogicExpContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(139);
          exp(9);
          break;
        }

        } 
      }
      setState(144);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LvalueContext ------------------------------------------------------------------

tigerParser::LvalueContext::LvalueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t tigerParser::LvalueContext::getRuleIndex() const {
  return tigerParser::RuleLvalue;
}

void tigerParser::LvalueContext::copyFrom(LvalueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SimpleVarContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::SimpleVarContext::ID() {
  return getToken(tigerParser::ID, 0);
}

tigerParser::SimpleVarContext::SimpleVarContext(LvalueContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::SimpleVarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitSimpleVar(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FieldVarContext ------------------------------------------------------------------

tigerParser::LvalueContext* tigerParser::FieldVarContext::lvalue() {
  return getRuleContext<tigerParser::LvalueContext>(0);
}

tree::TerminalNode* tigerParser::FieldVarContext::ID() {
  return getToken(tigerParser::ID, 0);
}

tigerParser::FieldVarContext::FieldVarContext(LvalueContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::FieldVarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitFieldVar(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SubScriptVarContext ------------------------------------------------------------------

tigerParser::LvalueContext* tigerParser::SubScriptVarContext::lvalue() {
  return getRuleContext<tigerParser::LvalueContext>(0);
}

tigerParser::ExpContext* tigerParser::SubScriptVarContext::exp() {
  return getRuleContext<tigerParser::ExpContext>(0);
}

tigerParser::SubScriptVarContext::SubScriptVarContext(LvalueContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::SubScriptVarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitSubScriptVar(this);
  else
    return visitor->visitChildren(this);
}

tigerParser::LvalueContext* tigerParser::lvalue() {
   return lvalue(0);
}

tigerParser::LvalueContext* tigerParser::lvalue(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  tigerParser::LvalueContext *_localctx = _tracker.createInstance<LvalueContext>(_ctx, parentState);
  tigerParser::LvalueContext *previousContext = _localctx;
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, tigerParser::RuleLvalue, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<SimpleVarContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(146);
    match(tigerParser::ID);
    _ctx->stop = _input->LT(-1);
    setState(158);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(156);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<FieldVarContext>(_tracker.createInstance<LvalueContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleLvalue);
          setState(148);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(149);
          match(tigerParser::T__11);
          setState(150);
          match(tigerParser::ID);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<SubScriptVarContext>(_tracker.createInstance<LvalueContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleLvalue);
          setState(151);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(152);
          match(tigerParser::T__1);
          setState(153);
          exp(0);
          setState(154);
          match(tigerParser::T__2);
          break;
        }

        } 
      }
      setState(160);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExpsContext ------------------------------------------------------------------

tigerParser::ExpsContext::ExpsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t tigerParser::ExpsContext::getRuleIndex() const {
  return tigerParser::RuleExps;
}

void tigerParser::ExpsContext::copyFrom(ExpsContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprListContext ------------------------------------------------------------------

std::vector<tigerParser::ExpContext *> tigerParser::ExprListContext::exp() {
  return getRuleContexts<tigerParser::ExpContext>();
}

tigerParser::ExpContext* tigerParser::ExprListContext::exp(size_t i) {
  return getRuleContext<tigerParser::ExpContext>(i);
}

tigerParser::ExprListContext::ExprListContext(ExpsContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::ExprListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitExprList(this);
  else
    return visitor->visitChildren(this);
}
tigerParser::ExpsContext* tigerParser::exps() {
  ExpsContext *_localctx = _tracker.createInstance<ExpsContext>(_ctx, getState());
  enterRule(_localctx, 6, tigerParser::RuleExps);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<ExpsContext *>(_tracker.createInstance<tigerParser::ExprListContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(169);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << tigerParser::T__0)
      | (1ULL << tigerParser::T__8)
      | (1ULL << tigerParser::T__9)
      | (1ULL << tigerParser::T__12)
      | (1ULL << tigerParser::T__24)
      | (1ULL << tigerParser::T__27)
      | (1ULL << tigerParser::T__29)
      | (1ULL << tigerParser::T__31)
      | (1ULL << tigerParser::T__32)
      | (1ULL << tigerParser::STRING)
      | (1ULL << tigerParser::ID)
      | (1ULL << tigerParser::INT))) != 0)) {
      setState(161);
      exp(0);
      setState(166);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == tigerParser::T__35) {
        setState(162);
        match(tigerParser::T__35);
        setState(163);
        exp(0);
        setState(168);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DecsContext ------------------------------------------------------------------

tigerParser::DecsContext::DecsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t tigerParser::DecsContext::getRuleIndex() const {
  return tigerParser::RuleDecs;
}

void tigerParser::DecsContext::copyFrom(DecsContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DecListContext ------------------------------------------------------------------

std::vector<tigerParser::DecContext *> tigerParser::DecListContext::dec() {
  return getRuleContexts<tigerParser::DecContext>();
}

tigerParser::DecContext* tigerParser::DecListContext::dec(size_t i) {
  return getRuleContext<tigerParser::DecContext>(i);
}

tigerParser::DecListContext::DecListContext(DecsContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::DecListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitDecList(this);
  else
    return visitor->visitChildren(this);
}
tigerParser::DecsContext* tigerParser::decs() {
  DecsContext *_localctx = _tracker.createInstance<DecsContext>(_ctx, getState());
  enterRule(_localctx, 8, tigerParser::RuleDecs);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<DecsContext *>(_tracker.createInstance<tigerParser::DecListContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(174);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << tigerParser::T__36)
      | (1ULL << tigerParser::T__37)
      | (1ULL << tigerParser::T__39)
      | (1ULL << tigerParser::T__41)
      | (1ULL << tigerParser::T__44))) != 0)) {
      setState(171);
      dec();
      setState(176);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DecContext ------------------------------------------------------------------

tigerParser::DecContext::DecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t tigerParser::DecContext::getRuleIndex() const {
  return tigerParser::RuleDec;
}

void tigerParser::DecContext::copyFrom(DecContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DecVarDecContext ------------------------------------------------------------------

tigerParser::VardecContext* tigerParser::DecVarDecContext::vardec() {
  return getRuleContext<tigerParser::VardecContext>(0);
}

tigerParser::DecVarDecContext::DecVarDecContext(DecContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::DecVarDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitDecVarDec(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunDecContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::FunDecContext::ID() {
  return getToken(tigerParser::ID, 0);
}

tigerParser::TyfieldsContext* tigerParser::FunDecContext::tyfields() {
  return getRuleContext<tigerParser::TyfieldsContext>(0);
}

tigerParser::ExpContext* tigerParser::FunDecContext::exp() {
  return getRuleContext<tigerParser::ExpContext>(0);
}

tigerParser::Type_idContext* tigerParser::FunDecContext::type_id() {
  return getRuleContext<tigerParser::Type_idContext>(0);
}

tigerParser::FunDecContext::FunDecContext(DecContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::FunDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitFunDec(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassDecContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::ClassDecContext::ID() {
  return getToken(tigerParser::ID, 0);
}

tigerParser::Type_idContext* tigerParser::ClassDecContext::type_id() {
  return getRuleContext<tigerParser::Type_idContext>(0);
}

std::vector<tigerParser::ClassfieldsContext *> tigerParser::ClassDecContext::classfields() {
  return getRuleContexts<tigerParser::ClassfieldsContext>();
}

tigerParser::ClassfieldsContext* tigerParser::ClassDecContext::classfields(size_t i) {
  return getRuleContext<tigerParser::ClassfieldsContext>(i);
}

tigerParser::ClassDecContext::ClassDecContext(DecContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::ClassDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitClassDec(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TypeDecContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::TypeDecContext::ID() {
  return getToken(tigerParser::ID, 0);
}

tigerParser::TyContext* tigerParser::TypeDecContext::ty() {
  return getRuleContext<tigerParser::TyContext>(0);
}

tigerParser::TypeDecContext::TypeDecContext(DecContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::TypeDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitTypeDec(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ImportDecContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::ImportDecContext::STRING() {
  return getToken(tigerParser::STRING, 0);
}

tigerParser::ImportDecContext::ImportDecContext(DecContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::ImportDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitImportDec(this);
  else
    return visitor->visitChildren(this);
}
tigerParser::DecContext* tigerParser::dec() {
  DecContext *_localctx = _tracker.createInstance<DecContext>(_ctx, getState());
  enterRule(_localctx, 10, tigerParser::RuleDec);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(210);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case tigerParser::T__36: {
        _localctx = dynamic_cast<DecContext *>(_tracker.createInstance<tigerParser::TypeDecContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(177);
        match(tigerParser::T__36);
        setState(178);
        match(tigerParser::ID);
        setState(179);
        match(tigerParser::T__5);
        setState(180);
        ty();
        break;
      }

      case tigerParser::T__37: {
        _localctx = dynamic_cast<DecContext *>(_tracker.createInstance<tigerParser::ClassDecContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(181);
        match(tigerParser::T__37);
        setState(182);
        match(tigerParser::ID);
        setState(185);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == tigerParser::T__38) {
          setState(183);
          match(tigerParser::T__38);
          setState(184);
          type_id();
        }
        setState(187);
        match(tigerParser::T__4);
        setState(191);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == tigerParser::T__43

        || _la == tigerParser::T__44) {
          setState(188);
          classfields();
          setState(193);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(194);
        match(tigerParser::T__7);
        break;
      }

      case tigerParser::T__44: {
        _localctx = dynamic_cast<DecContext *>(_tracker.createInstance<tigerParser::DecVarDecContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(195);
        vardec();
        break;
      }

      case tigerParser::T__39: {
        _localctx = dynamic_cast<DecContext *>(_tracker.createInstance<tigerParser::FunDecContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(196);
        match(tigerParser::T__39);
        setState(197);
        match(tigerParser::ID);
        setState(198);
        match(tigerParser::T__9);
        setState(199);
        tyfields();
        setState(200);
        match(tigerParser::T__10);
        setState(203);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == tigerParser::T__40) {
          setState(201);
          match(tigerParser::T__40);
          setState(202);
          type_id();
        }
        setState(205);
        match(tigerParser::T__5);
        setState(206);
        exp(0);
        break;
      }

      case tigerParser::T__41: {
        _localctx = dynamic_cast<DecContext *>(_tracker.createInstance<tigerParser::ImportDecContext>(_localctx));
        enterOuterAlt(_localctx, 5);
        setState(208);
        match(tigerParser::T__41);
        setState(209);
        match(tigerParser::STRING);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TyContext ------------------------------------------------------------------

tigerParser::TyContext::TyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t tigerParser::TyContext::getRuleIndex() const {
  return tigerParser::RuleTy;
}

void tigerParser::TyContext::copyFrom(TyContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RecordTyContext ------------------------------------------------------------------

tigerParser::TyfieldsContext* tigerParser::RecordTyContext::tyfields() {
  return getRuleContext<tigerParser::TyfieldsContext>(0);
}

tigerParser::RecordTyContext::RecordTyContext(TyContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::RecordTyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitRecordTy(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NameTyContext ------------------------------------------------------------------

tigerParser::Type_idContext* tigerParser::NameTyContext::type_id() {
  return getRuleContext<tigerParser::Type_idContext>(0);
}

tigerParser::NameTyContext::NameTyContext(TyContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::NameTyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitNameTy(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassTyContext ------------------------------------------------------------------

tigerParser::Type_idContext* tigerParser::ClassTyContext::type_id() {
  return getRuleContext<tigerParser::Type_idContext>(0);
}

std::vector<tigerParser::ClassfieldsContext *> tigerParser::ClassTyContext::classfields() {
  return getRuleContexts<tigerParser::ClassfieldsContext>();
}

tigerParser::ClassfieldsContext* tigerParser::ClassTyContext::classfields(size_t i) {
  return getRuleContext<tigerParser::ClassfieldsContext>(i);
}

tigerParser::ClassTyContext::ClassTyContext(TyContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::ClassTyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitClassTy(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayTyContext ------------------------------------------------------------------

tigerParser::Type_idContext* tigerParser::ArrayTyContext::type_id() {
  return getRuleContext<tigerParser::Type_idContext>(0);
}

tigerParser::ArrayTyContext::ArrayTyContext(TyContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::ArrayTyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitArrayTy(this);
  else
    return visitor->visitChildren(this);
}
tigerParser::TyContext* tigerParser::ty() {
  TyContext *_localctx = _tracker.createInstance<TyContext>(_ctx, getState());
  enterRule(_localctx, 12, tigerParser::RuleTy);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(233);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case tigerParser::ID: {
        _localctx = dynamic_cast<TyContext *>(_tracker.createInstance<tigerParser::NameTyContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(212);
        type_id();
        break;
      }

      case tigerParser::T__4: {
        _localctx = dynamic_cast<TyContext *>(_tracker.createInstance<tigerParser::RecordTyContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(213);
        match(tigerParser::T__4);
        setState(214);
        tyfields();
        setState(215);
        match(tigerParser::T__7);
        break;
      }

      case tigerParser::T__42: {
        _localctx = dynamic_cast<TyContext *>(_tracker.createInstance<tigerParser::ArrayTyContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(217);
        match(tigerParser::T__42);
        setState(218);
        match(tigerParser::T__3);
        setState(219);
        type_id();
        break;
      }

      case tigerParser::T__37: {
        _localctx = dynamic_cast<TyContext *>(_tracker.createInstance<tigerParser::ClassTyContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(220);
        match(tigerParser::T__37);
        setState(223);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == tigerParser::T__38) {
          setState(221);
          match(tigerParser::T__38);
          setState(222);
          type_id();
        }
        setState(225);
        match(tigerParser::T__4);
        setState(229);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == tigerParser::T__43

        || _la == tigerParser::T__44) {
          setState(226);
          classfields();
          setState(231);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(232);
        match(tigerParser::T__7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TyfieldsContext ------------------------------------------------------------------

tigerParser::TyfieldsContext::TyfieldsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t tigerParser::TyfieldsContext::getRuleIndex() const {
  return tigerParser::RuleTyfields;
}

void tigerParser::TyfieldsContext::copyFrom(TyfieldsContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TyFieldsContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> tigerParser::TyFieldsContext::ID() {
  return getTokens(tigerParser::ID);
}

tree::TerminalNode* tigerParser::TyFieldsContext::ID(size_t i) {
  return getToken(tigerParser::ID, i);
}

std::vector<tigerParser::Type_idContext *> tigerParser::TyFieldsContext::type_id() {
  return getRuleContexts<tigerParser::Type_idContext>();
}

tigerParser::Type_idContext* tigerParser::TyFieldsContext::type_id(size_t i) {
  return getRuleContext<tigerParser::Type_idContext>(i);
}

tigerParser::TyFieldsContext::TyFieldsContext(TyfieldsContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::TyFieldsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitTyFields(this);
  else
    return visitor->visitChildren(this);
}
tigerParser::TyfieldsContext* tigerParser::tyfields() {
  TyfieldsContext *_localctx = _tracker.createInstance<TyfieldsContext>(_ctx, getState());
  enterRule(_localctx, 14, tigerParser::RuleTyfields);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<TyfieldsContext *>(_tracker.createInstance<tigerParser::TyFieldsContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(247);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == tigerParser::ID) {
      setState(235);
      match(tigerParser::ID);
      setState(236);
      match(tigerParser::T__40);
      setState(237);
      type_id();
      setState(244);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == tigerParser::T__6) {
        setState(238);
        match(tigerParser::T__6);
        setState(239);
        match(tigerParser::ID);
        setState(240);
        match(tigerParser::T__40);
        setState(241);
        type_id();
        setState(246);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassfieldsContext ------------------------------------------------------------------

tigerParser::ClassfieldsContext::ClassfieldsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t tigerParser::ClassfieldsContext::getRuleIndex() const {
  return tigerParser::RuleClassfields;
}

void tigerParser::ClassfieldsContext::copyFrom(ClassfieldsContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MethodDecContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::MethodDecContext::ID() {
  return getToken(tigerParser::ID, 0);
}

tigerParser::TyfieldsContext* tigerParser::MethodDecContext::tyfields() {
  return getRuleContext<tigerParser::TyfieldsContext>(0);
}

tigerParser::ExpContext* tigerParser::MethodDecContext::exp() {
  return getRuleContext<tigerParser::ExpContext>(0);
}

tigerParser::Type_idContext* tigerParser::MethodDecContext::type_id() {
  return getRuleContext<tigerParser::Type_idContext>(0);
}

tigerParser::MethodDecContext::MethodDecContext(ClassfieldsContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::MethodDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitMethodDec(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassVarDecContext ------------------------------------------------------------------

tigerParser::VardecContext* tigerParser::ClassVarDecContext::vardec() {
  return getRuleContext<tigerParser::VardecContext>(0);
}

tigerParser::ClassVarDecContext::ClassVarDecContext(ClassfieldsContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::ClassVarDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitClassVarDec(this);
  else
    return visitor->visitChildren(this);
}
tigerParser::ClassfieldsContext* tigerParser::classfields() {
  ClassfieldsContext *_localctx = _tracker.createInstance<ClassfieldsContext>(_ctx, getState());
  enterRule(_localctx, 16, tigerParser::RuleClassfields);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(262);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case tigerParser::T__44: {
        _localctx = dynamic_cast<ClassfieldsContext *>(_tracker.createInstance<tigerParser::ClassVarDecContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(249);
        vardec();
        break;
      }

      case tigerParser::T__43: {
        _localctx = dynamic_cast<ClassfieldsContext *>(_tracker.createInstance<tigerParser::MethodDecContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(250);
        match(tigerParser::T__43);
        setState(251);
        match(tigerParser::ID);
        setState(252);
        match(tigerParser::T__9);
        setState(253);
        tyfields();
        setState(254);
        match(tigerParser::T__10);
        setState(257);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == tigerParser::T__40) {
          setState(255);
          match(tigerParser::T__40);
          setState(256);
          type_id();
        }
        setState(259);
        match(tigerParser::T__5);
        setState(260);
        exp(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardecContext ------------------------------------------------------------------

tigerParser::VardecContext::VardecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t tigerParser::VardecContext::getRuleIndex() const {
  return tigerParser::RuleVardec;
}

void tigerParser::VardecContext::copyFrom(VardecContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- VarDecContext ------------------------------------------------------------------

tree::TerminalNode* tigerParser::VarDecContext::ID() {
  return getToken(tigerParser::ID, 0);
}

tigerParser::ExpContext* tigerParser::VarDecContext::exp() {
  return getRuleContext<tigerParser::ExpContext>(0);
}

tigerParser::Type_idContext* tigerParser::VarDecContext::type_id() {
  return getRuleContext<tigerParser::Type_idContext>(0);
}

tigerParser::VarDecContext::VarDecContext(VardecContext *ctx) { copyFrom(ctx); }

antlrcpp::Any tigerParser::VarDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitVarDec(this);
  else
    return visitor->visitChildren(this);
}
tigerParser::VardecContext* tigerParser::vardec() {
  VardecContext *_localctx = _tracker.createInstance<VardecContext>(_ctx, getState());
  enterRule(_localctx, 18, tigerParser::RuleVardec);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<VardecContext *>(_tracker.createInstance<tigerParser::VarDecContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(264);
    match(tigerParser::T__44);
    setState(265);
    match(tigerParser::ID);
    setState(268);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == tigerParser::T__40) {
      setState(266);
      match(tigerParser::T__40);
      setState(267);
      type_id();
    }
    setState(270);
    match(tigerParser::T__23);
    setState(271);
    exp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Type_idContext ------------------------------------------------------------------

tigerParser::Type_idContext::Type_idContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* tigerParser::Type_idContext::ID() {
  return getToken(tigerParser::ID, 0);
}


size_t tigerParser::Type_idContext::getRuleIndex() const {
  return tigerParser::RuleType_id;
}

antlrcpp::Any tigerParser::Type_idContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<tigerVisitor*>(visitor))
    return parserVisitor->visitType_id(this);
  else
    return visitor->visitChildren(this);
}

tigerParser::Type_idContext* tigerParser::type_id() {
  Type_idContext *_localctx = _tracker.createInstance<Type_idContext>(_ctx, getState());
  enterRule(_localctx, 20, tigerParser::RuleType_id);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(273);
    match(tigerParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool tigerParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return expSempred(dynamic_cast<ExpContext *>(context), predicateIndex);
    case 2: return lvalueSempred(dynamic_cast<LvalueContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool tigerParser::expSempred(ExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 11);
    case 1: return precpred(_ctx, 10);
    case 2: return precpred(_ctx, 9);
    case 3: return precpred(_ctx, 8);

  default:
    break;
  }
  return true;
}

bool tigerParser::lvalueSempred(LvalueContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> tigerParser::_decisionToDFA;
atn::PredictionContextCache tigerParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN tigerParser::_atn;
std::vector<uint16_t> tigerParser::_serializedATN;

std::vector<std::string> tigerParser::_ruleNames = {
  "prog", "exp", "lvalue", "exps", "decs", "dec", "ty", "tyfields", "classfields", 
  "vardec", "type_id"
};

std::vector<std::string> tigerParser::_literalNames = {
  "", "'nil'", "'['", "']'", "'of'", "'{'", "'='", "','", "'}'", "'new'", 
  "'('", "')'", "'.'", "'-'", "'*'", "'/'", "'+'", "'<>'", "'>='", "'<='", 
  "'>'", "'<'", "'&'", "'|'", "':='", "'if'", "'then'", "'else'", "'while'", 
  "'do'", "'for'", "'to'", "'break'", "'let'", "'in'", "'end'", "';'", "'type'", 
  "'class'", "'extends'", "'function'", "':'", "'import'", "'array'", "'method'", 
  "'var'"
};

std::vector<std::string> tigerParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "STRING", "ID", "INT", "COMMENT", 
  "WS"
};

dfa::Vocabulary tigerParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> tigerParser::_tokenNames;

tigerParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x34, 0x116, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x1b, 0xa, 
    0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 
    0x3, 0x31, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x34, 0xb, 0x3, 0x5, 0x3, 0x36, 
    0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x42, 0xa, 0x3, 0xc, 
    0x3, 0xe, 0x3, 0x45, 0xb, 0x3, 0x5, 0x3, 0x47, 0xa, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 
    0x3, 0x51, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x54, 0xb, 0x3, 0x5, 0x3, 0x56, 
    0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x6a, 0xa, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x5, 0x3, 0x81, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x7, 0x3, 0x8f, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x92, 0xb, 0x3, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x9f, 0xa, 0x4, 0xc, 
    0x4, 0xe, 0x4, 0xa2, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 
    0xa7, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0xaa, 0xb, 0x5, 0x5, 0x5, 0xac, 
    0xa, 0x5, 0x3, 0x6, 0x7, 0x6, 0xaf, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0xb2, 
    0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0xbc, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 
    0x7, 0xc0, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0xc3, 0xb, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x5, 0x7, 0xce, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x5, 0x7, 0xd5, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x5, 0x8, 0xe2, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0xe6, 0xa, 
    0x8, 0xc, 0x8, 0xe, 0x8, 0xe9, 0xb, 0x8, 0x3, 0x8, 0x5, 0x8, 0xec, 0xa, 
    0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x7, 0x9, 0xf5, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0xf8, 0xb, 0x9, 0x5, 
    0x9, 0xfa, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x104, 0xa, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x5, 0xa, 0x109, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x5, 0xb, 0x10f, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x2, 0x4, 0x4, 0x6, 0xd, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x2, 0x6, 0x3, 0x2, 0x10, 0x11, 
    0x4, 0x2, 0xf, 0xf, 0x12, 0x12, 0x4, 0x2, 0x8, 0x8, 0x13, 0x17, 0x3, 
    0x2, 0x18, 0x19, 0x2, 0x13c, 0x2, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x4, 0x80, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x93, 0x3, 0x2, 0x2, 0x2, 0x8, 0xab, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xc, 0xd4, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0xeb, 0x3, 0x2, 0x2, 0x2, 0x10, 0xf9, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x108, 0x3, 0x2, 0x2, 0x2, 0x14, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x16, 0x113, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0x1b, 0x5, 0x4, 0x3, 0x2, 0x19, 0x1b, 0x5, 
    0xa, 0x6, 0x2, 0x1a, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x19, 0x3, 0x2, 
    0x2, 0x2, 0x1b, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x8, 0x3, 0x1, 
    0x2, 0x1d, 0x81, 0x7, 0x3, 0x2, 0x2, 0x1e, 0x81, 0x7, 0x32, 0x2, 0x2, 
    0x1f, 0x81, 0x7, 0x30, 0x2, 0x2, 0x20, 0x21, 0x5, 0x16, 0xc, 0x2, 0x21, 
    0x22, 0x7, 0x4, 0x2, 0x2, 0x22, 0x23, 0x5, 0x4, 0x3, 0x2, 0x23, 0x24, 
    0x7, 0x5, 0x2, 0x2, 0x24, 0x25, 0x7, 0x6, 0x2, 0x2, 0x25, 0x26, 0x5, 
    0x4, 0x3, 0x14, 0x26, 0x81, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x5, 0x16, 
    0xc, 0x2, 0x28, 0x35, 0x7, 0x7, 0x2, 0x2, 0x29, 0x2a, 0x7, 0x31, 0x2, 
    0x2, 0x2a, 0x2b, 0x7, 0x8, 0x2, 0x2, 0x2b, 0x32, 0x5, 0x4, 0x3, 0x2, 
    0x2c, 0x2d, 0x7, 0x9, 0x2, 0x2, 0x2d, 0x2e, 0x7, 0x31, 0x2, 0x2, 0x2e, 
    0x2f, 0x7, 0x8, 0x2, 0x2, 0x2f, 0x31, 0x5, 0x4, 0x3, 0x2, 0x30, 0x2c, 
    0x3, 0x2, 0x2, 0x2, 0x31, 0x34, 0x3, 0x2, 0x2, 0x2, 0x32, 0x30, 0x3, 
    0x2, 0x2, 0x2, 0x32, 0x33, 0x3, 0x2, 0x2, 0x2, 0x33, 0x36, 0x3, 0x2, 
    0x2, 0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 0x35, 0x29, 0x3, 0x2, 0x2, 
    0x2, 0x35, 0x36, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 0x2, 0x2, 0x2, 
    0x37, 0x38, 0x7, 0xa, 0x2, 0x2, 0x38, 0x81, 0x3, 0x2, 0x2, 0x2, 0x39, 
    0x3a, 0x7, 0xb, 0x2, 0x2, 0x3a, 0x81, 0x5, 0x16, 0xc, 0x2, 0x3b, 0x81, 
    0x5, 0x6, 0x4, 0x2, 0x3c, 0x3d, 0x7, 0x31, 0x2, 0x2, 0x3d, 0x46, 0x7, 
    0xc, 0x2, 0x2, 0x3e, 0x43, 0x5, 0x4, 0x3, 0x2, 0x3f, 0x40, 0x7, 0x9, 
    0x2, 0x2, 0x40, 0x42, 0x5, 0x4, 0x3, 0x2, 0x41, 0x3f, 0x3, 0x2, 0x2, 
    0x2, 0x42, 0x45, 0x3, 0x2, 0x2, 0x2, 0x43, 0x41, 0x3, 0x2, 0x2, 0x2, 
    0x43, 0x44, 0x3, 0x2, 0x2, 0x2, 0x44, 0x47, 0x3, 0x2, 0x2, 0x2, 0x45, 
    0x43, 0x3, 0x2, 0x2, 0x2, 0x46, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x46, 0x47, 
    0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 0x2, 0x48, 0x81, 0x7, 
    0xd, 0x2, 0x2, 0x49, 0x4a, 0x5, 0x6, 0x4, 0x2, 0x4a, 0x4b, 0x7, 0xe, 
    0x2, 0x2, 0x4b, 0x4c, 0x7, 0x31, 0x2, 0x2, 0x4c, 0x55, 0x7, 0xc, 0x2, 
    0x2, 0x4d, 0x52, 0x5, 0x4, 0x3, 0x2, 0x4e, 0x4f, 0x7, 0x9, 0x2, 0x2, 
    0x4f, 0x51, 0x5, 0x4, 0x3, 0x2, 0x50, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x51, 
    0x54, 0x3, 0x2, 0x2, 0x2, 0x52, 0x50, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 
    0x3, 0x2, 0x2, 0x2, 0x53, 0x56, 0x3, 0x2, 0x2, 0x2, 0x54, 0x52, 0x3, 
    0x2, 0x2, 0x2, 0x55, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x3, 0x2, 
    0x2, 0x2, 0x56, 0x57, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 0x7, 0xd, 0x2, 
    0x2, 0x58, 0x81, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x7, 0xf, 0x2, 0x2, 
    0x5a, 0x81, 0x5, 0x4, 0x3, 0xe, 0x5b, 0x5c, 0x7, 0xc, 0x2, 0x2, 0x5c, 
    0x5d, 0x5, 0x8, 0x5, 0x2, 0x5d, 0x5e, 0x7, 0xd, 0x2, 0x2, 0x5e, 0x81, 
    0x3, 0x2, 0x2, 0x2, 0x5f, 0x60, 0x5, 0x6, 0x4, 0x2, 0x60, 0x61, 0x7, 
    0x1a, 0x2, 0x2, 0x61, 0x62, 0x5, 0x4, 0x3, 0x8, 0x62, 0x81, 0x3, 0x2, 
    0x2, 0x2, 0x63, 0x64, 0x7, 0x1b, 0x2, 0x2, 0x64, 0x65, 0x5, 0x4, 0x3, 
    0x2, 0x65, 0x66, 0x7, 0x1c, 0x2, 0x2, 0x66, 0x69, 0x5, 0x4, 0x3, 0x2, 
    0x67, 0x68, 0x7, 0x1d, 0x2, 0x2, 0x68, 0x6a, 0x5, 0x4, 0x3, 0x2, 0x69, 
    0x67, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x81, 
    0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x7, 0x1e, 0x2, 0x2, 0x6c, 0x6d, 0x5, 
    0x4, 0x3, 0x2, 0x6d, 0x6e, 0x7, 0x1f, 0x2, 0x2, 0x6e, 0x6f, 0x5, 0x4, 
    0x3, 0x6, 0x6f, 0x81, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 0x7, 0x20, 0x2, 
    0x2, 0x71, 0x72, 0x7, 0x31, 0x2, 0x2, 0x72, 0x73, 0x7, 0x1a, 0x2, 0x2, 
    0x73, 0x74, 0x5, 0x4, 0x3, 0x2, 0x74, 0x75, 0x7, 0x21, 0x2, 0x2, 0x75, 
    0x76, 0x5, 0x4, 0x3, 0x2, 0x76, 0x77, 0x7, 0x1f, 0x2, 0x2, 0x77, 0x78, 
    0x5, 0x4, 0x3, 0x5, 0x78, 0x81, 0x3, 0x2, 0x2, 0x2, 0x79, 0x81, 0x7, 
    0x22, 0x2, 0x2, 0x7a, 0x7b, 0x7, 0x23, 0x2, 0x2, 0x7b, 0x7c, 0x5, 0xa, 
    0x6, 0x2, 0x7c, 0x7d, 0x7, 0x24, 0x2, 0x2, 0x7d, 0x7e, 0x5, 0x8, 0x5, 
    0x2, 0x7e, 0x7f, 0x7, 0x25, 0x2, 0x2, 0x7f, 0x81, 0x3, 0x2, 0x2, 0x2, 
    0x80, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x80, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x80, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0x80, 0x20, 0x3, 0x2, 0x2, 0x2, 0x80, 0x27, 
    0x3, 0x2, 0x2, 0x2, 0x80, 0x39, 0x3, 0x2, 0x2, 0x2, 0x80, 0x3b, 0x3, 
    0x2, 0x2, 0x2, 0x80, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x80, 0x49, 0x3, 0x2, 
    0x2, 0x2, 0x80, 0x59, 0x3, 0x2, 0x2, 0x2, 0x80, 0x5b, 0x3, 0x2, 0x2, 
    0x2, 0x80, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x80, 0x63, 0x3, 0x2, 0x2, 0x2, 
    0x80, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x80, 0x70, 0x3, 0x2, 0x2, 0x2, 0x80, 
    0x79, 0x3, 0x2, 0x2, 0x2, 0x80, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x81, 0x90, 
    0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0xc, 0xd, 0x2, 0x2, 0x83, 0x84, 0x9, 
    0x2, 0x2, 0x2, 0x84, 0x8f, 0x5, 0x4, 0x3, 0xe, 0x85, 0x86, 0xc, 0xc, 
    0x2, 0x2, 0x86, 0x87, 0x9, 0x3, 0x2, 0x2, 0x87, 0x8f, 0x5, 0x4, 0x3, 
    0xd, 0x88, 0x89, 0xc, 0xb, 0x2, 0x2, 0x89, 0x8a, 0x9, 0x4, 0x2, 0x2, 
    0x8a, 0x8f, 0x5, 0x4, 0x3, 0xc, 0x8b, 0x8c, 0xc, 0xa, 0x2, 0x2, 0x8c, 
    0x8d, 0x9, 0x5, 0x2, 0x2, 0x8d, 0x8f, 0x5, 0x4, 0x3, 0xb, 0x8e, 0x82, 
    0x3, 0x2, 0x2, 0x2, 0x8e, 0x85, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x88, 0x3, 
    0x2, 0x2, 0x2, 0x8e, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x92, 0x3, 0x2, 
    0x2, 0x2, 0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x3, 0x2, 0x2, 
    0x2, 0x91, 0x5, 0x3, 0x2, 0x2, 0x2, 0x92, 0x90, 0x3, 0x2, 0x2, 0x2, 
    0x93, 0x94, 0x8, 0x4, 0x1, 0x2, 0x94, 0x95, 0x7, 0x31, 0x2, 0x2, 0x95, 
    0xa0, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 0xc, 0x4, 0x2, 0x2, 0x97, 0x98, 
    0x7, 0xe, 0x2, 0x2, 0x98, 0x9f, 0x7, 0x31, 0x2, 0x2, 0x99, 0x9a, 0xc, 
    0x3, 0x2, 0x2, 0x9a, 0x9b, 0x7, 0x4, 0x2, 0x2, 0x9b, 0x9c, 0x5, 0x4, 
    0x3, 0x2, 0x9c, 0x9d, 0x7, 0x5, 0x2, 0x2, 0x9d, 0x9f, 0x3, 0x2, 0x2, 
    0x2, 0x9e, 0x96, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x99, 0x3, 0x2, 0x2, 0x2, 
    0x9f, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa0, 
    0xa1, 0x3, 0x2, 0x2, 0x2, 0xa1, 0x7, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa0, 
    0x3, 0x2, 0x2, 0x2, 0xa3, 0xa8, 0x5, 0x4, 0x3, 0x2, 0xa4, 0xa5, 0x7, 
    0x26, 0x2, 0x2, 0xa5, 0xa7, 0x5, 0x4, 0x3, 0x2, 0xa6, 0xa4, 0x3, 0x2, 
    0x2, 0x2, 0xa7, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa6, 0x3, 0x2, 0x2, 
    0x2, 0xa8, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xac, 0x3, 0x2, 0x2, 0x2, 
    0xaa, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xab, 
    0xac, 0x3, 0x2, 0x2, 0x2, 0xac, 0x9, 0x3, 0x2, 0x2, 0x2, 0xad, 0xaf, 
    0x5, 0xc, 0x7, 0x2, 0xae, 0xad, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xb2, 0x3, 
    0x2, 0x2, 0x2, 0xb0, 0xae, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 0x3, 0x2, 
    0x2, 0x2, 0xb1, 0xb, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb0, 0x3, 0x2, 0x2, 
    0x2, 0xb3, 0xb4, 0x7, 0x27, 0x2, 0x2, 0xb4, 0xb5, 0x7, 0x31, 0x2, 0x2, 
    0xb5, 0xb6, 0x7, 0x8, 0x2, 0x2, 0xb6, 0xd5, 0x5, 0xe, 0x8, 0x2, 0xb7, 
    0xb8, 0x7, 0x28, 0x2, 0x2, 0xb8, 0xbb, 0x7, 0x31, 0x2, 0x2, 0xb9, 0xba, 
    0x7, 0x29, 0x2, 0x2, 0xba, 0xbc, 0x5, 0x16, 0xc, 0x2, 0xbb, 0xb9, 0x3, 
    0x2, 0x2, 0x2, 0xbb, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x3, 0x2, 
    0x2, 0x2, 0xbd, 0xc1, 0x7, 0x7, 0x2, 0x2, 0xbe, 0xc0, 0x5, 0x12, 0xa, 
    0x2, 0xbf, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xc3, 0x3, 0x2, 0x2, 0x2, 
    0xc1, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc2, 
    0xc4, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xd5, 
    0x7, 0xa, 0x2, 0x2, 0xc5, 0xd5, 0x5, 0x14, 0xb, 0x2, 0xc6, 0xc7, 0x7, 
    0x2a, 0x2, 0x2, 0xc7, 0xc8, 0x7, 0x31, 0x2, 0x2, 0xc8, 0xc9, 0x7, 0xc, 
    0x2, 0x2, 0xc9, 0xca, 0x5, 0x10, 0x9, 0x2, 0xca, 0xcd, 0x7, 0xd, 0x2, 
    0x2, 0xcb, 0xcc, 0x7, 0x2b, 0x2, 0x2, 0xcc, 0xce, 0x5, 0x16, 0xc, 0x2, 
    0xcd, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 0x3, 0x2, 0x2, 0x2, 0xce, 
    0xcf, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xd0, 0x7, 0x8, 0x2, 0x2, 0xd0, 0xd1, 
    0x5, 0x4, 0x3, 0x2, 0xd1, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd3, 0x7, 
    0x2c, 0x2, 0x2, 0xd3, 0xd5, 0x7, 0x30, 0x2, 0x2, 0xd4, 0xb3, 0x3, 0x2, 
    0x2, 0x2, 0xd4, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xc5, 0x3, 0x2, 0x2, 
    0x2, 0xd4, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xd2, 0x3, 0x2, 0x2, 0x2, 
    0xd5, 0xd, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xec, 0x5, 0x16, 0xc, 0x2, 0xd7, 
    0xd8, 0x7, 0x7, 0x2, 0x2, 0xd8, 0xd9, 0x5, 0x10, 0x9, 0x2, 0xd9, 0xda, 
    0x7, 0xa, 0x2, 0x2, 0xda, 0xec, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xdc, 0x7, 
    0x2d, 0x2, 0x2, 0xdc, 0xdd, 0x7, 0x6, 0x2, 0x2, 0xdd, 0xec, 0x5, 0x16, 
    0xc, 0x2, 0xde, 0xe1, 0x7, 0x28, 0x2, 0x2, 0xdf, 0xe0, 0x7, 0x29, 0x2, 
    0x2, 0xe0, 0xe2, 0x5, 0x16, 0xc, 0x2, 0xe1, 0xdf, 0x3, 0x2, 0x2, 0x2, 
    0xe1, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe3, 
    0xe7, 0x7, 0x7, 0x2, 0x2, 0xe4, 0xe6, 0x5, 0x12, 0xa, 0x2, 0xe5, 0xe4, 
    0x3, 0x2, 0x2, 0x2, 0xe6, 0xe9, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe5, 0x3, 
    0x2, 0x2, 0x2, 0xe7, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xea, 0x3, 0x2, 
    0x2, 0x2, 0xe9, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xea, 0xec, 0x7, 0xa, 0x2, 
    0x2, 0xeb, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xd7, 0x3, 0x2, 0x2, 0x2, 
    0xeb, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xde, 0x3, 0x2, 0x2, 0x2, 0xec, 
    0xf, 0x3, 0x2, 0x2, 0x2, 0xed, 0xee, 0x7, 0x31, 0x2, 0x2, 0xee, 0xef, 
    0x7, 0x2b, 0x2, 0x2, 0xef, 0xf6, 0x5, 0x16, 0xc, 0x2, 0xf0, 0xf1, 0x7, 
    0x9, 0x2, 0x2, 0xf1, 0xf2, 0x7, 0x31, 0x2, 0x2, 0xf2, 0xf3, 0x7, 0x2b, 
    0x2, 0x2, 0xf3, 0xf5, 0x5, 0x16, 0xc, 0x2, 0xf4, 0xf0, 0x3, 0x2, 0x2, 
    0x2, 0xf5, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf4, 0x3, 0x2, 0x2, 0x2, 
    0xf6, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xf8, 
    0xf6, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xed, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xfa, 
    0x3, 0x2, 0x2, 0x2, 0xfa, 0x11, 0x3, 0x2, 0x2, 0x2, 0xfb, 0x109, 0x5, 
    0x14, 0xb, 0x2, 0xfc, 0xfd, 0x7, 0x2e, 0x2, 0x2, 0xfd, 0xfe, 0x7, 0x31, 
    0x2, 0x2, 0xfe, 0xff, 0x7, 0xc, 0x2, 0x2, 0xff, 0x100, 0x5, 0x10, 0x9, 
    0x2, 0x100, 0x103, 0x7, 0xd, 0x2, 0x2, 0x101, 0x102, 0x7, 0x2b, 0x2, 
    0x2, 0x102, 0x104, 0x5, 0x16, 0xc, 0x2, 0x103, 0x101, 0x3, 0x2, 0x2, 
    0x2, 0x103, 0x104, 0x3, 0x2, 0x2, 0x2, 0x104, 0x105, 0x3, 0x2, 0x2, 
    0x2, 0x105, 0x106, 0x7, 0x8, 0x2, 0x2, 0x106, 0x107, 0x5, 0x4, 0x3, 
    0x2, 0x107, 0x109, 0x3, 0x2, 0x2, 0x2, 0x108, 0xfb, 0x3, 0x2, 0x2, 0x2, 
    0x108, 0xfc, 0x3, 0x2, 0x2, 0x2, 0x109, 0x13, 0x3, 0x2, 0x2, 0x2, 0x10a, 
    0x10b, 0x7, 0x2f, 0x2, 0x2, 0x10b, 0x10e, 0x7, 0x31, 0x2, 0x2, 0x10c, 
    0x10d, 0x7, 0x2b, 0x2, 0x2, 0x10d, 0x10f, 0x5, 0x16, 0xc, 0x2, 0x10e, 
    0x10c, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x10f, 
    0x110, 0x3, 0x2, 0x2, 0x2, 0x110, 0x111, 0x7, 0x1a, 0x2, 0x2, 0x111, 
    0x112, 0x5, 0x4, 0x3, 0x2, 0x112, 0x15, 0x3, 0x2, 0x2, 0x2, 0x113, 0x114, 
    0x7, 0x31, 0x2, 0x2, 0x114, 0x17, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1a, 0x32, 
    0x35, 0x43, 0x46, 0x52, 0x55, 0x69, 0x80, 0x8e, 0x90, 0x9e, 0xa0, 0xa8, 
    0xab, 0xb0, 0xbb, 0xc1, 0xcd, 0xd4, 0xe1, 0xe7, 0xeb, 0xf6, 0xf9, 0x103, 
    0x108, 0x10e, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

tigerParser::Initializer tigerParser::_init;
