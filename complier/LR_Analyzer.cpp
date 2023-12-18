#include "SynAnalyzer.h"
/***********************
*
* 函数名：LR_Analyzer
* 函数功能：LR语法分析，利用两个栈对词法表。
* 变量意义：list<Token> LexRes 词法token表
* 返回值：(Status)int 判断分析正确还是错误
*
************************/
Status Syn_analyzer::LRAnalyse(list<Token> LexRes)
{
    SymbolStack.push(Symbol("#", true));
    StatusStack.push(0);

    int cnt = 0;

    int T_temp = 0;

    line = 0;
    level = 0;

    list<Token>::iterator itToken = LexRes.begin();
    while (itToken != LexRes.end())
    {
        this->Stack_print(cnt);
        this->Stack_statustxt(cnt);
        this->Stack_symboltxt(cnt);
        cnt++;

        // 如果读到注释，就继续
        if (itToken->first == LCOMMENT || itToken->first == LPCOMMENT || itToken->first == RPCOMMENT || itToken->first == PCOMMENT)
        {
            itToken++;
            continue;
        }

        if (itToken->first == NEXTL)
        {
            itToken++;
            line++;
            continue;
        }

        //if (itToken->first == ENDFILE)
        //	break;

        Symbol next;
        if (itToken->first == ID)
            next = Symbol("ID", true, itToken->second);
        else if (itToken->first == NUM)
            next = Symbol("num", true, itToken->second);
        else if(itToken->first == FLOATING)
            next = Symbol("floating", true, itToken->second);
        else
            next = Symbol(itToken->second, true);

        Motivation statement = Action_tb[GOTO(StatusStack.top(), next)];
        //cout <<;
        // 开始LR分析，利用两个栈
        if (statement.cur_state == shift) // 若为移进
        {
            SymbolStack.push(next);
            StatusStack.push(statement.nextS);
            itToken++;
            continue;
        }

        else if (statement.cur_state == reduct) // 若为归约
        {
            Production p = Productions[statement.nextS];
            int popNum = p.rcontent.size();

            Symbol Symbolpushed = p.lcontent;

            // 弹出阶段，顺便产生一下中间代码
            if (statement.nextS == 0) // P ::= N declare_list
            {
                Symbol _declare_list = pop();
                Symbol _N = pop();
             
                // 首先我们这里的N用于定义函数调用间的关系，找到函数出口
                // 这里由于我们不需要考虑子函数的过程调用，因此我觉得似乎不需要这里的N，修改产生式
                // 这里修改产生式为P ::= declare_list

            }
            else if (statement.nextS == 1) // declare_list ::= declare declare_list
            {
                Symbol _declare_list = pop();
                Symbol _declare = pop();
            }
            else if (statement.nextS == 2) // declare_list ::= declare
            {
                Symbol _declare = pop();
            }
            else if (statement.nextS == 3) // declare ::= int ID M A function_declare
            {
                Symbol _function_declare = pop();
                Symbol _A = pop();
                Symbol _M = pop();
                Symbol _ID = pop();
                Symbol _int = pop();

                // 加入function表当中
                func_tb.push_back(Function(_ID.name, Vint, _function_declare.parType, _M.quad));
            }
            else if (statement.nextS == 4) // declare ::= int ID var_declare
            {
                Symbol _var_declare = pop();
                Symbol _ID = pop();
                Symbol _int = pop();

                // 加入variable表当中
                var_tb.push_back(Variable(_ID.name, Vint, level));
            }

            else if (statement.nextS == 5) // declare ::= int ID M A function_declare
            {
                Symbol _function_declare = pop();
                Symbol _A = pop();
                Symbol _M = pop();
                Symbol _ID = pop();
                Symbol _float = pop();

                // 加入function表当中
                func_tb.push_back(Function(_ID.name, Vfloat, _function_declare.parType, _M.quad));
            }
            else if (statement.nextS == 6) // declare ::= int ID var_declare
            {
                Symbol _var_declare = pop();
                Symbol _ID = pop();
                Symbol _float = pop();

                // 加入variable表当中
                var_tb.push_back(Variable(_ID.name, Vfloat, level));
            }
            else if (statement.nextS == 7) // declare ::= void ID M A function_declare
            {
                Symbol _function_declare = pop();
                Symbol _A = pop();
                Symbol _M = pop();
                Symbol _ID = pop();
                Symbol _void = pop();

                // 加入function表当中
                func_tb.push_back(Function(_ID.name, Vvoid, _function_declare.parType, _M.quad));
            }


            else if (statement.nextS == 8) // A ::=
            {
                level++;
            }
            else if (statement.nextS == 9) // var_declare ::= ;
            {
                Symbol _semicolon = pop();
            }
            else if (statement.nextS == 10) // function_declare ::= ( parameter ) sentence_block
            {
                Symbol _sectence_block = pop();
                Symbol _rbracket = pop();
                Symbol _parameter = pop();
                Symbol _lbracket = pop();
                // 函数
                Symbolpushed.parType.assign(_parameter.parType.begin(), _parameter.parType.end());
            }
            else if (statement.nextS == 11) // parameter ::= parameter_list
            {
                Symbol _parameter_list = pop();
                // 函数
                Symbolpushed.parType.assign(_parameter_list.parType.begin(), _parameter_list.parType.end());
            }
            else if (statement.nextS == 12) // parameter ::=
            {
                // 函数
            }
            else if (statement.nextS == 13) // parameter_list :: = param
            {
                Symbol _param = pop();
                // 函数
                Symbolpushed.parType.push_back(Vint);
            }
            else if (statement.nextS == 14) // parameter_list ::= param , parameter_list
            {
                Symbol _parameter_list = pop();
                Symbol _comma = pop();
                Symbol _param = pop();
                // 函数
                _parameter_list.parType.push_front(Vint);
                Symbolpushed.parType.assign(_parameter_list.parType.begin(), _parameter_list.parType.end());
            }
            else if (statement.nextS == 15) // param ::= int ID
            {
                Symbol _ID = pop();
                Symbol _int = pop();
                var_tb.push_back(Variable(_ID.name, Vint, level));
                //code.emit(Quaternion("get", "_", "_", _ID.name));
            }
            else if (statement.nextS == 16) // param ::= int ID
            {
            Symbol _ID = pop();
            Symbol _float = pop();
            var_tb.push_back(Variable(_ID.name, Vfloat, level));
            //code.emit(Quaternion("get", "_", "_", _ID.name));
            }

            // 这个地方需要注意局部变量的销毁
            else if (statement.nextS == 17) // sentence_block ::= { inner_declare sentence_list }
            {
                Symbol _rbrace = pop();
                Symbol _sentence_list = pop();
                Symbol _inner_declare = pop();
                Symbol _lbrace = pop();
                Symbolpushed.nextlist = _sentence_list.nextlist;

                // 局部变量的销毁
                level--; // 首先当前层级需要做减法
                int delNum = 0;
                for (vector<Variable>::reverse_iterator r = var_tb.rbegin(); r != var_tb.rend(); r++) {
                    if (r->depth > level) {
                        delNum++;
                        continue;
                    }
                    break; // 检查到不属于这个层级的就直接退出去
                }
                for (int cnt = 0; cnt < delNum; cnt++) {
                    var_tb.pop_back();

                }
            }
            else if (statement.nextS == 18) // inner_declare ::=
            {

            }
            else if (statement.nextS == 19) // inner_declare ::= inner_var_declare ; inner_declare
            {
                Symbol _inner_declare = pop();
                Symbol _semicolon = pop();
                Symbol _inner_var_decalre = pop();
            }
            else if (statement.nextS == 20) // inner_var_declare ::= int ID
            {
                Symbol _ID = pop();
                Symbol _int = pop();
                var_tb.push_back(Variable(_ID.name, Vint, level));
            }
            else if (statement.nextS == 21) // inner_var_declare ::= int ID
            {
            Symbol _ID = pop();
            Symbol _float = pop();
            var_tb.push_back(Variable(_ID.name, Vfloat, level));
            }

            else if (statement.nextS == 22) // sentence_list ::= sentence M sentence_list
            {
                Symbol _sentence_list = pop();
                Symbol _M = pop();
                Symbol _sentence = pop();
                Symbolpushed.nextlist = _sentence_list.nextlist;

            }
            else if (statement.nextS == 23) // sentence_list :: = sentence
            {
                Symbol _sentence = pop();
                Symbolpushed.nextlist = _sentence.nextlist;
            }
            else if (statement.nextS == 24) // sentence ::= if_sentence
            {
                Symbol _if_sentence = pop();
                Symbolpushed.nextlist = _if_sentence.nextlist;
            }
            else if (statement.nextS == 25) // sentence ::= while_sentence
            {
                Symbol _while_sentence = pop();
                Symbolpushed.nextlist = _while_sentence.nextlist;
            }
            else if (statement.nextS == 26) // sentence ::= return_sentence
            {
                Symbol _return_sentence = pop();
            }
            else if (statement.nextS == 27) // sentence ::= assign_sentence
            {
                Symbol _assign_sentence = pop();
            }
            else if (statement.nextS == 28) // assign_sentence ::= ID = expression ;
            {
                Symbol _semicolon = pop();
                Symbol _expression = pop();
                Symbol _assign = pop();
                Symbol _ID = pop();


                Variable* v = findVariable(_ID.name);
                if (!v) {
                    cerr << "语法错误，第" << line << "行未声明的变量: " << _ID.name << endl;
                    exit(-1);
                }
            }
            else if (statement.nextS == 29) // return_sentence ::= return ;
            {
                Symbol _semicolon = pop();
                Symbol _return = pop();

            }
            else if (statement.nextS == 30) // return_sentence ::= return expression ;
            {
                Symbol _semicolon = pop();
                Symbol _expression = pop();
                Symbol _return = pop();

            }
            else if (statement.nextS == 31) // while_sentence ::= while M ( expression ) A sentence_block
            {
                Symbol _sentence_block = pop();
                Symbol _A = pop();
                Symbol _rbracket = pop();
                Symbol _expression = pop();
                Symbol _lbracket = pop();
                Symbol _M = pop();
                Symbol _while = pop();

                Symbolpushed.nextlist = _expression.falselist;

            }
            else if (statement.nextS == 32) // if_sentence ::= if ( expression ) A sentence_block
            {
                Symbol _sentence_block = pop();
                Symbol _A = pop();
                Symbol _rbracket = pop();
                Symbol _expression = pop();
                Symbol _lbracket = pop();
                Symbol _if = pop();
                _expression.falselist.splice(_expression.falselist.begin(), _sentence_block.nextlist);
                Symbolpushed.nextlist = _expression.falselist;
            }
            else if (statement.nextS == 33) // if_sentence ::= if ( expression ) A sentence_block N else M A sentence_block
            {
                Symbol _sentence_block1 = pop();
                Symbol _A1 = pop();
                Symbol _M = pop();
                Symbol _else = pop();
                Symbol _N = pop();
                Symbol _sentence_block2 = pop();
                Symbol _A2 = pop();
                Symbol _rbracket = pop();
                Symbol _expression = pop();
                Symbol _lbracket = pop();
                Symbol _if = pop();

                Symbolpushed.nextlist = merge(_sentence_block2.nextlist, _sentence_block1.nextlist);
                Symbolpushed.nextlist = merge(Symbolpushed.nextlist, _N.nextlist);
            }
            else if (statement.nextS == 34) // N ::=
            {
                ;
            }
            else if (statement.nextS == 35) // M ::=
            {
                ;
            }
            else if (statement.nextS == 36) // expression ::= add_expression
            {
                Symbol _add_expressio = pop();
                Symbolpushed.name = _add_expressio.name;
            }
            else if (statement.nextS == 37) // expression ::= add_expression > add_expression
            {
                Symbol _add_expressio1 = pop();
                Symbol _gt = pop();
                Symbol _add_expressio2 = pop();

            }
            else if (statement.nextS == 38) // expression ::= add_expression < add_expression
            {
                Symbol _add_expressio1 = pop();
                Symbol _lt = pop();
                Symbol _add_expressio2 = pop();

            }
            else if (statement.nextS == 39) // expression ::= add_expression == add_expression
            {
                Symbol _add_expressio1 = pop();
                Symbol _equal = pop();
                Symbol _add_expressio2 = pop();

            }
            else if (statement.nextS == 40) // expression ::= add_expression >= add_expression
            {
                Symbol _add_expressio1 = pop();
                Symbol _gte = pop();
                Symbol _add_expressio2 = pop();

            }
            else if (statement.nextS == 41) // expression ::= add_expression <= add_expression
            {
                Symbol _add_expressio1 = pop();
                Symbol _lte = pop();
                Symbol _add_expressio2 = pop();

            }
            else if (statement.nextS == 42) // expression ::= add_expression != add_expression
            {
                Symbol _add_expressio1 = pop();
                Symbol _ne = pop();
                Symbol _add_expressio2 = pop();

            }
            else if (statement.nextS == 43) // add_expression ::= item
            {
                Symbol _item = pop();
                Symbolpushed.name = _item.name;
            }
            else if (statement.nextS == 44) // add_expression ::= item + add_expression
            {
                Symbol _add_expressio = pop();
                Symbol _plus = pop();
                Symbol _item = pop();
                Symbolpushed.name = "T" + to_string(T_temp);
                T_temp++;

            }
            else if (statement.nextS == 45) // add_expression ::= item - add_expression
            {
                Symbol _add_expressio = pop();
                Symbol _minus = pop();
                Symbol _item = pop();
                Symbolpushed.name = "T" + to_string(T_temp);
                T_temp++;

            }
            else if (statement.nextS == 46) // item ::= factor
            {
                Symbol _factor = pop();
                Symbolpushed.name = _factor.name;
            }
            else if (statement.nextS == 47) // item ::= factor * item
            {
                Symbol _item = pop();
                Symbol _mul = pop();
                Symbol _factor = pop();
                Symbolpushed.name = "T" + to_string(T_temp);
                T_temp++;

            }
            else if (statement.nextS == 48) // item ::= factor / item
            {
                Symbol _item = pop();
                Symbol _div = pop();
                Symbol _factor = pop();
                Symbolpushed.name = "T" + to_string(T_temp);
                T_temp++;

            }
            else if (statement.nextS == 49) // factor ::= num
            {
                Symbol _num = pop();
                Symbolpushed.name = _num.name;

            }
            else if (statement.nextS == 50) // factor ::= ( expression )
            {
                Symbol _rbracket = pop();
                Symbol _expression = pop();
                Symbol _lbracket = pop();
                Symbolpushed.name = _expression.name;
            }
            else if (statement.nextS == 51) // factor ::= ID ( argument_list )
            {
                Symbol _rbracket = pop();
                Symbol _argument_list = pop();
                Symbol _lbracket = pop();
                Symbol _ID = pop();
                // 函数

                Function* Func = findFunction(_ID.name);
                if (!Func) {
                    cerr << "语法错误，第" << line << "行未声明的函数: " << _ID.name << endl;
                    exit(-1);
                }
                else {

                    Symbolpushed.name = "T" + to_string(T_temp);
                    T_temp++;

                }
            }
            else if (statement.nextS == 52) // factor ::= ID
            {
                Symbol _ID = pop();
                Symbolpushed.name = _ID.name;
                Variable* v = findVariable(_ID.name);
                if (!v) {
                    cerr << "语法错误，第" << line << "行未声明的变量: " << _ID.name << endl;
                    exit(-1);
                }
            }
            else if (statement.nextS == 53) // argument_list ::=
            {
                // 函数
            }
            else if (statement.nextS == 54) // argument_list ::= expression
            {
                Symbol _expression = pop();
                // 函数
                Symbolpushed.par.push_back(_expression.name);
            }
            else if (statement.nextS == 55) // argument_list ::= expression , argument_list
            {
                Symbol _argument_list = pop();
                Symbol _comma = pop();
                Symbol _expression = pop();
                // 函数
                _argument_list.par.push_front(_expression.name);
                Symbolpushed.par.assign(_argument_list.par.begin(), _argument_list.par.end());
            }

            else if (statement.nextS == 56) // factor ::= floating
            {
                Symbol _floating = pop();
                Symbolpushed.name = _floating.name;

            }
            else
            {
                // 弹出对应栈顶元素popNum个
                for (int cnt = 0; cnt < popNum; cnt++)
                {
                    SymbolStack.pop();
                    StatusStack.pop();
                }

            }

            // 压入对应的Goto表中的状态，归约式的左端
            SymbolStack.push(Symbolpushed);
            StatusStack.push(Goto_tb[GOTO(StatusStack.top(), p.lcontent)]);
        }

        // P :: = N declare_list
        else if (statement.cur_state == accept) // 接受
        {
            Function* f = findFunction("main");
            if (!f)
            {
                cout << "语法错误，缺少main函数" << endl;
                exit(-1);
            }
            Symbol _declare_list = pop();
            Symbol _N = pop();
            cout << "accept!" << endl;
            cout << "成功归约出目标结果，程序结束" << endl;

            break;
        }

        else // error
        {
            cout << "归约过程出现错误，已跳出，请检查你的输入程序，栈断点值已经保留在Stack_print.txt中" << endl;
            break;
        }

    }

    return OK;
}
