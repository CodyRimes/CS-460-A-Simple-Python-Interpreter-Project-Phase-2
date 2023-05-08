//
// Created by Ali Kooshesh on 4/4/23.
//

//Cody: Note to self/logic explanation: A lot of the bool functions compare our private attribute _symbol against a char literal, and if they match it will return true in these bool functions below

#ifndef APYTHONINTERPRETER_TOKEN_HPP
#define APYTHONINTERPRETER_TOKEN_HPP

#include<string>

class Token {

public:
    Token();
    //Setters. How? The & operator returns the member variables by reference instead of by value so their data is accessed directly. The compiler will use the setter when you do modifying statements to the symbol "eol()" because the getter cannot be modified by definition, and the setter can
    //it matches the appropriate function call based on how the resulting object is operated on
    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }

    //Getters
    bool eof() const { return _eof; }
    bool eol() const  { return _eol; }

    bool isString() const {return _isStringBoolValue;}
    void isStringSetter(bool doWeHaveAStringBoolValue) {_isStringBoolValue = doWeHaveAStringBoolValue;}

    bool isPythonIntegerDivisionSymbol() const {return _isPythonIntegerDivisionSymbol;}
    void isPythonIntegerDivisionSymbolBoolValueSetter(bool boolValueForIfWeHaveAPythonIntegerDivisionSymbolOrNot){_isPythonIntegerDivisionSymbol = boolValueForIfWeHaveAPythonIntegerDivisionSymbolOrNot;}

    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }

    bool isOpeningCurlyBrace() const { return _symbol == '{' ;}
    bool isClosingCurlyBrace() const { return _symbol == '}' ;}

    //Setter and getter for our _symbol private variable
    void symbol(char c) { _symbol = c; }
    char symbol() { return _symbol; }

    //Returns true if the _symbol private member variable is equivalent to the comparison we give it, returns false if it is not match
    bool isSemiColon() const { return _symbol == ';'; }
    bool isAssignmentOperator() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; }
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; }
    bool isModuloOperator() const         { return _symbol == '%'; }
    bool isDivisionOperator() const       { return _symbol == '/'; }
    bool isNotEqualOperator() const       { return _stringforrationaloperator == "!=";}
    bool isGreaterThanOperator() const    { return _symbol == '>';}
    bool isLessThanOperator() const       { return _symbol == '<'; }
    //Cody: Adding tokens that identify when we see greater than or equal ">=" to or less than or equal to "<=" signs. NOTE: I DO NOT THINK THIS WORKS SINCE _symbol IS A CHAR DATATYPE
    bool isGreaterThanOrEqualToOperator() const   { return _stringforrationaloperator == ">=";}
    bool isLessThanOrEqualToOperator() const      { return _stringforrationaloperator == "<=";}
    bool isEqualOperator() const               { return _stringforrationaloperator == "==";}
    bool isHashtag() const { return _symbol == '#';}
    bool isPeriod() const {return _symbol == '.';}
    bool isQuotationMark() const {return _symbol == '"';}
    bool isComma() const {return _symbol == ',';}

    bool isArithmeticOperator() const {
        return isMultiplicationOperator() ||
               isAdditionOperator() ||
               isSubtractionOperator() ||
               isModuloOperator() ||
               isDivisionOperator();
    }
    bool isName() const                   { return _name.length() > 0; }
    std::string getName() const                  { return _name; }
    void setName(std::string n) { _name = n; }

    std::string getStringForRelationalOperator() const { return _stringforrationaloperator; }
    void setStringForRelationalOperator(std::string incomingString) { _stringforrationaloperator = incomingString;}

    std::string getStringFromGenericStringHolder() const { return _genericStringHolder; }
    void setStringFromGenericStringHolder(std::string incomingString) { _genericStringHolder = incomingString;}

    std::string getPythonIntegerDivisionStringValueFromPrivateVariable() const {return _stringForPythonIntegerDivisionSymbol;}
    void setPythonIntegerDivisionStringValueForPrivateVariable(std::string shouldBePythonIntegerDivisionSymbol) {_stringForPythonIntegerDivisionSymbol = shouldBePythonIntegerDivisionSymbol;}


    bool &isWholeNumber() { return _isWholeNumber; }
    bool isWholeNumber() const { return _isWholeNumber; }
    int getWholeNumber() const { return _wholeNumber; }
    void setWholeNumber(int n) {
        _wholeNumber = n;
        isWholeNumber() = true;
    }
    //Cody May 8th 2023: Adding functionality so a token can hold and recognize it's holding a double
    void setDoubleNumber(double doubleNumberWeNeedToSetOurPrivateMemberDoubleVariableTo){ _ourActualDoubleNumber = doubleNumberWeNeedToSetOurPrivateMemberDoubleVariableTo; }
    double getDoubleNumber() { return _ourActualDoubleNumber; }
    bool isItADouble() { return _isDouble; }
    void setDoubleBoolValue(bool boolValueWeWantToSetOurIsDoublePrivateMemberVariableTo) { _isDouble = boolValueWeWantToSetOurIsDoublePrivateMemberVariableTo; }
    // STEP 2
    //Cody: Returns true if one of the bools within the function return true
    bool isRelationalOperator() const {
        return isLessThanOperator() ||
        isLessThanOrEqualToOperator() ||
        isGreaterThanOperator() ||
        isGreaterThanOrEqualToOperator() ||
        isEqualOperator() ||
        isNotEqualOperator();
    }


    /* Cody: I think this is Adam's code I'm commenting out?
    bool isNotEqualOperator() const {
        return _name == "!=";
    }
    bool isGreaterThanOperator() const {
        return _name == ">";
    }
    bool isGreaterThanOrEqualOperator() const {
        return _name == ">=";
    }
    bool isLessThanOperator() const {
        return _name == "<";
    }
    bool isLessThanOrEqualOperator() const {
        return _name == "<=";
    }
     */

    // STEP 5 HERE, Cody: Adam added isKeyword
    //Cody: is the variable _name equal to "print" or "for"? If so it will return true
    bool isKeyword() const {
        return _name == "print" || _name == "for";
    }


    void print() const;

private:
    std::string _name;
    std::string _stringforrationaloperator;
    std::string _genericStringHolder;
    std::string _stringForPythonIntegerDivisionSymbol;
    bool _eof, _eol;
    bool _isWholeNumber;
    char _symbol;
    int _wholeNumber;
    double _ourActualDoubleNumber;
    bool _isDouble;
    bool _isStringBoolValue;
    bool _isPythonIntegerDivisionSymbol;
};


#endif //APYTHONINTERPRETER_TOKEN_HPP
