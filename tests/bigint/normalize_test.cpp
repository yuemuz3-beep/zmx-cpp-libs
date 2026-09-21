//
// Created by Lenovo on 2026/9/20.
//
#include<iostream>
#include <string>
#include <stdexcept>

std::string normalize(std::string s){
    if(s.empty())throw std::runtime_error("输入不能为空！");
    bool is_neg=(s[0]=='-');
    if(s[0]=='-'||s[0]=='+') {
        s=s.substr(1);
    }
    if(s.empty())throw std::runtime_error("符号后必须有数字！");
    for(char i : s){
        if(i>='0'&&i<='9'){}
        else throw std::runtime_error("输入不合法！");
    }
    size_t pos=s.find_first_not_of('0');
    if(pos==std::string::npos)s="0";
    else s=s.substr(pos);
    if(is_neg&&s!="0")s='-'+s;
    return s;
}

int main() {
    std::string tests[] = {
            "123",
            "+123",
            "-123",
            "00123",
            "+00123",
            "-00123",
            "000",
            "+000",
            "-000",
            "",
            "+",
            "-",
            "12a3",
            "1.23",
            "--123",
            "+-123"
    };

    int i=0;
    for (const auto& s : tests) {
        i++;
        std::cout << "第" << i << "组测试：";

        try {
            std::string result = normalize(s);
            std::cout << "\"" << s << "\" -> "
                      << "\"" << result << "\"\n";
        }
        catch (const std::exception& e) {
            std::cout << "\"" << s << "\" -> 错误："
                      << e.what() << '\n';
        }
    }
}
