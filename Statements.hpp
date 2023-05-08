//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_STATEMENTS_HPP
#define APYTHONINTERPRETER_STATEMENTS_HPP

#include <iostream>
#include <vector>

#include "ExprNode.hpp"
#include "SymTab.hpp"
#include "Parser.cpp"

// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.

class Statement {
public:
    Statement();

    virtual void print() = 0;
    virtual void evaluate(SymTab &symTab) = 0;

};


// Statements is a collection of Statement. For example, all statements in a function
// can be represented by an instance of Statements.

class Statements {
public:
    Statements();

    void addStatement(Statement *statement);
    void evaluate(SymTab &symTab);

    void print();

private:
    std::vector<Statement *> _statements;
};



// AssignmentStatement represents the notion of an lValue having been assigned an rValue.
// The rValue is an expression.

class AssignmentStatement : public Statement {
public:
    //Default constructor
    AssignmentStatement();
    //Parameterized constructor that we use in the parser.cpp file after we have correctly parsed the tokens in the correct manner.
    //I.e. we give back the correct pieces of an assignment statement after making sure was syntatically and correctly formated, and we use this assignment statement that used the parameterized constructor to start analyzing what our actual assignment statement contains later on with our evaluate() function
    AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr);

    //Functions to get the private member variables/their values
    //Note how we do not need setters as we use our parameterized constructor as a setter
    std::string &lhsVariable();
    ExprNode *&rhsExpression();

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    //The left hand side of the assignment statement will be a variable name as we know that is the proper syntax of an assignment statement. Lets create a private string variable called _lhsVariable to capture that. Ex. (sum = 3 + 3) this variable will capture the string "sum" in this example
    std::string _lhsVariable;
    //On the right hand side of an assignment statement we know generically we will have some sort of expression on the right hand side
    ExprNode* _rhsExpression;
};

class PrintStatement : public Statement {
public:
    //Default constructor
    PrintStatement();

    //Parameterized constructor which will be used by our parser after our parser checks to make sure everything is in the right order and our tokens are the right tokens. This is the print statement we will then use our evaluate() and print() functions on
    PrintStatement(ExprNode* rhsExprs);

    //Probably will need this code for phase 2 of the project. Commenting out below code for now - Cody May 1st 2023
    //Parameterized constructor which will be used by our parser after our parser checks to make sure everything is in the right order and our tokens are the right tokens. This is the print statement we will then use our evaluate() and print() functions on
    //PrintStatement(std::string lhsVar, std::vector<ExprNode*> rhsExprs);

    //Functions to get the private member variables/their values
    //Note how we do not need setters as we use our parameterized constructor as a setter
    //std::string& lhsVariableGetter();
    ExprNode* _rhsExpressionGetter();

    //We will need below code for phase 2
    std::vector<ExprNode*> &rhsExpression();

    virtual void print();
    virtual void evaluate(SymTab& symTab);

private:
    //For a print statement we may not need a left hand side variable, we only know we need to print whatever is after a print keyword!
    //std::string _lhsVariable;
    ExprNode* _rhsExpression;

    //May need below code for phase 2
    std::vector<ExprNode*> containerForMultipleExpressionNodes;
};



//CODY MAY 7th 2023 COMMENTING OUT THIS CODE AS IT IS NOT NECESSARY:
/*
//SimpleStatement class will hold all the parts of a correctly parsed print_statement or assignment_statement once the parser.cpp file is finished parsing one for us.
//ON MAY 3rd 2023 MADE THIS COMMIT MESSAGE:
//"Without testing, I believe I have implemented code that handles the grammar rules necessary for <simple-statement> -> <print-statement
//nt> | <assignment-statement>. This entails a class called SimpleStatement which basically holds either an AssignmentStatement or a PrintStatement, and can print and evaluate either/or. I have also included a parser function that parses tokens to make sur
//e they follow the correct syntax for a <simple-statement> within the parser.cpp file. I want to be very clear that I am making this commit at this time to provide context that after writing all this code I do believe there is a way to parse simple-statem
//ents without the class or additional parser function. I believe had I worked on the statements() parser function in parser.cpp I could have done the parsing there and effectively still followed the grammar rule <simple-statemetn> -> <print-statement> | <
//assignment-statement>, i.e. could have functionally followed the grammar rules with a lot less work. If testing fails I would recommend coming to this commit and branching off of it and implementing the above recommended solution (deleting the SimpleStat
//ement class, and deleting the simpleStatement() parser function in parser.cpp and instead focusing on parsing a simple-statement within the statements() parser function). Committing now and pushing code up to remote repository.
//BASICALLY THIS CODE MAY BE UNESSARY AND COULD HAVE FUNCTIONALLY PASSED THE GRAMMAR RULES BY MODIFYING THE statements() PARSER FUNCTION!!
class SimpleStatement : public Statement
{
public:
    //Default constructor for a SimpleStatement
    SimpleStatement();

    //Parameterized constructors for a SimpleStatement (Parser.cpp will use this to set the private member variables of a syntactically correct
    //Note how in our simple statement class we will only have one or the other when it comes to the SimpleStatement being made up of a AssignmentStatement or a PrintStatement, never both. Hence we will have an overloaded parameterized constructor the parser will use when it sees that the SimpleStatement is made up of one or the other.
    SimpleStatement(AssignmentStatement* setPrivateAssignmentStatementVariableToThis);
    SimpleStatement(PrintStatement* setPrivatePrintStatementVariableToThis);

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    //A simple statement is either made up of a print_statement or assignment_statement. Let's declare private member variables to hold these values
    AssignmentStatement* _thisSimpleStatementsAssignmentStatement;
    PrintStatement* _thisSimpleStatementsPrintStatement;
    //A simple statement is terminated with a new line character. For now lets make sure we capture that to make sure we have a syntatically correct simple statement
    //Token _endOfLineToken; commenting out as we may not need this
};
*/

class ForStatement : public Statement {
public:
    //Default constructor
    ForStatement();
    //Parameterized constructor which will be used by our parser after our parser checks to make sure everything is in the right order and our tokens are the right tokens. This is the for statement we will then use our evaluate() and print() functions within our main.cpp file
    ForStatement(AssignmentStatement* firstAssignmentStatement, ExprNode* relationalExpressionWithinForLoop, AssignmentStatement* updateToFirstAssignmentStatement, Statements* statementsWithinTheForLoopBody);


    //Here are the getters for our private member variables in case we need them. Note how we use the parameterized constructor as a setter for all of our private member variables in one shot.
    AssignmentStatement* getOurInitialStatement();
    ExprNode* getOurConditionalExpressionInForLoop();
    AssignmentStatement* getOurUpdateToInitialAssignmentExpression();
    Statements* getOurBodyOfForLoop();

    virtual void evaluate(SymTab &symTab);
    virtual void print();



    //Commenting out code Adam gave me. I believe this will be used for phase 2 but this is not needed for phase 1. - Cody May 1st 2023
    /* ForLoopStatement();

    ForLoopStatement(AssignmentStatement* pStatement, ExprNode* pNode, AssignmentStatement* pStatement1, Statements* pStatements) :
            _initStatement(pStatement), _conditionExpression(pNode), _updateExpression(pStatement1), _body(pStatements) {}

    //Functions to get the private member variables/their values
    //Note how we do not need setters as we use our parameterized constructor as a setter
    AssignmentStatement _initialAssignmentStatement() { return *_initialAssignmentStatement; }
    ExprNode* _conditionalExpressionInForLoop() { return _conditionalExpressionInForLoop; }
    AssignmentStatement _updateToInitialAssignmentExpression() { return *_updateToInitialAssignmentExpression; }
    Statements& _bodyOfForLoop() { return *_bodyOfForLoop; }

    virtual void print() {
        std::cout << "for ( "; _initStatement->print(); std::cout << ";  "; _conditionExpression->print(); std::cout << "; "; _updateExpression->print(); std::cout << ") {";
        _body->print();
        std::cout << "}";
    }

    virtual void evaluate(SymTab& symTab) {
        _initStatement->evaluate(symTab);
        while (_conditionExpression->evaluate(symTab)) {
            _body->evaluate(symTab);
            _updateExpression->evaluate(symTab);
        }
    }

     */


private:
    AssignmentStatement* _initialAssignmentStatement;
    ExprNode* _conditionalExpressionInForLoop;
    AssignmentStatement* _updateToInitialAssignmentExpression;
    Statements* _bodyOfForLoop;
};




//Cody May 7th 2023: Moved Adam's code/funcationality to our tokenizer as comemnts need to be thrown away by the compiler but we still need to process them/read past them (i.e. they do not impact the program we are trying to interpret with this project)
//Commenting out code
/*
class CommentStatement : public Statement {
public:
    // Default constructor
    CommentStatement() {}

    // Parameterized constructor
    CommentStatement(std::vector<std::string> expression) : expression(expression) {}

    // Override the print function
    virtual void print() {
        std::cout << "# ";
        for (std::string str : expression) {
            std::cout << str << " ";
        }
        std::cout << std::endl;
    }

    // Override the evaluate function
    virtual void evaluate(SymTab& symTab) {}

private:
    // We only need to save the comment as a string
    std::vector<std::string> expression;

};
*/
#endif //APYTHONINTERPRETER_STATEMENTS_HPP
