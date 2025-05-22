parser: yprojecty.tab.c lex.yy.c
	gcc -o parser yprojecty.tab.c lex.yy.c

lex.yy.c: scanner.l
	flex scanner.l

yprojecty.tab.c: yprojecty.y
	bison -d yprojecty.y

yprojecty.tab.h: yprojecty.y
	bison -d yprojecty.y