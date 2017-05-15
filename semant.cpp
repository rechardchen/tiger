#include "semant.h"
#include "type.h"
#include "translate.h"

namespace tiger {

#define VALID_VAR_TYPE(ty) ((ty)->tt != Ty_Void)

	Semant::Semant(BumpPtrAllocator& allocator)
		: C(allocator)
		, VENV(env::baseVEnv())
		, FENV(env::baseFEnv())
		, TENV(env::baseTEnv())
	{
		Translator = new (C) Translate(C);
	}

	Semant::ExpTy Semant::TransExp(ASTNode n)
	{
		ExpTy ret;
		switch (n->type) {
		case A_Nil:
		{
			ret.first = Translator->TransConst(0);
			ret.second = NilType();
		}
			break;

		case A_Int:
		{
			auto ix = static_cast<IntExp*>(n);
			ret.first = Translator->TransConst(ix->val);
			ret.second = IntType();
		}
			break;

		case A_String:
		{
			auto sx = static_cast<StringExp*>(n);
			ret.first = Translator->TransStrConst(sx->val);
			ret.second = StringType();
		}
			break;

		case A_Array:
		{
			auto ax = static_cast<ArrayExp*>(n);
			auto ty = TENV.Look(ax->type);
			if (ty) {
				auto expty = TransExp(ax->init);
				if (expty.second == nullptr)
					goto TRANS_EXP_ERR;
				if (!ValidateTypeCheck(ty, expty.second)) {
					reportErr("type mismatch!");
					goto TRANS_EXP_ERR;
				}
				auto initExp = expty.first;
				expty = TransExp(ax->size);
				if (expty.second == nullptr)
					goto TRANS_EXP_ERR;
				if (expty.second != IntType()) {
					reportErr("array index must be integer");
					goto TRANS_EXP_ERR;
				}
				auto sizeExp = expty.first;
				ret.first = Translator->TransArrayInit(sizeExp, initExp);
				//so we need to add special validate in ValidateTypeCheck for arrays
				ret.second = new(C)ArrayType(ty);
			}
			else {
				reportErr("type %s not defined", ax->type.c_str());
			}
		}
			break;

		case A_Record:
		{
			auto rx = static_cast<RecordExp*>(n);
			auto ty = TENV.Look(rx->type);
			if (ty) {
				ty = actualTy(ty);
				if (ty->tt != Ty_Record) {
					reportErr("%s is not a record type", rx->type.c_str());
					goto TRANS_EXP_ERR;
				}

				auto rt = static_cast<RecordType*>(ty);
				std::vector<Symbol> fnames;
				std::vector<TrExp*> fexps;
				for (auto field : rx->fields) {
					auto efield = static_cast<EField*>(field);
					auto fieldTy = rt->GetMemberTy(efield->name);
					if (fieldTy == nullptr) {
						reportErr("%s is not a valid field name", efield->name.c_str());
						goto TRANS_EXP_ERR;
					}
					ExpTy expty = TransExp(efield->exp);
					if (expty.second == nullptr)
						goto TRANS_EXP_ERR;

					if (!ValidateTypeCheck(fieldTy, expty.second)) {
						reportErr("field %s type mismatch!", efield->name.c_str());
						goto TRANS_EXP_ERR;
					}
					fnames.push_back(efield->name);
					fexps.push_back(expty.first);
				}
				ret.second = ty;
				ret.first = Translator->TransRecordInit(rt, fnames, fexps);
			}
			else {
				reportErr("type %s not exists", rx->type.c_str());
			}
		}
			break;

		case A_Call:
		{
			auto cx = static_cast<CallExp*>(n);

			auto entry = FENV.Look(cx->name);
			if (entry == nullptr) {
				reportErr("func %s is not defined", cx->name.c_str());
				goto TRANS_EXP_ERR;
			}
			//check params
			if (cx->params.size() != entry->paramTypes.size()) {
				reportErr("number of parameter not match!");
				goto TRANS_EXP_ERR;
			}
			std::vector<ASTNode> params(cx->params.begin(), cx->params.end());
			std::vector<TrExp*> exps;
			for (size_t i = 0; i < params.size(); ++i) {
				ExpTy expty = TransExp(params[i]);
				if (expty.second == nullptr)
					goto TRANS_EXP_ERR;
				if (!ValidateTypeCheck(entry->paramTypes[i], expty.second)) {
					reportErr("type mismatch!");
					goto TRANS_EXP_ERR;
				}
				exps.push_back(expty.first);
			}
			ret.second = actualTy(entry->resultType);
			ret.first = Translator->TransCall(entry->level->Name, exps);
		}
			break;

		case A_UnaryOp:
		{
			auto ux = static_cast<UnaryOpExp*>(n);
			auto expty = TransExp(ux->exp);
			
			if (expty.second) {
				if (expty.second != IntType()) {
					reportErr("not implemented: unary op only support integers");
					goto TRANS_EXP_ERR;
				}
				ret.second = IntType();
				ret.first = Translator->TransBinarySub(Translator->TransConst(0), expty.first);
			}
		}
			break;

		case A_BinOp:
		{
			auto bx = static_cast<BinOpExp*>(n);
			switch (bx->op) {
			case BinOpExp::OP_MUL:
			{
				ExpTy expty = TransExp(bx->lhs);
				if (expty.second == nullptr)
					goto TRANS_EXP_ERR;
				if (expty.second != IntType()) {
					reportErr("invalid oprand type, integer expected!");
					goto TRANS_EXP_ERR;
				}
				auto lhs = expty.first;
				
				expty = TransExp(bx->rhs);
				if (expty.second == nullptr)
					goto TRANS_EXP_ERR;
				if (expty.second != IntType()) {
					reportErr("invalid oprand type, integer expected!");
					goto TRANS_EXP_ERR;
				}
				auto rhs = expty.first;

				ret.second = IntType();
				ret.first = Translator->TransBinaryMul(lhs, rhs);
			}
				break;

			case BinOpExp::OP_DIV:
			{
				ExpTy expty = TransExp(bx->lhs);
				if (expty.second == nullptr)
					goto TRANS_EXP_ERR;
				if (expty.second != IntType()) {
					reportErr("invalid oprand type, integer expected!");
					goto TRANS_EXP_ERR;
				}
				auto lhs = expty.first;
				expty = TransExp(bx->rhs);
				if (expty.second == nullptr)
					goto TRANS_EXP_ERR;
				if (expty.second != IntType()) {
					reportErr("invalid oprand type, integer expected!");
					goto TRANS_EXP_ERR;
				}
				auto rhs = expty.first;
				auto exp = Translator->TransBinaryDiv(lhs, rhs);
				if (exp == nullptr) {
					reportErr("zero division error!");
					goto TRANS_EXP_ERR;
				}
				ret.second = IntType();
				ret.first = exp;
			}
				break;

			case BinOpExp::OP_ADD:
			{
				ExpTy expty = TransExp(bx->lhs);
				if (expty.second==nullptr)
					goto TRANS_EXP_ERR;
				auto ltype = expty.second;
				auto lexp = expty.first;

				expty = TransExp(bx->rhs);
				if (expty.second == nullptr)
					goto TRANS_EXP_ERR;
				auto rtype = expty.second;
				auto rexp = expty.first;

				if (ltype == IntType() && rtype == IntType()) {
					ret.second = IntType();
					ret.first = Translator->TransBinaryAdd(lexp, rexp);
				}
				else if (ltype == StringType() && rtype == StringType()) {
					ret.second = StringType();
					ret.first = Translator->TransStrConcat(lexp, rexp);
				}
				else {
					reportErr("invalid oprand type, only integer and string addition is permitted!");
					goto TRANS_EXP_ERR;
				}
			}
				break;

			case BinOpExp::OP_SUB:
			{
				//TODO: change to two-way check
				ExpTy expty = TransExp(bx->lhs);
				if (expty.second == nullptr)
					goto TRANS_EXP_ERR;
				if (expty.second != IntType()) {
					reportErr("invalid oprand type, integer expected!");
					goto TRANS_EXP_ERR;
				}
				auto lhs = expty.first;
				expty = TransExp(bx->rhs);
				if (expty.second == nullptr)
					goto TRANS_EXP_ERR;
				if (expty.second != IntType()) {
					reportErr("invalid oprand type, integer expected!");
					goto TRANS_EXP_ERR;
				}
				auto rhs = expty.first;

				ret.second = IntType();
				ret.first = Translator->TransBinarySub(lhs, rhs);
			}
				break;

			case BinOpExp::OP_EQ:
			case BinOpExp::OP_NE:
			case BinOpExp::OP_LT:
			case BinOpExp::OP_GT:
			case BinOpExp::OP_LE:
			case BinOpExp::OP_GE:
			{
				ExpTy left = TransExp(bx->lhs), right = TransExp(bx->rhs);
				if (left.second == nullptr || right.second == nullptr)
					goto TRANS_EXP_ERR;
				TrRelOp op = Tr_EQ;
				switch (bx->op) {
				case BinOpExp::OP_EQ:op = Tr_EQ; break;
				case BinOpExp::OP_NE:op = Tr_NE; break;
				case BinOpExp::OP_LT:op = Tr_LT; break;
				case BinOpExp::OP_GT:op = Tr_GT; break;
				case BinOpExp::OP_LE:op = Tr_LE; break;
				case BinOpExp::OP_GE:op = Tr_GE; break;
				}
				if (left.second == IntType() && right.second == IntType()) {
					ret.second = IntType();
					ret.first = Translator->TransRelOp(op, left.first, right.first, false);
				}
				else if (left.second == StringType() && right.second == StringType()) {
					ret.second = IntType();
					ret.first = Translator->TransRelOp(op, left.first, right.first, true);
				}
				else {
					reportErr("invalid rel oprand type!");
					goto TRANS_EXP_ERR;
				}
			}
				break;

			case BinOpExp::OP_AND:
			case BinOpExp::OP_OR:
			{
				auto left = TransExp(bx->lhs), right = TransExp(bx->rhs);
				if (left.second == nullptr || right.second == nullptr)
					goto TRANS_EXP_ERR;
				if (!VALID_VAR_TYPE(left.second)) {
					reportErr("invalid logic oprand type");
					goto TRANS_EXP_ERR;
				}
				if (!VALID_VAR_TYPE(right.second)) {
					reportErr("invalid logic oprand type");
					goto TRANS_EXP_ERR;
				}

				ret.second = IntType();
				ret.first = Translator->TransLogicOp(
					bx->op == BinOpExp::OP_AND ? Tr_LogicAnd: Tr_LogicOr,
					left.first,
					right.first
					);
			}
				break;
			}
		}
			break;

		case A_If:
		{
			auto ix = static_cast<IfExp*>(n);
			ExpTy test = TransExp(ix->test), then = TransExp(ix->then), elsee;
			bool hasElse = ix->elsee != nullptr;
			if (hasElse) elsee = TransExp(ix->elsee);
			if (test.second == nullptr)
				goto TRANS_EXP_ERR;
			if (!VALID_VAR_TYPE(test.second)) {
				reportErr("test exp type incorrect!");
				goto TRANS_EXP_ERR;
			}
			if (!hasElse) {
				if (then.second == nullptr)
					goto TRANS_EXP_ERR;
				if (then.second != VoidType()) {
					reportErr("if without else must have type void!");
					goto TRANS_EXP_ERR;
				}

				ret.second = VoidType();
				ret.first = Translator->TransIf(test.first, then.first, nullptr);
			}
			else {
				if (then.second == nullptr || elsee.second == nullptr)
					goto TRANS_EXP_ERR;

				if (!ValidateTypeCheck(then.second, elsee.second)) {
					reportErr("then and else type mismatch!");
					goto TRANS_EXP_ERR;
				}

				ret.second = then.second;
				ret.first = Translator->TransIf(test.first, then.first, elsee.first);
			}
		}
			break;

		case A_While:
		{

		}
			break;

		case A_For:
		{

		}
			break;

		case A_Break:
			break;

		case A_Let:
			break;
		default:
			assert(0);
			break;
		}

TRANS_EXP_ERR:
		return ret;
	}

	Semant::ExpTy Semant::TransDecs(ASTNode n)
	{
		//TODO: handle class definitions
		assert(n->type == A_DeclareList);
		DeclareList* dl = static_cast<DeclareList*>(n);
		TrExp* initExp = nullptr;

		//first pass only process type headers
		for (auto dec : dl->decs) {
			if (dec->type == A_TypeDec) {
				auto tydec = static_cast<TypeDec*>(dec);
				switch (tydec->ty->type) {
				case A_NameTy:
				case A_RecordTy:
				case A_ArrayTy:
					TENV.Enter(tydec->name, new(C) NameType(tydec->name, nullptr));
					break;
				default:
					assert(0);
					break;
				}
			}
		}
		for (auto dec : dl->decs) {
			//second pass get the complete type definition
			if (dec->type == A_TypeDec) {
				auto tydec = static_cast<TypeDec*>(dec);
				Symbol typeName = tydec->name;
				auto ty = TENV.Look(typeName);
				assert(ty->tt == Ty_Name);
				auto nt = static_cast<NameType*>(ty);
				nt->type = TransTy(tydec);

				//check: recursive define and incomplete define
				Type* realTy = nt->type;
				while (realTy != nt && realTy->tt == Ty_Name) {
					auto realNT = static_cast<NameType*>(realTy);
					if (realNT->type == nullptr) {
						reportErr("type %s has an incomplete definition!", tydec->name.c_str());
						//TODO: pop error type
						break;
					}
					else
						realTy = realNT->type;
				}
				if (realTy == nt)
					reportErr("type %s has a recursive definition!", tydec->name.c_str());
			}
			else if (dec->type == A_VarDec) {
				auto vardec = static_cast<VarDec*>(dec);
				auto expty = TransVarDec(vardec);
				if (expty.second) {
					if (initExp == nullptr) 
						initExp = expty.first;
					else 
						initExp = Translator->CombineStm(initExp, expty.first);
				}
			}
			else if (dec->type == A_FuncDec) {
				auto fundec = static_cast<FuncDec*>(dec);
				Type* retType = VoidType();
				if (!fundec->rtype.empty()) {
					Type* rtype = TENV.Look(fundec->rtype);
					if (!rtype) {
						reportErr("%s is not a valid return type!", fundec->rtype.c_str());
						retType = nullptr;
					}
					else {
						retType = actualTy(rtype);
					}
				}
				//check param types
				bool validParam = true;
				std::vector<Symbol> formalName;
				std::vector<Type*> formalTypes;
				std::vector<bool> formalEscape;
				for (auto para : fundec->params->fields) {
					Type* ty = TENV.Look(para->name);
					if (!ty) {
						reportErr("para %s has invalid type %s", para->name.c_str(),
							para->type.c_str());
						validParam = false;
						break;
					}
					else {
						formalTypes.push_back(actualTy(ty));
						formalEscape.push_back(para->escape);
						formalName.push_back(para->name);
					}
				}
				if (retType && validParam) {
					//for recursive func
					auto newLevel = Translator->NewLevel(
						Translator->CurLevel(),
						temp::newLabel(),
						formalEscape
					);
					//register func in outer level
					auto entry = new(C) FuncEntry;
					entry->level = Translator->CurLevel(); //newlevel
					entry->paramTypes = formalTypes;
					entry->resultType = retType;
					FENV.Enter(fundec->name, entry);
					//begin level of the func
					TENV.BeginScope();
					VENV.BeginScope();
					FENV.BeginScope();
					
					for (size_t i = 0; i < formalName.size(); ++i) {
						auto entry = new(C)VarEntry;
						entry->access = newLevel->Argument(i);
						entry->type = formalTypes[i];

						VENV.Enter(formalName[i], entry);
					}
					ExpTy expty = TransExp(fundec->body);
					//make sure endscope is called
					FENV.EndScope();
					VENV.EndScope();
					TENV.EndScope();
					//check return type
					if (expty.second == NULL ||
						!ValidateTypeCheck(retType, expty.second)) {
						reportErr("return type mismatch!");
						FENV.Pop(fundec->name);
						Translator->ExitLevel(nullptr);
					}
					else {
						Translator->ExitLevel(expty.first);
					}
				}
			}
		}

		return ExpTy(initExp, nullptr);
	}

	Semant::ExpTy Semant::TransVar(ASTNode n)
	{
		ExpTy ret;

		switch (n->type) {
		case A_SimpleVar:
		{
			auto sv = static_cast<SimpleVar*>(n);
			auto entry = VENV.Look(sv->name);
			if (!entry) {
				reportErr("undefined variable %s", sv->name.c_str());
			}
			else {
				ret.second = entry->type;
				ret.first = Translator->TransSimpleVar(entry->access);
			}
		}
			break;
			
		case A_FieldVar:
		{
			auto fv = static_cast<FieldVar*>(n);
			auto expty = TransVar(fv->var);
			auto ty = expty.second;
			if (ty) {
				if (ty->tt == Ty_Record) {
					auto rt = static_cast<RecordType*>(ty);
					ty = rt->GetMemberTy(fv->field);
					if (ty) {
						ty = actualTy(ty);

						ret.second = ty;
						ret.first = Translator->TransFieldVar(
							expty.first,
							rt,
							fv->field
						);
					}
					else {
						reportErr("%s is not a valid field name", fv->field.c_str());
					}
				}
				else {
					reportErr("need a record type");
				}
			}
		}
			break;

		case A_SubscriptVar:
		{
			auto sv = static_cast<SubscriptVar*>(n);
			auto expty = TransVar(sv->var);
			auto ty = expty.second;
			if (ty) {
				if (ty->tt != Ty_Array) {
					reportErr("must be array type");
				}
				else {
					auto itemTy = actualTy(static_cast<ArrayType*>(ty)->arrTy);
					auto varExp = expty.first;
					expty = TransExp(sv->exp);
					if (expty.second != IntType()) {
						reportErr("array index must be integer");
					}
					else {
						ret.first = Translator->TransSubscriptVar(varExp, expty.first);
						ret.second = itemTy;
					}
				}
			}

		}
			break;

		default: 
		{
			reportErr("need an l-value");
			assert(0);
		}
			break;
		}

		return ret;
	}

	Type* Semant::TransTy(ASTNode n)
	{
		switch (n->type) {
		case A_NameTy:
		{
			NameTy* nt = static_cast<NameTy*>(n);
			Type* ty = TENV.Look(nt->name);
			if (ty == nullptr) {
				reportErr("type %s not defined!", nt->name.c_str());
				goto TRANS_TY_ERR;
			}
			return ty;
		}
			break;

		case A_RecordTy:
		{
			RecordTy* rt = static_cast<RecordTy*>(n);
			std::vector<RecordType::Field> fieldVec;
			for (auto field : rt->tyfields->fields) {
				RecordType::Field tempField;
				tempField.first = field->name;
				Type* ty = TENV.Look(field->type);
				if (ty == nullptr) {
					reportErr("type %s not defined!", field->type.c_str());
					goto TRANS_TY_ERR;
				}
				tempField.second = ty;

				for (auto f : fieldVec) {
					if (f.first == tempField.first) {
						reportErr("repeat field definition %s", tempField.first.Name());
						goto TRANS_TY_ERR;
					}
				}

				fieldVec.push_back(tempField);
			}
			return new (C) RecordType(fieldVec);
		}
			break;

		case A_ArrayTy:
		{
			ArrayTy* at = static_cast<ArrayTy*>(n);
			Type* ty = TENV.Look(at->type);
			if (ty == nullptr)
			{
				reportErr("type %s not defined!", at->type.c_str());
				goto TRANS_TY_ERR;
			}
			return new (C) ArrayType(ty);
		}
			break;

		default:
			assert(0);
			break;
		}

TRANS_TY_ERR:
		return nullptr;
	}

	Type* actualTy(Type* ty) {
		while (ty->tt == Ty_Name)
			ty = static_cast<NameType*>(ty)->type;
		return ty;
	}

	Semant::ExpTy Semant::TransVarDec(VarDec* vardec) {
		Type* ty = nullptr;
		TrExp* exp = nullptr;
		ExpTy ret(nullptr, nullptr);

		if (!vardec->type.empty()) { //if var type not specified, need type induction
			ty = TENV.Look(vardec->type);
			if (ty == nullptr) {
				reportErr("type %s not exists!", vardec->type.c_str());
				return ret;
			}
			else {
				ty = actualTy(ty);
			}
		}

		ExpTy expty = TransExp(vardec->init); //TransExp do not return nullptr type
		if (expty.second == nullptr)
			return ret;

		if (!VALID_VAR_TYPE(expty.second)) {
			reportErr("cannot assign void to variable %s", vardec->name.c_str());
			return ret;
		}

		if (ty == nullptr) //type deduce
			ty = expty.second;

		if (!ValidateTypeCheck(ty, expty.second)) {
			reportErr("type mismatch!");
			return ret;
		}

		auto curLevel = Translator->CurLevel();
		auto vAccess = curLevel->AllocLocal(vardec->escape);
		auto entry = new(C) VarEntry;
		entry->access = vAccess;
		entry->type = ty;
		VENV.Enter(vardec->name, entry);

		//code gen
		TrExp* varExp = Translator->TransSimpleVar(vAccess);
		TrExp* assign = Translator->TransAssign(varExp, expty.first);

		ret.first = assign;
		ret.second = ty;
		return ret;
	}

}