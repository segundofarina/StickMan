all:
	$(MAKE) grammar
	$(MAKE) lex
	gcc -o cstickman main.c y.tab.c lex.yy.c

grammar:
	yacc -d yacc.y

lex:
	lex lex.l

test:
	$(MAKE) all
	./cstickman < helloworld.stick > code.c
	gcc -o code code.c
