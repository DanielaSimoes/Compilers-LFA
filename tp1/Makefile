CC = g++
CFLAGS = -Wall
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Wno-deprecated-register 
LEX = flex
YACC = bison

all:	lsm-asm lsm-vm

lsm-asm:	    lsm-asm.o lsm-parser.o lsm-lexer.o lbl-table.o
	$(CC) -o $@ $^

lsm-asm.o:	lsm-parser.h lsm-lexer.h lsm-data.h

lsm-parser.o:	lsm-lexer.h lsm-data.h

lsm-lexer.o:	lsm-parser.h

lsm-parser.cpp lsm-parser.h:	lsm-parser.y
	$(YACC) lsm-parser.y -o lsm-parser.cpp --graph

lsm-lexer.cpp lsm-lexer.h:	lsm-lexer.l
	$(LEX) -olsm-lexer.cpp lsm-lexer.l


clean:
	rm -f *.o lsm-parser.h lsm-lexer.h lsm-parser.cpp lsm-lexer.cpp
	rm -f *.output *.dot *~

cleanall:	clean
	rm -f lsm-asm lsm-vm
