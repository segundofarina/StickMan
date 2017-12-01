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

<<<<<<< HEAD
	./stickman < ../testCodes/mrmeeseeks.stick > ../compiled/compiledCode.c
=======
	./cstickman < ../testCodes/helloworld.stick > ../compiled/compiledCode.c
>>>>>>> cfb5dc0b1b3da667e847b20bbf25679b9a5ab1a5

clean:
	rm lex.yy.c y.tab.c y.tab.h
