all:
	$(MAKE) grammar
	$(MAKE) lex
	gcc -o cstickman cstickman.c y.tab.c lex.yy.c

grammar:
	yacc -d grammar.y

lex:
	lex tokens.l

test:
	$(MAKE) all
	./cstickman < ../test/code.st > ../test/code.c
	gcc -o ../test/code ../test/code.c
