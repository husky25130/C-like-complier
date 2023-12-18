#include "complier.h"

bool isNum(char c)
{
    return (c >= '0' && c <= '9') ? true : false;
}

bool isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ? true : false;
}

bool isVt(string str)
{
    return str == "int" || str=="float" || str == "void" || str == "if" || str == "else" || str == "while" || str == "return" || str == "ID" || str == "num" || str=="floating"
        || str == ">" || str == "<" || str == ">=" || str == "<=" || str == "==" || str == "!="
        || str == "," || str == ";" || str == "+" || str == "-" || str == "*" || str == "/" || str == "="
        || str == "(" || str == ")" || str == "{" || str == "}" || str == "#";

}

// 转换Token中的First项，便于输出
string ttostr(Token t)
{
    const char words[33][10] = {
        // 关键字 int void if else while return float
        "INT", "VOID", "IF", "ELSE", "WHILE", "RETURN", "FLOAT",
        // identifier
        "ID",
        // 整数  浮点数
        "NUM", "FLOATING",
        // 赋值
        "ASSIGN",
        // 算符 +  -      *    /    ==      >   >=   <   <=   !=
        "PLUS", "MINUS", "MUL", "DIV", "EQUAL", "GT", "GTE", "LT", "LTE", "NE",
        // ;
        "SEMICOLON",
        // 分隔符  ,
        "COMMA",
        // 注释 /*      */         //        /* */
        "LPCOMMENT", "RPCOMMENT", "LCOMMENT", "PCOMMENT",
        // 括号 (      )
        "LBRACKET", "RBRACKET",
        // 大括号  {    }
        "LBRACE", "RBRACE",
        // 换行 \n
        "NEXTL",
        // 结束符
        "ENDFILE"
    };

    string str = words[t.first];

    return str;
}

list<int> merge(list<int> l1, list<int> l2)
{
    list<int> l;
    l.assign(l1.begin(), l1.end());
    l.splice(l.end(), l2);
    return l;
}
