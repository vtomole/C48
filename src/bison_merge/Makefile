FILES	= lexer.c parser.c expression.c main.c 
CC	= gcc
CFLAGS	= -g -ansi

test:		$(FILES)
		$(CC) $(CFLAGS) $(FILES) -o test -g

Lexer.c:	lexer.l 
		flex lexer.l

Parser.c:	parser.y pexer.c
		bison parser.y

clean:
		rm -f *.o *~ lexer.c lexer.h parser.c parser.h tree.dot test 
