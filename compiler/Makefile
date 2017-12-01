all:
	$(MAKE) grammar
	$(MAKE) lex
	gcc -o  cstickman cstickman.c y.tab.c lex.yy.c syntaxTree/*.c helpers/*.c ../lib.c
	$(MAKE) clean

grammar:
	yacc -d yacc.y

lex:
	lex lex.l

test:
	$(MAKE) all


	./cstickman < ../testCodes/helloworld.stick > ../compiled/compiledCode.c

clean:
	rm lex.yy.c y.tab.c y.tab.h
