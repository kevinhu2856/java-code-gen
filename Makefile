parser: yprojecty.tab.c lex.yy.c
	gcc -c yprojecty.tab.c
	gcc -c lex.yy.c
	gcc -o parser yprojecty.tab.o lex.yy.o

lex.yy.c: scanner.l
	flex scanner.l

yprojecty.tab.c: yprojecty.y
	bison -d yprojecty.y

yprojecty.tab.h: yprojecty.y
	bison -d yprojecty.y

clean:
	rm -f *.o parser.exe yprojecty.tab.c yprojecty.tab.h lex.yy.c *.class