all:
	$(MAKE) grammar
	$(MAKE) lex
	gcc -o  cstickman cstickman.c y.tab.c lex.yy.c syntaxTree/*.c helpers/*.c
	$(MAKE) clean

grammar:
	yacc -d yacc.y

lex:
	lex lex.l

test:
	$(MAKE) all


	./cstickman < ../testCodes/mrmeeseeks.stick > ../compiled/compiledCode.c
testCompiled:

	gcc -o prueba helpers/lib.c ../compiled/compiledCode.c
clean:
	rm lex.yy.c y.tab.c y.tab.h
