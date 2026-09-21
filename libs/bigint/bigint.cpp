//
// Created by Lenovo on 2026/9/19.
//
#include "bigint.h"
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <vector>
namespace {
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
    int cmp_abs(const std::string& us1,const std::string& us2){
        if( us1.size()>us2.size()
        || (us1.size() == us2.size() && us1>us2))return 1;
        else if(us1==us2)return 0;
        else return -1;
    }
    std::string add_abs(const std::string& us1,const std::string& us2) {
        std::string ans;
        //计算us1+us2
        std::vector<int> a(us1.size());
        std::vector<int> b(us2.size());
        for(int i=0;i<us1.size();i++){
            a[i]=us1[us1.size()-i-1]-'0';
        }
        for(int i=0;i<us2.size();i++){
            b[i]=us2[us2.size()-i-1]-'0';
        }

        int len=int(std::max(us1.size(),us2.size()));
        std::vector<int> c(len+1);
        for(int i=0;i<len;i++){
            int x = i < a.size() ? a[i] : 0;
            int y = i < b.size() ? b[i] : 0;
            c[i]=x+y;
        }
        for(int i=0;i<len;i++){
            if(c[i]>=10){
                c[i+1]+=c[i]/10;
                c[i]%=10;
            }
        }
        if(c[len]!=0)len++;
        for(int i=len-1;i>=0;i--){
            ans+=char(c[i]+'0');
        }
        return ans;
    }
    // 要求 us1 >= us2，且 us1、us2 均为无符号数字字符串
    std::string sub_abs(const std::string& us1,const std::string& us2){
        std::string ans;
        //计算us1-us2
        std::vector<int> a(us1.size());
        std::vector<int> b(us2.size());
        for(int i=0;i<us1.size();i++){
            a[i]=us1[us1.size()-i-1]-'0';
        }
        for(int i=0;i<us2.size();i++){
            b[i]=us2[us2.size()-i-1]-'0';
        }
        int len=(int)a.size();
        std::vector<int> c(len);
        for(int i=0;i<len;i++){
            int y = i < b.size() ? b[i] : 0;
            if(a[i]<y){
                a[i]+=10;
                a[i+1]--;
            }
            c[i]=a[i]-y;
        }
        while (c.size() > 1 && c.back() == 0)
            c.pop_back();
        for(int i=(int)c.size()-1;i>=0;i--){
            ans+=char(c[i]+'0');
        }
        return ans;
    }
}
namespace bigint{

    //有符号高精度加法
    std::string add(std::string s1,std::string s2){
        //加入处理字符串的异常情况
        s1 = normalize(s1);
        s2 = normalize(s2);

        std::string ans;
        std::string us1=s1;
        std::string us2=s2;
        //判断正负号
        bool is_neg_s1=s1[0]=='-';
        bool is_neg_s2=s2[0]=='-';
        if(is_neg_s1)us1=s1.substr(1);
        if(is_neg_s2)us2=s2.substr(1);
        if (!is_neg_s1 && !is_neg_s2) {
            // 正 + 正
            ans=add_abs(us1,us2);
        }
        else if (is_neg_s1 && is_neg_s2) {
            // 负 + 负
            ans+='-';
            ans+=add_abs(us1,us2);
        }
        else {
            if (us1 == us2) {
                return "0";
            }

            //异号相加
            bool us2Big = cmp_abs(us1,us2)<0;

            if (us2Big) {
                // s2 的符号决定结果符号
                if (is_neg_s2)
                    ans = '-' + ans;

                // |s2| > |s1|
                ans += sub_abs(us2, us1);
            }
            else {
                // s1 的符号决定结果符号
                if (is_neg_s1)
                    ans = '-' + ans;

                // |s1| >= |s2|
                ans += sub_abs(us1, us2);
            }
        }
        return ans;
    }
    //有符号高精度减法
    std::string sub(std::string s1,std::string s2){
        //加入处理字符串为异常情况
        s1 = normalize(s1);
        s2 = normalize(s2);

        std::string ns2;
        if(s2[0]=='-'){
            ns2=s2.substr(1);
        }
        else{
            ns2='-'+s2;
        }
        return add(s1,ns2);
    }
    //有符号高精度乘法
    std::string mul(std::string s1,std::string s2){
        //加入处理字符串为空的异常情况
        s1 = normalize(s1);
        s2 = normalize(s2);

        std::string ans;
        std::string us1=s1;
        std::string us2=s2;
        //判断符号
        bool is_neg_s1 = s1[0] == '-';
        bool is_neg_s2 = s2[0] == '-';
        bool is_neg = is_neg_s1 != is_neg_s2;
        if(is_neg_s1)us1=s1.substr(1);
        if(is_neg_s2)us2=s2.substr(1);

        //关于0的特殊判定
        if (us1 == "0" || us2 == "0")
            return "0";

        std::vector<int> a(us1.size());
        std::vector<int> b(us2.size());
        for(int i=0;i<us1.size();i++){
            a[i]=us1[us1.size()-i-1]-'0';
        }
        for(int i=0;i<us2.size();i++){
            b[i]=us2[us2.size()-i-1]-'0';
        }

        std::vector<int> c(us1.size()+us2.size());
        for(int i=0;i<us1.size();i++){
            for(int j=0;j<us2.size();j++){
                c[i+j]+=a[i]*b[j];
            }
        }
        for(int i=0;i<c.size()-1;i++){
            if(c[i]>=10){
                c[i+1]+=c[i]/10;
                c[i]%=10;
            }
        }
        while(c.size()>1&&c.back()==0){
            c.pop_back();
        }

        for(int i=(int)c.size()-1;i>=0;i--){
            ans+=char(c[i]+'0');
        }
        ans=is_neg?'-'+ans:ans;
        return ans;
    }

    //有符号高精度除法带余数
    DivResult div_rem(std::string s1,std::string s2){
        //加入处理字符串为空的异常情况
        s1 = normalize(s1);
        s2 = normalize(s2);

        DivResult ans;
        std::string us1=s1;
        std::string us2=s2;
        //判断符号
        bool is_neg_s1 = s1[0] == '-';
        bool is_neg_s2 = s2[0] == '-';
        bool is_neg = is_neg_s1 != is_neg_s2;
        if(is_neg_s1)us1=s1.substr(1);
        if(is_neg_s2)us2=s2.substr(1);

        if (us2 == "0") {
            throw std::runtime_error("除数不能为0！");
        }

        for(auto item:us1){
            if(ans.remainder == "0")
                ans.remainder = std::string(1, item);
            else
                ans.remainder += item;
            int n=0;
            while(cmp_abs(ans.remainder,us2)>=0){
                ans.remainder=sub_abs(ans.remainder,us2);
                n++;
            }
            ans.quotient+=char('0'+n);
        }

        size_t pos=ans.quotient.find_first_not_of('0');
        if(pos==std::string::npos){
            ans.quotient="0";
        }else {
            ans.quotient=ans.quotient.substr(pos);
        }

        if(ans.quotient!="0" && is_neg)
            ans.quotient='-'+ans.quotient;
        if(ans.remainder!="0" && is_neg_s1)
            ans.remainder='-'+ans.remainder;

        return ans;
    }

    //有符号除法高精度求商保留p位小数
    std::string div_dec(std::string s1,std::string s2,int p){
        //加入处理字符串为空的异常情况
        s1 = normalize(s1);
        s2 = normalize(s2);

        std::string ans;
        std::string r;
        std::string us1=s1;
        std::string us2=s2;
        //判断符号
        bool is_neg_s1 = s1[0] == '-';
        bool is_neg_s2 = s2[0] == '-';
        bool is_neg = is_neg_s1 != is_neg_s2;
        if(is_neg_s1||s1[0]=='+')us1=s1.substr(1);
        if(is_neg_s2||s2[0]=='+')us2=s2.substr(1);

        if (us2 == "0") {
            throw std::runtime_error("除数不能为0！");
        }
        if(us1 == "0")
            return std::string("0.") + std::string(p, '0');

        //整数部分
        for(auto item:us1){
            if(r == "0")
                r = std::string(1, item);
            else
                r += item;
            int n=0;
            while(cmp_abs(r,us2)>=0){
                r=sub_abs(r,us2);
                n++;
            }
            ans+=char('0'+n);
        }
        //去除前导0
        size_t pos = ans.find_first_not_of('0');

        if(pos == std::string::npos){
            ans = "0";
        }else{
            ans = ans.substr(pos);
        }
        //小数部分
        if(p>0){
            ans+='.';
            for(int i=0;i<p;i++){
                if(r == "0"){
                    ans += '0';
                    continue;
                }
                else
                    r += '0';
                int n=0;
                while(cmp_abs(r,us2)>=0){
                    r=sub_abs(r,us2);
                    n++;
                }
                ans+=char('0'+n);
            }
        }
        //四舍五入
        int np=0;
        if(r == "0"){
            np=0;
        }
        else
            r += '0';
        while(cmp_abs(r,us2)>=0){
            r=sub_abs(r,us2);
            np++;
        }
        if(np>=5){
            int i=(int)ans.size()-1;
            while(i>=0){
                if(ans[i]=='.'){i--;continue;}
                if(ans[i]=='9'){
                    ans[i]='0';
                    i--;
                }else{
                    ans[i]++;
                    break;
                }
            }
            if(i<0)ans='1'+ans;
        }

        ans=is_neg?'-'+ans:ans;
        return ans;
    }

/*
    std::string mul(const std::string& s,long long n){//高精度乘单精度
        if (n == 0 || s == "0" || s == "-0") return "0";
        bool is_neg = (s[0]=='-')^(n<0);
        std::string us=s[0]=='-'?s.substr(1):s;
        long long un=llabs(n);
        std::string ans;
        long long a[MAX]={0};
        long long temp=un;
        long long b=un;
        int len_b=0;
        while(temp){
            len_b++;
            temp/=10;
        }
        for(int i=0;i<us.size();i++){
            a[us.size()-i-1]=us[i]-'0';
        }

        for(int i=0;i<us.size();i++){
            a[i]*=b;
        }

        for(int i=0;i<us.size()+len_b;i++){
            if(a[i]>=10){
                a[i+1]+=a[i]/10;
                a[i]%=10;
            }
        }

        int index=0;
        for(int i=int(us.size()+len_b-1);i>=0;i--){
            if(a[i]!=0){
                index=i;
                break;
            }
        }
        if(is_neg)ans+='-';
        for(int i=index;i>=0;i--){
            ans+=char('0'+a[i]);
        }
        return ans;
    }


    std::string mul(const std::string& s1,const std::string& s2){//高精度乘高精度
        if (s1== "0" || s1== "-0" || s2== "0" || s2== "-0") return "0";
        bool is_neg_s1=s1[0]=='-';
        bool is_neg_s2=s2[0]=='-';
        bool is_neg =is_neg_s1^is_neg_s2;
        std::string us1=is_neg_s1?s1.substr(1):s1;
        std::string us2=is_neg_s2?s2.substr(1):s2;
        std::string ans;
        int a1[MAX]={0},a2[MAX]={0},a3[2*MAX]={0};
        //逆序
        for(int i=0;i<us1.size();i++){
            a1[i]=us1[us1.size()-i-1]-'0';
        }
        for(int i=0;i<us2.size();i++){
            a2[i]=us2[us2.size()-i-1]-'0';
        }

        //模拟计算
        for(int i=0;i<us2.size();i++){
            for(int j=0;j<us1.size();j++){
                a3[j+i]+=a1[j]*a2[i];
                if(a3[j+i]>=10){
                    a3[j+i+1]+=a3[j+i]/10;
                    a3[j+i]%=10;
                }
            }
        }

        int index=0;
        for(int i=int(us1.size()+us2.size()-1);i>=0;i--){
            if(a3[i]!=0){
                index=i;
                break;
            }
        }
        if(is_neg)ans+='-';
        for(int i=index;i>=0;i--){
            ans+=char('0'+a3[i]);
        }
        return ans;
    }
//单精度除以单精度得高精度商
    std::string div_dec(long long n1,long long n2,int p){//a是被除数，b是除数，n是保留n位小数
        std::string ans;
        if (n2 == 0) {
            throw std::runtime_error("除数不能为0！");
        }
        //判断符号
        bool is_neg =(n1<0)^(n2<0);//异或，一正一负时为true
        if(n1==0)is_neg=false;

        //取绝对值
        //abs(INT_MIN) 溢出问题：int 的最小值是 -2147483648，
        //而最大值是 2147483647。对 INT_MIN 取绝对值会导致溢出（依然是负数）。
        //建议在函数内部把类型提升为 long long。
        long long ua = llabs(n1);
        long long ub = llabs(n2);

        long long temp=ua/ub;
        if (temp == 0) ans = "0";
        while(temp){//计算整数部分
            ans+=char('0'+temp%10);
            temp/=10;
        }
        reverse(ans.begin(), ans.end());

        temp = ua % ub;
        if(p>0) {
            ans += '.';
            for (int i = 0; i < p; i++) {//计算小数部分
                temp *= 10;
                ans += char('0' + temp / ub);
                temp %= ub;
            }
        }

        temp *= 10;
        int next_digit = int(temp / ub);
        if(next_digit>=5){
            int i=int(ans.size()-1);
            while(i>=0){
                if(ans[i]=='.'){i--;continue;}
                if(ans[i]=='9'){
                    ans[i]='0';
                    i--;
                }else{
                    ans[i]++;
                    break;
                }
            }
            if(i<0)ans='1'+ans;
        }

        if(is_neg)ans='-'+ans;
        return ans;
    }

//高精度被除数除以单精度得商和余数
    DivResult div_rem(const std::string& s,long long n){
        if (n == 0) {
            throw std::runtime_error("除数不能为0！");
        }
        DivResult ans;
        long long temp=0;
        for(auto& ch:s){
            temp=temp*10+int(ch-'0');
            ans.quotient+=char(temp/n+'0');
            temp%=n;
        }
        ans.remainder=temp;
        size_t pos = ans.quotient.find_first_not_of('0');
        if (pos == std::string::npos) {
            ans.quotient = "0";
        } else {
            ans.quotient = ans.quotient.substr(pos);
        }
        return ans;
    }
//高精度被除数除以单精度得高精度商
    std::string div_dec(const std::string& s,long long n,int p){
        if (n == 0) {
            throw std::runtime_error("除数不能为0！");
        }
        bool is_neg_s=s[0]=='-';
        bool is_neg_b=n<0;
        bool is_neg=is_neg_s^is_neg_b;
        std::string us=is_neg_s?s.substr(1):s;
        long long ub=llabs(n);

        std::string ans;
        long long temp=0;
        for(auto& ch:us){
            temp=temp*10+int(ch-'0');
            ans+=char(temp/ub+'0');
            temp%=ub;
        }
        size_t pos = ans.find_first_not_of('0');
        if (pos == std::string::npos) ans = "0";
        else ans = ans.substr(pos);
        if(p>0){
            ans+='.';
            for (int i = 0; i < p; i++) {
                temp *= 10;
                ans += char('0' + temp / ub);
                temp %= ub;
            }
        }
        temp *= 10;
        int next_digit = int(temp / ub);
        if(next_digit>=5){
            int i=int(ans.size()-1);
            while(i>=0){
                if(ans[i]=='.'){i--;continue;}
                if(ans[i]=='9'){
                    ans[i]='0';
                    i--;
                }else{
                    ans[i]++;
                    break;
                }
            }
            if(i<0)ans.insert(0,1,'1');
        }

        if (is_neg) {
            bool all_zero = true;
            for (char c : ans) {
                if (c != '0' && c != '.') { all_zero = false; break; }
            }
            if (!all_zero) ans.insert(0, 1, '-');
        }
        return ans;
    }
    */

}//namespace bigint