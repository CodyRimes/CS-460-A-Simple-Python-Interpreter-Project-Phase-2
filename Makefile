.SUFFIXES: .o .cpp .x

CFLAGS = -ggdb -std=c++17
objects =  Token.o Tokenizer.o Parser.o ExprNode.o SymTab.o Statements.o main.o TypeDescriptor.o git

statement.x: $(objects)
	g++ $(CFLAGS) -o statement.x $(objects)

.cpp.o:
	g++ $(CFLAGS) -c $< -o $@


Token.o:  Token.cpp Token.hpp
Tokenizer.o: Tokenizer.cpp Tokenizer.hpp
ExprNode.o: ExprNode.cpp ExprNode.hpp Token.hpp SymTab.hpp
TypeDescriptor.o: TypeDescriptor.cpp TypeDescriptor.hpp
SymTab.o: SymTab.cpp SymTab.hpp
Parser.o: Parser.cpp Token.hpp Parser.hpp Tokenizer.hpp SymTab.hpp ExprNode.hpp Statements.hpp
Statements.o: Statements.cpp Statements.hpp ExprNode.hpp Token.hpp SymTab.hpp
main.o: main.cpp Token.hpp Tokenizer.hpp Parser.hpp SymTab.hpp ExprNode.hpp Statements.hpp

clean:
	rm -fr *.o *~ *.x

#To run the code please use the command ./statements.x sampleInput.txt
