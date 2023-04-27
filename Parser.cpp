//
// Created by Ali Kooshesh on 4/4/23.
//


#include<vector>
#include<iostream>
#include "Token.hpp"
#include "Parser.hpp"
#include "Statements.hpp"

// Parser functions

void Parser::die(std::string where, std::string message, Token &token) {
    std::cout << where << " " << message << std::endl;
    token.print();
    std::cout << std::endl;
    std::cout << "\nThe following is a list of tokens that have been identified up to this point.\n";
    tokenizer.printProcessedTokens();
    exit(1);
}

Statements *Parser::statements() {
    // This function is called when we KNOW that we are about to parse
    // a series of assignment statements.

    // This function parses the grammar rules:

    // <statement> -> <assignStatement> <statement>
    // <statement> -> Epsilon


    Statements *stmts = new Statements();
    Token tok = tokenizer.getToken();
    while (tok.isName() || tok.isKeyword() || tok.eol()) {
        tokenizer.ungetToken();
        if (tok.isName())
        {
            AssignmentStatement *assignStmt = assignStatement();
            stmts->addStatement(assignStmt);
        }
        if (tok.isKeyword())
        {
            if (tok.getName() == "for")
            {
                ForStatement *forstatement = ForStatement();
                stmts->addStatement(forstatement);
            }
            if (tok.getName() == "print")
            {
                PrintStatement *printstatement = PrintStatement();
                stmts->addStatement(printstatement);
            }
        }
        if (tok.eol())
        {

        }

        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return stmts;
}

AssignmentStatement *Parser::assignStatement() {
    // Parses the following grammar rule
    //
    // <assign-stmtement> -> <id> = <expr>

    // STEP 4 HERE BY CODY APRIL 26th 2023:
    // The grammar we now need to implement should follow the grammar rule:
    // <assign-statement> -> <id> "=" <relational-expression> NOTE: "=" denotes a literal equal sign expected

    //Lets get our variable name if we expect a string in the form of an assignment statement.
    //Thus our very first token in an assignment should be an <id> which should be the variable name
    Token varName = tokenizer.getToken();
    //If the token we get back is not a variable name we need to kill the program and display an error message
    //We can do this with our die() function
    if (!varName.isName())
        die("Parser::assignStatement", "Expected a name token, instead got", varName);

    //The next token we would expect after our <id> token would be the assignment/equal sign operator we expect, see grammar here: <id> "=" <relational-expression>
    Token assignOp = tokenizer.getToken();
    //If we do not  have an assignment operator we should kill the program and tell our user why the program has failed
    if (!assignOp.isAssignmentOperator())
        die("Parser::assignStatement", "Expected an equal sign, instead got", assignOp);

    // STEP 4 HERE BY CODY APRIL 26th 2023: Commenting out this code as assignment statemnet should lead to:
    // <assign-statement> -> <id> "=" <relational-expression> NOTE: "=" denotes a literal equal sign expected
    //ExprNode *rightHandSideExpr = expr();
    //The above code should now be replace with:
    ExprNode *rightHandSideRelationalExpression = relationalExpression();


    /* STEP 1 HERE. We no longer need to process semi-colons (as we are parsing python code) so we have commented this section of code out
    Token tok = tokenizer.getToken();

    if (!tok.isSemiColon())
        die("Parser::assignStatement", "Expected a semicolon, instead got", tok);
    */
    return new AssignmentStatement(varName.getName(), rightHandSideRelationalExpression);
}

//STEP 4 HERE BY CODY APRIL 26th 2023: Adding a parser function that will take care of the grammar rule:
//<rel-expr> -> <rel-term> {(==, !=) <rel-term>} in english that is: <relational-expression> -> <relational-term> {(==, !=) <relational-term>}
ExprNode *Parser::relationalExpression()
{
    //Our first token expected for this grammar rule is a relational term, thus
    //I guess you can kind of think of this as a place holder, but in reality it is not
    //This variable holds the return value of a function that drills down and will eventually return the atomic values the grammar rules will eventually parse
    ExprNode *leftSideOfRelationalExpressionIsOurFirstRelationalTerm = relationalTerm();

    //Our second token which is expected for this grammar rule should be an equal to "==" or not equal to "!=" operator, thus
    Token relationalOperator = tokenizer.getToken();

    //If the token we get back from the .getToken() function is not an equal to "==" or not equal to "!=" relational operator, as we would expect in our grammar, kill the program and throw and error message back to our user
    if (!relationalOperator.isEqualOperator() | !relationalOperator.isNotEqualOperator())
        die("Parser::relationalExpression", "Expected an assignment operator \"==\" or a not equal to operator \"!=\" , instead got", relationalOperator);

    //While our relational operator is indeed an equal or not equal to operator
    while (relationalOperator.isEqualOperator() || relationalOperator.isNotEqualOperator())
    {
        //We know that by grammar rules we should expect a relational term after them, and in this program
        //we handle those terms via our InfixExprNode sub-class described in ExprNode.cpp
        //Lets make an InfixExprNode that will parse the left and right values of an infix expression i.e. 2+3 (2 being left, 3 being right)
        //LOOK UP LEFT DERIVATION SYNTENTIAL FORM TO VISUALIZE THIS TREE THAT GETS CREATED
        InfixExprNode *p = new InfixExprNode(relationalOperator);
        p->left() = leftSideOfRelationalExpressionIsOurFirstRelationalTerm;
        p->right() = relationalTerm();
        leftSideOfRelationalExpressionIsOurFirstRelationalTerm = p;
        //Get the next token. If it is indeed an equal operator or a not equal to operator, we continue to get relational expressions using this while loop
        relationalOperator = tokenizer.getToken();
    }
    //If the next token is not a equal operator or a not equal operator, we break out of the while loop. There are no more relational expressions to read at this point

    //Set flag for ungetToken to tell .getToken() function that will use last gotten token we previously picked up (i.e. getToken() will return the last gotten token which is stored as a private variable in the tokenizer class)
    tokenizer.ungetToken();
    //
    return leftSideOfRelationalExpressionIsOurFirstRelationalTerm;
}

//STEP 4 HERE BY CODY APRIL 26th 2023:  Adding a parser function that will take care of the grammar rule:
//<rel-term> -> <rel-primary> {(>, >=, <, <=) <rel-primary>} in english that is: <relational-term> -> <relational-primary> {(>, >=, <, <=) <relational-primary>}
ExprNode *Parser::relationalTerm()
{
    //CODY APRIL 26th 2023: USE C++ EXPR() FUNCTION TO REPRESENT <REL-PRIMARY> GRAMMAR RULE FOR NOW
    //THIS MAY NEED TO BE FIXED LATER ON FOR A LATER PHASE OF THE PROJECT


    //Our first token expected for this grammar rule is a relational term, thus
    //I guess you can kind of think of this as a place holder, but in reality it is not
    //This variable holds the return value of a function that drills down and will eventually return the atomic values the grammar rules will eventually parse
    ExprNode *leftSideOfRelationalTermIsOurFirstRelationalPrimary = expr();

    //Our second token which is expected for this grammar rule should be a ">", ">=", "<", or "<=" operator, thus
    Token relationalOperator = tokenizer.getToken();

    //If the token we get back from the .getToken() function is not a ">", ">=", "<", or "<=" operator, as we would expect in our grammar, kill the program and throw and error message back to our user
    if (!relationalOperator.isLessThanOperator() | !relationalOperator.isLessThanOrEqualToOperator() | !relationalOperator.isGreaterThanOperator() | !relationalOperator.isGreaterThanOrEqualToOperator())
        die("Parser::relationalTerm", "Expected a less than operator \"<\" or a less than or equal to operator \"<=\", or a greater than or equal to operator \">=\", or a greater than operator \">\" instead got", relationalOperator);

    //While our relational operator is indeed a">", ">=", "<", or "<=" operator
    while (relationalOperator.isLessThanOperator() || relationalOperator.isLessThanOrEqualToOperator() || relationalOperator.isGreaterThanOperator() || relationalOperator.isLessThanOrEqualToOperator())
    {
        //We know that by grammar rules we should expect a relational primary after them, and in this program
        //we handle those primary's via our InfixExprNode sub-class described in ExprNode.cpp
        //Lets make an InfixExprNode that will parse the left and right values of an infix expression i.e. 2+3 (2 being left, 3 being right)
        //LOOK UP LEFT DERIVATION SYNTENTIAL FORM TO VISUALIZE THIS TREE THAT GETS CREATED
        InfixExprNode *p = new InfixExprNode(relationalOperator);
        p->left() = leftSideOfRelationalTermIsOurFirstRelationalPrimary;
        p->right() = expr();
        leftSideOfRelationalTermIsOurFirstRelationalPrimary = p;
        //Get the next token. If it is indeed an equal operator or a not equal to operator, we continue to get relational expressions using this while loop
        relationalOperator = tokenizer.getToken();
    }
    //If the next token is not a equal operator or a not equal operator, we break out of the while loop. There are no more relational expressions to read at this point

    //Set flag for ungetToken to tell .getToken() function that will use last gotten token we previously picked up (i.e. getToken() will return the last gotten token which is stored as a private variable in the tokenizer class)
    tokenizer.ungetToken();
    //
    return leftSideOfRelationalTermIsOurFirstRelationalPrimary;
}

ExprNode *Parser::expr() {
    // This function parses the grammar rules:

    // <expr> -> <term> { <add_op> <term> }
    // <add_op> -> + | -

    // However, it makes the <add_op> left associative.

    ExprNode *left = term();
    Token tok = tokenizer.getToken();
    while (tok.isAdditionOperator() || tok.isSubtractionOperator() || tok.isEqualOperator() || tok.isNotEqualOperator()){
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = term();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}


ExprNode *Parser::term() {
    // This function parses the grammar rules:

    // <term> -> <primary> { <mult_op> <primary> }
    // <mult_op> -> * | / | %

    // However, the implementation makes the <mult-op> left associate.
    ExprNode *left = primary();
    Token tok = tokenizer.getToken();

    while (tok.isMultiplicationOperator() || tok.isDivisionOperator() || tok.isModuloOperator() || tok.isLessThanOrEqualToOperator() || tok.isLessThanOperator() || tok.isGreaterThanOrEqualToOperator() || tok.isGreaterThanOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = primary();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::primary() {
    // This function parses the grammar rules:

    // <primary> -> [0-9]+
    // <primary> -> [_a-zA-Z]+
    // <primary> -> (<expr>)

    Token tok = tokenizer.getToken();

    if (tok.isWholeNumber() )
        return new WholeNumber(tok);
    else if( tok.isName() )
        return new Variable(tok);
    else if (tok.isOpenParen()) {
        ExprNode *p = expr();
        Token token = tokenizer.getToken();
        if (!token.isCloseParen())
            die("Parser::primary", "Expected close-parenthesis, instead got", token);
        return p;
    }
    die("Parser::primary", "Unexpected token", tok);

    return nullptr;  // Will not reach this statement!
}

//Cody: Looks like Adam added this functionality
ExprNode *Parser::relationalExpr() {
    // This function parses the grammar rules:
    // <relational-expr> -> <expr> <rel_op> <expr>
    // <rel_op> -> < | <= | > | >= | == | !=
    // However, it makes the <rel_op> left associative.

    ExprNode *left = expr();
    Token tok = tokenizer.getToken();
    while (tok.isLessThanOperator() || tok.isLessThanOrEqualToOperator()||
           tok.isGreaterThanOperator() || tok.isGreaterThanOrEqualToOperator() ||
           tok.isEqualOperator() || tok.isNotEqualOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = expr();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return static_cast<ExprNode *>(left);
}