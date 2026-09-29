//
// Created by Lenovo on 2026/9/27.
//

#ifndef ZMX_CPP_LIBS_DECIMAL_H
#define ZMX_CPP_LIBS_DECIMAL_H

#endif //ZMX_CPP_LIBS_DECIMAL_H

#include<bigint.h>
#include<string>

namespace zmx{

    struct DecimalParts{
        BigInt value;
        int scale=0;
        bool negative=false;
    };

    class Decimal{
    private:
        BigInt value;
        int scale;
        bool negative;
    public:
        Decimal();
        Decimal(std::string s);
    };
}
