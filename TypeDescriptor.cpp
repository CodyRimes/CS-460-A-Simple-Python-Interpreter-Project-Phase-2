//
// Created by Cody on 5/3/2023.
//
//Phase 2 Step 3 HERE May 4th 2023 by Cody:
//these TypeDescriptor files help our SymbolTable not only process integer variables as it did before but extends it to handle different datatypes such as doubles, bools, and strings, and also helps it keep track of what datatypes the variables names contain/are associated with, and (with the way I built out my TypeDescriptors) helps our ExpressionNodes do (arithemetic and relational comparison) operations amongst different the data types

#include<iostream>
#include "TypeDescriptor.hpp"

//Here is a good video on how the inheritance hierarchy works and interacts with the different default and parameterized constructors of base and derived classes:
//https://www.youtube.com/watch?v=MmR_qpYthP8

//Default constructor of our TypeDescriptor base class
TypeDescriptor::TypeDescriptor()
{
    _type = BOGUS;
    _ourString = "";
    dataTypeWeChooseToBe.boolValueWeChooseToBe = false;
}

//Parameterized constructor of our TypeDescriptor base class
TypeDescriptor::TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype incomingType)
{
    _type = incomingType;
    _ourString = "";
    dataTypeWeChooseToBe.boolValueWeChooseToBe = false;
}

//Parameterized constructor of our TypeDescriptor base class
TypeDescriptor::TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype incomingType, std::string ourStringValue)
{
    _type = incomingType;
    _ourString = ourStringValue;
    dataTypeWeChooseToBe.boolValueWeChooseToBe = false;
}

//Parameterized constructor of our TypeDescriptor base class
TypeDescriptor::TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype incomingType, int incomingIntegerValue)
{
    _type = incomingType;
    _ourString = "";
    dataTypeWeChooseToBe.integerValueWeChooseToBe = incomingIntegerValue;
}

//Parameterized constructor of our TypeDescriptor base class
TypeDescriptor::TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype incomingType, double incomingDoubleValue)
{
    _type = incomingType;
    _ourString = "";
    dataTypeWeChooseToBe.doubleValueWeChooseToBe = incomingDoubleValue;
}

//Parameterized constructor of our TypeDescriptor base class
TypeDescriptor::TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype incomingType, bool incomingBoolValue)
{
    _type = incomingType;
    _ourString = "";
    dataTypeWeChooseToBe.boolValueWeChooseToBe = incomingBoolValue;
}

//Get the string value our StringTypeDescriptor has
std::string TypeDescriptor::getStringValue() const
{
    return _ourString;
}
//Set the string value for our StringTypeDescriptor
void TypeDescriptor::setStringValue(std::string value)
{
    _ourString = value;
}

//Getters
double TypeDescriptor::doubleValue() const
{
    return dataTypeWeChooseToBe.doubleValueWeChooseToBe;
}
int TypeDescriptor::intValue () const
{
    return dataTypeWeChooseToBe.integerValueWeChooseToBe;
}
bool TypeDescriptor::boolValue() const
{
    return dataTypeWeChooseToBe.boolValueWeChooseToBe;
}


TypeDescriptor* TypeDescriptor::operator + ( TypeDescriptor* other)
{
    //we need to account for when two TypeDescriptor are either:


    if ( (this->getOurDataType() == STRING) && (other->getOurDataType() == STRING))
    {
        std::string ourTemporaryStringVariableToConcatenateTheTwoStrings;
        ourTemporaryStringVariableToConcatenateTheTwoStrings = this->getStringValue() + other->getStringValue();
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::STRING, ourTemporaryStringVariableToConcatenateTheTwoStrings);
    }

    //This is a double, the incoming one is an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER))
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::DOUBLE, this->doubleValue() + other->intValue());
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->intValue() + other->doubleValue());
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() + other->doubleValue());
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER))
    {
        return new TypeDescriptor(TypeDescriptor::INTEGER, this->intValue() + other->intValue());
    }

    else//Lets give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload + between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }



}

TypeDescriptor* TypeDescriptor::operator - ( TypeDescriptor* other)
{
    //we need to account for when two NumbericTypeDescriptors are either:


    //This is a double, the incoming one is an integer
    if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() - other->intValue());
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->intValue() - other->doubleValue());
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() - other->doubleValue());
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER))
    {
        return new TypeDescriptor(TypeDescriptor::INTEGER, this->intValue() - other->intValue());
    }
    else//Lets give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload - between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }



}
TypeDescriptor* TypeDescriptor::operator * ( TypeDescriptor* other)
{
    //we need to account for when two NumbericTypeDescriptors are either:


    //This is a double, the incoming one is an integer
    if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() * other->intValue());
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->intValue() * other->doubleValue());
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() * other->doubleValue());
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER))
    {
        return new TypeDescriptor(TypeDescriptor::INTEGER, this->intValue() * other->intValue());
    }

    else//Lets give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload * between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }



}

//ASK KOOSHESH HOW WE WOULD HANDLE THE // PYTHON OPERATOR IN C++
TypeDescriptor* TypeDescriptor::operator / ( TypeDescriptor* other)
{
    //we need to account for when two NumbericTypeDescriptors are either:


    //This is a double, the incoming one is an integer
    if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() / other->intValue());
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->intValue() / other->doubleValue());
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() / other->doubleValue());
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER))
    {
        return new TypeDescriptor(TypeDescriptor::INTEGER, this->intValue() / other->intValue());
    }

    else//Lets give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload / between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }


}

TypeDescriptor* TypeDescriptor::operator % ( TypeDescriptor* other)
{
    //we need to account for when two NumbericTypeDescriptors are either:


    //This is a double, the incoming one is an integer
    if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, static_cast<int>(this->doubleValue()) % other->intValue());
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, this->intValue() % static_cast<int>(other->doubleValue()));
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE))
    {
        return new TypeDescriptor(TypeDescriptor::DOUBLE, static_cast<int>(this->doubleValue()) %  static_cast<int>(other->doubleValue()));
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER))
    {
        return new TypeDescriptor(TypeDescriptor::INTEGER, this->intValue() % other->intValue());
    }

    else//Lets give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload / between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }


}

TypeDescriptor* TypeDescriptor::operator < ( TypeDescriptor* other)
{
    //we need to account for when two NumbericTypeDescriptors are either:

    //This is a double, the incoming one is an integer
    if ( (this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() < other->intValue()));
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() < other->doubleValue()));
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() < other->doubleValue()));
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() < other->intValue()));
    }

    else//Lets give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload < between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }

    /*
    else //no comparisons have passed. return false
    {
        return false;
    }
     */

}
TypeDescriptor* TypeDescriptor::operator > ( TypeDescriptor* other)
{
    //we need to account for when two NumbericTypeDescriptors are either:

    //This is a double, the incoming one is an integer
    if ( (this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() > other->intValue()));
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() > other->doubleValue()));
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() > other->doubleValue()));
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() > other->intValue()));
    }
    else //Let's give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload > between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }

    /*
    else //no comparisons have passed. return false
    {
        return false;
    }
    */
}

TypeDescriptor* TypeDescriptor::operator <= ( TypeDescriptor* other)
{
    //we need to account for when two NumbericTypeDescriptors are either:

    //This is a double, the incoming one is an integer
    if ( (this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() <= other->intValue()));
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() <= other->doubleValue()));
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() <= other->doubleValue()));
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() <= other->intValue()));
    }

    else//Lets give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload <= between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }
    /*
    else //no comparisons have passed. return false
    {
        return false;
    }
    */

}

TypeDescriptor* TypeDescriptor::operator >= ( TypeDescriptor* other)
{
    //we need to account for when two NumbericTypeDescriptors are either:

    //This is a double, the incoming one is an integer
    if ( (this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() >= other->intValue()));
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() >= other->doubleValue()));
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() >= other->doubleValue()));
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() >= other->intValue()));
    }
    else//Lets give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload >= between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }
    /*
    else //no comparisons have passed. return false
    {
        return false;
    }
     */
}

TypeDescriptor* TypeDescriptor::operator == ( TypeDescriptor* other)
{
    //we need to account for when two NumbericTypeDescriptors are either:

    //This is a double, the incoming one is an integer
    if ( (this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() == other->intValue()));
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() == other->doubleValue()));
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() == other->doubleValue()));
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() == other->intValue()));
    }
    else//Lets give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload >= between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }
    /*
    else //no comparisons have passed. return false
    {
        return false;
    }
    */
}

TypeDescriptor* TypeDescriptor::operator != ( TypeDescriptor* other)
{
    //we need to account for when two NumbericTypeDescriptors are either:

    //This is a double, the incoming one is an integer
    if ( (this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() != other->intValue()));
    }

        //This is an integer, the incoming one is a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() != other->doubleValue()));
    }

        //Both are a double
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() != other->doubleValue()));
    }

        //Both are an integer
    else if ((this->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) && (other->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER) )
    {
        return new TypeDescriptor(TypeDescriptor::BOOL, (this->intValue() != other->intValue()));
    }
    else//Lets give the user an error message if something unexpected happens
    {
        return new TypeDescriptor(TypeDescriptor::ourCustomEnumDatatype::BOGUS);
        std::cout <<"Operation overload >= between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
    }
    /*
    else //no comparisons have passed. return false
    {
        return false;
    }
     */

}

//Allows us to actually print what a TypeDescriptor pointer, when de-referenced, contains:
std::ostream& operator << (std::ostream& ourOutputStreamWeTakeInToModify, TypeDescriptor* ourTypeDescriptorWeWantToPrintToScreen)
{

    if (ourTypeDescriptorWeWantToPrintToScreen->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::DOUBLE)
    {
        //std::cout <<"They TypeDescriptor pointer we are trying to dereference and print is a DOUBLE type as seen here: " << ourTypeDescriptorWeWantToPrintToScreen->getOurDataType() << " and it's value it contains is: " << ourTypeDescriptorWeWantToPrintToScreen->doubleValue() << std::endl;
        std::cout << "  Datatype: Double; " <<  ourTypeDescriptorWeWantToPrintToScreen->doubleValue();
    }
    else if (ourTypeDescriptorWeWantToPrintToScreen->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::INTEGER)
    {
        //std::cout <<"They TypeDescriptor pointer we are trying to dereference and print is a INTEGER type as seen here: " << ourTypeDescriptorWeWantToPrintToScreen->getOurDataType() << " and it's value it contains is: " << ourTypeDescriptorWeWantToPrintToScreen->intValue() << std::endl;
        std::cout << " Datatype: Integer; " <<  ourTypeDescriptorWeWantToPrintToScreen->intValue();
    }
    else if (ourTypeDescriptorWeWantToPrintToScreen->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::BOOL)
    {
        //std::cout <<"They TypeDescriptor pointer we are trying to dereference and print is a BOOL type as seen here: " << ourTypeDescriptorWeWantToPrintToScreen->getOurDataType() << " and it's value it contains is: " << ourTypeDescriptorWeWantToPrintToScreen->boolValue() << std::endl;
        std::cout << " Datatype: Bool; " <<  ourTypeDescriptorWeWantToPrintToScreen->boolValue();
    }
    else if (ourTypeDescriptorWeWantToPrintToScreen->getOurDataType() == TypeDescriptor::ourCustomEnumDatatype::STRING)
    {
        //std::cout <<"They TypeDescriptor pointer we are trying to dereference and print is a STRING type as seen here: " << ourTypeDescriptorWeWantToPrintToScreen->getOurDataType() << " and it's value it contains is: " << ourTypeDescriptorWeWantToPrintToScreen->getStringValue() << std::endl;
        std::cout <<  " Datatype: String; " <<  ourTypeDescriptorWeWantToPrintToScreen->getStringValue();
    }
    else //We have run into an unknown case
    {
        std::cout << "Something wrong has happened when trying to output this TypeDescriptor. You are a failure" << std::endl;
    }

    //Now we have modified what we've wanted to do with our TypeDescriptor when it comes to outputting one, we can return the outputStream we've taken in by reference and return the "modified" version
    return ourOutputStreamWeTakeInToModify;
}




//
//
////Parameterized constructors of our NumericTypeDescriptors
//
////Default constructor of our sub-class NumericTypeDescriptor
////Note how we use the default constructor of our TypeDescriptor base class to set the private member variable that only it can touch but this class inherits
//NumericTypeDescriptor::NumericTypeDescriptor() : TypeDescriptor()
//{
//    //And then our constructor sets the private member variable for this class. We'll choose integer as our union datatype and zero as our bogus value
//    dataTypeWeChooseToBe.integerValueWeChooseToBe = 0;
//}
//
////parameterized constructors
////Note the inheritance structure we are using here.
////When we create an instance of a NumericTypeDescriptor, for example such as in the line:
////return new NumericTypeDescriptor(DOUBLE, 20.2);
////We create an instance of NumericTypeDescriptor, not BOTH an instance of NumericTypeDescriptor and TypeDescriptor as I previously thought. It is hard to describe my thought process that I was having before but I believe that it was something along the lines of us creating an instance of TypeDescriptor, setting it's private member variables, then creating an instance of NumericTypeDescriptor and it needing to inhert those values from TypeDescriptor (and thought we needed to pass the inherited private member data from the base class to the sub-class). Anyways, it doesn't matter what my old thought processw was, the follow is how this inheritance stuff really works:
////Thus when we create an instance of NumericTypeDescriptor we can give it parameters that belong to it's inherited parent class (TypeDescriptor) and that belong to the extended class itself (NumericTypeDescriptor)
////As we can see TypeDescriptor is what contains and handles our custom enum that we've made which we called ourCustomEnumDatatype. We will need to pass this to the TYPEDESCRIPTOR constructor in order to set this, and thus we will need use it/inherit it. The follow code is how you use the inherited parent class constructor in order to set the appropriate variable.
////But in our new instance of our NumericTypeDescriptor example above, we can also pass it parameters that it itself only contains, and can use this constructor to set those member variables as well. In this case, that is the value of the datatype our enum is, whatever it may be, and we will make our union according to the enum we've received.
////Thus for our example, we will have received an double for our enum datatype, which gives us a clue as to what our union value will actually hold/contain. Since in this example we receive an double, we know we will want to call the constructor that has the double parameter being passed to it such as below, which will set our union to hold a double data type and contain the value we just passed in.
////A long explanation but I hope as time goes on just reading this code may be self explanatory. Basically we are just having a NumericTypeDescriptor constructor call in a TypeDescriptor constructor in order to help set a value for a member variable it has inherited and doesn't have "direct" access to (since our enum is private in our base class TypeDescriptor)
//NumericTypeDescriptor::NumericTypeDescriptor(ourCustomEnumDatatype incomingDataType, double valueOfThatDatatype) : TypeDescriptor(incomingDataType)
//{
//    //Set our union to the correct union data type, and set the value of that data type, all in one shot
//    dataTypeWeChooseToBe.doubleValueWeChooseToBe = valueOfThatDatatype;
//
//}
////Pass the datatype we receive to the TypeDescriptor's constructor (so the TypeDescriptor constructor can set the private member variable, which is what that constructor does), and set our union that we have in this class to the value we receive as our 2nd parameter here in this constructor
//NumericTypeDescriptor::NumericTypeDescriptor(ourCustomEnumDatatype incomingDataType, int valueOfThatDatatype): TypeDescriptor(incomingDataType)
//{
//    //Set our union to the correct union data type, and set the value of that data type, all in one shot
//    dataTypeWeChooseToBe.integerValueWeChooseToBe = valueOfThatDatatype;
//}
////Pass the datatype we receive to the TypeDescriptor's constructor (so the TypeDescriptor constructor can set the private member variable, which is what that constructor does), and set our union that we have in this class to the value we receive as our 2nd parameter here in this constructor
//NumericTypeDescriptor::NumericTypeDescriptor(ourCustomEnumDatatype incomingDataType, bool valueOfThatDatatype) : TypeDescriptor(incomingDataType)
//{
//    //Set our union to the correct union data type, and set the value of that data type, all in one shot
//    dataTypeWeChooseToBe.boolValueWeChooseToBe = valueOfThatDatatype;
//}
//
////For whatever reason if we receive no value, we can at least set the data type we got using the TypeDescriptor constructor
//NumericTypeDescriptor::NumericTypeDescriptor(ourCustomEnumDatatype incomingDataType) : TypeDescriptor(incomingDataType)
//{
//
//}
//
//
//
////Getters
//double NumericTypeDescriptor::doubleValue() const
//{
//    return dataTypeWeChooseToBe.doubleValueWeChooseToBe;
//}
//int NumericTypeDescriptor::intValue () const
//{
//    return dataTypeWeChooseToBe.integerValueWeChooseToBe;
//}
//bool NumericTypeDescriptor::boolValue() const
//{
//    return dataTypeWeChooseToBe.boolValueWeChooseToBe;
//}
//
//
//
//TypeDescriptor* NumericTypeDescriptor::operator + ( TypeDescriptor* other)
//{
//    //we need to account for when two NumbericTypeDescriptors are either:
//
//    //other = static_cast<NumericTypeDescriptor*>(other);
//
//    //This is a double, the incoming one is an integer
//    if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::INTEGER))
//    {
//        //Note how we are casting TypeDescriptor pointer we received(which we've called other) to NumericDescriptor pointer and dereferencing the result to access NumericDescriptor member functions
//        //Note how we could have written the code like this:
//        //return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->intValue() + (*(NumericTypeDescriptor*)other).intValue());
//        //This may be easier to read, so lets do this:
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() + ((NumericTypeDescriptor*)other)->intValue());
//
//    }
//
//    //This is an integer, the incoming one is a double
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::DOUBLE))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->intValue() + ((NumericTypeDescriptor*)other)->doubleValue());
//    }
//
//    //Both are a double
//    else if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::DOUBLE))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() +((NumericTypeDescriptor*)other)->doubleValue());
//    }
//
//    //Both are an integer
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::INTEGER))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::INTEGER, this->intValue() + ((NumericTypeDescriptor*)other)->intValue());
//    }
//
//    else//Lets give the user an error message if something unexpected happens
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOGUS);
//        std::cout <<"Operation overload + between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
//    }
//
//
//
//}
//
//TypeDescriptor* NumericTypeDescriptor::operator - ( TypeDescriptor* other)
//{
//    //we need to account for when two NumbericTypeDescriptors are either:
//
//
//    //This is a double, the incoming one is an integer
//    if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::INTEGER))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() - ((NumericTypeDescriptor*)other)->intValue());
//    }
//
//    //This is an integer, the incoming one is a double
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::DOUBLE))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->intValue() - ((NumericTypeDescriptor*)other)->doubleValue());
//    }
//
//    //Both are a double
//    else if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::DOUBLE))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() - ((NumericTypeDescriptor*)other)->doubleValue());
//    }
//
//    //Both are an integer
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::INTEGER))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::INTEGER, this->intValue() - ((NumericTypeDescriptor*)other)->intValue());
//    }
//    else//Lets give the user an error message if something unexpected happens
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOGUS);
//        std::cout <<"Operation overload - between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
//    }
//
//
//
//}
//TypeDescriptor* NumericTypeDescriptor::operator * ( TypeDescriptor* other)
//{
//    //we need to account for when two NumbericTypeDescriptors are either:
//
//
//    //This is a double, the incoming one is an integer
//    if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::INTEGER))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() * ((NumericTypeDescriptor*)other)->intValue());
//    }
//
//    //This is an integer, the incoming one is a double
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::DOUBLE))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->intValue() * ((NumericTypeDescriptor*)other)->doubleValue());
//    }
//
//    //Both are a double
//    else if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::DOUBLE))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() * ((NumericTypeDescriptor*)other)->doubleValue());
//    }
//
//    //Both are an integer
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::INTEGER))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::INTEGER, this->intValue() * ((NumericTypeDescriptor*)other)->intValue());
//    }
//
//    else//Lets give the user an error message if something unexpected happens
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOGUS);
//        std::cout <<"Operation overload * between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
//    }
//
//
//
//}
//
////ASK KOOSHESH HOW WE WOULD HANDLE THE // PYTHON OPERATOR IN C++
//TypeDescriptor* NumericTypeDescriptor::operator / ( TypeDescriptor* other)
//{
//    //we need to account for when two NumbericTypeDescriptors are either:
//
//
//    //This is a double, the incoming one is an integer
//    if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::INTEGER))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() / ((NumericTypeDescriptor*)other)->intValue());
//    }
//
//    //This is an integer, the incoming one is a double
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::DOUBLE))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->intValue() / ((NumericTypeDescriptor*)other)->doubleValue());
//    }
//
//    //Both are a double
//    else if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::DOUBLE))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::DOUBLE, this->doubleValue() / ((NumericTypeDescriptor*)other)->doubleValue());
//    }
//
//    //Both are an integer
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::INTEGER))
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::INTEGER, this->intValue() / ((NumericTypeDescriptor*)other)->intValue());
//    }
//
//    else//Lets give the user an error message if something unexpected happens
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOGUS);
//        std::cout <<"Operation overload / between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
//    }
//
//
//}
//
//TypeDescriptor* NumericTypeDescriptor::operator < ( TypeDescriptor* other)
//{
//    //we need to account for when two NumbericTypeDescriptors are either:
//
//    //This is a double, the incoming one is an integer
//    if ( (this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() < ((NumericTypeDescriptor*)other)->intValue()));
//    }
//
//    //This is an integer, the incoming one is a double
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() < ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//    //Both are a double
//    else if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() < ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//    //Both are an integer
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() < ((NumericTypeDescriptor*)other)->intValue()));
//    }
//
//    else//Lets give the user an error message if something unexpected happens
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOGUS);
//        std::cout <<"Operation overload < between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
//    }
//
//    /*
//    else //no comparisons have passed. return false
//    {
//        return false;
//    }
//     */
//
//}
//TypeDescriptor* NumericTypeDescriptor::operator > ( TypeDescriptor* other)
//{
//    //we need to account for when two NumbericTypeDescriptors are either:
//
//    //This is a double, the incoming one is an integer
//    if ( (this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() > ((NumericTypeDescriptor*)other)->intValue()));
//    }
//
//        //This is an integer, the incoming one is a double
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() > ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//        //Both are a double
//    else if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() > ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//        //Both are an integer
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() > ((NumericTypeDescriptor*)other)->intValue()));
//    }
//    else //Let's give the user an error message if something unexpected happens
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOGUS);
//        std::cout <<"Operation overload > between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
//    }
//
//    /*
//    else //no comparisons have passed. return false
//    {
//        return false;
//    }
//    */
//}
//
//TypeDescriptor* NumericTypeDescriptor::operator <= ( TypeDescriptor* other)
//{
//    //we need to account for when two NumbericTypeDescriptors are either:
//
//    //This is a double, the incoming one is an integer
//    if ( (this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() <= ((NumericTypeDescriptor*)other)->intValue()));
//    }
//
//        //This is an integer, the incoming one is a double
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() <= ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//        //Both are a double
//    else if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() <= ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//        //Both are an integer
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() <= ((NumericTypeDescriptor*)other)->intValue()));
//    }
//
//    else//Lets give the user an error message if something unexpected happens
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOGUS);
//        std::cout <<"Operation overload <= between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
//    }
//    /*
//    else //no comparisons have passed. return false
//    {
//        return false;
//    }
//    */
//
//}
//
//TypeDescriptor* NumericTypeDescriptor::operator >= ( TypeDescriptor* other)
//{
//    //we need to account for when two NumbericTypeDescriptors are either:
//
//    //This is a double, the incoming one is an integer
//    if ( (this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() >= ((NumericTypeDescriptor*)other)->intValue()));
//    }
//
//        //This is an integer, the incoming one is a double
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() >= ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//        //Both are a double
//    else if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() >= ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//        //Both are an integer
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() >= ((NumericTypeDescriptor*)other)->intValue()));
//    }
//    else//Lets give the user an error message if something unexpected happens
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOGUS);
//        std::cout <<"Operation overload >= between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
//    }
//    /*
//    else //no comparisons have passed. return false
//    {
//        return false;
//    }
//     */
//}
//
//TypeDescriptor* NumericTypeDescriptor::operator == ( TypeDescriptor* other)
//{
//    //we need to account for when two NumbericTypeDescriptors are either:
//
//    //This is a double, the incoming one is an integer
//    if ( (this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() == ((NumericTypeDescriptor*)other)->intValue()));
//    }
//
//        //This is an integer, the incoming one is a double
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() == ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//        //Both are a double
//    else if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() == ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//        //Both are an integer
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() == ((NumericTypeDescriptor*)other)->intValue()));
//    }
//    else//Lets give the user an error message if something unexpected happens
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOGUS);
//        std::cout <<"Operation overload >= between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
//    }
//    /*
//    else //no comparisons have passed. return false
//    {
//        return false;
//    }
//    */
//}
//
//TypeDescriptor* NumericTypeDescriptor::operator != ( TypeDescriptor* other)
//{
//    //we need to account for when two NumbericTypeDescriptors are either:
//
//    //This is a double, the incoming one is an integer
//    if ( (this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() != ((NumericTypeDescriptor*)other)->intValue()));
//    }
//
//        //This is an integer, the incoming one is a double
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() != ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//        //Both are a double
//    else if ((this->type() == TypeDescriptor::DOUBLE) && (other->type() == TypeDescriptor::DOUBLE) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->doubleValue() != ((NumericTypeDescriptor*)other)->doubleValue()));
//    }
//
//        //Both are an integer
//    else if ((this->type() == TypeDescriptor::INTEGER) && (other->type() == TypeDescriptor::INTEGER) )
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOOL, (this->intValue() != ((NumericTypeDescriptor*)other)->intValue()));
//    }
//    else//Lets give the user an error message if something unexpected happens
//    {
//        return new NumericTypeDescriptor(TypeDescriptor::BOGUS);
//        std::cout <<"Operation overload >= between two NumericTypeDescriptors seems to have failed. Do you have the right data types?" << std::endl;
//    }
//    /*
//    else //no comparisons have passed. return false
//    {
//        return false;
//    }
//     */
//
//}
//
////AREA FOR STRING TYPE DESCRIPTOR
//
////Default constructor
//StringTypeDescriptor::StringTypeDescriptor()
//{
//    //Initialize to an empty string
//    _ourString = "";
//}
//
////Parameterized constructors, note how we use the TypeDescriptor's constructor as well to help us set the private member variable only it can modify using it's constructor
//StringTypeDescriptor::StringTypeDescriptor(ourCustomEnumDatatype incomingDataType, std::string ourStringValue) : TypeDescriptor(incomingDataType)
//{
//    _ourString = ourStringValue;
//}
////In case we don't receive a value for our string but only receive a data type for our enum in our TypeDescriptor class to be set to
//StringTypeDescriptor::StringTypeDescriptor(ourCustomEnumDatatype incomingDataType) : TypeDescriptor(incomingDataType)
//{
//
//}
//
////Get the string value our StringTypeDescriptor has
//std::string StringTypeDescriptor::getStringValue() const
//{
//    return _ourString;
//}
////Set the string value for our StringTypeDescriptor
//void StringTypeDescriptor::setStringValue(std::string value)
//{
//    _ourString = value;
//}
//
////Overloading the + operator to handle the concatentation of the two strings two seperate StringTypeDescriptor instances/classes would have
////Returns a new StringTypeDescriptor pointer that will have the concatenated string
//TypeDescriptor* StringTypeDescriptor::operator + ( TypeDescriptor* other)
//{
//    std::string myTemporaryStringHolderToHoldConcatenatedString;
//    myTemporaryStringHolderToHoldConcatenatedString = this->getStringValue() + ((StringTypeDescriptor*)other)->getStringValue();
//
//    //Use the StringTypeDescriptor constructor to return a new instance of StringTypeDescriptor with the concatenated string. Going to go against some good programming rules here and not validate the datatype of a StringTypeDescriptor and assume if we are already dealing with adding two StringTypeDescriptor objects together we will obviously be dealing with a string datatype, and thus sending that to the constructor
//    //What are the double colons for? See scope resolution operator "::" to see why this works (we are referencing a different scope within TypeDescriptor)
//    return new StringTypeDescriptor(TypeDescriptor::STRING, myTemporaryStringHolderToHoldConcatenatedString);
//}
//


