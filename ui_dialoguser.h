/********************************************************************************
** Form generated from reading UI file 'dialoguser.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGUSER_H
#define UI_DIALOGUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialogUser
{
public:
    QTableWidget *tableWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnAdd;
    QPushButton *btnDel;
    QPushButton *btnEdit;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QDialog *dialogUser)
    {
        if (dialogUser->objectName().isEmpty())
            dialogUser->setObjectName(QString::fromUtf8("dialogUser"));
        dialogUser->resize(469, 408);
        tableWidget = new QTableWidget(dialogUser);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 70, 311, 301));
        verticalLayoutWidget = new QWidget(dialogUser);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(340, 120, 111, 201));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnAdd = new QPushButton(verticalLayoutWidget);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        btnAdd->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setPointSize(14);
        btnAdd->setFont(font);

        verticalLayout->addWidget(btnAdd);

        btnDel = new QPushButton(verticalLayoutWidget);
        btnDel->setObjectName(QString::fromUtf8("btnDel"));
        btnDel->setMinimumSize(QSize(0, 40));
        btnDel->setFont(font);

        verticalLayout->addWidget(btnDel);

        btnEdit = new QPushButton(verticalLayoutWidget);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));
        btnEdit->setMinimumSize(QSize(0, 40));
        btnEdit->setFont(font);

        verticalLayout->addWidget(btnEdit);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 40));
        pushButton->setFont(font);

        verticalLayout->addWidget(pushButton);

        label = new QLabel(dialogUser);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 131, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        retranslateUi(dialogUser);

        QMetaObject::connectSlotsByName(dialogUser);
    } // setupUi

    void retranslateUi(QDialog *dialogUser)
    {
        dialogUser->setWindowTitle(QCoreApplication::translate("dialogUser", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("dialogUser", "Name", nullptr));
        btnAdd->setText(QCoreApplication::translate("dialogUser", "Add", nullptr));
        btnDel->setText(QCoreApplication::translate("dialogUser", "Delete", nullptr));
        btnEdit->setText(QCoreApplication::translate("dialogUser", "Edit", nullptr));
        pushButton->setText(QCoreApplication::translate("dialogUser", "Exit", nullptr));
        label->setText(QCoreApplication::translate("dialogUser", "User List", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialogUser: public Ui_dialogUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGUSER_H
