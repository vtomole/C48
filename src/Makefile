# $Header: /home/johnl/flnb/code/RCS/Makefile.ch3,v 2.1 2009/11/08 02:53:18 johnl Exp $
# Companion source code for "flex & bison", published by O'Reilly
# Media, ISBN 978-0-596-15597-1
# Copyright (c) 2009, Taughannock Networks. All rights reserved.
# See the README file for license conditions and contact info.

# programs in chapter 3


test:	lexer.l parser.y expression.h expression.c
	bison -d parser.y && \
	flex -olexer.lex.c lexer.l && \
	cc -g -o $@ parser.tab.c lexer.lex.c expression.c -lm
repl:
	gcc repl.c -o repl

clean:
	rm -f parser.tab.c lexer.lex.c parser.tab.h test
