//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_TOKEN_HPP
#define APYTHONINTERPRETER_TOKEN_HPP

#include<string>

class Token {

public:
    Token();
    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }

    bool eof() const { return _eof; }
    bool eol() const  { return _eol; }

    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }

    void symbol(char c) { _symbol = c; }
    char symbol() { return _symbol; }

    bool isSemiColon() const { return _symbol == ';'; }
    bool isAssignmentOperator() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; }
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; }
    bool isModuloOperator() const         { return _symbol == '%'; }
    bool isDivisionOperator() const       { return _symbol == '/'; }
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

    bool &isWholeNumber() { return _isWholeNumber; }
    bool isWholeNumber() const { return _isWholeNumber; }
    int getWholeNumber() const { return _wholeNumber; }
    void setWholeNumber(int n) {
        _wholeNumber = n;
        isWholeNumber() = true;
    }
    // STEP 2
    bool isRelationalOperator() const {
        return isLessThanOperator() ||
        isLessThanOrEqualOperator() ||
        isGreaterThanOperator() ||
        isGreaterThanOrEqualOperator() ||
        isEqualityOperator() ||
        isNotEqualOperator();
    }

    bool isEqualityOperator() const {
        return _name == "==";
    }
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
    // STEP 5 HERE
    bool isKeyword() const {
        return _name == "print" || _name == "for";
    }


    void print() const;

private:
    std::string _name;
    bool _eof, _eol;
    bool _isWholeNumber;
    char _symbol;
    int _wholeNumber;
};


#endif //APYTHONINTERPRETER_TOKEN_HPP
