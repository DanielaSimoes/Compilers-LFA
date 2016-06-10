CXX = g++
CXXFLAGS = -Wall -std=c++11

ANCLASSES += astNode

NCLASSES += astBreak
NCLASSES += astExit
NCLASSES += astFloatDecl
NCLASSES += astIf
NCLASSES += astIntDecl
NCLASSES += astLoop
NCLASSES += astPrintStr
NCLASSES += astProgram
NCLASSES += astSeq
NCLASSES += astSpaceDecl
NCLASSES += astStringDecl

AVCLASSES += astValue

VCLASSES += astIntegerValue
VCLASSES += astFloatValue
VCLASSES += astVarValue
VCLASSES += astFunctionCall
VCLASSES += astPrint
VCLASSES += astAssignToVar
VCLASSES += astCast
VCLASSES += astRelop
VCLASSES += astOperation
VCLASSES += astArrayHead
VCLASSES += astIntegerArrayValue
VCLASSES += astFloatArrayValue
VCLASSES += astArrayElementValue
VCLASSES += astStringValue
VCLASSES += astAssignToArrayElement
VCLASSES += astByteArrayValue

OBJS += $(ANCLASSES:%=%.o)
OBJS += $(NCLASSES:%=%.o)
OBJS += $(VCLASSES:%=%.o)

libast.a :	$(OBJS)
	ar cr $@ $^

$(NCLASSES:%=%.o):	%.o:	%.h $(ANCLASSES:%=%.h)
$(VCLASSES:%=%.o):	%.o:	%.h $(ANCLASSES:%=%.h) $(AVCLASSES:%=%.h)
$(ANCLASSES:%=%.o):	%.o:	%.h

clean:
	rm -rf *.o

cleanall:	clean
	rm -f libast.a
