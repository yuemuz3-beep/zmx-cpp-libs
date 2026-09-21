#include "bigint.h"
#include <iostream>
#include <string>

using namespace std;
using namespace bigint;


// ==================== 测试工具 ====================

void test_add(const string& a, const string& b, const string& expected) {
    string result = add(a, b);

    cout << a << " + " << b
         << " = " << result;

    if (result == expected)
        cout << "  [PASS]\n";
    else
        cout << "  [FAIL]  expected: " << expected << '\n';
}


void test_sub(const string& a, const string& b, const string& expected) {
    string result = sub(a, b);

    cout << a << " - " << b
         << " = " << result;

    if (result == expected)
        cout << "  [PASS]\n";
    else
        cout << "  [FAIL]  expected: " << expected << '\n';
}


void test_mul(const string& a, const string& b, const string& expected) {
    string result = mul(a, b);

    cout << a << " * " << b
         << " = " << result;

    if (result == expected)
        cout << "  [PASS]\n";
    else
        cout << "  [FAIL]  expected: " << expected << '\n';
}


void test_div(const string& a,
              const string& b,
              const string& expected_q,
              const string& expected_r) {

    try {
        DivResult result = div_rem(a, b);

        cout << a << " / " << b
             << " = " << result.quotient
             << " ... " << result.remainder;

        if (result.quotient == expected_q &&
            result.remainder == expected_r) {
            cout << "  [PASS]\n";
        }
        else {
            cout << "  [FAIL]"
                 << "  expected: "
                 << expected_q << " ... " << expected_r
                 << '\n';
        }
    }
    catch (const exception& e) {
        cout << a << " / " << b
             << "  [EXCEPTION] "
             << e.what() << '\n';
    }
}


// ==================== 加法 ====================

void test_addition() {
    cout << "\n[Addition]\n";

    test_add("123", "456", "579");
    test_add("999", "1", "1000");
    test_add("0", "123", "123");

    // 同号
    test_add("-123", "-456", "-579");
    test_add("123", "456", "579");

    // 异号
    test_add("123", "-456", "-333");
    test_add("-123", "456", "333");

    // 结果为 0
    test_add("123", "-123", "0");
    test_add("-123", "123", "0");

    // 大数
    test_add(
            "123456789012345678901234567890",
            "987654321098765432109876543210",
            "1111111110111111111011111111100"
    );

    //加入非法测试
    test_add("123", "456","579");
    test_add("+00123", "000456","579");
    test_add("-00123", "+000456","333");
    test_add("-000", "+000","0");
}


// ==================== 减法 ====================

void test_subtraction() {
    cout << "\n[Subtraction]\n";

    test_sub("456", "123", "333");
    test_sub("1000", "1", "999");
    test_sub("123", "123", "0");

    // 结果为负数
    test_sub("123", "456", "-333");

    // 负数参与
    test_sub("-123", "456", "-579");
    test_sub("123", "-456", "579");
    test_sub("-123", "-456", "333");

    // 大数
    test_sub(
            "987654321098765432109876543210",
            "123456789012345678901234567890",
            "864197532086419753208641975320"
    );
}


// ==================== 乘法 ====================

void test_multiplication() {
    cout << "\n[Multiplication]\n";

    test_mul("123", "456", "56088");
    test_mul("999", "999", "998001");

    // 0
    test_mul("0", "123456789", "0");
    test_mul("-123456789", "0", "0");

    // 正负号
    test_mul("123", "-456", "-56088");
    test_mul("-123", "456", "-56088");
    test_mul("-123", "-456", "56088");

    // 1
    test_mul("123456789", "1", "123456789");
    test_mul("-123456789", "1", "-123456789");

    // 大数
    test_mul(
            "12345678901234567890",
            "98765432109876543210",
            "1219326311370217952237463801111263526900"
    );
}


// ==================== 除法 ====================

void test_division() {
    cout << "\n[Division]\n";

    // 基本情况
    test_div("100", "5", "20", "0");
    test_div("100", "3", "33", "1");
    test_div("3", "7", "0", "3");

    // 整除
    test_div("123", "123", "1", "0");
    test_div("999999", "9", "111111", "0");

    // 被除数为 0
    test_div("0", "123", "0", "0");

    // 被除数小于除数
    test_div("123", "123456789", "0", "123");

    // 大数
    test_div(
            "12345678901234567890",
            "123456789",
            "100000000010",
            "0"
    );

    // ==================== 负数 ====================

    // 负 / 正
    test_div("-100", "5", "-20", "0");
    test_div("-100", "3", "-33", "-1");
    test_div("-12345", "123", "-100", "-45");

    // 正 / 负
    test_div("100", "-5", "-20", "0");
    test_div("100", "-3", "-33", "1");
    test_div("12345", "-123", "-100", "45");

    // 负 / 负
    test_div("-100", "-5", "20", "0");
    test_div("-100", "-3", "33", "-1");
    test_div("-12345", "-123", "100", "-45");

    // 被除数绝对值小于除数
    test_div("-3", "7", "0", "-3");
    test_div("3", "-7", "0", "3");
    test_div("-3", "-7", "0", "-3");

    // 0 和负数
    test_div("0", "-123", "0", "0");
}

void test_div_dec_case(
        const std::string& s1,
        const std::string& s2,
        int p,
        const std::string& expected
) {
    std::string actual = div_dec(s1, s2, p);

    std::cout << s1 << " / " << s2
              << " (p=" << p << ") = "
              << actual;

    if (actual == expected) {
        std::cout << "  [PASS]\n";
    } else {
        std::cout << "  [FAIL]"
                  << "  expected: " << expected << '\n';
    }
}

void test_div_dec() {
    std::cout << "\n[Decimal Division]\n";

    test_div_dec_case("1", "2", 3, "0.500");
    test_div_dec_case("1", "8", 3, "0.125");
    test_div_dec_case("1", "3", 3, "0.333");
    test_div_dec_case("2", "3", 3, "0.667");

    // 四舍五入
    test_div_dec_case("1", "6", 3, "0.167");
    test_div_dec_case("1", "7", 4, "0.1429");

    // 不需要进位
    test_div_dec_case("123", "10", 3, "12.300");

    // 连续进位
    test_div_dec_case("99995", "10000", 3, "10.000");

    // p = 0
    test_div_dec_case("1", "2", 0, "1");
    test_div_dec_case("5", "2", 0, "3");
    test_div_dec_case("4", "2", 0, "2");

    // 负数
    test_div_dec_case("-1", "2", 3, "-0.500");
    test_div_dec_case("1", "-2", 3, "-0.500");
    test_div_dec_case("-1", "-2", 3, "0.500");

    // 0
    test_div_dec_case("0", "123456789", 5, "0.00000");
    test_div_dec_case("0", "-123456789", 5, "0.00000");

    // 大整数
    test_div_dec_case(
            "12345678901234567890",
            "7",
            5,
            "1763668414462081127.14286"
    );
}


// ==================== 主函数 ====================

int main() {

    test_addition();

    test_subtraction();

    test_multiplication();

    test_division();

    test_div_dec();

    return 0;
}