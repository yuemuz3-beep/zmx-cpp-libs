//
// Created by Lenovo on 2026/9/19.
//

#pragma once
#include <string>

namespace zmx {

    class BigInt{
    private:
        std::string value;
    public:
        BigInt();

        explicit BigInt(std::string s);

        [[nodiscard]] std::string to_string() const;

        //赋值
        BigInt& operator=(const std::string& s);

        //基础运算
        BigInt operator+(const BigInt& other)const;

        BigInt operator-(const BigInt& other)const;

        BigInt operator*(const BigInt& other)const;

        BigInt operator/(const BigInt& other)const;

        BigInt operator%(const BigInt& other)const;

        //比较运算
        bool operator==(const BigInt& other)const;

        bool operator<(const BigInt& other)const;

        bool operator!=(const BigInt& other)const;

        bool operator>(const BigInt& other)const;

        bool operator<=(const BigInt& other)const;

        bool operator>=(const BigInt& other)const;

        //复合运算
        BigInt& operator+=(const BigInt& other);

        BigInt& operator-=(const BigInt& other);

        BigInt& operator*=(const BigInt& other);

        BigInt& operator/=(const BigInt& other);

        BigInt& operator%=(const BigInt& other);

    };

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
    std::string div_decimal(std::string s1,std::string s2,int p=6);
//    DivResult div_rem(const std::string& s,long long n);
    DivResult div_rem(std::string s1,std::string s2);


}// namespace zmx

