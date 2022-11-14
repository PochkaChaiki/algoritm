#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <type_traits>



// template <typename T>
// class VarType {
// public:
//     T type;
// };





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

// Function same to valueInput(), but checks if the input value fits in allowed limits
template <typename T>
T GetRightValue(std::istream& in, T min, T max){
    T checkingValue;
    while (!valueInput(in, checkingValue) || (checkingValue < min) || (checkingValue > max)){
        std::cout<<"INPUT ERROR: Invalid value. Try again."<<std::endl;
    }
    return checkingValue;
}

template <typename T, typename U>
using filter = bool (*) (T& object, U param);

template <typename T>
bool checkName(T& object, std::string name) {return (object.name.find(name) != std::string::npos);}

template <typename T, typename U>
std::unordered_set<int> findObjectByParam(std::unordered_map<int, T>& objects, filter<T, U> f, U param){
    std::unordered_set<int> result;
    for (auto& obj: objects)
        if (f(obj.second, param))
            result.insert(obj.second.GetID());
    
    return result;
}

// template <typename T>
// void getObjectsToEdit(std::unordered_map<int, T>, std::unordered_set<int> resultSet){
    
// }

#endif