#include "SynAnalyzer.h"


/***********************
*
*     变量分析
*
************************/
Variable::Variable(string name, Vtype type)
{
    this->name = name;
    this->type = type;
}

Variable::Variable(string name, Vtype type, int depth)
{
    this->name = name;
    this->type = type;
    this->depth = depth;
}

Variable* Syn_analyzer::findVariable(string name)
{
    for (vector<Variable>::iterator i = var_tb.begin(); i != var_tb.end(); i++)
    {
        if (i->name == name)
        {
            return &(*i);
        }
    }
    return nullptr;
}




/***********************
*
*     函数分析
*
************************/
Function::Function(string name, Vtype type, list<Vtype> parType)
{
    this->name = name;
    this->type = type;
    this->parType.assign(parType.begin(), parType.end());
}

Function::Function(string name, Vtype type, list<Vtype> parType, int enter)
{
    this->name = name;
    this->type = type;
    this->parType.assign(parType.begin(), parType.end());
    this->enter = enter;
}

Function* Syn_analyzer::findFunction(string name)
{
    for (vector<Function>::iterator i = func_tb.begin(); i != func_tb.end(); i++)
    {
        if (i->name == name)
        {
            return &(*i);
        }
    }
    return nullptr;
}

vector<pair<int, string> > Syn_analyzer::getFunctionEnter()
{
    vector<pair<int, string> > funcEnter;
    for (vector<Function>::iterator i = func_tb.begin(); i != func_tb.end(); i++)
    {
        funcEnter.push_back(pair<int, string>(i->enter, i->name));
    }
    sort(funcEnter.begin(), funcEnter.end());
    return funcEnter;
}
