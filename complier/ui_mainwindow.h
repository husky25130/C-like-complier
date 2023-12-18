/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *Btn_esc;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayout;
    QPushButton *Btn_LexAnalyst;
    QSpacerItem *verticalSpacer;
    QPushButton *Btn_Production;
    QSpacerItem *verticalSpacer_2;
    QPushButton *Btn_First;
    QSpacerItem *verticalSpacer_3;
    QPushButton *Btn_Action;
    QSpacerItem *verticalSpacer_4;
    QPushButton *Btn_Goto;
    QSpacerItem *verticalSpacer_6;
    QPushButton *Btn_Stack;
    QStackedWidget *stackedWidget;
    QWidget *page_input;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *lineEdit_input;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *Btn_input;
    QTextEdit *TextEdit_input;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QPushButton *Btn_enter;
    QWidget *page_stack;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_7;
    QPlainTextEdit *TextEdit_Status;
    QVBoxLayout *verticalLayout_16;
    QLabel *label_8;
    QPlainTextEdit *TextEdit_Symbol;
    QWidget *page_LexAly;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *lineEdit_lexAnalyst;
    QSpacerItem *horizontalSpacer_2;
    QPlainTextEdit *TextEdit_LexAly;
    QWidget *page_Production;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_Production;
    QSpacerItem *horizontalSpacer_4;
    QPlainTextEdit *TextEdit_Production;
    QWidget *page_First;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEdit_First;
    QSpacerItem *horizontalSpacer_5;
    QPlainTextEdit *TextEdit_First;
    QWidget *page_Action;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QLineEdit *lineEdit_Action;
    QSpacerItem *horizontalSpacer_6;
    QPlainTextEdit *TextEdit_Action;
    QWidget *page_Goto;
    QVBoxLayout *verticalLayout_14;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QLineEdit *lineEdit_Goto;
    QSpacerItem *horizontalSpacer_7;
    QPlainTextEdit *TextEdit_Goto;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(787, 584);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        Btn_esc = new QPushButton(centralwidget);
        Btn_esc->setObjectName(QString::fromUtf8("Btn_esc"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Btn_esc->sizePolicy().hasHeightForWidth());
        Btn_esc->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(Btn_esc);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Btn_LexAnalyst = new QPushButton(centralwidget);
        Btn_LexAnalyst->setObjectName(QString::fromUtf8("Btn_LexAnalyst"));
        sizePolicy2.setHeightForWidth(Btn_LexAnalyst->sizePolicy().hasHeightForWidth());
        Btn_LexAnalyst->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(Btn_LexAnalyst);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        Btn_Production = new QPushButton(centralwidget);
        Btn_Production->setObjectName(QString::fromUtf8("Btn_Production"));
        sizePolicy2.setHeightForWidth(Btn_Production->sizePolicy().hasHeightForWidth());
        Btn_Production->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(Btn_Production);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        Btn_First = new QPushButton(centralwidget);
        Btn_First->setObjectName(QString::fromUtf8("Btn_First"));
        sizePolicy2.setHeightForWidth(Btn_First->sizePolicy().hasHeightForWidth());
        Btn_First->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(Btn_First);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        Btn_Action = new QPushButton(centralwidget);
        Btn_Action->setObjectName(QString::fromUtf8("Btn_Action"));
        sizePolicy2.setHeightForWidth(Btn_Action->sizePolicy().hasHeightForWidth());
        Btn_Action->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(Btn_Action);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        Btn_Goto = new QPushButton(centralwidget);
        Btn_Goto->setObjectName(QString::fromUtf8("Btn_Goto"));
        sizePolicy2.setHeightForWidth(Btn_Goto->sizePolicy().hasHeightForWidth());
        Btn_Goto->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(Btn_Goto);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        Btn_Stack = new QPushButton(centralwidget);
        Btn_Stack->setObjectName(QString::fromUtf8("Btn_Stack"));

        verticalLayout->addWidget(Btn_Stack);


        horizontalLayout->addLayout(verticalLayout);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        page_input = new QWidget();
        page_input->setObjectName(QString::fromUtf8("page_input"));
        sizePolicy1.setHeightForWidth(page_input->sizePolicy().hasHeightForWidth());
        page_input->setSizePolicy(sizePolicy1);
        verticalLayout_5 = new QVBoxLayout(page_input);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(page_input);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\351\232\266\344\271\246"));
        font.setPointSize(20);
        label_5->setFont(font);

        horizontalLayout_2->addWidget(label_5);

        lineEdit_input = new QLineEdit(page_input);
        lineEdit_input->setObjectName(QString::fromUtf8("lineEdit_input"));

        horizontalLayout_2->addWidget(lineEdit_input);

        horizontalSpacer_3 = new QSpacerItem(13, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        Btn_input = new QPushButton(page_input);
        Btn_input->setObjectName(QString::fromUtf8("Btn_input"));

        horizontalLayout_2->addWidget(Btn_input);


        verticalLayout_2->addLayout(horizontalLayout_2);

        TextEdit_input = new QTextEdit(page_input);
        TextEdit_input->setObjectName(QString::fromUtf8("TextEdit_input"));
        sizePolicy.setHeightForWidth(TextEdit_input->sizePolicy().hasHeightForWidth());
        TextEdit_input->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(TextEdit_input);


        verticalLayout_5->addLayout(verticalLayout_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        Btn_enter = new QPushButton(page_input);
        Btn_enter->setObjectName(QString::fromUtf8("Btn_enter"));

        horizontalLayout_9->addWidget(Btn_enter);


        verticalLayout_5->addLayout(horizontalLayout_9);

        stackedWidget->addWidget(page_input);
        page_stack = new QWidget();
        page_stack->setObjectName(QString::fromUtf8("page_stack"));
        horizontalLayout_10 = new QHBoxLayout(page_stack);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        label_7 = new QLabel(page_stack);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        verticalLayout_15->addWidget(label_7);

        TextEdit_Status = new QPlainTextEdit(page_stack);
        TextEdit_Status->setObjectName(QString::fromUtf8("TextEdit_Status"));

        verticalLayout_15->addWidget(TextEdit_Status);


        horizontalLayout_10->addLayout(verticalLayout_15);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        label_8 = new QLabel(page_stack);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        verticalLayout_16->addWidget(label_8);

        TextEdit_Symbol = new QPlainTextEdit(page_stack);
        TextEdit_Symbol->setObjectName(QString::fromUtf8("TextEdit_Symbol"));

        verticalLayout_16->addWidget(TextEdit_Symbol);


        horizontalLayout_10->addLayout(verticalLayout_16);

        stackedWidget->addWidget(page_stack);
        page_LexAly = new QWidget();
        page_LexAly->setObjectName(QString::fromUtf8("page_LexAly"));
        sizePolicy1.setHeightForWidth(page_LexAly->sizePolicy().hasHeightForWidth());
        page_LexAly->setSizePolicy(sizePolicy1);
        verticalLayout_7 = new QVBoxLayout(page_LexAly);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(page_LexAly);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout_3->addWidget(label_4);

        lineEdit_lexAnalyst = new QLineEdit(page_LexAly);
        lineEdit_lexAnalyst->setObjectName(QString::fromUtf8("lineEdit_lexAnalyst"));

        horizontalLayout_3->addWidget(lineEdit_lexAnalyst);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout_3);

        TextEdit_LexAly = new QPlainTextEdit(page_LexAly);
        TextEdit_LexAly->setObjectName(QString::fromUtf8("TextEdit_LexAly"));

        verticalLayout_6->addWidget(TextEdit_LexAly);


        verticalLayout_7->addLayout(verticalLayout_6);

        stackedWidget->addWidget(page_LexAly);
        page_Production = new QWidget();
        page_Production->setObjectName(QString::fromUtf8("page_Production"));
        verticalLayout_9 = new QVBoxLayout(page_Production);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(page_Production);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_4->addWidget(label_3);

        lineEdit_Production = new QLineEdit(page_Production);
        lineEdit_Production->setObjectName(QString::fromUtf8("lineEdit_Production"));

        horizontalLayout_4->addWidget(lineEdit_Production);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_8->addLayout(horizontalLayout_4);

        TextEdit_Production = new QPlainTextEdit(page_Production);
        TextEdit_Production->setObjectName(QString::fromUtf8("TextEdit_Production"));

        verticalLayout_8->addWidget(TextEdit_Production);


        verticalLayout_9->addLayout(verticalLayout_8);

        stackedWidget->addWidget(page_Production);
        page_First = new QWidget();
        page_First->setObjectName(QString::fromUtf8("page_First"));
        sizePolicy1.setHeightForWidth(page_First->sizePolicy().hasHeightForWidth());
        page_First->setSizePolicy(sizePolicy1);
        verticalLayout_11 = new QVBoxLayout(page_First);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(page_First);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        horizontalLayout_5->addWidget(label_6);

        lineEdit_First = new QLineEdit(page_First);
        lineEdit_First->setObjectName(QString::fromUtf8("lineEdit_First"));

        horizontalLayout_5->addWidget(lineEdit_First);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_10->addLayout(horizontalLayout_5);

        TextEdit_First = new QPlainTextEdit(page_First);
        TextEdit_First->setObjectName(QString::fromUtf8("TextEdit_First"));

        verticalLayout_10->addWidget(TextEdit_First);


        verticalLayout_11->addLayout(verticalLayout_10);

        stackedWidget->addWidget(page_First);
        page_Action = new QWidget();
        page_Action->setObjectName(QString::fromUtf8("page_Action"));
        sizePolicy1.setHeightForWidth(page_Action->sizePolicy().hasHeightForWidth());
        page_Action->setSizePolicy(sizePolicy1);
        horizontalLayout_7 = new QHBoxLayout(page_Action);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(page_Action);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_6->addWidget(label_2);

        lineEdit_Action = new QLineEdit(page_Action);
        lineEdit_Action->setObjectName(QString::fromUtf8("lineEdit_Action"));

        horizontalLayout_6->addWidget(lineEdit_Action);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout_12->addLayout(horizontalLayout_6);

        TextEdit_Action = new QPlainTextEdit(page_Action);
        TextEdit_Action->setObjectName(QString::fromUtf8("TextEdit_Action"));

        verticalLayout_12->addWidget(TextEdit_Action);


        horizontalLayout_7->addLayout(verticalLayout_12);

        stackedWidget->addWidget(page_Action);
        page_Goto = new QWidget();
        page_Goto->setObjectName(QString::fromUtf8("page_Goto"));
        sizePolicy1.setHeightForWidth(page_Goto->sizePolicy().hasHeightForWidth());
        page_Goto->setSizePolicy(sizePolicy1);
        verticalLayout_14 = new QVBoxLayout(page_Goto);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label = new QLabel(page_Goto);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_8->addWidget(label);

        lineEdit_Goto = new QLineEdit(page_Goto);
        lineEdit_Goto->setObjectName(QString::fromUtf8("lineEdit_Goto"));

        horizontalLayout_8->addWidget(lineEdit_Goto);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        verticalLayout_13->addLayout(horizontalLayout_8);

        TextEdit_Goto = new QPlainTextEdit(page_Goto);
        TextEdit_Goto->setObjectName(QString::fromUtf8("TextEdit_Goto"));

        verticalLayout_13->addWidget(TextEdit_Goto);


        verticalLayout_14->addLayout(verticalLayout_13);

        stackedWidget->addWidget(page_Goto);

        horizontalLayout->addWidget(stackedWidget);


        verticalLayout_4->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 787, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Btn_esc->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        Btn_LexAnalyst->setText(QCoreApplication::translate("MainWindow", "LexAnalyst", nullptr));
        Btn_Production->setText(QCoreApplication::translate("MainWindow", "Production", nullptr));
        Btn_First->setText(QCoreApplication::translate("MainWindow", "First\351\233\206", nullptr));
        Btn_Action->setText(QCoreApplication::translate("MainWindow", "Action\350\241\250", nullptr));
        Btn_Goto->setText(QCoreApplication::translate("MainWindow", "Goto\350\241\250", nullptr));
        Btn_Stack->setText(QCoreApplication::translate("MainWindow", "Show Stack", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\344\273\243\347\240\201\350\257\273\345\205\245", nullptr));
        lineEdit_input->setInputMask(QCoreApplication::translate("MainWindow", "\350\257\273\345\205\245\346\226\207\344\273\266\347\232\204\347\233\256\345\275\225", nullptr));
        lineEdit_input->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\205\245\346\226\207\344\273\266\347\232\204\347\233\256\345\275\225", nullptr));
        Btn_input->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        Btn_enter->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\205\245", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "StatusStack", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "SymbolStack", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "LexAnalyst", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Production", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "First\351\233\206", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Action\350\241\250", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Goto\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
