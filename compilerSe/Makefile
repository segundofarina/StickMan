all:
	$(MAKE) grammar
	$(MAKE) lex
	gcc -o stickman main.c y.tab.c lex.yy.c
	$(MAKE) clean

grammar:
	yacc -d yacc.y

lex:
	lex lex.l

test:
	$(MAKE) all
	./stickman < helloworld.stick
clean:
	rm lex.yy.c y.tab.c y.tab.h  
