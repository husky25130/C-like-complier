#ifndef LEXANALYZER_H
#define LEXANALYZER_H

#pragma once

#include "complier.h"

class Lex_analyzer
{
private:
    list<Token> lex_res;
    ifstream lex_file;


    Status open_lexfile(string path);
    char get_char();
    Token get_token();
    //Token get_token(char c);


public:

    Lex_analyzer();
    Lex_analyzer(const char* path);     //grammar文件输入

    Status lex_analyze();
    Status lex_print();    //打印

    list<Token>& get_list();  //返回private的result列
    Status lex_txt();  //生成词法分析最终文件
    //char get_next();
    //int test();

    // ~Lex_analyzer();
};

#endif // LEXANALYZER_H
