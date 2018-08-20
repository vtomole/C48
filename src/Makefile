c48:	lexer.l parser.y expression.h expression.c
	bison -d parser.y && \
	flex -olexer.lex.c lexer.l && \
	cc -g -o $@ parser.tab.c lexer.lex.c expression.c -lm
clean:
	rm -f parser.tab.c lexer.lex.c parser.tab.h c48

.PHONY: all c48 clean

open:
	gedit expression.c expression.h parser.y lexer.l convert.c &

display: 
	 dot tree.dot -Tpng -o tree.png
