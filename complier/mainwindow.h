#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qmessagebox.h>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Btn_LexAnalyst_released();

    void on_Btn_input_released();

    void on_Btn_esc_released();

    void on_Btn_Production_released();

    void on_Btn_First_released();

    void on_Btn_Action_released();

    void on_Btn_Goto_released();

    void on_Btn_enter_released();

    void on_Btn_Stack_released();

private:
    Ui::MainWindow *ui;
    QString context_input;          //源代码文件
    QString path_input;             //源代码文件地址
//    QString lexcial_name;//文法产生式序列文件
    QString context_lexAnalyst;    //词法分析文件
    QString path_lexAnalyst;       //词法分析文件地址
    QString context_Production;     //Production文件
    QString path_Production;        //Production文件地址
    QString context_First;     //First文件
    QString path_First;        //First文件地址
    QString context_Action;     //Action文件
    QString path_Action;        //Action文件地址
    QString context_Goto;     //Goto文件
    QString path_Goto;        //Goto文件地址
    QString context_Status;     //Status文件
    QString path_Status;        //Status文件地址
    QString context_Symbol;     //Symbol文件
    QString path_Symbol;        //Symbol文件地址
};

#endif // MAINWINDOW_H
