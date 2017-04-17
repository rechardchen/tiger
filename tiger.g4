grammar tiger;


STR :
COMMENT : '/*' .*? '*/' -> skip;
ID : LETTER [LETTER | DIGIT | '_']*;
INT : DIGIT+;
WS : [ \t\r\n]+ -> skip;

fragment
LETTER : [a-zA-Z];

fragment
DIGIT : [0-9];