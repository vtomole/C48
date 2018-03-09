INTRODUCTION

This is the reference manual for the C48 programming language.

C48 is a static, strong, inferred and garbage collected language that students can use to understand compilers.

The notation for this spec is extended BNF


SOURCE CODE REPRESENTATION

The source code is represented in UTF-8


LEXICAL STRUCTURE

Line commments start with // and stop at the end of the line

Multi-line comments start with /* a and stop after a subsequenct  */


Lines that contain blanks tabs and comments are ignored


Semicolons are used to terminate statements


Identifiers are for variables and types. It can be a sequence of one or more letters and digits. The first letter has to be a letter:

identifier = letter{ letter | digit}


Keywords:

else
for
fun
if
return
and
or 
equal
switch
true
false


Operators and punctuation:

+
-
*
/
%
<
>
;
.

Integer:

int = decimal
decimal = ("1" .. "9")



FLoating point:
TODO


Imaginary:
imaginary = (decimals | float) "i"



String:
Strings are represented in double quotes:
Example " "



Constants:
TODO


Variables:

set "variable" whatever you want to set


Types:
Array
Boolean
Struct
Functions
Lists

Program → Expr
Expr → Number | Variable | ArithExpr | IfExpr | VarExpr | FExpr | VarExpr | RefExpr

ArithExpr → ( + Expr Expr) | ( - Expr Expr) | ( * Expr Expr) | ( / Expr Expr) | ( % Expr Expr)
IfExpr → (CCond Expr Expr)
CCond → BCond | (or CCond CCond) | (and CCond CCond) | (not CCond)
BCond → (gt Expr Expr) | (lt Expr Expr) | (eq Expr Expr)

VarExpr → (set VarAssign Expr)
VarAssign → Variable Expr

FExpr → (fun FAssign Expr)
FAssign → ((name FormalParams ) Expr)
FormalParams → () | (FormalParamList)
FormalParamList → Variable | Variable FormalParamList

ApplyF → (apply (name Args))
Args → () | (ArgList)
ArgList → Expr | Expr ArgList

RefExpr → DRef | WRef | Ref
DRef → (deref Expr)
WRef → (wref Expr)
Ref → (ref Expr) | (free Expr)


















