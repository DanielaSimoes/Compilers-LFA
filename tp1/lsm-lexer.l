%{
    #include <stdlib.h>

    #include <stdint.h>
    #include "lsm-parser.h"

    #define UPDATE_LOC yylloc->first_line = yylloc->last_line = yylineno; \
        yylloc->first_column = yycolumn; yylloc->last_column = yycolumn+yyleng-1; \
        yycolumn += yyleng;
%}

%option noyywrap
%option nounput noinput
%option nodefault yylineno
%option reentrant bison-bridge bison-locations
%option header-file="lsm-lexer.h"

/*intop         (iadd|isub|imul|idiv|irem|ineg|iand|ior|ixor|ishl|ishr|iushr)*/
/*realop        (fadd|fsub|fmul|fdfv|frem|fneg|i2f|f2i)*/
/*jumpop        (goto|jsr|ifeq|ifne|iflt|ifge|ifgt|ifle)*/
/*stack         (pop|dup|dup_x1|dup2|swap|baload|bastore|iaload|iastore|faload|fastore)*/
/*stacklabel    (load|store)*/

hexadecimal   [+-]?0[Xx][0-9A-Fa-f]{1,8}
decimal       [+-]?[0-9]+
float         [+-]?(([0-9]*\.)*[0-9]+)|(\.[0-9]+)|([0-9]+\.)
char		      ('.')
string		    ("[A-za-z_][A-za-z0-9_]*")
iadd          (iadd)
isub          (isub)
imul          (imul)
idiv          (idiv)
irem          (irem)
ineg          (ineg)
iand          (iand)
ior           (ior)
ixor          (ixor)
ishl          (ishl)
ishr          (ishr)
iushr         (iushr)
fadd          (fadd)
fsub          (fsub)
fmul          (fmul)
fdiv          (fdiv)
frem          (frem)
fneg          (fneg)
i2f           (i2f)
f2i           (f2i)
ret           (ret)
goto          (goto)
jsr           (jsr)
ifeq          (ifeq)
ifne          (ifne)
iflt          (iflt)
ifge          (ifge)
ifgt          (ifgt)
ifle          (ifle)
bipush        (bipush)
ipush         (ipush)
fpush         (fpush)
store         (store)
load          (load)
pop           (pop)
dup           (dup)
dup_x1        (dup_x1)
dup2          (dup2)
swap          (swap)
baload        (baload)
bastore       (bastore)
iaload        (iaload)
iastore       (iastore)
faload        (faload)
fastore       (fastore)
nop           (nop)
halt          (halt)
read          (read)
write         (write)
dirdata       (\.data)
dirtext       (\.text)
dirbyte  	    (\.byte)
dirword		    (\.word)
dirfloat	    (\.float)
dirstring	    (\.string)
dirspace	    (\.space)
label         [A-za-z_][A-za-z0-9_]*
comment       ;[^\n\r]*
whitespace    [ \r\t]*
%%
