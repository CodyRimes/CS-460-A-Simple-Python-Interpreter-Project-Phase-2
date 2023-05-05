//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_SYMTAB_HPP
#define APYTHONINTERPRETER_SYMTAB_HPP

#include "TypeDescriptor.hpp"
#include <string>
#include <map>

// This is a flat and integer-based symbol table. It allows for variables to be
// initialized, determines if a give variable has been defined or not, and if
// a variable has been defined, it returns its value.

//Step 4 in phase 2 changed all int's in the symbol table to instead hold type descriptors
class SymTab {
public:
    void setValueFor(const std::string &vName, TypeDescriptor* value);
    bool isDefined(const std::string &vName);
    TypeDescriptor* getValueFor(const std::string &vName);
    void print();

private:
    std::map<std::string, TypeDescriptor*> symTab;
    bool debug = false;
};


#endif //APYTHONINTERPRETER_SYMTAB_HPP
