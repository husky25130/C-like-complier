#ifndef COMPLIER_H
#define COMPLIER_H


#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <set>
#include <sstream>
#include <fstream>


#include <vector>
#include <stack>
#include <map>
#include <list>
#include <queue>

#include <qstring.h>

using namespace std;


// 函数返回状态
typedef int Status;
const int ERROR = -1;
const int OK = 0;

const int ENDINPUT = -2;


// 一些定义
const int MAXLINECNT = 1024;
const int MAXCOMMENTCNT = 2048;    //读取最大长度


// 词法分析种类
typedef enum
{
// 关键字 int void if else while return float
    INT, VOID, IF, ELSE, WHILE, RETURN, FLOAT,
// 标识符(变量名)
    ID,
// 整数和浮点数
    NUM, FLOATING,
// 赋值 =
    ASSIGN,
// 算符  +  -      *    /    ==      >   >=   <   <=   !=
    PLUS, MINUS, MUL, DIV, EQUAL, GT, GTE, LT, LTE, NE,
// //
    SEMICOLON,
// 分隔符 ,
    COMMA,
// 注释符  /*      */         //        /* */
    LPCOMMENT, RPCOMMENT, LCOMMENT, PCOMMENT,
// 括号 (      )
    LBRACKET, RBRACKET,
// 大括号 {    }
    LBRACE, RBRACE,
// 换行  \n
    NEXTL,
// 结束符
    ENDFILE
} LexType;

// 词法二元组
typedef pair<LexType, string> Token;

// 一些简单的函数定义
bool isNum(char c);
bool isAlpha(char c);
bool isVt(string s);
string ttostr(Token t);    //token to string
list<int> merge(list<int> l1, list<int> l2);

#endif // COMPLIER_H
