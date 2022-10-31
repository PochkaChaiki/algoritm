#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <unordered_map>

// Function to input value to a variable and to check if it fits the requirements of variable's type.
template <typename T>
bool valueInput(std::istream& in, T& checkingValue, char delim = '\n'){
    if (!(in>>checkingValue) || ((in.peek() != delim) && (in.peek()!= ' '))|| in.fail()){
        checkingValue = -1;
        in.clear();
        in.ignore(INT_MAX, delim);
        return false;
    } else {
        // If there is any delimeteres except for '\n' advance the input by one character.
        if (delim != '\n')
            in.rdbuf()->std::streambuf::sbumpc();
        return true;
    }
}

template <typename T, typename U>
using filter = bool (*) (T& object, U param);

template <typename T>
bool checkName(T& object, std::string name) {return (object.name.find(name) != std::string::npos);}

template <typename T, typename U>
std::vector<int> findObjectByParam(std::unordered_map<int, T>& objects, filter<T, U> f, U param){
    std::vector<int> result;
    for (auto& obj: objects)
        if (f(obj.second, param))
            result.push_back(obj.second.GetID());
    
    return result;
}


#endif