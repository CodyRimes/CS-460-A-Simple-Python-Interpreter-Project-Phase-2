//
// Created by Ali Kooshesh on 4/4/23.
//

#include <iostream>
#include "Token.hpp"

Token::Token(): _name{""}, _eof{false}, _eol{false}, _symbol{'\0'}, _isWholeNumber{false}, _isStringBoolValue{false} {}

void Token::print() const {
    if( eol() ) std::cout << "EOL\n" ;
    else if( eof() )                    std::cout << "EOF" ;
    else if( isOpenParen() )  std::cout << "(" ;
    else if( isCloseParen() )  std::cout << ")" ;
    else if( isAssignmentOperator() )  std::cout << " = " ;
    else if( isSemiColon() )  std::cout << ";" ;
    else if( isMultiplicationOperator() )  std::cout << " * " ;
    else if( isAdditionOperator() )  std::cout << " + " ;
    else if( isSubtractionOperator() )  std::cout << " - " ;
    else if( isModuloOperator() )  std::cout << " % " ;
    else if( isDivisionOperator() )  std::cout << " / " ;
    else if( isName() ) std::cout << getName();
    else if( isWholeNumber() ) std::cout << getWholeNumber();
    else if( isEqualOperator() ) std:: cout << " ==";
    else if( isNotEqualOperator() ) std:: cout << "!=";
    else if( isGreaterThanOperator() ) std::cout << ">";
    else if( isGreaterThanOrEqualToOperator() ) std::cout << ">=";
    else if( isLessThanOperator() ) std::cout << "<";
    else if( isLessThanOrEqualToOperator() ) std::cout << "<=";
    else if ( isHashtag() ) std::cout << "#";
    else if ( isPeriod() ) std::cout << ".";
    else if ( isQuotationMark() ) std::cout << "\"";
    else if ( isOpeningCurlyBrace() ) std::cout << "{";
    else if ( isClosingCurlyBrace() ) std::cout << "}";
    else if ( isString() ) std::cout << getStringFromGenericStringHolder();
    //Could we do this?:
    //else if(isRelationalOperator() ) std::cout << getStringForRelationalOperator();

    //Cody: Adam added isKeyword
    else if( isKeyword()) std::cout << getName();
    else std::cout << "Uninitialized token.\n";
}
