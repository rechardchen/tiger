grammar tiger;

//grammar
prog : exp | decs;

exp
	// Literals
	: 'nil'												#NilExp
	| INT												#IntExp
	| STRING											#StringExp
	// Array and record creations
	| type_id '[' exp ']' 'of' exp 						#ArrayExp
	| type_id '{' (ID '=' exp (',' ID '=' exp)* )? '}'	#RecordExp
	//Object creation
	| 'new' type_id										#NewExp
	//Lvalue
	| lvalue 											#LvalueExp
	// Function call
	| ID '(' (exp (',' exp)*)? ')' 						#FuncCallExp
	// Method call
	| lvalue '.' ID '(' (exp (',' exp)*)? ')' 			#MethodCallExp
	//Operations
	| '-' exp 											#NegExp
	| exp op=('*'|'/') exp 								#MulDivExp
	| exp op=('+'|'-') exp 								#AddSubExp
	| exp op=('='|'<>'|'>='|'<='|'>'|'<') exp 				#RelOpExp
	| exp op=('&'|'|') exp 								#LogicExp
	| '(' exps ')' 										#ExplistExp
	//Assignment
	| lvalue ':=' exp 									#AssignExp
	//Control structures
	| 'if' exp 'then' exp ('else' exp)? 				#IfExp
	| 'while' exp 'do' exp 								#WhileExp
	| 'for' ID ':=' exp 'to' exp 'do' exp 				#ForExp
	| 'break' 											#BreakExp
	| 'let' decs 'in' exps 'end' 						#LetExp
	;

// Can not handle lvalue such as F(x,y), todo add this
lvalue
	: ID 												#SimpleVar
	| lvalue '.' ID 									#FieldVar
	| lvalue '[' exp ']' 								#SubScriptVar
	;

exps: (exp (';' exp)*)? #ExprList; 								

decs: dec* #DecList; 											

dec
	//Type declaration
	: 'type' ID '=' ty 									#TypeDec
	//Class definition (alternative form)
	| 'class' ID ('extends' type_id)? '{' classfields* '}' #ClassDec
	//Variable declaration
	| vardec   	#DecVarDec									
	//Function declaration
	| 'function' ID '(' tyfields ')' (':' type_id)? '=' exp #FunDec
	//Import a set of declarations, add from x import y (TODO)
	| 'import' STRING  										#ImportDec
	;

ty
	//Type alias
	: type_id  											#NameTy
	//Record type definition
	| '{' tyfields '}' 									#RecordTy
	//Array type definition
	| 'array' 'of' type_id 								#ArrayTy
	//Class type definition
	| 'class' ('extends' type_id)? '{' classfields* '}'  #ClassTy
	;

tyfields: (ID ':' type_id (',' ID ':' type_id)*)? #TyFields; 

classfields
	//Attribute declaration
	: vardec      										#ClassVarDec
	//method declaration
	| 'method' ID '(' tyfields ')' (':' type_id)? '=' exp #MethodDec
	;

vardec: 'var' ID (':' type_id)? ':=' exp #VarDec; 				

type_id: ID;



//lexer
STRING : '"' (ESC|.)*? '"';
ID : LETTER (LETTER | DIGIT | '_')*;
INT : DIGIT+;
COMMENT : '/*' .*? '*/' -> skip;
WS : [ \t\r\n]+ -> skip;

fragment
LETTER : [a-zA-Z];

fragment
DIGIT : [0-9];

fragment
ESC : '\\\\' | '\\n' | '\\t' | '\\a' | '\\b' | '\\v' | '\\f' | '\\r' | '\\"';