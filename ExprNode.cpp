//
// Created by Ali Kooshesh on 4/4/23.
//


#include<iostream>
#include "ExprNode.hpp"
#include "TypeDescriptor.hpp"
//ExprNode is a base class that we literally never use directly. We only use ExprNode pointers so that we can employ polymorphism to have code which works on all ExprNode subclasses and dynamically behaves according to subclass traits at runtime. We are always using the evaluate method of subclasses because every ExprNode subclass must define their own evaluate method (because it is declared a virtual method in ExprNode). If we aren't evaluating an atomic value (a variable, a literal number, a literal string, etc.) then we are using the InfixExprNode evaluate method.
// STEP 3 RENAME ArithExpr to ExprNode
// ExprNode
ExprNode::ExprNode(Token token): _token{token} {}

Token ExprNode::token() { return _token; }

// InfixExprNode functions
InfixExprNode::InfixExprNode(Token tk) : ExprNode{tk}, _left(nullptr), _right(nullptr) {}

ExprNode *&InfixExprNode::left() { return _left; }

ExprNode *&InfixExprNode::right() { return _right; }

//Phase 2 step 4 changed this to return type descriptors now
TypeDescriptor* InfixExprNode::evaluate(SymTab &symTab) {
    // Evaluates an infix expression using a post-order traversal of the expression tree.
    // Cody May 4th 2023: Phase 2 Part 3: changed lValue and rValue to be of TypeDescriptor* pointer types. Note how we could probably use auto here as well.
    TypeDescriptor* lValue = left()->evaluate(symTab);
    TypeDescriptor* rValue = right()->evaluate(symTab);
    if(debug)
        std::cout << "InfixExprNode::evaluate: " << lValue << " " << token().symbol() << " " << rValue << std::endl;
    if (token().isAdditionOperator())
        return *lValue + rValue;
    else if (token().isSubtractionOperator())
        return *lValue - rValue;
    else if (token().isMultiplicationOperator())
        return *lValue * rValue;
    else if (token().isDivisionOperator())
        return *lValue / rValue; // division by zero?
    else if (token().isModuloOperator())
        return *lValue % rValue;
    //Cody: Looks like Adam completed part of Step 4 here and added this functionality to the expression node class function
    else if (token().isLessThanOperator())
        return *lValue < rValue;
    else if (token().isLessThanOrEqualToOperator())
        return *lValue <= rValue;
    else if (token().isGreaterThanOperator())
        return *lValue > rValue;
    else if (token().isGreaterThanOrEqualToOperator())
        return *lValue >= rValue;
    else if (token().isEqualOperator())
        return *lValue == rValue;
    else if (token().isNotEqualOperator())
        return *lValue != rValue;
    else if (token().isPythonIntegerDivisionSymbol())
    {
        return *lValue / rValue;
    }
    else {
        std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
        token().print();
        std::cout << std::endl;
        exit(2);
    }
}

void InfixExprNode::print() {
    _left->print();
    token().print();
    _right->print();
}

// WholeNumber
WholeNumber::WholeNumber(Token token): ExprNode{token} {}

void WholeNumber::print() {
    token().print();
}

//Phase 2 step 4 changed this to return type descriptors now
TypeDescriptor* WholeNumber::evaluate(SymTab &symTab) {
    if(debug)
        std::cout << "WholeNumber::evaluate: returning " << token().getWholeNumber() << std::endl;
    return new TypeDescriptor(TypeDescriptor::INTEGER,  token().getWholeNumber());
    //return token().getWholeNumber();
}

//Cody May 8th 2023: For Phase 2 we will need to have an ExprNode that can handle doubles as well
//Constructor (This allows our ExprNode to hold a token/data
DoubleNumber::DoubleNumber(Token token): ExprNode{token} {}

//Print what the token that this type of ExprNode holds
void DoubleNumber::print() {
    token().print();
}

TypeDescriptor* DoubleNumber::evaluate(SymTab &symTab) {
    if(debug)
        std::cout << "ExprNode.cpp::DoubleNumber::evaluate: returning " << token().getDoubleNumber() << std::endl;
    return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::DOUBLE,  token().getDoubleNumber());
    //return token().getWholeNumber();
}


// Variable

Variable::Variable(Token token): ExprNode{token} {}

void Variable::print() {
    token().print();
}

//Phase 2 step 4 changed this to return type descriptors now
TypeDescriptor* Variable::evaluate(SymTab &symTab) {
    if( ! symTab.isDefined(token().getName())) {
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }
    if(debug)
        std::cout << "Variable::evaluate: returning " << symTab.getValueFor(token().getName()) << std::endl;
    return symTab.getValueFor(token().getName());
}

//Cody May 7th 2023 Phase 2 Step 4 had to add a new ExprNode sub-class that can handle string literals
StringLiteral::StringLiteral(Token token) : ExprNode{token} {}

void StringLiteral::print() {
    token().print();
}

//Phase 2 step 4 changed this to return type descriptors now
//Cody May 11th 2023: If you think about it when we call our evaluate function on our statements class (which will eventually call all evaluate methods on the substructures that make up that class, including this one)
//When we get to a ExpressionNode that contains a string (i.e. our String sub-class of ExprNode that extends ExprNode class to handle strings) and we want to evaluate it
//Such as in a statement such as: VariableToConcatenateTwoStringsTogether = "Hello" + "World"
//When we get down in our ExprNode tree of just the two string literals, when we "evaluate" them to return them up to the calling function (i.e. going back up our tree)
//We will just want to return the string literal as our evaluation when we get this low in the program, that way the ExprNode above us (in this case can add the two string literals together) can do whatever operation it contains on String ExprNode sub-class it gets back
//Thus there is no need for a look up in the Symbol Table or operation on it, like how we would do if we had a Variable ExprNode sub-class type that contained a variable which would need it's value/datatype looked up in the SymbolTable
//String literals do not need to go into the SymbolTable or modify it as they are not variables that contain a value/need to be looked up for. String literals are string literals and that's what they return
//Note how we pass in the &symTab parameter here but never use it within the function. That is to follow the virtual function declared in our parent class ExprNode which must have a match with the function declaration
TypeDescriptor* StringLiteral::evaluate(SymTab &symTab) {

    if(debug)
        std::cout << "StringLiteral::evaluate: returning " << token().getStringFromGenericStringHolder() << std::endl;
    return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::STRING, token().getStringFromGenericStringHolder());;
}


