//
// Created by Lenovo on 2026/9/27.
//
#include "bigint.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace zmx;

int main() {
    // =========================
    // add
    // =========================

    assert(add("123", "456") == "579");
    assert(add("999", "1") == "1000");
    assert(add("-123", "456") == "333");
    assert(add("123", "-456") == "-333");
    assert(add("-123", "-456") == "-579");
    assert(add("0", "123") == "123");

    // 大数
    assert(add(
            "999999999999999999999999999999",
            "1"
    ) == "1000000000000000000000000000000");


    // =========================
    // sub
    // =========================

    assert(sub("456", "123") == "333");
    assert(sub("123", "456") == "-333");
    assert(sub("-123", "456") == "-579");
    assert(sub("123", "-456") == "579");
    assert(sub("-123", "-456") == "333");
    assert(sub("123", "123") == "0");


    // =========================
    // mul
    // =========================

    assert(mul("123", "456") == "56088");
    assert(mul("-123", "456") == "-56088");
    assert(mul("123", "-456") == "-56088");
    assert(mul("-123", "-456") == "56088");

    assert(mul("0", "123456789") == "0");
    assert(mul("1", "999999999") == "999999999");

    assert(mul(
            "999999999999999999",
            "999999999999999999"
    ) == "999999999999999998000000000000000001");


    // =========================
    // div_rem
    // =========================

    {
        auto result = div_rem("10", "3");

        assert(result.quotient == "3");
        assert(result.remainder == "1");
    }

    {
        auto result = div_rem("123456789", "100");

        assert(result.quotient == "1234567");
        assert(result.remainder == "89");
    }

    {
        auto result = div_rem("-10", "3");

        assert(result.quotient == "-3");
        assert(result.remainder == "-1");
    }

    {
        auto result = div_rem("10", "-3");

        assert(result.quotient == "-3");
        assert(result.remainder == "1");
    }

    {
        auto result = div_rem("-10", "-3");

        assert(result.quotient == "3");
        assert(result.remainder == "-1");
    }

    // 整除
    {
        auto result = div_rem("100", "10");

        assert(result.quotient == "10");
        assert(result.remainder == "0");
    }


    // =========================
    // div_decimal
    // =========================

    assert(div_decimal("1", "2", 6) == "0.500000");
    assert(div_decimal("1", "3", 6) == "0.333333");
    assert(div_decimal("10", "4", 2) == "2.50");

    // 四舍五入
    assert(div_decimal("1", "8", 2) == "0.13");

    // 负数
    assert(div_decimal("-1", "2", 3) == "-0.500");
    assert(div_decimal("1", "-2", 3) == "-0.500");
    assert(div_decimal("-1", "-2", 3) == "0.500");

    // p = 0
    assert(div_decimal("1", "2", 0) == "1");
    assert(div_decimal("9", "2", 0) == "5");

    // 零
    assert(div_decimal("0", "123456", 5) == "0.00000");


    // =========================
    // 异常
    // =========================

    bool caught = false;

    try {
        div_rem("123", "0");
    } catch (const std::runtime_error&) {
        caught = true;
    }

    assert(caught);

    caught = false;

    try {
        div_decimal("123", "0", 5);
    } catch (const std::runtime_error&) {
        caught = true;
    }

    assert(caught);


    std::cout << "algorithm_test passed!\n";

    return 0;
}