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
    // 构造
    // =========================

    BigInt a;

    // 默认构造应该为 0
    assert(a.to_string() == "0");

    BigInt b("123456789");
    assert(b.to_string() == "123456789");

    // 前导零应该被 normalize
    BigInt c("0000012345");
    assert(c.to_string() == "12345");

    // 负数
    BigInt d("-00012345");
    assert(d.to_string() == "-12345");

    // -0 应该规范化为 0
    BigInt e("-0000");
    assert(e.to_string() == "0");


    // =========================
    // 赋值
    // =========================

    BigInt x;

    x = "123456789";
    assert(x.to_string() == "123456789");

    x = "-000999";
    assert(x.to_string() == "-999");

    x = "0";
    assert(x.to_string() == "0");


    // =========================
    // +
    // =========================

    {
        BigInt a("123");
        BigInt b("456");

        BigInt c = a + b;

        assert(c.to_string() == "579");
    }

    {
        BigInt a("-123");
        BigInt b("456");

        assert((a + b).to_string() == "333");
    }


    // =========================
    // -
    // =========================

    {
        BigInt a("456");
        BigInt b("123");

        assert((a - b).to_string() == "333");
    }

    {
        BigInt a("123");
        BigInt b("456");

        assert((a - b).to_string() == "-333");
    }


    // =========================
    // *
    // =========================

    {
        BigInt a("123456789");
        BigInt b("987654321");

        assert(
                (a * b).to_string()
                == "121932631112635269"
        );
    }

    {
        BigInt a("-123");
        BigInt b("-456");

        assert((a * b).to_string() == "56088");
    }


    // =========================
    // /
    // =========================

    {
        BigInt a("10");
        BigInt b("3");

        assert((a / b).to_string() == "3");
    }

    {
        BigInt a("-10");
        BigInt b("3");

        assert((a / b).to_string() == "-3");
    }


    // =========================
    // %
    // =========================

    {
        BigInt a("10");
        BigInt b("3");

        assert((a % b).to_string() == "1");
    }

    {
        BigInt a("-10");
        BigInt b("3");

        assert((a % b).to_string() == "-1");
    }


    // =========================
    // 连续运算
    // =========================

    {
        BigInt a("100");
        BigInt b("20");
        BigInt c("5");

        assert(((a + b) * c).to_string() == "600");
        assert(((a - b) / c).to_string() == "16");
    }


    // =========================
    // 除零
    // =========================

    {
        BigInt a("123");
        BigInt zero("0");

        bool caught = false;

        try {
            [[maybe_unused]] BigInt result = a / zero;
        } catch (const std::runtime_error&) {
            caught = true;
        }

        assert(caught);
    }

    {
        BigInt a("123");
        BigInt zero("0");

        bool caught = false;

        try {
            [[maybe_unused]] BigInt result = a % zero;
        } catch (const std::runtime_error&) {
            caught = true;
        }

        assert(caught);
    }


    // =========================
    // 非法输入
    // =========================

    {
        bool caught = false;

        try {
            BigInt invalid("");
        } catch (const std::runtime_error&) {
            caught = true;
        }

        assert(caught);
    }

    {
        bool caught = false;

        try {
            BigInt invalid("123abc");
        } catch (const std::runtime_error&) {
            caught = true;
        }

        assert(caught);
    }

    {
        bool caught = false;

        try {
            BigInt invalid("-");
        } catch (const std::runtime_error&) {
            caught = true;
        }

        assert(caught);
    }

    assert(BigInt("123") == BigInt("123"));
    assert(BigInt("123") != BigInt("456"));

    assert(BigInt("123") < BigInt("456"));
    assert(BigInt("456") > BigInt("123"));

    assert(BigInt("123") <= BigInt("123"));
    assert(BigInt("123") >= BigInt("123"));

    assert(BigInt("-123") < BigInt("123"));
    assert(BigInt("123") > BigInt("-123"));

    assert(BigInt("-456") < BigInt("-123"));
    assert(BigInt("-123") > BigInt("-456"));

    assert(BigInt("-123") <= BigInt("-123"));
    assert(BigInt("-123") >= BigInt("-123"));

    assert(BigInt("-100") < BigInt("-20"));
    assert(BigInt("-20") > BigInt("-100"));

    assert(BigInt("-1") < BigInt("0"));
    assert(BigInt("0") < BigInt("1"));

    assert(BigInt("-100000000000000000000")
           < BigInt("-99999999999999999999"));

    // =========================
    // 复合运算
    // =========================
    {
        BigInt a("100");
        BigInt b("30");

        a += b;
        assert(a.to_string() == "130");

        a -= b;
        assert(a.to_string() == "100");

        a *= b;
        assert(a.to_string() == "3000");

        a /= b;
        assert(a.to_string() == "100");

        a %= b;
        assert(a.to_string() == "10");
    }

    {
        BigInt a("10");
        BigInt b("20");

        (a += b) += b;

        assert(a.to_string() == "50");
    }

    std::cout << "BigInt_test passed!\n";

    return 0;
}