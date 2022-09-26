#ifndef COMPANY_H
#define COMPANY_H

#define INT_TYPE (int)1
#define DOUBLE_TYPE (double)1.0

#include <iostream>
#include <sstream>
#include <string>

template <typename T>
T checkInput(std::istream& in, T checkingValue){
    std::string input;
    in >> input;
    std::stringstream inputStream(input);
    if (in.fail() || !(inputStream >> checkingValue) || !inputStream.eof()){
            // std::cout<<"INPUT ERROR: Invalid value. Try again."<<std::endl;
            in.clear();
            in.ignore(INT_MAX, '\n');
            return -1;
    } else {
        return checkingValue;
    }
}

#endif