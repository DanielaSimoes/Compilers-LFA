CXX = g++
CXXFLAGS = -Wall -std=c++11 -I. -Iast
LEX = flex
YACC = bison

OBJS = main.o parser.o lexer.o symtable.o

.PHONY: all clean cleanall lib

all:	lib s16c

s16c:	    $(OBJS) lib
	$(CXX) -o $@ $(OBJS) -L ast -l ast

main.o:	    parser.h lexer.h main-data.h ast.h symtable.h

symtable.o: symtable.h

lib:	
	make -C ast libast.a

parser.cpp parser.h parser.dot:	parser.y main-data.h ast.h symtable.h
	$(YACC) parser.y --graph -o parser.cpp

lexer.cpp lexer.h:	lexer.l parser.h ast.h
	$(LEX) -olexer.cpp lexer.l

lexer.o:	lexer.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

parser.o:	parser.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:	
	rm -f *.o parser.h lexer.h parser.cpp lexer.cpp parser.dot
	rm -f *.output
	make -C ast clean

cleanall:	clean
	rm -f s16c
	make -C ast cleanall
