//
// Created by Lenovo on 2026/9/19.
//

#pragma once
#include <string>

namespace bigint {

    struct DivResult {
        std::string quotient;
        std::string remainder;
    };


    std::string add(std::string s1,std::string s2);
    std::string sub(std::string s1,std::string s2);
//    std::string mul(const std::string& s,long long n);
    std::string mul(std::string s1,std::string s2);
//    std::string div_dec(long long n1,long long n2,int p);
//    std::string div_dec(const std::string& s,long long n,int p);
    std::string div_dec(std::string s1,std::string s2,int p);
//    DivResult div_rem(const std::string& s,long long n);
    DivResult div_rem(std::string s1,std::string s2);


}// namespace bigint

