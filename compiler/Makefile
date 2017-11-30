all:
	$(MAKE) grammar
	$(MAKE) lex
	gcc -o stickman main.c y.tab.c lex.yy.c syntaxTree/*.c
	$(MAKE) clean

grammar:
	yacc -d yacc.y

lex:
	lex lex.l

test:
	$(MAKE) all

	./stickman < ../testCodes/mrmeeseeks.stick > ../compiled/compiledCode.c

clean:
	rm lex.yy.c y.tab.c y.tab.h
