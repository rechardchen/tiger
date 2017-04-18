grammar tiger;

//grammar
prog : exp | decs;

exp
	// Literals
	: 'nil'
	| INT
	| STRING
	// Array and record creations
	| typeid '[' exp ']' 'of' exp
	| typeid '{' (ID '=' exp (',' ID '=' exp)* )? '}'
	//Object creation
	| 'new' typeid
	//Lvalue
	| lvalue
	// Function call
	| ID '(' (exp (',' exp)*)? ')'
	// Method call
	| lvalue '.' ID '(' (exp (',' exp)*)? ')'
	//Operations
	| '-' exp
	| exp ('*'|'/') exp
	| exp ('+'|'-') exp
	| exp ('='|'<>'|'>='|'<='|'>'|'<') exp
	| exp ('&'|'|') exp
	| '(' exps ')'
	//Assignment
	| lvalue ':=' exp
	//Control structures
	| 'if' exp 'then' exp ('else' exp)?
	| 'while' exp 'do' exp
	| 'for' ID ':=' exp 'to' exp 'do' exp
	| 'break'
	| 'let' decs 'in' exps 'end'
	;

lvalue
	: ID
	| lvalue '.' ID
	| lvalue '[' exp ']'
	;

exps: (exp (';' exp)*)? ;

decs: dec*;

dec
	//Type declaration
	: 'type' ID '=' ty
	//Class definition (alternative form)
	| 'class' ID ('extends' typeid)? '{' classfields '}'
	//Variable declaration
	| vardec
	//Function declaration
	| 'function' ID '(' tyfields ')' (':' typeid)? '=' exp
	//Import a set of declarations, add from x import y (TODO)
	| 'import' STRING
	;

ty
	//Type alias
	: typeid
	//Record type definition
	| '{' tyfields '}'
	//Array type definition
	| 'array' 'of' typeid
	//Class type definition
	| 'class' ('extends' typeid)? '{' classfields '}'
	;

tyfields: (ID ':' typeid (',' ID ':' typeid)*)? ;

classfields
	//Attribute declaration
	: vardec
	//method declaration
	| 'method' ID '(' tyfields ')' (':' typeid)? '=' exp
	;

vardec: 'var' ID (':' typeid)? ':=' exp;

typeid: ID;



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