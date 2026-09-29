#include "decimal.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace zmx;

namespace {

    DecimalParts normalize(std::string s) {
        DecimalParts result;
        int point_cnt = 0; // 小数点的个数
        size_t point_index = std::string::npos; // 小数点的下标

        if (s.empty())
            throw std::runtime_error("输入不能为空！");

        result.negative = (s[0] == '-');

        if (s[0] == '-' || s[0] == '+') {
            s = s.substr(1);
        }

        if (s.empty())
            throw std::runtime_error("符号后必须有数字！");

        for (size_t i = 0; i < s.size(); i++) {
            // 判断字符是否合法，同时寻找小数点
            if (s[i] >= '0' && s[i] <= '9') {
            }
            else if (s[i] == '.') {
                point_cnt++;
                point_index = i;
            }
            else {
                throw std::runtime_error("输入不合法！");
            }
        }

        if (point_cnt > 1) {
            throw std::runtime_error("不能有超过一个小数点");
        }
        else if (point_cnt == 1) {
            result.scale = static_cast<int>(s.size() - point_index - 1);

            // 删除小数点
            s.erase(point_index, 1);

            // 删除前导 0
            size_t pos = s.find_first_not_of('0');

            if (pos == std::string::npos) {
                result.value = "0";
                result.scale = 0;
                result.negative = false;
            }
            else {
                result.value = s.substr(pos);
            }
        }
        else {
            // 没有小数点
            size_t pos = s.find_first_not_of('0');

            if (pos == std::string::npos) {
                result.value = "0";
                result.scale = 0;
                result.negative = false;
            }
            else {
                result.value = s.substr(pos);
                result.scale = 0;
            }
        }

        return result;
    }

    bool check(
            const std::string& input,
            const std::string& expected_value,
            int expected_scale,
            bool expected_negative
    ) {
        try {
            DecimalParts result = normalize(input);

            bool ok =
                    result.value.to_string() == expected_value &&
                    result.scale == expected_scale &&
                    result.negative == expected_negative;

            if (!ok) {
                std::cout << "FAILED: " << input << '\n';
                std::cout << "  expected: "
                          << expected_value << ", "
                          << expected_scale << ", "
                          << expected_negative << '\n';
                std::cout << "  actual:   "
                          << result.value.to_string() << ", "
                          << result.scale << ", "
                          << result.negative << '\n';
            }

            return ok;
        }
        catch (const std::exception& e) {
            std::cout << "FAILED: " << input
                      << " unexpectedly threw: "
                      << e.what() << '\n';
            return false;
        }
    }

    bool check_invalid(const std::string& input) {
        try {
            normalize(input);

            std::cout << "FAILED: " << input
                      << " should throw an exception\n";

            return false;
        }
        catch (const std::exception&) {
            return true;
        }
    }

} // namespace


int main() {
    int passed = 0;
    int total = 0;

    // =========================
    // 合法输入
    // =========================

    total++;
    passed += check("123.45", "12345", 2, false);

    total++;
    passed += check("-123.45", "12345", 2, true);

    total++;
    passed += check("+123.45", "12345", 2, false);

    total++;
    passed += check("000123.4500", "1234500", 4, false);

    total++;
    passed += check("000.001", "1", 3, false);

    total++;
    passed += check("-000.001", "1", 3, true);

    total++;
    passed += check("000123", "123", 0, false);

    total++;
    passed += check("-000123", "123", 0, true);

    // .123
    total++;
    passed += check(".123", "123", 3, false);

    // 123.
    total++;
    passed += check("123.", "123", 0, false);

    // 0
    total++;
    passed += check("0", "0", 0, false);

    // -0 -> 0
    total++;
    passed += check("-0", "0", 0, false);

    // 000.000 -> 0
    total++;
    passed += check("000.000", "0", 0, false);

    // -000.000 -> 0
    total++;
    passed += check("-000.000", "0", 0, false);


    // =========================
    // 非法输入
    // =========================

    total++;
    passed += check_invalid("");

    total++;
    passed += check_invalid("-");

    total++;
    passed += check_invalid("+");

    total++;
    passed += check_invalid("12.34.56");

    total++;
    passed += check_invalid("12a34");

    total++;
    passed += check_invalid("12-34");

    total++;
    passed += check_invalid("1.2.3");

    total++;
    passed += check_invalid("--123");

    total++;
    passed += check_invalid("++123");


    // =========================
    // 测试结果
    // =========================

    std::cout << '\n'
              << passed << '/' << total
              << " tests passed!\n";

    return passed == total ? 0 : 1;
}