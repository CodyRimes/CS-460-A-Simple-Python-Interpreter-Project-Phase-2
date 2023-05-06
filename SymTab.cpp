//
// Created by Ali Kooshesh on 4/4/23.
//

#include <iostream>
#include "SymTab.hpp"

//Cody May 4th 2023: receives a variable name and corresponding TypeDescriptor which will hold the datatype for that variable name and also it's value
void SymTab::setValueFor(const std::string &vName, TypeDescriptor* dataTypeAndValue) {
    // Define a variable by setting its initial value.
    if(debug)
        std::cout << vName << " <- " << dataTypeAndValue << std::endl;
    symTab[vName] = dataTypeAndValue;
}

//Cody May 4th 2023: Checks to make sure a variable name we receive actually exists in our private member map variable called symTab. Returns a bool if the variable is found or not.
bool SymTab::isDefined(const std::string &vName) {
    return symTab.find(vName) != symTab.end();
}
//Cody May 4th 2023: Gets the value for a variable we check for
TypeDescriptor* SymTab::getValueFor(const std::string &vName) {
    //If we cannot find a variable defined in this map with the variable name we are passed in this function then we need to throw an error message to the user
    if( ! isDefined(vName)) {
        std::cout << "SymTab::getValueFor: " << vName << " has not been defined.\n";
        exit(1);
    }
    if(debug)
        std::cout << "SymTab::getValueFor: " << vName << " contains " << symTab.find(vName)->second << std::endl;
    //.find() is an in-built function for the Standard Tempalte Library map data structure that find's a specific key in our map, and in this case that is our variable name
    //->second is used to access the second member of the key-value pair that a map holds at each index, and thus this will return the value of our variable name
    return symTab.find(vName)->second;
}
//Cody May 4th 2023: Prints the private member map called symbTab
void SymTab::print() {
    for(auto [var, value] : symTab )
        std::cout << var << " = " << value << std::endl;
}

