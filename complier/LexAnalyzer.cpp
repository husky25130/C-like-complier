#include "LexAnalyzer.h"

// 打开文件
Status Lex_analyzer::open_lexfile(string path)
{
    lex_file.open(path, ios::in|ios::binary);
    if (!lex_file.is_open())
    {
        cerr << "打开输入文件" << path << "失败" << endl;
        exit(ERROR);
    }
    return OK;
}

// 初始化分析器，打开对应的输入文件
Lex_analyzer::Lex_analyzer()
{
    open_lexfile("code_file.txt");
}

Lex_analyzer::Lex_analyzer(const char* path)
{
    open_lexfile(path);
}





// 拿到一个字符
char Lex_analyzer::get_char()
{
    char tempChar;
    //cout << lex_file.tellg() << "** \n";
    while (tempChar = lex_file.get())
    {
        if (tempChar == ' ' || tempChar == '\t')
            continue;
        break;
    }
    if (lex_file.eof())
        return ENDINPUT;

    return tempChar;
}

/***********************
*

* 函数名：get_token
* 函数功能：分析代码中的词语，得到一个二元组。
* 变量意义：无变量
* 返回值：一个二元组（一个关键词和对应的权重）
*
************************/
Token Lex_analyzer::get_token()
{
    char c = get_char();
    //cout << "^^" << c << endl;
    if (c == '(')
        return Token(LBRACKET, "(");
    else if (c == ')')
        return Token(RBRACKET, ")");
    else if (c == '{')
        return Token(LBRACE, "{");
    else if (c == '}')
        return Token(RBRACE, "}");
    else if (c == '+')
        return Token(PLUS, "+");
    else if (c == '-')
        return Token(MINUS, "-");
    else if (c == '*')
        return Token(MUL, "*");
    else if (c == ';')
        return Token(SEMICOLON, ";");
    else if (c == ',')
        return Token(COMMA, ",");
    else if (c == '/')
    {
        // 单行注释
        if (lex_file.peek() == '/')
        {
            char t_str[MAXLINECNT];
            t_str[0] = '/';
            lex_file.getline(t_str + 1, MAXLINECNT, '\n');
            return Token(LCOMMENT, t_str);
        }
        /* 多行注释 */
        else if (lex_file.peek() == '*')
        {
            lex_file.get();
            string t_str = "/*";
            while (lex_file >> c)
            {
                t_str += c;
                if (c == '*')
                {
                    if (lex_file.peek() == '/')
                    {
                        lex_file >> c;
                        t_str += c;
                        return Token(PCOMMENT, t_str);
                    }
                    else
                        continue;
                }
            }
            // 正常情况下不会执行到这里，执行到这里说明匹配不到*/
            cerr << "匹配不到*/" << endl;
            exit(ERROR);
        }
        // 除法
        else
        {
            return Token(DIV, "/");
        }
    }
    else if (c == '=')
    {
        if (lex_file.peek() == '=')
        {
            lex_file.get();
            return Token(EQUAL, "==");
        }
        else
            return Token(ASSIGN, "=");
    }
    else if (c == '>')
    {
        if (lex_file.peek() == '=')
        {
            lex_file.get();
            return Token(GTE, ">=");
        }
        else
            return Token(GT, ">");
    }
    else if (c == '<')
    {
        if (lex_file.peek() == '=')
        {
            lex_file.get();
            return Token(LTE, "<=");
        }
        else
            return Token(LT, "<");
    }
    else if (c == '!')
    {
        if (lex_file.peek() == '=')
        {
            lex_file.get();
            return Token(NE, "!=");
        }
        else
        {
            cerr << "这是一个取否符号，不符合我们的简单类C语法规则" << endl;
            exit(ERROR);
        }
    }
    else if (c == '#')
        return Token(ENDFILE, "#");
    else if (c == '\n')
        return Token(NEXTL, "\\n");
    // 进入到这里，说明是字母或数字或乱码（乱码就错了，else判断掉）
    else
    {
        if (isNum(c))
        {
            string t_str;
            t_str += c;
            int tFlag = 0;

            size_t pos;   //记录文件的读取
            while (!lex_file.eof())
            {
                char next = lex_file.get();

                if (!isNum(next))
                { //下一个不是数字，判断是否是浮点数
                    if (next == '.')
                    {//是浮点数
                        t_str += next;
                        while (!lex_file.eof())
                        {
                            if(!lex_file.eof())
                            next = lex_file.get();

                            //cout << t_str << endl;
                            if (!isNum(next))
                            {//浮点数下一个不是数字，需要退回
                                lex_file.clear();
                                pos = lex_file.tellg();
                                //cout << pos;
                                lex_file.seekg(pos-1, ios::beg);//输入文件指针回退,因为多读了next
                                pos = lex_file.tellg();
                                //cout << pos;
                                //cout << lex_file.get() << "&" << endl;
                                //lex_file.peek();

                                //lex_res.push_back(Token(FLOATING, t_str));
                                //string tmp_next(1, next);
                                //return Token(SEMICOLON, tmp_next);
                                //lex_res.push_back();


                                return Token(FLOATING, t_str);
                            }
                            t_str += next;
                        }
                    }
                    else
                    {//不是浮点数，需要退回
                        lex_file.clear();
                        pos = lex_file.tellg();
                        cout << pos;
                        lex_file.seekg(pos - 1, ios::beg);//输入文件指针回退,因为多读了next
                        pos = lex_file.tellg();
                        cout << pos;
                        string tmp_next(1, next);

                        if (next == '\n')
                            ;
                        break;

                    }
                }
                else  //下一个还是数字，继续循环
                    t_str += next;
            }


            /*lex_res.push_back(Token(NUM, t_str));
            return Token(SEMICOLON, ";");*/

            return Token(NUM, t_str);
        }
        else if (isAlpha(c))
        {
            string t_str;
            t_str += c;
            while (1)
            {
                char tempCh = lex_file.peek();
                if (isAlpha(tempCh) || isNum(tempCh))
                {
                    lex_file.get();
                    t_str += tempCh;
                }
                // 说明已经读到了这个标识符/关键字以外的东西了
                else
                    break;
            }
            if (t_str == "int")
                return Token(INT, t_str);
            else if (t_str == "void")
                return Token(VOID, t_str);
            else if (t_str == "if")
                return Token(IF, t_str);
            else if (t_str == "else")
                return Token(ELSE, t_str);
            else if (t_str == "while")
                return Token(WHILE, t_str);
            else if (t_str == "return")
                return Token(RETURN, t_str);
            else if (t_str == "float")
                return Token(FLOAT, t_str);
            else
                return Token(ID, t_str);
        }
        else
        {
            cerr << "无法判断的符号"  << c << endl;
            exit(ERROR);
        }
    }

    // 整个大判断的外面，但是这显然是不可能的，随便写一下
    cerr << "未知错误" << endl;
    exit(ERROR);
}

//char Lex_analyzer::Get_Next() {
//	char ch;
//	ch = lex_file.get();
//
//	if (ch == '\n')//换行
//		line++;
//	return ch;
//}

// 分析过程
Status Lex_analyzer::lex_analyze()
{
    while (1)
    {
        Token tempToken = get_token();
        lex_res.push_back(tempToken);
        if (tempToken.first == ENDFILE)
            break;
    }
    return OK;
}

// 输出到控制台
Status Lex_analyzer::lex_print()
{
    list <Token>::iterator resultIterator;
    for (resultIterator = lex_res.begin(); resultIterator != lex_res.end(); resultIterator++)
    {
        cout << '<' << ttostr(*resultIterator) << ',' << resultIterator->second << '>' << endl;
    }
    return OK;
}

list<Token>& Lex_analyzer::get_list()
{
    return lex_res;
}

// 输出到文件
Status Lex_analyzer::lex_txt()
{
    ofstream out;
    out.open("Lex_print.txt", ios::out);
    if (!out.is_open())
    {
        cerr << "打开输出文件Lex_print.txt失败" << endl;
        exit(-1);
    }
    list <Token>::iterator resultIterator;
    for (resultIterator = lex_res.begin(); resultIterator != lex_res.end(); resultIterator++)
    {
        out << '<' << ttostr(*resultIterator) << ',' << resultIterator->second << '>' << endl;
    }

    out.close();
    return OK;
}
