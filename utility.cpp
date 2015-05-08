#include <iostream>
#include <sstream>
#include <string>
#include "../StanfordCPPLib/error.h"

int str2int(std::string s)
{
    std::istringstream iss(s);
    int res;
    iss >> res >> std::ws;
    if (iss.eof()){
        return res;
    }else{
        error("INVALID NUMBER");
    }
}

int input_int()
{
    while(true){
        std::string s;
        std::cout << " ? ";  //prompt
        std::getline(std::cin, s);
        try{
            return str2int(s);
        }catch(...){
            std::cout << "INVALID NUMBER" << std::endl;
        }
    }
}

