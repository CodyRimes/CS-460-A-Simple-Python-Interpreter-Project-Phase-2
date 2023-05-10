//
// Created by Cody on 5/2/2023.
//

#ifndef APYTHONINTERPRETER_TYPEDESCRIPTOR_HPP
#define APYTHONINTERPRETER_TYPEDESCRIPTOR_HPP
#include<iostream>

//Creating a "TypeDescriptor" class which will allow us to use a "TypeDescriptor" class in our SymbolTable. The type descriptor allows us to give the symbol table information about the variable it is mapping such as datatype data.
//Thus instead of std::map<std::string, int> symTab; inside the symbol table class we will have:
//std::map<std::string, TypeDescriptor*> symTab;
class TypeDescriptor {
public:

    // This enum can expand to include additional types.
    //So we can differentiate what we're using when using references to the base class, helps us distinguish what we are trying to be
    enum ourCustomEnumDatatype {INTEGER, DOUBLE, BOOL, STRING, BOGUS};
    //Default constructor
    TypeDescriptor();
    //Parameterized constructor
    TypeDescriptor(ourCustomEnumDatatype type);
    TypeDescriptor(ourCustomEnumDatatype type, std::string ourStringValue);
    TypeDescriptor(ourCustomEnumDatatype type, int incomingIntegerValue);
    TypeDescriptor(ourCustomEnumDatatype type, double incomingDoubleValue);
    TypeDescriptor(ourCustomEnumDatatype type, bool incomingBoolValue);
    //Getter that returns our private member variable
    ourCustomEnumDatatype getOurDataType()  { return _type; }

    //Getters for our private member variables
    bool boolValue() const; // if our union private member variable is a bool datatype, returns the bool value
    double doubleValue() const;  // if our union private member variable is a double datatype, returns the double value
    int intValue () const;  // if our union private member variable is a integer datatype, returns the integer value

    //Getter
    std::string getStringValue() const; // returns our private member variable's string value.
    //Setter
    void setStringValue(std::string value);  // sets our private member variable's string value.

    //CHANGED TO NOT VIRTUAL SINCE WE ARE NO LONGER USING POLYMORPHISM
    //virtual destructor, allows derived classes to define their own implementation of the desctructor if necessary
     ~TypeDescriptor() {}

     TypeDescriptor* operator + (TypeDescriptor* secondTypeDescriptorWeWantToAdd);
     TypeDescriptor* operator - (TypeDescriptor* secondTypeDescriptorWeWantToSubtract);
     TypeDescriptor* operator * (TypeDescriptor* secondTypeDescriptorWeWantToMultiply);
     TypeDescriptor* operator / (TypeDescriptor* secondTypeDescriptorWeWantToDivide);
     TypeDescriptor* operator < (TypeDescriptor* secondTypeDescriptorWeWantToCompareAgainst);
     TypeDescriptor* operator > (TypeDescriptor* secondTypeDescriptorWeWantToCompareAgainst);
     TypeDescriptor* operator <= (TypeDescriptor* secondTypeDescriptorWeWantToCompareAgainst);
     TypeDescriptor* operator >= (TypeDescriptor* secondTypeDescriptorWeWantToCompareAgainst);
     TypeDescriptor* operator == (TypeDescriptor* secondTypeDescriptorWeWantToCompareAgainst);
     TypeDescriptor* operator != (TypeDescriptor* secondTypeDescriptorWeWantToCompareAgainst);



private:
    //This is our enum datatypes which we gave the variable name "types" to earlier in this code
    ourCustomEnumDatatype _type;
    std::string _ourString;
    union
    {
        int integerValueWeChooseToBe;
        double doubleValueWeChooseToBe;
        bool boolValueWeChooseToBe;
    } dataTypeWeChooseToBe;
};



/* CODY MAY 5th 2023 COMMENTING OUT THIS CODE. TRYING TO KEEP OBJECT ORIENTED PROGRAMMING CONCEPTS SEEMS TO BE CAUSING MORE PROBLEMS THAN IT IS HELPING TO SOLVE. MAKING TYPE DESCRIPTOR ABLE TO HANDLE EVERYTHING ON ITS OWN/FULLY ENCOMPASSING

//TypeDescriptor sub-class that will handle integers and doubles
class NumericTypeDescriptor : public TypeDescriptor {
public:
    //Default constructor, do we need this? I want to take the initialized value of our base class and bring it into our derived class?
    NumericTypeDescriptor();

    //Parameterized constructors to handle different types of numeric datatypes we can encounter. Note how we inherit from the base class the enum datatype we made; our variable is named "_type"
    //Note how we use our constructors as setters for our private member variables as well
    NumericTypeDescriptor(ourCustomEnumDatatype dataTypeWeReceiveUponDeclaringInstanceOfNumericTypeDescriptor, double valueOfThatDatatype);
    NumericTypeDescriptor(ourCustomEnumDatatype dataTypeWeReceiveUponDeclaringInstanceOfNumericTypeDescriptor, int valueOfThatDatatype);
    NumericTypeDescriptor(ourCustomEnumDatatype dataTypeWeReceiveUponDeclaringInstanceOfNumericTypeDescriptor, bool valueOfThatDatatype);
    NumericTypeDescriptor(ourCustomEnumDatatype dataTypeWeReceiveUponDeclaringInstanceOfNumericTypeDescriptor);
    //Getters for our private member variables
    bool boolValue() const; // if our union private member variable is a bool datatype, returns the bool value
    double doubleValue() const;  // if our union private member variable is a double datatype, returns the double value
    int intValue () const;  // if our union private member variable is a integer datatype, returns the integer value

    //Overloaded operators so we can do arithmetic operations between two instances of this class (note that the compiler itself would not know how to do those types of operations without our specific instructions)
    TypeDescriptor* operator + ( TypeDescriptor* other) override; // adds two numerical values
    TypeDescriptor* operator - ( TypeDescriptor* other) override; // subtracts two numerical values
    TypeDescriptor* operator * ( TypeDescriptor* other) override; // multiplies two numerical values
    TypeDescriptor* operator / ( TypeDescriptor* other) override; // divides two numerical values
    TypeDescriptor* operator < ( TypeDescriptor* other) override;
    TypeDescriptor* operator > ( TypeDescriptor* other) override;
    TypeDescriptor* operator <= ( TypeDescriptor* other) override;
    TypeDescriptor* operator >= ( TypeDescriptor* other) override;
    TypeDescriptor* operator == ( TypeDescriptor* other) override;
    TypeDescriptor* operator != ( TypeDescriptor* other) override;




private:
    //Here is a good video on what a union is in C++:
    //https://www.youtube.com/watch?v=b9_0bqrm2G8
    //It basically allows us to be more efficient with how we use our memory depending on what datatype we want to be, and once we know what datatype we want to be, it will actually contain the value of our datatype as well
    //(we get a hint of what our union will be from our TypeDescriptor's enum member variable)
    union
    {
        int integerValueWeChooseToBe;
        double doubleValueWeChooseToBe;
        bool boolValueWeChooseToBe;
    } dataTypeWeChooseToBe;

};

//Type descriptor sub-class that will handle strings
class StringTypeDescriptor : public TypeDescriptor {
public:

    //Default constructor
    StringTypeDescriptor();

    //Parameterized constructors
    StringTypeDescriptor(ourCustomEnumDatatype dataTypeWeReceiveUponDeclaringInstanceOfStringTypeDescriptor , std::string value);
    StringTypeDescriptor(ourCustomEnumDatatype dataTypeWeReceiveUponDeclaringInstanceOfStringTypeDescriptor );

    //Getter
    std::string getStringValue() const; // returns our private member variable's string value.
    //Setter
    void setStringValue(std::string value);  // sets our private member variable's string value.

    //May be unnecessary. Use getter and add two instances's strings together that way?
    TypeDescriptor* operator+( TypeDescriptor* other) override; // concatenates two instances of our StringTypeDescriptor together
private:
    std::string _ourString;
    //Note how inherit the private member variable _type from our base class in TypeDescriptor
};

 */
#endif //APYTHONINTERPRETER_TYPEDESCRIPTOR_HPP
