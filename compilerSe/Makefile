all:
	$(MAKE) grammar
	$(MAKE) lex
<<<<<<< HEAD
	gcc -o cstickman main.c y.tab.c lex.yy.c

grammar:
	yacc -d yacc.y
=======
	gcc -o stickman main.c y.tab.c lex.yy.c
	$(MAKE) clean

grammar:
	yacc -d grammar.y
>>>>>>> 756338923cef32a1d0c62c13e0dc8d3edc2dabcc

lex:
	lex lex.l

test:
	$(MAKE) all
<<<<<<< HEAD
	./cstickman < helloworld.stick > code.c
	gcc -o code code.c
=======
	./stickman > helloworld.stick

clean:
	rm lex.yy.c y.tab.c y.tab.h  
>>>>>>> 756338923cef32a1d0c62c13e0dc8d3edc2dabcc
