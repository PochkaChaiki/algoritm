#include <iostream>
#include <sstream>
#include <string>


int main(){
    int x;
    std::string s;
    std::cin >> s;
    std::stringstream ss (s);

    if (!(ss >> x) || (!ss.eof())){
        std::cout<<"FUCK"<<std::endl;
    }

    return 0;
}