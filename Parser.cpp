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

    //KOOSHESH:
    // <statement> -> <assignStatement> <statement>
    // <statement> -> Epsilon

    //CODY APRIL 27th 2023: THIS CODE SHOULD NOW PARSE THE GRAMMAR RULES:
    //<statements> - <statement> {<statement>}   <--- note how braces {} denotes 0 or more statements following the first statement

    //A single statement itself can be of 3 different types, a for statement, an assignment statement, or a print statement. The grammar rules are as follows:
    //<statement> -> <for-statement> | <assignment-statement> | <print-statement>


    //Create an instance of statements
    //This will at LEAST hold one statement, if not more as we parse and identify what we have
    Statements *stmts = new Statements();
    //Get a token
    Token tok = tokenizer.getToken();
    //if our token is a name (a variable/identifier), or a keyword (which would be "for" or "print"), or an End Of Line marker enter the while loop
    while (tok.isName() || tok.isKeyword() || tok.eol())
    {
        //un-get the token if its not an EOL token so we can use this same token later the next time we call .getToken() in our code/later in our nested function calls ex.forStatement(), assignmentStatement(), printStatement() etc.
        if (!tok.eol())
        {
            tokenizer.ungetToken();
        }
        //If we have a name of a variable we know we will have some type of simple statement (so long as the token name isn't the keyword "print")
        if (tok.isName() && !tok.isKeyword())
        {
            //Create an AssignmentStatement type pointer and point it to the returned value of the assignStatement() function call
            //Lets call it parsedAssignmentStatementWeveCaptured
            AssignmentStatement* parsedAssignmentStatementWeveCaptured = assignStatement();
            //Add this assignment-statement to our vector of statements held by the Statements class
            stmts->addStatement(parsedAssignmentStatementWeveCaptured);

            //HOW DO WE PROCESS STATEMENTS AFTER THIS ONE STATEMENTS? HANDLED IN ASSIGNSTATEMENT() FUNCTION? SEE THE WHILE LOOP
        }
        //If we have a keyword for the token, lets process the correct statement each keyword represents
        //MAY 3rd 2023 CODY: STARTING TO REALIZE THAT THE SIMPLE STATEMENT CLASS MAY BE VERY UNNESSARY AS HERE WE STILL HAVE TO BASICALLY DO THE SAME PARSING SIMPLE STATEMENT WOULD DO BUT JUST CHECKING FOR ANOTHER KEYWORD
        //MAY HAVE TO REFACTOR THIS CODE LATER ON
        if (tok.isKeyword())
        {
            //MAY 3rd 2023 CODY: NOTE HOW FOR PHASE 2 OF THIS PROJECT WE TOTALLY SKIPPED THE COMPOUND STATEMENT GRAMMAR RULE:
            //<compound-statement> -> <for-statement>
            //As it is redundant and unnecessary
            //The grammar rules provide a guide for the structure and flow of the program, but are not necessary to follow verbatim in order to complete the programs objectives.
            //notice how we don't make a class for grammar rule <file_input> or grammar rule <atom> or <comp_op>
            //there are some things there which are named to categorically relate symbols in their syntactical order but that we don't necessarily need to implement

            //If we have a "print" keyword,
            if (tok.getName() == "for")
            {
                //Lets make an instance of a print statement pointer that captures the returned result of our PrintStatement() function
                //Call it  printstatement
                ForStatement* parsedForStatementWeveCaptured = forStatement();
                //Lets add this print-statement to our vector of statements held by the Statements class
                stmts->addStatement(parsedForStatementWeveCaptured);
            }
            //If we have a "print" keyword,
            if (tok.getName() == "print")
            {
                //Lets make an instance of a print statement pointer that captures the returned result of our PrintStatement() function
                //Call it  printstatement
                PrintStatement* parsedPrintStatementWeveCaptured = printStatement();
                //Lets add this print-statement to our vector of statements held by the Statements class
                stmts->addStatement(parsedPrintStatementWeveCaptured);
            }
        }
        /*
        if(tok.isHashtag())
        {
            CommentStatement *commmentstatement = commentStatement();
            stmts->addStatement(commmentstatement);
        }
         */
        //GET ANOTHER TOKEN TO CONTINUE THE WHILE LOOP/OR BREAK OUT OF IT DEPENDING WHAT TOKEN WE GET BACK
        tok = tokenizer.getToken();
    }
    //Unget last token that broke us out of the while loop so we may use it later on in the program if needed (I believe it should be expected to be an EOF token after we've collected all of our statements)
    tokenizer.ungetToken();
    //Now that you have all the statements from the input file, return this out to main.cpp to use
    return stmts;
}

//CODY MAY 7TH 2023 COMMENTED OUT SIMPLE STATEMENT AS IT IS NOT NECESSARY
/*
SimpleStatement* Parser::simpleStatement()
{
    // Parses the following grammar rule from phase 2's grammar rules
    //
    // <simple_statement> -> (print_statement | assignment_statement) NEWLINE


    //Get a token from the tokenizer
    Token genericNameToken = tokenizer.getToken();

    //If our token is either a print_statement or an assignment_statement this if condition will run, as both return .isName() as true (remember .isKeyword() is for a specific case for the _name private member variable of a token so checking for that will be another if condition after this first if condition)
    if (genericNameToken.isName())
    {
        //We know we at least have a name token if the above if condition passed and we are now inside the if block

        //Now lets check if the name token we got is a keyword
        if (genericNameToken.isKeyword())
        {
            //Now that we've entered this if block we know we have a name token that is at least a keyword. Let's double check that it is indeed matching the "print" keyword
            if (genericNameToken.getName() == "print")
            {
                //Create a PrintStatement type pointer and set it equal to the return value that the parser function printStatement() gets for us
                PrintStatement* printStatementWeveCapturedFromOurParser = printStatement();
                //Now that we know we have a proper formatted/syntactically correct PrintStatement we now need to check if the next token is indeed an EOL token, which will is by grammar rule what terminates a <simple_statement>
                Token expectedEndOfLineToken = tokenizer.getToken();

                //Lets check if that token is indeed an end of line token. If it isn't, kill the program
                if (expectedEndOfLineToken.eol() == false)
                    die("Parser::simpleStatment()", "Expected an end of line token, instead got", expectedEndOfLineToken);

                //Since we got past the if condition above checking for an end of line token, we can now return a properly formatted <simple_statement>
                return new SimpleStatement(printStatementWeveCapturedFromOurParser);

            }
        }
        else //We know we have an assignment statement since the if condition of genericNameToken.isName() has passed as true in the appropriate if block, but we did not enter the isKeyword() if condition block, thus we have an assignment statement we need to take care of
        {
            //Create an AssignmentStatement type pointer and set it equal to the return value that the parser function assignStatement() gets for us
            AssignmentStatement* assignmentStatementWeveCapturedFromOurParser = assignStatement();
            //Now that we know we have a proper formatted/syntactically correct AssignmentStatement we now need to check if the next token is indeed an EOL token, which will is by grammar rule what terminates a <simple_statement>
            Token expectedEndOfLineToken = tokenizer.getToken();
            //Lets check if that token is indeed an end of line token. If it isn't, kill the program
            if (expectedEndOfLineToken.eol() == false)
                die("Parser::simpleStatment()", "Expected an end of line token, instead got", expectedEndOfLineToken);

            //Since we got past the if condition above checking for an end of line token, we can now return a properly formatted <simple_statement>
            return new SimpleStatement(assignmentStatementWeveCapturedFromOurParser);


        }
    }

}
 */

AssignmentStatement* Parser::assignStatement()
{
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
    ExprNode* rightHandSideRelationalExpression = relationalExpression();


    /* STEP 1 HERE. We no longer need to process semi-colons (as we are parsing python code) so we have commented this section of code out
    Token tok = tokenizer.getToken();

    if (!tok.isSemiColon())
        die("Parser::assignStatement", "Expected a semicolon, instead got", tok);
    */
    //Return a new AssignmentStatement, but first give this new AssignmentStatement the appropriate parameters using it's parameterized constructor
    //Note how in the Statements.hpp/.cpp files we this assignment statement an evaluation function. This is what we will be using when we eventually return all of our statements back to the main.cpp via our parser::statements() function. See how it recursively goes back up the stack?
    return new AssignmentStatement(varName.getName(), rightHandSideRelationalExpression);
}

//CODY APRIL 29th 2023: STEP 7 HERE.
//Adding a function to the parser that will handle seeing a for-statement
//Also added functionality to the Statements class/.cpp/.hpp file to make a sub-class of statement called ForStatement
ForStatement* Parser::forStatement()
{
    // Parses the following grammar rule
    //
    // <for-statement> -> "for" "(" <assignment-statement> ";" <relational-expression ";" <assignment-statement> ")" {<statements>}
    //NOTE: remember {<statements>} denotes zero or more statements can be expected

    //Our first expected token in a for-statement according to our grammar is a "for" keyword.
    Token forKeyword = tokenizer.getToken();

    //Lets check if that's what we get, if not, lets kill the program
    if (!forKeyword.isKeyword() && !(forKeyword.getName() == "for"))
        die("Parser::forStatement", "Expected an open parentheses \"(\" , instead got", forKeyword);

    //Our second expected token in a for-statement according to our grammar is an opening parentheses
    Token leftParentheses = tokenizer.getToken();
    //Lets check if we indeed got the expected token, a opening parentheses
    if (!leftParentheses.isOpenParen())
        die("Parser::forStatement", "Expected an open parentheses \"(\" , instead got", leftParentheses);

    //Next we would expect an assignment statement in our for statement conditional (think: for (i=0; i<array.length; i++))
    //This would take care of the i=0 for our example for statement above
    AssignmentStatement* firstAssignmentStatement = assignStatement();

    //After our first assignment statement should come our first semi-colon. Lets pick up that token and analyze it
    Token firstSemiColon = tokenizer.getToken();
    //If our token we picked up isn't a semi colon we do not have a properly syntaxed for statement
    if (!firstSemiColon.isSemiColon())
        die("Parser::forStatement", "Expected a semi-colon \";\" , instead got", firstSemiColon);

    //After our first semi-colon should be a relational expression, so lets assign something that will drill down and figure out what that expression is
    //JOE IS THIS AN INFIX EXPRESSION? THIS SHOULD BE ASSIGNED TO RELATIONAL EXPRESSION CORRECT?
    ExprNode* ourRelationalExpression = relationalExpression();

    //After our relational expression should come another semi-colon to terminate it. Lets pick up another token and analyze it
    Token secondSemiColon = tokenizer.getToken();

    //If we do not capture a semi-colon at this point we have an ill-formatted for-statement and we should kill the program
    if (!secondSemiColon.isSemiColon())
        die("Parser::forStatement", "Expected a semi-colon \";\" , instead got", secondSemiColon);

    //After the second semi-colon we expect another assignment statement
    //Lets create an instance of an assignmentStatement pointer to capture what the assignmentStatement() function figures out
    AssignmentStatement* secondAssignmentStatement = assignStatement();

    //After the last assignment statement in our for loop's conditional, we expect a closing parentheses to close out the conditional
    //Lets grab a token and analyze it
    Token rightParentheses = tokenizer.getToken();
    //Lets check if we indeed got the expected token, a closing parentheses
    if (!rightParentheses.isCloseParen())
        die("Parser::forStatement", "Expected a closing parentheses \")\" , instead got", rightParentheses);

    Token openingCurlyBrace = tokenizer.getToken();

    if (!openingCurlyBrace.isOpeningCurlyBrace())
        die("Parser::forStatement", "Expected a closing parentheses \"{\" , instead got", rightParentheses);

    //Next we will need to deal with the for statement's loop body. Here we can assign a Statements pointer to capture the return value of what the statements() function processes
    Statements* forLoopBody = statements();

    Token closingCurlyBrace = tokenizer.getToken();

    if (!closingCurlyBrace.isClosingCurlyBrace())
        die("Parser::forStatement", "Expected a closing parentheses \"}\" , instead got", rightParentheses);

    return new ForStatement(firstAssignmentStatement, ourRelationalExpression, secondAssignmentStatement, forLoopBody);
}


//CODY MAY 7th 2023: PHASE 2 STEP 5 HERE. Modifying parser to handle the new grammar rule
// print_statement -> ’print’ ’(’ [ testlist ] ’)’   (Note here how 'print', '(', and ')' are string and character literals)
// testlist -> test {’,’ test}*   (note that ',' is a character literal for a comma, and that commas in python produce blank character output

//CODY APRIL 29th 2023: STEP 6 HERE
//Added a function to the parser that will handle seeing a for-statement
//Also added functionality to the Statements class/.cpp/.hpp file to make a sub-class of statement called PrintStatement
PrintStatement* Parser::printStatement()
{
    //Cody May 7th 2023: Updated grammar rule is as follows:
    //print_statement -> ’print’ ’(’ [ testlist ] ’)’
    //This function will help us parse that expected syntax flow

    // Parses the following grammar rule
    //
    // <print-statement> -> print <ID>

    //Note how in our sample input for phase 1 all of our print statements are only printing out variables and their values
    //These values are integers from the symbol table

    //Our first token we get should be a print keyword, lets grab a token and analyze it
    Token ourPrintKeyword = tokenizer.getToken();

    //If the token we got and expected to be our print keyword is not, we need to kill the program and throw an error message to our user
    if (!ourPrintKeyword.isKeyword() && !(ourPrintKeyword.getName() == "print"))
        die("Parser::printStatement()", "Expected a \"print\" keyword here , instead got", ourPrintKeyword);

    //CODY PHASE 2 MAY 7th 2023: Due to our updated grammar rules, after our print keyword we should now expect an open parenthesis right after. Lets get the next token.
    Token ourExpectedOpeningParenthesis = tokenizer.getToken();
    //CODY PHASE 2 MAY 7th 2023: After we get our next token, we should check to see if we did indeed get an opening parenthesis
    if (!ourExpectedOpeningParenthesis.isOpenParen())
        die("Parser::printStatement()", "Expected a \"(\" here , instead got", ourExpectedOpeningParenthesis);


    //Next we want to declare an expression node that will drill down and identify the term we want to print after the print keyword we've received
    //We will want to start from the top even though in phase 1 we could assume it will be what the primary() function would solve for us, however this could give us some issues:
    //It is better coding practice to let the program be as generic as possible (and thus will be more flexible for other use cases) and let the code solve the problem/do the work for us. Eventually it will drill down to primary and resolve the variable names and corresponding values when it reaches primary() down the call stack
    //In conversation with Joe, there was a good explanation in that, "if you used primary() to drill down, you would be assuming that the user is exclusively passing you a literal number or a variable with no modification. This fails to account for other valid print expressions involving any operator, such as a + 1, 2 < 3, or a + b + c. You don't need to think to much about what you choose to drill down with in the parser: the answer is always to start from the top of your "drilling" methods." My response was, "So better to start from the top and be safer rather than sorry. I think I get it. It doesn't hurt to drill down rather thank skipping steps/checks which come with starting at the top". And he responded, " Otherwise you open yourself to missing text which is valid. Its necessary to check every condition to perform the fundamental function of the program"
    ExprNode* variableWhosValueIsContainedInSymbolTableWeWillWantToPrint = relationalExpression();

    //We will need a vector of relational expressions to send back to our parsed PrintStatement we will returning after this parser function is done running
    std::vector<ExprNode*> ourVectorToHoldRelationalExpressions;

    //Our first relational expression that comes back needs to be captured/put back in our vector of relational expressions
    ourVectorToHoldRelationalExpressions.push_back(variableWhosValueIsContainedInSymbolTableWeWillWantToPrint);

    //CODY PHASE 2 MAY 7th 2023: After we have parsed all possible expressions within our print statement (i.e. variable names that need to be evaluated and printed, string literals, and commas that need to output blank space), the last token we should expect in a print statement is a closing parenthesis
    Token ourExpectedClosingParenthesis = tokenizer.getToken();


    //Cody May 8th 2023: I am going to try and build a "test list" class (as we would probably expect with our new grammar rules)
    //Basically our print statement contains at least one relational expression, with zero or more able to come after that when following a comma
    //The grammar rule for a test-list is as follows:
    // testlist -> test {’,’ test}*
    //With that being in mind, a parsed PrintStatement should contain a testlist that we will pass back to the constructor after we've finished parsing
    //A test list class should contain everything necessary that a test list should contain by grammar rule, that being at least one relational expression, if not more, if it encounters a comma after the relational expression
    //Since we need to check if there is a comma, not only will test list be a class containing a vector of relational expressions, but it will need a parsing function out here in parser as well
    //Thus the PrintStatement class will now contain a test list
    //testlist will be a class that contains one or more relational expressions in a vector it contains.
    //It should have the capability of printing that vector and evaluating it
    //Test list will also be a parser function that needs to make sure relational expressions are following the correct syntax after a comma is seen

    //Probably not how we want to handle print statements (as we keep overwriting the same variable)
    while (ourExpectedClosingParenthesis.isComma())
    {
        //Get another relational expression
        ExprNode* nextRelationalExpressionToCapture = relationalExpression();
        //Pus back that relational expression into our vector
        ourVectorToHoldRelationalExpressions.push_back(nextRelationalExpressionToCapture)
        //Get the next token. If it is a closing parenthesis we break out of this while loop. If it is a comma we keep looping and adding relational expressions to our vector.
        ourExpectedClosingParenthesis = tokenizer.getToken();
    }
    //CODY PHASE 2 MAY 7th 2023: After we get this expected closing parenthesis token, we should analyze it to make sure it is indeed a closing parenthesis
    if (!ourExpectedClosingParenthesis.isCloseParen())
        die("Parser::printStatement()", "Expected a \")\" here , instead got", ourExpectedClosingParenthesis);

    //Return a new printStatement instance who has all the correct parts since we have gotten through all of our parsing for a printStatement
    //Cody May 8th 2023, now our print statement will not only be taking in one relational expression, but multiple, so we will hand back our vector we just made to our parsed PrintStatement's constructor
    return new PrintStatement(ourVectorToHoldRelationalExpressions);

}

/*
CommentStatement *Parser::commentStatement() {
    //Get the next token
    Token hashtag = tokenizer.getToken();
    // The token we get should be a '#' token
    if (!hashtag.isHashtag()){
        die("Parser::commentStatement", "Expect a # token , instead got ", hashtag );
    }
    // Process the comment and save it
    std::vector<ExprNode*> comment = {};
    std::vector<std::string> comment1 = {};

    // Keep getting tokens until we reach the end of line or end of file
    Token tok;
    do {
        tok = tokenizer.getToken();
        if (tok.eol()) {
            break;
        }
        comment1.push_back(tok.getName());
    } while (true);


    // Construct and return the CommentStatement object
    return new CommentStatement(comment1);
}
 */

//STEP 4 HERE BY CODY APRIL 26th 2023: Adding a parser function that will take care of the grammar rule:
//<rel-expr> -> <rel-term> {(==, !=) <rel-term>} in english that is: <relational-expression> -> <relational-term> {(==, !=) <relational-term>}
//Cody May 3rd 2023: STEP 2 PHASE 2 HERE: Bringing everything up we had in "relationalTerm()" parser function in regards to relational operators up to this function
ExprNode* Parser::relationalExpression()
{
    //Our first token expected for this grammar rule is a relational term, thus
    //I guess you can kind of think of this as a place holder, but in reality it is not
    //This variable holds the return value of a function that drills down and will eventually return the atomic values the grammar rules will eventually parse

    //Cody May 3rd 2023: Commented out below code and replaced with: ExprNode *leftSideOfRelationalExpressionIsOurFirstRelationalTerm = expr();
    //ExprNode *leftSideOfRelationalExpressionIsOurFirstRelationalTerm = relationalTerm();
    ExprNode *leftSideOfRelationalExpressionIsOurFirstRelationalTerm = expr();

    //Our second token which is expected for this grammar rule should be an equal to "==" or not equal to "!=" operator, thus
    //UPDATE CODY MAY 3rd 2023: Our token we grab which is expected for this grammar rule should be an equal to’<’|’>’|’==’|’>=’|’<=’|’<>’|’!=’ NOTE TO SELF I STILL NEED TO ADD <> TO TOKENIZER AND TOKEN
    Token relationalOperator = tokenizer.getToken();

    //If the token we get back from the .getToken() function is not an equal to "==" or not equal to "!=" relational operator, as we would expect in our grammar, kill the program and throw and error message back to our user
    //if (!relationalOperator.isEqualOperator() | !relationalOperator.isNotEqualOperator())
        //die("Parser::relationalExpression", "Expected an assignment operator \"==\" or a not equal to operator \"!=\" , instead got", relationalOperator);

    //While our relational operator is indeed an equal or not equal to operator
    while (relationalOperator.isEqualOperator() || relationalOperator.isNotEqualOperator() || relationalOperator.isLessThanOperator() || relationalOperator.isLessThanOrEqualToOperator() || relationalOperator.isGreaterThanOperator() || relationalOperator.isGreaterThanOrEqualToOperator())
    {
        //We know that by grammar rules we should expect a relational term after them, and in this program
        //we handle those terms via our InfixExprNode sub-class described in ExprNode.cpp
        //Lets make an InfixExprNode that will parse the left and right values of an infix expression i.e. 2+3 (2 being left, 3 being right)
        //LOOK UP LEFT DERIVATION SYNTENTIAL FORM TO VISUALIZE THIS TREE THAT GETS CREATED
        InfixExprNode* p = new InfixExprNode(relationalOperator);
        p->left() = leftSideOfRelationalExpressionIsOurFirstRelationalTerm;
        //Cody May 3rd 2023: Commented out below code and replaced with: p->right() = expr();
        //p->right() = relationalTerm();
        p->right() = expr();
        leftSideOfRelationalExpressionIsOurFirstRelationalTerm = p;
        //Get the next token. If it is indeed an equal operator or a not equal to operator, we continue to get relational expressions using this while loop
        relationalOperator = tokenizer.getToken();
    }
    //If the next token is not a an equal to a ’<’|’>’|’==’|’>=’|’<=’|’<>’|’!=’ operator, we break out of the while loop. There are no more relational expressions to read at this point

    //Set flag for ungetToken to tell .getToken() function that will use last gotten token we previously picked up (i.e. getToken() will return the last gotten token which is stored as a private variable in the tokenizer class)
    tokenizer.ungetToken();
    
    return leftSideOfRelationalExpressionIsOurFirstRelationalTerm;
}
//STEP 2 PHASE 2 UPDATE BY CODY MAY 3rd 2023: COMMENTING OUT relationalTerm() FUNCTION AS IT'S FUNCTIONALITY HAS NOW BEEN INCORPORATED INTO THE relationalExpression() PARSER FUNCTION. THIS FUNCTION IS NO LONGER NECESSARY
//STEP 4 HERE BY CODY APRIL 26th 2023:  Adding a parser function that will take care of the grammar rule:
//<rel-term> -> <rel-primary> {(>, >=, <, <=) <rel-primary>} in english that is: <relational-term> -> <relational-primary> {(>, >=, <, <=) <relational-primary>}
/*
ExprNode* Parser::relationalTerm()
{
    //CODY APRIL 26th 2023: USE C++ EXPR() FUNCTION TO REPRESENT <REL-PRIMARY> GRAMMAR RULE FOR NOW
    //THIS MAY NEED TO BE FIXED LATER ON FOR A LATER PHASE OF THE PROJECT


    //Our first token expected for this grammar rule is a relational term, thus
    //I guess you can kind of think of this as a place holder, but in reality it is not
    //This variable holds the return value of a function that drills down and will eventually return the atomic values the grammar rules will eventually parse
    ExprNode* leftSideOfRelationalTermIsOurFirstRelationalPrimary = expr();

    //Our second token which is expected for this grammar rule should be a ">", ">=", "<", or "<=" operator, thus
    Token relationalOperator = tokenizer.getToken();

    //If the token we get back from the .getToken() function is not a ">", ">=", "<", or "<=" operator, as we would expect in our grammar, kill the program and throw and error message back to our user
    //if (!relationalOperator.isLessThanOperator() | !relationalOperator.isLessThanOrEqualToOperator() | !relationalOperator.isGreaterThanOperator() | !relationalOperator.isGreaterThanOrEqualToOperator())
        //die("Parser::relationalTerm", "Expected a less than operator \"<\" or a less than or equal to operator \"<=\", or a greater than or equal to operator \">=\", or a greater than operator \">\" instead got", relationalOperator);

    //While our relational operator is indeed a">", ">=", "<", or "<=" operator
    while (relationalOperator.isLessThanOperator() || relationalOperator.isLessThanOrEqualToOperator() || relationalOperator.isGreaterThanOperator() || relationalOperator.isLessThanOrEqualToOperator())
    {
        //We know that by grammar rules we should expect a relational primary after them, and in this program
        //we handle those primary's via our InfixExprNode sub-class described in ExprNode.cpp
        //Lets make an InfixExprNode that will parse the left and right values of an infix expression i.e. 2+3 (2 being left, 3 being right)
        //LOOK UP LEFT DERIVATION SYNTENTIAL FORM TO VISUALIZE THIS TREE THAT GETS CREATED
        InfixExprNode* p = new InfixExprNode(relationalOperator);
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
*/

ExprNode* Parser::expr() {
    // This function parses the grammar rules:

    // <expr> -> <term> { <add_op> <term> }
    // <add_op> -> + | -

    // However, it makes the <add_op> left associative.
    //ADD ADDITIONAL RELATIONAL OPERATORS HERE???
    ExprNode* left = term();
    Token tok = tokenizer.getToken();
    while (tok.isAdditionOperator() || tok.isSubtractionOperator() || tok.isEqualOperator() || tok.isNotEqualOperator()){
        InfixExprNode* p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = term();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}


ExprNode* Parser::term() {
    // This function parses the grammar rules:

    // <term> -> <primary> { <mult_op> <primary> }
    // <mult_op> -> * | / | %

    // However, the implementation makes the <mult-op> left associate.
    ExprNode* left = primary();
    Token tok = tokenizer.getToken();

    //Cody May 7th 2023: Added integer division functionality to this section of code
    while (tok.isMultiplicationOperator() || tok.isDivisionOperator() || tok.isModuloOperator() || tok.isLessThanOrEqualToOperator() || tok.isLessThanOperator() || tok.isGreaterThanOrEqualToOperator() || tok.isGreaterThanOperator() || tok.isPythonIntegerDivisionSymbol()) {
        InfixExprNode* p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = primary();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode* Parser::primary() {
    // This function parses the grammar rules:

    // <primary> -> [0-9]+
    // <primary> -> [_a-zA-Z]+
    // <primary> -> (<expr>)

    Token tok = tokenizer.getToken();

    if (tok.isWholeNumber() )
        //Cody May 4th 2023: Phase 2 Step 3 these ExprNode classes now will return TypeDescriptors instead of integers
        return new WholeNumber(tok);
    else if( tok.isName() )
        //Cody May 4th 2023: Phase 2 Step 3 these ExprNode classes now will return TypeDescriptors instead of integers
        return new Variable(tok);
    else if (tok.isString())
        //Cody May 7th 2023: Phase 2 Step 4 Adding another ExprNode class to handle string literals here (see ExprNode.cpp)
        return new String(tok);
    else if (tok.isItADouble())
        //Cody May 8th 2023: Phase 2, Adding another ExprNode class to handle doubles (see ExprNode.cpp)
        return new DoubleNumber(tok);
    else if (tok.isOpenParen()) {
        ExprNode* p = relationalExpression();
        Token token = tokenizer.getToken();
        if (!token.isCloseParen())
            die("Parser::primary", "Expected close-parenthesis, instead got", token);
        return p;
    }
    die("Parser::primary", "Unexpected token", tok);

    return nullptr;  // Will not reach this statement!
}

//Cody: Looks like Adam added this functionality
//This code is no longer needed. Commented out - Cody May 2nd 2023
/*
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
*/