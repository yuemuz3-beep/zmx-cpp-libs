#include "decimal.h"
#include<bigint.h>
#include <stdexcept>
#include <utility>

namespace {
    zmx::DecimalParts normalize(std::string s){
        zmx::DecimalParts result;
        size_t point_index=std::string::npos;//小数点的下标

        if(s.empty())throw std::runtime_error("输入不能为空！");
        result.negative=(s[0]=='-');
        if(s[0]=='-'||s[0]=='+') {
            s=s.substr(1);
        }
        if(s.empty())throw std::runtime_error("符号后必须有数字！");
        for(size_t i=0;i<s.size();i++){//寻找小数点与判断字符合法性
            if(s[i]>='0'&&s[i]<='9'){}
            else if(s[i]=='.'){
                if (point_index != std::string::npos) {
                    throw std::runtime_error("不能有超过一个小数点");
                }
                point_index=i;
            }
            else throw std::runtime_error("输入不合法！");
        }

        if(point_index != std::string::npos){
            result.scale=int(s.size()-point_index-1);//将小数点的下标转化成scale信息
            s=s.erase(point_index,1);

            size_t pos=s.find_first_not_of('0');
            if(pos==std::string::npos){
                result.value="0";
                result.scale=0;
                result.negative=false;
            }
            else result.value=s.substr(pos);
        }
        else{
            size_t pos=s.find_first_not_of('0');
            if(pos==std::string::npos){
                result.value="0";
                result.scale=0;
                result.negative=false;
            }else{
                result.value=s.substr(pos);
                result.scale=0;
            }
        }
        return result;
    }

}

namespace zmx {

    Decimal::Decimal()
    :value("0"),scale(0),negative(false){
    }
    Decimal::Decimal(std::string s){
        auto result=normalize(std::move(s));
        value=result.value;
        scale=result.scale;
        negative=result.negative;
    }

}



