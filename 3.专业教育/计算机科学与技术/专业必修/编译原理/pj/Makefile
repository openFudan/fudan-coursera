CC=gcc
CFLAGS=-D YYDEBUG -g -Wno-varargs

OBJ=minijava.tab.o sym.o absyn.o state.o error.o lex.yy.o util.o parse_tree_back.o #parse_tree_front.o
all: scaner parse
	@echo done

parse: $(OBJ) parse.o
	gcc $^ -o $@

scaner: $(OBJ) scaner.o
	gcc $^ -o $@

lex.yy.c: minijava.lex
	lex $^
	
lex.yy.o: lex.yy.c
	gcc $(CFLAGS) -c $^ -o $@

minijava.tab.o: minijava.tab.c
	gcc $(CFLAGS) -c $^ -o $@

minijava.tab.c: minijava.y
	bison -d -x $^
	xsltproc `bison --print-datadir`/xslt/xml2xhtml.xsl minijava.xml > debug.html

clean:
	rm -rf *.o a.out y.tab.[ch] lex.yy.c minijava.xml minijava.tab.[ch] debug.html \
		parse scaner
