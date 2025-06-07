parser:  yprojecty.tab.o lex.yy.o
	gcc -o parser yprojecty.tab.o lex.yy.o

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	flex scanner.l

yprojecty.tab.o: yprojecty.tab.c yprojecty.tab.h parser_header.h
	gcc -c yprojecty.tab.c

yprojecty.tab.c: yprojecty.y
	bison -d yprojecty.y

yprojecty.tab.h: yprojecty.y
	bison -d yprojecty.y

clean:
	rm -f *.o parser.exe parser yprojecty.tab.c yprojecty.tab.h lex.yy.c *.jasm *.class

jasm: 
	for f in *.sd; do \
		./parser "$$f"; \
		jasmfile="$${f%.sd}.jasm"; \
		if [ -f "$$jasmfile" ]; then \
			../javaaPortable/javaa "$$jasmfile"; \
		fi \
	done