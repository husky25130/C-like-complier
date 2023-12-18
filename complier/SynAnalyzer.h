#ifndef SYNANALYZER_H
#define SYNANALYZER_H

#pragma once

#include "complier.h"


enum Vtype
{
    Vvoid,
    Vint,
    Vfloat
};   //数据类型



class Symbol   //符号类
{
public:
    string content;   //
    bool Vt;			// 是否
    string name;		// 仅当ID/NUM/floating有效
    int quad;

    list<int> nextlist;
    list<int> falselist;
    list<int> truelist;

    list<string> par;
    list<Vtype> parType;

    Symbol(string content, bool Vt);
    Symbol(string content, bool Vt, string name);
    Symbol();

    // 重载运算符 便于类与类之间运算
    friend bool operator <(const Symbol& a, const Symbol& b);
    friend bool operator ==(const Symbol& a, const Symbol& b);
};

class SymbolID :public Symbol    //继承
{
private:
    string idName;
public:
    SymbolID(Symbol s, string name);
};

class SymbolNum :public Symbol
{
private:
    string numName;
public:
    SymbolNum(Symbol s, string num);
};

class SymbolFloating :public Symbol
{
private:
    string floatname;
public:
    SymbolFloating(Symbol s, string floatname);
};


class Production
{
public:
    int id;
    Symbol lcontent;
    vector<Symbol> rcontent;
    Production();
};

class Item      ///状态
{
public:
    int my_pos;												// 注明点的位置
    int my_id;												// 产生式id
    Symbol my_expect;										// 展望符

    Item(int my_pos, Symbol my_expect, int my_id);

    //重载运算符
    friend bool operator <(const Item& a, const Item& b);
    friend bool operator ==(const Item& a, const Item& b);

};

class set_Item // 状态集
{
public:
    set<Item> Items;
};


//goto二元组定义
typedef pair<int, Symbol> GOTO;


class DFA
{
public:
    list<set_Item> status;
    map<GOTO, int> gotos;       //当前状态读到GOTO（当前态读到symbol到哪里），到map映射的gotos的int处
};

class Variable
{
public:
    string name;
    Vtype type;
    int depth;

    Variable(string name, Vtype type);
    Variable(string name, Vtype type, int depth);
};

class Function
{
public:
    string name;
    Vtype type;
    list<Vtype> parType;
    int enter; // 函数入口，在我call的时候是需要函数入口的


    Function(string name, Vtype type, list<Vtype> parType);
    Function(string name, Vtype type, list<Vtype> parType, int enter);
};

enum ACT { shift, reduct, accept, error };
class Motivation
{
public:
    ACT cur_state;
    int nextS;
    Motivation();
    Motivation(ACT statement, int s);

};

class Syn_analyzer
{
private:
    ifstream inputProductions;

    vector<Production> Productions;
    map<Symbol, set<Symbol>> First;
    map<Symbol, set<Symbol>> Follow;

    DFA DFA;

    map<GOTO, Motivation> Action_tb;
    map<GOTO, int> Goto_tb;

    stack<int> StatusStack;
    stack<Symbol> SymbolStack;

    vector<Variable> var_tb; // 变量表
    vector<Function> func_tb; // 函数表


    int line;					// 行数
    int level;					 // 当前变量处于的层级


public:
    Syn_analyzer();
    Syn_analyzer(string path);

    Status open_synfile(string path);
    Status get_production();
    Status show_production();
    Status production_print();
    Status init_First();

    Status First_print();
    Status First_txt();    //first集合到文件

    Status create_DFA();    //生成dfa

    set_Item create_Closure(Item item);
    set<Symbol> get_expect(list<Symbol> S);
    //action
    Status Action_print();
    Status Action_txt();
    //goto
    Status Goto_print();
    Status Goto_txt();

    Status LRAnalyse(list<Token> LexRes);

    Status StatusStack_print();
    Status SymbolStack_print();

    Status Stack_print(int cnt);
    Status Stack_statustxt(int cnt);
    Status Stack_symboltxt(int cnt);
    Symbol pop();

    vector<pair<int, string> > getFunctionEnter();

    // 匹配函数，匹配变量
    Function* findFunction(string name);
    Variable* findVariable(string name);
};





#endif // SYNANALYZER_H
