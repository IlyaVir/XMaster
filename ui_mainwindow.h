/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_10;
    QLineEdit *input;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_12;
    QPushButton *pushButton_7;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_11;
    QPushButton *pushButton_13;
    QPushButton *pushButton_15;
    QPushButton *pushButton_5;
    QPushButton *pushButton_14;
    QPushButton *pushButton_9;
    QPushButton *pushButton_3;
    QPushButton *pushButton_8;
    QPushButton *pushButton_6;
    QPushButton *pushButton_16;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1026, 624);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(90);
        sizePolicy1.setHeightForWidth(pushButton_10->sizePolicy().hasHeightForWidth());
        pushButton_10->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        pushButton_10->setFont(font);
        pushButton_10->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(pushButton_10);

        input = new QLineEdit(centralwidget);
        input->setObjectName(QStringLiteral("input"));
        sizePolicy.setHeightForWidth(input->sizePolicy().hasHeightForWidth());
        input->setSizePolicy(sizePolicy);
        input->setMaximumSize(QSize(424, 16777215));
        QFont font1;
        font1.setPointSize(24);
        input->setFont(font1);
        input->setInputMethodHints(Qt::ImhNone);

        horizontalLayout->addWidget(input);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy2);
        checkBox->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(checkBox, 0, 0, 1, 1, Qt::AlignHCenter);

        checkBox_3 = new QCheckBox(centralwidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setEnabled(true);
        sizePolicy2.setHeightForWidth(checkBox_3->sizePolicy().hasHeightForWidth());
        checkBox_3->setSizePolicy(sizePolicy2);
        checkBox_3->setCursor(QCursor(Qt::PointingHandCursor));
        checkBox_3->setChecked(true);

        gridLayout_2->addWidget(checkBox_3, 0, 3, 1, 1, Qt::AlignHCenter);

        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        sizePolicy2.setHeightForWidth(checkBox_2->sizePolicy().hasHeightForWidth());
        checkBox_2->setSizePolicy(sizePolicy2);
        checkBox_2->setCursor(QCursor(Qt::PointingHandCursor));
        checkBox_2->setChecked(false);

        gridLayout_2->addWidget(checkBox_2, 0, 1, 1, 1, Qt::AlignHCenter);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setPointSize(60);
        pushButton_2->setFont(font2);
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2->setAutoFillBackground(false);

        gridLayout_3->addWidget(pushButton_2, 1, 2, 1, 1);

        pushButton_12 = new QPushButton(centralwidget);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        sizePolicy3.setHeightForWidth(pushButton_12->sizePolicy().hasHeightForWidth());
        pushButton_12->setSizePolicy(sizePolicy3);
        QFont font3;
        font3.setPointSize(40);
        pushButton_12->setFont(font3);
        pushButton_12->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton_12, 5, 3, 1, 1);

        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        sizePolicy3.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy3);
        QFont font4;
        font4.setPointSize(25);
        pushButton_7->setFont(font4);
        pushButton_7->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton_7, 5, 0, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy3.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy3);
        pushButton->setFont(font2);
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        sizePolicy3.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy3);
        pushButton_4->setFont(font2);
        pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton_4, 2, 3, 1, 1);

        pushButton_11 = new QPushButton(centralwidget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        sizePolicy3.setHeightForWidth(pushButton_11->sizePolicy().hasHeightForWidth());
        pushButton_11->setSizePolicy(sizePolicy3);
        pushButton_11->setFont(font3);
        pushButton_11->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton_11, 5, 2, 1, 1);

        pushButton_13 = new QPushButton(centralwidget);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setEnabled(false);
        sizePolicy3.setHeightForWidth(pushButton_13->sizePolicy().hasHeightForWidth());
        pushButton_13->setSizePolicy(sizePolicy3);
        pushButton_13->setFont(font4);
        pushButton_13->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton_13, 7, 0, 1, 1);

        pushButton_15 = new QPushButton(centralwidget);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        sizePolicy3.setHeightForWidth(pushButton_15->sizePolicy().hasHeightForWidth());
        pushButton_15->setSizePolicy(sizePolicy3);
        pushButton_15->setFont(font4);

        gridLayout_3->addWidget(pushButton_15, 7, 3, 1, 1);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        sizePolicy3.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy3);
        QFont font5;
        font5.setPointSize(48);
        pushButton_5->setFont(font5);
        pushButton_5->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton_5, 4, 3, 1, 1);

        pushButton_14 = new QPushButton(centralwidget);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        sizePolicy3.setHeightForWidth(pushButton_14->sizePolicy().hasHeightForWidth());
        pushButton_14->setSizePolicy(sizePolicy3);
        pushButton_14->setFont(font4);

        gridLayout_3->addWidget(pushButton_14, 7, 2, 1, 1);

        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        sizePolicy3.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy3);
        pushButton_9->setFont(font2);
        pushButton_9->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton_9, 1, 3, 1, 1);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        sizePolicy3.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy3);
        pushButton_3->setFont(font2);
        pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton_3, 2, 0, 1, 1);

        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        sizePolicy3.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy3);
        QFont font6;
        font6.setPointSize(55);
        pushButton_8->setFont(font6);
        pushButton_8->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton_8, 2, 2, 1, 1);

        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        sizePolicy3.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy3);
        pushButton_6->setFont(font5);
        pushButton_6->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_3->addWidget(pushButton_6, 4, 2, 1, 1);

        pushButton_16 = new QPushButton(centralwidget);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        sizePolicy3.setHeightForWidth(pushButton_16->sizePolicy().hasHeightForWidth());
        pushButton_16->setSizePolicy(sizePolicy3);
        QFont font7;
        font7.setPointSize(50);
        pushButton_16->setFont(font7);

        gridLayout_3->addWidget(pushButton_16, 4, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 2, 0, 2, 1);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QFont font8;
        font8.setPointSize(16);
        listWidget->setFont(font8);
        listWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        gridLayout->addWidget(listWidget, 0, 1, 4, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1026, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "\320\230\320\230", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("MainWindow", "\320\227\320\262\321\203\320\272 \320\272\320\273\320\260\320\262\320\270\321\210", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("MainWindow", "\320\244\320\276\320\275\320\276\320\262\320\260\321\217 \320\274\321\203\320\267\321\213\320\272\320\260", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        pushButton_12->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "\320\246\320\265\320\273\321\213\320\265\n"
"\320\272\320\276\321\200\320\275\320\270", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "div", Q_NULLPTR));
        pushButton_11->setText(QApplication::translate("MainWindow", "Copy", Q_NULLPTR));
        pushButton_13->setText(QApplication::translate("MainWindow", "\320\243\321\201\320\274\320\270\321\200\320\270\321\202\321\214\n"
"\320\230\320\230", Q_NULLPTR));
        pushButton_15->setText(QApplication::translate("MainWindow", "\320\241\320\275\321\217\321\202\321\214\n"
"\320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\270\320\265", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "f '(x)", Q_NULLPTR));
        pushButton_14->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\264\320\265\320\273\320\270\321\202\321\214\n"
"\320\262\321\201\321\221", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "==", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "*", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "mod", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "f(x)", Q_NULLPTR));
        pushButton_16->setText(QApplication::translate("MainWindow", "^", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
