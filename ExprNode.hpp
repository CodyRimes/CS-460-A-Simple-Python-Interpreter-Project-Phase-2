//
// Created by Ali Kooshesh on 4/4/23.
//

//Cody: I changed the #ifndef, #define, and #endif to more accurately represent this file
#ifndef APYTHONINTERPRETER_EXPRNODE_HPP
#define APYTHONINTERPRETER_EXPRNODE_HPP


#include "Token.hpp"
#include "SymTab.hpp"

// Classes in this file define the internal representation of arithmetic expressions.


// ExprNode serves as the base class (super class) for arithmetic expression.
// It forces the derived classes (subclasses) to implement two functions, print and
// evaluate.
// STEP 3 RENAMED ArithExpr to ExprNode

class ExprNode {
public:
    explicit ExprNode(Token token);
    Token token();
    virtual void print() = 0;
    //Phase 2 step 4 changed this to return type descriptors no
    virtual TypeDescriptor* evaluate(SymTab &symTab) = 0;

private:
    Token _token;

protected:
    bool debug = false;
};


// An InfixExprNode is useful to represent binary arithmetic operators.
//This type of notation is referred to as infix since the operator is in between the two operands that it is working on
// i.e. 1 + 2 (the plus sign operator is in between the two operands)
class InfixExprNode: public ExprNode {  // An expression tree node.

public:
    explicit InfixExprNode(Token tk);

    ExprNode *&left();
    ExprNode *&right();
    void print () override;
    //Phase 2 step 4 changed this to return type descriptors now
    TypeDescriptor* evaluate(SymTab &symTab) override;

private:
    ExprNode *_left, *_right;
};

// WholeNumber is a leaf-node in an expression tree. It corresponds to
// a terminal in the production rules of the grammar that describes the
// syntax of arithmetic expressions.

class WholeNumber: public ExprNode {
public:
    explicit WholeNumber(Token token);
    void print() override;
    //STEP 4 HERE BY ADAM: ADDED FUNCTIONALITY TO EVALUATE FUNCTION TO INCLUDE HANDLING RELATIONAL OPERATORS
    //Phase 2 step 4 changed this to return type descriptors now
    TypeDescriptor* evaluate(SymTab &symTab) override;
};

// Variable is a leaf-node in an expression tree. It corresponds to
// a terminal in the production rules of the grammar that describes the
// syntax of arithmetic expressions.

class Variable: public ExprNode {
public:
    explicit Variable(Token token);
    void print() override;
    //Phase 2 step 4 changed this to return type descriptors now
    TypeDescriptor* evaluate(SymTab &symTab) override;
};

class String: public ExprNode
{
public:
    explicit String(Token token);
    void print() override;
    TypeDescriptor* evaluate(SymTab &symTab) override;
};


#endif //APYTHONINTERPRETER_EXPRNODE_HPP
