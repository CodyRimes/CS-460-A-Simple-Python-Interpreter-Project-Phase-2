
#include<iostream>

struct TypeDescriptor {
    // The base class for datatype descriptors.

    // This enum can expand to include additional types.
    enum types {INTEGER, DOUBLE, BOOL};  

    TypeDescriptor(types type): _type{type} {}

    types &type() { return _type; }

    virtual ~TypeDescriptor() {}

private:
    types _type;
};

struct NumberDescriptor: public TypeDescriptor {
    // Number descriptor includes integer, double, and boolean datatypes.

    NumberDescriptor(types descType):  TypeDescriptor(descType) {}
    union {
	int intValue;
	double doubleValue;
	short boolValue;
    } value;
};

void printValue(TypeDescriptor *desc) {
    // If desc is of datatype NumberDescriptor, this function
    // print the value that is stored in it. Otherwise,
    // it just returns.

    // Use dynamic_cast to down-cast, from TypeDescriptor to 
    // NumberDescriptr. 
    NumberDescriptor *nDesc = dynamic_cast<NumberDescriptor *>(desc);
    // dynamic_cast will return a nullptr if
    // desc is not of datatype NumberDescritpr.
    if( nDesc == nullptr )
	return;

    // desc must have been of type NumberDescriptr
    if( nDesc->type() == TypeDescriptor::INTEGER )
	std::cout << nDesc->value.intValue << std::endl;
    else if( nDesc->type() == TypeDescriptor::DOUBLE )
	std::cout << nDesc->value.doubleValue << std::endl;
    else if( nDesc->type() == TypeDescriptor::BOOL )
	std::cout << nDesc->value.boolValue << std::endl;
    else 
	std::cout << "Misconfigured union type." << std::endl;
}

int main() {
    NumberDescriptor *desc = new NumberDescriptor(TypeDescriptor::INTEGER);
    desc->value.intValue =  25;
    printValue(desc);

    return 0;
}
