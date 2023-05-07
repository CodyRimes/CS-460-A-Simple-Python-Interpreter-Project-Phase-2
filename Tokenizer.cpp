//
// Created by Ali Kooshesh on 4/4/23.
//

#include <iostream>
#include <string>
#include "Tokenizer.hpp"

std::string Tokenizer::readName() {
    // This function is called when it is known that
    // the first character in input is an alphabetic character.
    // The function reads and returns all characters of the name.

    std::string name;
    char c;
    while( inStream.get(c) && isalnum(c) ) {
        name += c;
    }
    if(inStream.good())  // In the loop, we have read one char too many. QUESTION FOR KOOSHESH: HOW????
        inStream.putback(c);
    return name;
}

int Tokenizer::readInteger() {
    // This function is called when it is known that
    // the first character in input is a digit.
    // The function reads and returns all remaining digits.

    int intValue = 0;
    char c;
    while( inStream.get(c) && isdigit(c) ) {
        intValue = intValue * 10 + c - '0';
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return intValue;
}

//Cody: Constructor?
Tokenizer::Tokenizer(std::ifstream &stream): ungottenToken{false}, inStream{stream}, lastToken{} {}

Token Tokenizer::getToken() {

    //If ungottenToken's value is set to true, the if block runs
    if(ungottenToken) {
        //Set the ungottenToken member value back to false
        ungottenToken = false;
        //return the lastToken stored
        return lastToken;
    }

    char c;
    /*
    while( inStream.get(c) && isspace(c) && c != '\n' )  // Skip spaces but not new-line chars.
        ;
    */

    while( inStream.get(c) && isspace(c) && c!='\n')  // Skip spaces including the new-line chars.
        ;

    if(inStream.bad()) {
        std::cout << "Error while reading the input stream in Tokenizer.\n";
        exit(1);
    }

    //    std::cout << "c = " << c << std::endl;

    Token token;
    if( inStream.eof()) {
        token.eof() = true;
    } else if( c == '\n' ) {  // will not ever be the case unless new-line characters are not supressed in line 58 (isspace() would have taken in new line characters as well).
        token.eol() = true;
    } else if( isdigit(c) ) { // a integer?
        // put the digit back into the input stream so
        // we read the entire number in a function
        inStream.putback(c);
        token.setWholeNumber( readInteger() );

    }
    //STEP 2 HERE: Adding the additional code to handle a 2nd equal sign
    else if( c == '=' )
    {
        //Add the first '=' equal sign we've found as a symbol in our token's private member variable
        token.symbol(c);

        //if the 2nd character we get is another equal sign, we know we have a 2 character relational operator known as equal to i.e. "=="
        //We will need to build out a string for this
        //Lets make a temporary string
        std::string temp;
        //Adding whatever we've found in c that got us in the first if block to our string, i.e. our first '='
        temp = temp+c;

        //Overwrite that first character we got with the character that is after the character that got us in this if block i.e. the '=' character
        inStream.get(c);

        if (c == '=')
        {
            //Add that 2nd '=' to our string to build out our "==" string
            temp = temp+c;
            //Set the token's private attribute correctly
            token.setStringForRelationalOperator(temp);
            //Since we know we have a relational operator string that comprises of the two characters, we know that we will need to undo the token.symbol() operation we did earlier in this code.
            //Lets make that private attribute symbol back to what it contained before when we first initialized this token
            token.symbol('\0');
        }
        //Otherwise if the 2nd character we get after our first '=' isn't another '=' then we need to put this 2nd character back into the input stream
        //It does not follow the convention/syntax for an equal to relational operator "=="
        else
        {
            //Put our 2nd character back into the input stream
            inStream.putback(c);
        }
    }


    else if( c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
        token.symbol(c);
    //Phase 2 part 6 here, May 6th 2023 added some more characters we read in the input stream that need to be picked up as tokens. Adding token functions inside the Token.cpp file to identify these as well.
    else if( c == ';' || c == '.' || c == ',')
        token.symbol(c);
    else if( c == '(' || c == ')' || c == '{' || c == '}')
        token.symbol(c);
        //Phase 2 part 6 here, May 6th 2023 we are handling python # comments but since comments have no impact on the code we want to tokenize we will just need to let our tokenizer handle them, process them, and throw them away
        //i.e. python comments are not a part of our python program and do not need to be tokenized and parsed
    else if( c == '#')
    {
        //If we see a hashtag we know we will need to process a python comment
        //To do that we basically will need to keep reading in character inputs until we have reached an end of line character which means we've reached the end of the python comment
        while ( c != '\n')
        {
            inStream.get(c);
        }
        //Once we reach the end of the line character we need to mark that down in our token
        token.eol() = true;

    }
    //PHASE 2 STEP 4, MAKING IT SO OUR TOKENIZER CAN PARSE STRING LITERALS
    else if (c == '"')
    {
        //if we encounter a quotation mark we know everything after that first quotation mark and before the 2nd quotation mark is up for grabs in our string we need to tokenize/make a string token
        //Lets make a temporary string we can add to/build out character by character
        std::string myTemporaryStringToBuildOutOn;

        //Get the next token to make sure we have a string after it and not an empty string (which would be an immediate 2nd quotation mark after the first)
        inStream.get(c);

        //While our token isn't the 2nd quotation mark we should be building out our string. We do not want to capture the first quotation mark when we initially enter this while loop either so  overwriting the first character we get (that first quotationmark) is ok in this instance
        while (c != '"')
        {
            //Add the character we got to the string we are trying to build out
            myTemporaryStringToBuildOutOn = myTemporaryStringToBuildOutOn + c;
            //Get the next token from the input stream
            inStream.get(c);
        }
        //If we've encountered the 2nd quotation mark we break out of the while loop above and need to put the string we've captured into a token
        token.setStringFromGenericStringHolder(myTemporaryStringToBuildOutOn);
        //then we will mark this token as having a token inside of it
        token.isStringSetter(true);

    }
    //STEP 2 HERE CONTINUED:
    //Cody: If this indeed where we would handle the relational expressions character by character ( ex. ==, !=, >, >=, <, <= ) we will pick up  "<" and "=" character by character and put them back.
    //Only "!" needs to be added here from what I can see
    //Joe: Will need to change this logic to a string build out method
    else if (c == '<' || c == '>' || c == '!')
    {
        //if we have seen one of these symbols we know we MAY have the case of relational operators: "<=", ">=", or "!=" which will require a string
        //We know for sure if c is equal to '<' or '>' or '!' that we at least of a less than or greater than sign or a not operator.
        //Lets capture those as a symbol for now (in case our if condition that will grab the 2nd character after this one fails for finding an equal sign '='
        token.symbol(c);

        //Now lets build out a temporary string in case we do have the case of an equal sign following the symbols '<', '>', '!', which would be a less than or equal to, greater than or equal to, or a not equal to relational operator
        std::string temp;
        //Adding whatever we've found in c that got us in the first if block to our string
        temp = temp+c;

        //

        //Overwrite that first character we put into the string and get the character that follows what got us in this if block
        inStream.get(c);

        //Check if this 2nd character follows a valid relational operator form (only "=" can come after a valid relational operator for the cases of "<=", ">=", or "!=")
        if (c == '=')
        {
            //Add that 2nd character to our string
            temp = temp + c;
            //Set the token's private attribute correctly
            token.setStringForRelationalOperator(temp);
            //Since we know we have a relational operator string that comprises of the two characters, we know that we will need to undo the token.symbol() operation we did earlier in this code.
            //Lets make that private attribute symbol back to what it contained before when we first initialized this token
            token.symbol('\0');
        }
        //Otherwise we do not have a syntatically correct 2 character relational operator and must this character back into the input stream
        else
        {
            inStream.putback(c);
        }

    }
    else if(isalpha(c)) {  // an identifier?
        // put c back into the stream so we can read the entire name in a function.
        inStream.putback(c);
        token.setName( readName() );
    } else {
        std::cout << "Unknown character in input. ->" << c << "<-" << std::endl;
        exit(1);
    }
    _tokens.push_back(token);
    return lastToken = token;
}

void Tokenizer::ungetToken() {
    ungottenToken = true;
}

void Tokenizer::printProcessedTokens() {
    for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
        iter->print();
        std::cout << std::endl;
    }
}
