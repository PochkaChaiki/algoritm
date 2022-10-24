#ifndef UTILS_H
#define UTILS_H

#include <iostream>

template <typename T>
bool valueInput(std::istream& in, T& checkingValue, char delim = '\n'){
    if (!(in>>checkingValue) || ((in.peek() != delim) && (in.peek()!= ' '))|| in.fail()){
        checkingValue = -1;
        in.clear();
        in.ignore(INT_MAX, delim);
        return false;
    } else {
        if (delim == ',')
            std::cout<<"bumping character: "<<in.rdbuf()->std::streambuf::sbumpc()<<std::endl;
        return true;
    }
}

#endif