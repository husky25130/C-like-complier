#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

#include "LexAnalyzer.h"
#include "SynAnalyzer.h"
#include "complier.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 选择文件，并将文件内容显示在文本框中
void MainWindow::on_Btn_input_released()
{
    // 获取文件路径
    path_input = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("文本文件(*txt)"));
    // 文件路径显示在lineEdit
    ui->lineEdit_input->setText(path_input);

    //  打开文件
    QFile file(path_input);
    if(!(file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qDebug()<<"文件打开失败";
    }

    // 文件输出到文本框TextEdit_input
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        context_input.append(str);
    }
    ui->TextEdit_input->setText(context_input);
}

// 文件读入
void MainWindow::on_Btn_enter_released()
{
    bool sign=0;
    //弹窗正在读入
    QString str="分析器启动中，请稍后...";

    QMessageBox::information(NULL, "Waiting", str ,QMessageBox::Yes, QMessageBox::Yes);
    qDebug()<<"弹窗结束";

    Lex_analyzer LEXA("code_file.txt");
    LEXA.lex_analyze();

//    LEXA.lex_print();
    LEXA.lex_txt();

    Syn_analyzer SYNA("grammar.txt");
    SYNA.get_production();
    SYNA.show_production();  //控制台打印生成式
    SYNA.init_First();

    // SYNA.First_print();
    SYNA.First_txt();

    SYNA.create_DFA();
    sign=1;

    // SYNA.Action_print();
    SYNA.Action_txt();

    // SYNA.Goto_print();
    SYNA.Goto_txt();

    SYNA.LRAnalyse(LEXA.get_list());

    //弹窗结束

}


void MainWindow::on_Btn_LexAnalyst_released()
{
    //切换到LexAnalyst页面
    ui->stackedWidget->setCurrentWidget(ui->page_LexAly);

    QFile file_LexAnalyst("./Lex_print.txt");
    // 文件路径显示在lineEdit
    ui->lineEdit_lexAnalyst->setText(file_LexAnalyst.fileName());

    if(!(file_LexAnalyst.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qDebug()<<"LexAnalyst文件打开失败";
    }

    while(!file_LexAnalyst.atEnd())
    {
        QByteArray line = file_LexAnalyst.readLine();
        QString str_LexAnalyst(line);
        context_lexAnalyst.append(str_LexAnalyst);
    }

    ui->TextEdit_LexAly->setPlainText(context_lexAnalyst); //显示到文本框
}

void MainWindow::on_Btn_Production_released()
{
    //切换到Production页面
    ui->stackedWidget->setCurrentWidget(ui->page_Production);

    QFile file_Production("./Production_print.txt");
    // 文件路径显示在Production
    ui->lineEdit_Production->setText(file_Production.fileName());

    if(!(file_Production.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qDebug()<<"Production文件打开失败";
    }

    while(!file_Production.atEnd())
    {
        QByteArray line = file_Production.readLine();
        QString str_Production(line);
        context_Production.append(str_Production);
    }

    ui->TextEdit_Production->setPlainText(context_Production); //显示到文本框
}

void MainWindow::on_Btn_First_released()
{
    //切换到First页面
    ui->stackedWidget->setCurrentWidget(ui->page_First);

    QFile file_First("./First_print.txt");
    // 文件路径显示在First
    ui->lineEdit_First->setText(file_First.fileName());

    if(!(file_First.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qDebug()<<"First文件打开失败";
    }

    while(!file_First.atEnd())
    {
        QByteArray line = file_First.readLine();
        QString str_First(line);
        context_First.append(str_First);
    }

    ui->TextEdit_First->setPlainText(context_First); //显示到文本框
}

void MainWindow::on_Btn_Action_released()
{
    //切换到Action页面
    ui->stackedWidget->setCurrentWidget(ui->page_Action);

    QFile file_Action("./Action_print.txt");
    // 文件路径显示在Action
    ui->lineEdit_Action->setText(file_Action.fileName());

    if(!(file_Action.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qDebug()<<"Action文件打开失败";
    }

    while(!file_Action.atEnd())
    {
        QByteArray line = file_Action.readLine();
        QString str_Action(line);
        context_Action.append(str_Action);
    }

    ui->TextEdit_Action->setPlainText(context_Action); //显示到文本框
}

void MainWindow::on_Btn_Goto_released()
{
    //切换到Goto页面
    ui->stackedWidget->setCurrentWidget(ui->page_Goto);

    QFile file_Goto("./Goto_print.txt");
    // 文件路径显示在Goto
    ui->lineEdit_Goto->setText(file_Goto.fileName());

    if(!(file_Goto.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qDebug()<<"Goto文件打开失败";
    }

    while(!file_Goto.atEnd())
    {
        QByteArray line = file_Goto.readLine();
        QString str_Goto(line);
        context_Goto.append(str_Goto);
    }

    ui->TextEdit_Goto->setPlainText(context_Goto); //显示到文本框
}

// 返回按钮
void MainWindow::on_Btn_esc_released()
{
    // 切换到首页
    ui->stackedWidget->setCurrentWidget(ui->page_input);

    // 清空文件目录行的内容
    ui->lineEdit_input->setText("");
    ui->lineEdit_lexAnalyst->setText("");
    ui->lineEdit_Production->setText("");
    ui->lineEdit_First->setText("");
    ui->lineEdit_Action->setText("");
    ui->lineEdit_Goto->setText("");

    // 清空文本框的内容
    ui->TextEdit_input->setText("");
    ui->TextEdit_LexAly->setPlainText("");
    ui->TextEdit_Production->setPlainText("");
    ui->TextEdit_First->setPlainText("");
    ui->TextEdit_Action->setPlainText("");
    ui->TextEdit_Goto->setPlainText("");

    // 清空栈的内容
}

void MainWindow::on_Btn_Stack_released()
{
    //切换到LexAnalyst页面
    ui->stackedWidget->setCurrentWidget(ui->page_stack);

    // Status显示
    QFile file_Status("./Stackstatus_print.txt");

    if(!(file_Status.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qDebug()<<"Stackstatus_print文件打开失败";
    }

    while(!file_Status.atEnd())
    {
        QByteArray line_status = file_Status.readLine();
        QString str_Status(line_status);
        context_Status.append(str_Status);
    }

    ui->TextEdit_Status->setPlainText(context_Status); //显示到文本框

    // Symbol显示
    QFile file_Symbol("./Stacksymbol_print.txt");

    if(!(file_Symbol.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qDebug()<<"Stacksymbol_print文件打开失败";
    }

    while(!file_Symbol.atEnd())
    {
        QByteArray line_Symbol = file_Symbol.readLine();
        QString str_Symbol(line_Symbol);
        context_Symbol.append(str_Symbol);
    }

    ui->TextEdit_Symbol->setPlainText(context_Symbol); //显示到文本框

}
