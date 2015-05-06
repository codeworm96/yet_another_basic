#include <iostream>
#include <sstream>
#include <string>

int input_int()
{
    while(true){
        std::string s;
        std::cout << " ? ";  //prompt
        std::getline(std::cin, s);
        std::istringstream iss(s);
        int res;
        iss >> res >> std::ws;
        if (iss.eof()){
            return res;
        }
        std::cout << "INVALID NUMBER" << std::endl;
    }
}

