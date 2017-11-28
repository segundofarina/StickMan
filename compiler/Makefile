all:
	$(MAKE) grammar
	$(MAKE) lex
	gcc -o stickman main.c y.tab.c lex.yy.c

grammar:
	yacc -d grammar.y

lex:
	lex lex.l

test:
	$(MAKE) all
	./stickman > helloworld.stick
