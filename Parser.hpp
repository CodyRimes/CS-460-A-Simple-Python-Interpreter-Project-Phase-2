//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_PARSER_HPP
#define APYTHONINTERPRETER_PARSER_HPP

#include "Token.hpp"
#include "Tokenizer.hpp"
#include "SymTab.hpp"
#include "ExprNode.hpp"
#include "Statements.hpp"

#include<vector>
#include<iostream>
#include<map>


class Parser {
public:
    Parser(Tokenizer &tokenizer) : tokenizer{tokenizer} {};

    //STEP 1 Phase 2 HERE May 2nd 2023: Adding some functionality to statements to handle the new grammar rules for phase 2. Looks like statements from phase 1 would be pretty close to what file_input is handling.
    //STEP 1 Phase 2 HERE May 2nd 2023: If we look closely at the grammar rules for <simple_statement> and <compound_statement> we can see that:
    //<simple_statement> -> (<print_statement> | <assignment_statement) NEWLINE
    //i.e. simple_statement is basically just an overlay for print_statement or assignment_statement that is terminated by a NEWLINE character. We already have parsing functions for this, so implementing simple_statement will be pretty simple as all we will need to do is process a print_statement or assignment_statement and make sure an NEWLINE comes after one of the two.
    //if we look at
    //<compound_statement> -> for_statement
    //We can see that essentially nothing is different happens from going from a <compound_statement> to a for_statement, and thus that grammar rule is redudent, so we will not be building out any functions to process a compound_statement and will instead go straight to for_statement.
    //Much of this functionality can go inside our statements() function
    Statements* statements();

    //STEP 1 Phase 2 HERE May 2nd 2023: Meanwhile we can build out a simple_statement function that will basically determine if we've seen an assignment statement or print_statement and makes sure an NEWLINE character comes after one of the two
    SimpleStatement* simpleStatement();

    AssignmentStatement* assignStatement();

    ForStatement* forStatement();

    PrintStatement* printStatement();

    //STEP 1 Phase 2 HERE May 2nd 2023:


    ExprNode* expr();
    ExprNode* term();
    ExprNode* primary();
    //Cody May 2nd 2023: Deleted Adam's code for relationalExpr()
    //STEP 4 phase 1 HERE APRIL 26th 2023: Cody added code for relational expressions and relational terms in accordance with the grammar rules
    ExprNode* relationalExpression();
    ExprNode* relationalTerm();

    std::string id();

private:
    Tokenizer &tokenizer;

    void die(std::string where, std::string message, Token &token);

};


#endif //APYTHONINTERPRETER_PARSER_HPP
