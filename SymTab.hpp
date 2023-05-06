//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_SYMTAB_HPP
#define APYTHONINTERPRETER_SYMTAB_HPP

#include "TypeDescriptor.hpp"
#include <string>
#include <map>

//Cody May 4th 2023: Update (Phase 2 Part 3 has changed this to now hold type descriptors instead of integers)
// This is a flat and integer-based symbol table. It allows for variables to be
// initialized, determines if a given variable has been defined or not, and if
// a variable has been defined, it returns its value.

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
