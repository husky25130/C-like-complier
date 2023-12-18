#include "SynAnalyzer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


/***************
一些类的初始化
****************/
Symbol::Symbol(string content, bool Vt)
{
    this->content = content;
    this->Vt = Vt;
}

Symbol::Symbol(string content, bool Vt, string name)
{
    this->content = content;
    this->Vt = Vt;
    this->name = name;
}

Symbol::Symbol()
{
    // 这里啥也不做
}

SymbolID::SymbolID(Symbol s, string name) : Symbol(s)
{
    idName = name;
}

SymbolNum::SymbolNum(Symbol s, string num) : Symbol(s)
{
    numName = num;
}

Production::Production()
{
    ;
}

Motivation::Motivation()
{
    ;
}

Item::Item(int my_pos, Symbol my_expect, int idPro)
{
    this->my_pos = my_pos;
    this->my_expect = my_expect;
    this->my_id = idPro;
}

Motivation::Motivation(ACT cur_state, int S)
{
    this->cur_state = cur_state;
    this->nextS = S;
}




/***************

   读取语法规则

****************/
Status Syn_analyzer::open_synfile(string path)
{
    inputProductions.open(path, ios::in | ios::binary);
    if (!inputProductions.is_open())
    {
        cerr << "打开输入文件" << path << "失败" << endl;
        exit(ERROR);
    }
    return OK;
}

Syn_analyzer::Syn_analyzer()
{
    open_synfile("inputProductions.txt");
}

Syn_analyzer::Syn_analyzer(string path)
{
    open_synfile(path);
}




// 读产生式
Status Syn_analyzer::get_production()
{
    int id = 0;
    string tempString;

    // 不断的读产生式
    while (inputProductions >> tempString)
    {
        //cout << tempString << ' ';/////////////
        Production tempProduction;
        tempProduction.id = id;
        tempProduction.lcontent = Symbol(tempString, false);
        inputProductions >> tempString; // 读掉assign语句

        //cout << tempString <<' ';////////////////

        char temp[MAXLINECNT];
        inputProductions.getline(temp, MAXLINECNT, '\n');

        //cout << temp << endl;////////////////

        stringstream s(temp);
        while (s >> tempString)
        {
            //cout << tempString << endl;
            tempProduction.rcontent.push_back(Symbol(tempString, isVt(tempString)));
        }
        //cout << tempString << endl;
        Productions.push_back(tempProduction); // 放回项目组当中
        id++;
    }

    return OK;
}

// 输出读到的产生式（test）
Status Syn_analyzer::show_production()
{
    cout << setw(10) << "ID" << setw(20) << "LEFT" << setw(10) << "   " << "RIGHT" << endl;
    vector<Production>::iterator itProduction;
    for (itProduction = Productions.begin(); itProduction != Productions.end(); itProduction++)
    {
        cout << setw(10) << itProduction->id << "   " << setw(20) << itProduction->lcontent.content << "   ";
        vector<Symbol>::iterator itSymbol;
        for (itSymbol = itProduction->rcontent.begin(); itSymbol != itProduction->rcontent.end(); itSymbol++)
            cout << itSymbol->content << ' ';
        cout << endl;
    }
    return OK;
}

Status Syn_analyzer::production_print()
{
    ofstream out;
    out.open("Production_print.txt", ios::out);
    if (!out.is_open())
    {
        cerr << "打开输出文件Production_print.txt失败" << endl;
        exit(-1);
    }

    out << setw(10) << "ID" << setw(20) << "LEFT" << setw(10) << "   " << "RIGHT" << endl;
    vector<Production>::iterator itProduction;
    for (itProduction = Productions.begin(); itProduction != Productions.end(); itProduction++)
    {
        out << setw(10) << itProduction->id << "   " << setw(20) << itProduction->lcontent.content << "   ";
        vector<Symbol>::iterator itSymbol;
        for (itSymbol = itProduction->rcontent.begin(); itSymbol != itProduction->rcontent.end(); itSymbol++)
            out << itSymbol->content << ' ';
        out << endl;
    }
    return OK;
}



/***********************
*
* 函数名：init_First
* 函数功能：这里需要遍历每个项目的每个Symbol，找First集
*（右部符号是终结符，将其加入，若起始符号有空，继续遍历后面的符号，看看要不要加入left的first；若没有空集合(eps)，完成加入这个右部符号后，直接结束遍历该项目的右部符号，转入下一个项目(break)）。
* 变量意义：无
* 返回值：(Status)int 判断分析正确还是错误
*
************************/
Status Syn_analyzer::init_First()
{
    bool isAddFirst = false;

    First[Symbol("#", true)].insert(Symbol("#", true)); // 这里将#加入

    // 这里，重复这样的过程直至First集合不发生变化
    while (1)
    {
        isAddFirst = false;
        // 这里需要遍历每个项目的每个Symbol

        vector<Production>::iterator itProduction;
        for (itProduction = Productions.begin(); itProduction != Productions.end(); itProduction++)
        {
            vector<Symbol>::iterator itSymbol;
            for (itSymbol = itProduction->rcontent.begin(); itSymbol != itProduction->rcontent.end(); itSymbol++)
            {
                /*
                 *如果这里的右部符号是终结符，将其加入，直接结束遍历该项目的右部符号即可(break)
                 */
                if (isVt(itSymbol->content) == true)
                {
                    if (First[itProduction->lcontent].insert(*itSymbol).second == true)
                        isAddFirst = true;
                    break;
                }

                /*
                 * 如果这里的右部符号是非终结符，需要分类
                 * 若起始符号有空集合(eps)，继续遍历后面的符号，看看要不要加入left的first
                 * 若没有空集合(eps)，完成加入这个右部符号后，直接结束遍历该项目的右部符号，转入下一个项目(break)
                 */
                else
                {
                    bool isEps = false;
                    set<Symbol>::iterator itFirst;

                    // 遍历一个右部符号的first集合
                    for (itFirst = First[*itSymbol].begin(); itFirst != First[*itSymbol].end(); itFirst++)
                    {
                        if (itFirst->content == "EPS")
                        {
                            isEps = true;
                        }
                        else // 这里else是为了不加入空集合(eps)
                        {
                            if (First[itProduction->lcontent].insert(*itFirst).second == true)
                                isAddFirst = true;
                        }
                    }

                    // 如果没有空集合(eps)，那么就不需要继续遍历右部符号串
                    if (isEps == false)
                        break;
                }


            } // end of 遍历项目

            // 如果这里，在这个项目能够遍历到最后一个符号，则说明需要加入空集合(eps)作为该左部符号的First集合
            if (itSymbol == itProduction->rcontent.end())
            {
                if (First[itProduction->lcontent].insert(Symbol("EPS", true)).second == true)
                    isAddFirst = true;
            }

        }// end of 遍历产生式

        // 如果First集不变，就跳出while
        if (!isAddFirst)
            break;
    }// end of while

    return OK;
}


Status Syn_analyzer::First_print()
{
    map<Symbol, set<Symbol>>::iterator itFirst;
    for (itFirst = First.begin(); itFirst != First.end(); itFirst++)
    {
        cout << itFirst->first.content << "的First集合为{";
        set<Symbol>::iterator itSet;
        for (itSet = itFirst->second.begin(); itSet != itFirst->second.end(); itSet++)
            cout << itSet->content << ' ';
        cout << "}" << endl;
    }
    return OK;
}


Status Syn_analyzer::First_txt()
{
    ofstream out;
    out.open("First_print.txt", ios::out);
    if (!out.is_open())
    {
        cerr << "打开输出文件First_print.txt失败" << endl;
        exit(-1);
    }

    map<Symbol, set<Symbol>>::iterator itFirst;
    for (itFirst = First.begin(); itFirst != First.end(); itFirst++)
    {
        out << setw(20) << itFirst->first.content << "的FIRST集为：";
        set<Symbol>::iterator itSet;
        for (itSet = itFirst->second.begin(); itSet != itFirst->second.end(); itSet++)
            out << itSet->content << ' ';
        out << endl;
    }

    out.close();
    return OK;
}






/***********************
*
* 函数名：get_expect
* 函数功能：展望过程，如果右部符号是终结符，将其加入；若起始符号有空集合(eps)，继续遍历后面的符号，看看要不要加入left的first；若没有空集合(eps)，完成加入这个右部符号后，直接结束遍历该项目的右部符号，转入下一个项目(break)。
* 变量意义：list<Symbol> S 符号串
* 返回值：set<Symbol> 返回符号集合
*
************************/
set<Symbol> Syn_analyzer::get_expect(list<Symbol> S)
{
    set<Symbol> retSet;
    bool isAddFirst = false;

    while (1)
    {
        isAddFirst = false;
        list<Symbol>::iterator itList;
        for (itList = S.begin(); itList != S.end(); itList++)
        {
            /*
             * 如果这里的右部符号是终结符，将其加入，直接结束遍历该项目的右部符号即可(break)
             */
            if (isVt(itList->content) == true)
            {
                if (retSet.insert(*itList).second == true)
                    isAddFirst = true;
                break;
            }

            /*
             * 如果这里的右部符号是非终结符，需要分类
             * 若起始符号有空集合(eps)，继续遍历后面的符号，看看要不要加入left的first
             * 若没有空集合(eps)，完成加入这个右部符号后，直接结束遍历该项目的右部符号，转入下一个项目(break)
             */
            else
            {
                bool isEps = false;
                set<Symbol>::iterator itFirst;

                // 遍历一个右部符号的first集合
                for (itFirst = First[*itList].begin(); itFirst != First[*itList].end(); itFirst++)
                {
                    if (itFirst->content == "EPS")
                    {
                        isEps = true;
                    }
                    else // 这里else是为了不加入空集合(eps)
                    {
                        if (retSet.insert(*itFirst).second == true)
                            isAddFirst = true;
                    }
                }

                // 如果没有空集合(eps)，那么就不需要继续遍历右部符号串
                if (isEps == false)
                    break;
            }
        }// end of 遍历展望串
        // 如果这里，在这个项目能够遍历到最后一个符号，则说明需要加入空集合(eps)作为该左部符号的First集合
        if (itList == S.end())
        {
            if (retSet.insert(Symbol("EPS", true)).second == true)
                isAddFirst = true;
        }

        // 如果First集不变，就跳出while
        if (!isAddFirst)
            break;
    }// end of while

    return retSet;
}


/***********************
*
* 函数名：create_Closure
* 函数功能：找到一个状态产生一个状态集合（求闭包的过程）。
* 变量意义：Item item  状态集合
* 返回值：set_Item 返回状态集的列表
*
************************/

set_Item Syn_analyzer::create_Closure(Item item)
{
    set_Item ret;

    // 如果是规约项目
    // 如果点后面是终结符
    if (item.my_pos == Productions[item.my_id].rcontent.size() || isVt(Productions[item.my_id].rcontent[item.my_pos].content))
    {
        ret.Items.insert(item);
    }
    // 点后面是非终结符
    else
    {
        ret.Items.insert(item);
        vector<Production>::iterator itProduction;
        for (itProduction = Productions.begin(); itProduction != Productions.end(); itProduction++)
        {
            if (itProduction->lcontent == Productions[item.my_id].rcontent[item.my_pos])
            {
                // 这里需要将找到的产生式都加入set_Item，但是这里需要求一下展望符
                list<Symbol> SymList; 

                // 可能size会有问题
                // 将右边的产生式依次放入SymList，作为获得展望串的入口参数
                for (int cnt = 1; item.my_pos + cnt < (int)(Productions[item.my_id].rcontent.size()); cnt++)
                {
                    SymList.push_back(Productions[item.my_id].rcontent[item.my_pos + cnt]);
                }
                SymList.push_back(item.my_expect); //记得放a

                set<Symbol> retSet; //获得的展望串
                retSet = get_expect(SymList);

                // 将这些展望符依次加入set_Item（ret）中
                set<Symbol>::iterator itSymbol;
                for (itSymbol = retSet.begin(); itSymbol != retSet.end(); itSymbol++)
                {
                    set_Item temp = create_Closure(Item(0, *itSymbol, itProduction->id));

                    set<Item>::iterator itItem;
                    for (itItem = temp.Items.begin(); itItem != temp.Items.end(); itItem++)
                    {
                        if (ret.Items.insert(*itItem).second == 0)
                        {
                            ;
                        }

                    }
                }
            }
        }
    }

    return ret;
}



/***********************
*
* 函数名：create_DFA
* 函数功能：通过状态集创建DFA图。
* 变量意义：无
* 返回值：Status(函数分析正确与否)
*
************************/
Status Syn_analyzer::create_DFA()
{
    cout << "创建文法的LR(1)表中，请稍候（可能会很慢^ _ ^）" << endl;

    // 首先先新建好I0状态，从I0状态出发，去看别的状态
    set_Item itemp = create_Closure(Item(0, Symbol("#", true), 0));
    DFA.status.push_back(itemp);

    int idSNow = 0;
    // 遍历每一个状态的每一个项目
    //
    list<set_Item>::iterator itStatus;
    for (itStatus = DFA.status.begin(); itStatus != DFA.status.end(); itStatus++, idSNow++)
    {
        set<Item>::iterator itItem;
        int cnt = 0;
        for (itItem = itStatus->Items.begin(), cnt = 0; itItem != itStatus->Items.end(); itItem++, cnt++)
        {
            // 若为规约项目（点在最后）
            if (Productions[itItem->my_id].rcontent.size() == itItem->my_pos)
            {
                GOTO tempGOTO(idSNow, itItem->my_expect);
                if (itItem->my_id == 0) // 用第一个拓广文法规约
                {
                    Action_tb[tempGOTO] = Motivation(accept, itItem->my_id);
                }
                else
                {
                    Action_tb[tempGOTO] = Motivation(reduct, itItem->my_id);
                }
            }
            // 若为移进项目 或者 读到了非终结符号
            else
            {
                // 取出点后面的符号
                Symbol nextSymbol = Productions[itItem->my_id].rcontent[itItem->my_pos];

                // 先判断是否已经有之前的项目找过了对应的nextSymbol的状态，如果有就直接去找别的项目
                if (DFA.gotos.count(GOTO(idSNow, nextSymbol)) == 1)
                    continue;

                // 否则就产生新状态
                set_Item StatusNew = create_Closure(Item(itItem->my_pos + 1, itItem->my_expect, itItem->my_id));

                // 这里需要看一眼下面的项目的nextSymbol是不是也是一样的，如果是，把那个项目的闭包同样加入新状态，他们是同一种移进
                if (itItem != itStatus->Items.end())
                {
                    set<Item>::iterator nextItItem = itItem;
                    nextItItem++;
                    for (; nextItItem != itStatus->Items.end(); nextItItem++)
                    {
                        if (Productions[nextItItem->my_id].rcontent.size() == nextItItem->my_pos)
                            continue;
                        // 若这个状态之后的项目也是移进nextSymbol
                        else if (Productions[nextItItem->my_id].rcontent[nextItItem->my_pos] == nextSymbol)
                        {
                            set_Item StatusTemp = create_Closure(Item(nextItItem->my_pos + 1, nextItItem->my_expect, nextItItem->my_id));
                            StatusNew.Items.insert(StatusTemp.Items.begin(), StatusTemp.Items.end());
                        }
                    }
                }

                // 这里需要看一下是不是已经有了一样的状态
                list<set_Item>::iterator itHadS;
                int idS_ = 0;
                bool isFound = false;
                // 遍历已有状态，看看是不是已经出现了一样的状态
                for (itHadS = DFA.status.begin(); itHadS != DFA.status.end(); itHadS++, idS_++)
                {
                    // 如果已经有这样的状态了，就将当前状态读到nextSymbol指向已有的状态
                    if (itHadS->Items == StatusNew.Items)
                    {
                        DFA.gotos[GOTO(idSNow, nextSymbol)] = idS_;
                        if (isVt(nextSymbol.content)) // 假如是终结符
                            Action_tb[GOTO(idSNow, nextSymbol)] = Motivation(shift, idS_);
                        else // 假如是非终结符，这里更新gototb
                            Goto_tb[GOTO(idSNow, nextSymbol)] = idS_;
                        isFound = true;
                        break;
                    }
                }

                // 如果是新状态
                if (isFound == false)
                {
                    DFA.status.push_back(StatusNew);
                    DFA.gotos[GOTO(idSNow, nextSymbol)] = DFA.status.size() - 1;
                    if (isVt(nextSymbol.content))
                        Action_tb[GOTO(idSNow, nextSymbol)] = Motivation(shift, DFA.status.size() - 1);
                    else
                        Goto_tb[GOTO(idSNow, nextSymbol)] = DFA.status.size() - 1;
                }

            }// end of else

        }// end of 遍历项目
    }// end of 遍历状态


    return OK;
}




/***********************
*
* 函数名：xxx_print 打印信息到控制台
* 函数名：xxx_txt 打印信息到txt文件
*
************************/
Status Syn_analyzer::Action_print()
{
    cout << "***********************************************Action***********************************************" << endl;
    map<GOTO, Motivation>::iterator itMap;
    int cnt = 0;
    for (cnt = 0, itMap = Action_tb.begin(); itMap != Action_tb.end(); itMap++, cnt++)
    {
        cout << cnt << "   " << itMap->first.first << "   " << itMap->first.second.content << "   ";
        if (itMap->second.cur_state == 0)
            cout << "s";
        else if (itMap->second.cur_state == 1)
            cout << "r";
        else if (itMap->second.cur_state == 2)
            cout << "acc";
        else
            cout << "error";
        cout << "   " << itMap->second.nextS << endl;
    }
    return OK;
}

Status Syn_analyzer::Action_txt()
{
    ofstream out;
    out.open("Action_print.txt", ios::out);
    if (!out.is_open())
    {
        cerr << "打开输出文件Action_print.txt失败" << endl;
        exit(-1);
    }

    map<GOTO, Motivation>::iterator itMap;
    int cnt = 0;
    for (cnt = 0, itMap = Action_tb.begin(); itMap != Action_tb.end(); itMap++, cnt++)
    {
        out << setw(5) << cnt << "   " << setw(5) << itMap->first.first  << "   " << setw(10)<< itMap->first.second.content << "   ";
        if (itMap->second.cur_state == 0)
            out << setw(10) << "shift";
        else if (itMap->second.cur_state == 1)
            out << setw(10) << "reduct";
        else if (itMap->second.cur_state == 2)
            out << setw(10) << "acc";
        else
            out << setw(10) << "error";
        out << "   " << setw(10) << itMap->second.nextS << endl;
    }

    out.close();
    return OK;
}

Status Syn_analyzer::Goto_print()
{
    map<GOTO, int>::iterator itMap;
    int cnt = 0;
    for (cnt = 0, itMap = Goto_tb.begin(); itMap != Goto_tb.end(); itMap++, cnt++)
    {
        cout << setw(5) <<cnt << "   " << setw(5) << itMap->first.first << "   " << setw(5) <<
                itMap->first.second.content << "   " << setw(5) << itMap->second << endl;
    }
    return OK;
}

Status Syn_analyzer::Goto_txt()
{
    ofstream out;
    out.open("Goto_print.txt", ios::out);
    if (!out.is_open())
    {
        cerr << "打开输出文件Goto_print.txt失败" << endl;
        exit(-1);
    }

    map<GOTO, int>::iterator itMap;
    int cnt = 0;
    for (cnt = 0, itMap = Goto_tb.begin(); itMap != Goto_tb.end(); itMap++, cnt++)
    {
        out << setw(5) << cnt << "   " << setw(5) << itMap->first.first << "   " <<
               setw(20) << itMap->first.second.content << "   " << setw(5) << itMap->second << endl;
    }
    out.close();
    return OK;
}

Status Syn_analyzer::StatusStack_print()
{
    stack<int> S = StatusStack;
    cout << "StatusStack:";
    for (int cnt = 0; !S.empty(); cnt++)
    {
        cout << S.top() << ' ';
        S.pop();
    }
    cout << endl;
}

Status Syn_analyzer::SymbolStack_print()
{
    stack<Symbol> S = SymbolStack;
    cout << "SymbolStack:";
    for (int cnt = 0; !S.empty(); cnt++)
    {
        cout << S.top().content << ' ';
        S.pop();
    }
    cout << endl;
    return OK;
}

Status Syn_analyzer::Stack_print(int cnt)
{
    cout << "***********************栈空间" << cnt << "***********************" << endl;
    this->StatusStack_print();
    this->SymbolStack_print();
    return OK;
}

Status Syn_analyzer::Stack_statustxt(int cnt)
{

    ofstream out;

    if (cnt == 0)
        out.open("Stackstatus_print.txt", ios::ate);
    else
        out.open("Stackstatus_print.txt", ios::app);

    if (!out.is_open())
    {
        cerr << "打开输出文件Stackstatus_print.txt失败" << endl;
        exit(-1);
    }

    out << "********Step "<<cnt+1<<"********" << endl;

    stack<int> S0 = StatusStack;
//    out << "StatusStack:\n";
    for (int cnt = 0; !S0.empty(); cnt++)
    {
        out << S0.top() << '\n';
        S0.pop();
    }
    out << endl;

    out.close();
    return OK;
}

Status Syn_analyzer::Stack_symboltxt(int cnt)
{

    ofstream out;

    if (cnt == 0)
        out.open("Stacksymbol_print.txt", ios::ate);
    else
        out.open("Stacksymbol_print.txt", ios::app);

    if (!out.is_open())
    {
        cerr << "打开输出文件Stacksymbol_print.txt失败" << endl;
        exit(-1);
    }

    out << "********Step "<<cnt+1<<"********" << endl;

    stack<Symbol> S1 = SymbolStack;
//    out << "SymbolStack:\n";
    for (int cnt = 0; !S1.empty(); cnt++)
    {
        out << S1.top().content << '\n';
        S1.pop();
    }
    out << endl;

    out.close();
    return OK;
}

Symbol Syn_analyzer::pop()
{
    Symbol s = SymbolStack.top();
    SymbolStack.pop();
    StatusStack.pop();
    return s;
}








/****************************

重载运算符 便于类与类之间进行运算

******************************/
bool operator ==(const Symbol& a, const Symbol& b)
{
    return a.content == b.content;
}

bool operator <(const Item& a, const Item& b)
{
    if (a.my_id == b.my_id)
    {
        if (a.my_expect == b.my_expect)
        {
            return a.my_pos < b.my_pos;
        }
        else
            return a.my_expect < b.my_expect;
    }
    else
        return a.my_id < b.my_id;
}

bool operator ==(const Item& a, const Item& b)
{
    return a.my_id == b.my_id && a.my_expect == b.my_expect && a.my_pos == b.my_pos;
}


bool operator <(const Symbol& a, const Symbol& b)
{
    return a.content < b.content;
}









