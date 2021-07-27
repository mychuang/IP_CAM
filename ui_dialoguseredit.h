/********************************************************************************
** Form generated from reading UI file 'dialoguseredit.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGUSEREDIT_H
#define UI_DIALOGUSEREDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialogUserEdit
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *labUser;
    QLabel *labPwd;
    QLineEdit *editUser;
    QLineEdit *editPwd;
    QLabel *labPwdChk;
    QLineEdit *editPwdChk;
    QGroupBox *groupBox;
    QRadioButton *btnAdmin;
    QRadioButton *btnOperator;
    QRadioButton *btnView;
    QLabel *labMsg;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOk;
    QPushButton *btnCancle;

    void setupUi(QDialog *dialogUserEdit)
    {
        if (dialogUserEdit->objectName().isEmpty())
            dialogUserEdit->setObjectName(QString::fromUtf8("dialogUserEdit"));
        dialogUserEdit->resize(410, 353);
        gridLayoutWidget = new QWidget(dialogUserEdit);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 371, 161));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labUser = new QLabel(gridLayoutWidget);
        labUser->setObjectName(QString::fromUtf8("labUser"));
        QFont font;
        font.setPointSize(14);
        labUser->setFont(font);

        gridLayout->addWidget(labUser, 0, 0, 1, 1);

        labPwd = new QLabel(gridLayoutWidget);
        labPwd->setObjectName(QString::fromUtf8("labPwd"));
        labPwd->setFont(font);

        gridLayout->addWidget(labPwd, 1, 0, 1, 1);

        editUser = new QLineEdit(gridLayoutWidget);
        editUser->setObjectName(QString::fromUtf8("editUser"));
        editUser->setFont(font);

        gridLayout->addWidget(editUser, 0, 1, 1, 1);

        editPwd = new QLineEdit(gridLayoutWidget);
        editPwd->setObjectName(QString::fromUtf8("editPwd"));
        editPwd->setFont(font);
        editPwd->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(editPwd, 1, 1, 1, 1);

        labPwdChk = new QLabel(gridLayoutWidget);
        labPwdChk->setObjectName(QString::fromUtf8("labPwdChk"));
        labPwdChk->setFont(font);

        gridLayout->addWidget(labPwdChk, 2, 0, 1, 1);

        editPwdChk = new QLineEdit(gridLayoutWidget);
        editPwdChk->setObjectName(QString::fromUtf8("editPwdChk"));
        editPwdChk->setFont(font);
        editPwdChk->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(editPwdChk, 2, 1, 1, 1);

        groupBox = new QGroupBox(dialogUserEdit);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 190, 371, 61));
        btnAdmin = new QRadioButton(groupBox);
        btnAdmin->setObjectName(QString::fromUtf8("btnAdmin"));
        btnAdmin->setGeometry(QRect(10, 20, 98, 19));
        btnAdmin->setFont(font);
        btnOperator = new QRadioButton(groupBox);
        btnOperator->setObjectName(QString::fromUtf8("btnOperator"));
        btnOperator->setGeometry(QRect(130, 10, 121, 41));
        btnOperator->setFont(font);
        btnView = new QRadioButton(groupBox);
        btnView->setObjectName(QString::fromUtf8("btnView"));
        btnView->setGeometry(QRect(270, 10, 98, 41));
        btnView->setFont(font);
        labMsg = new QLabel(dialogUserEdit);
        labMsg->setObjectName(QString::fromUtf8("labMsg"));
        labMsg->setGeometry(QRect(20, 260, 271, 31));
        labMsg->setFont(font);
        horizontalLayoutWidget = new QWidget(dialogUserEdit);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(190, 290, 191, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnOk = new QPushButton(horizontalLayoutWidget);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setMinimumSize(QSize(30, 30));
        btnOk->setFont(font);

        horizontalLayout->addWidget(btnOk);

        btnCancle = new QPushButton(horizontalLayoutWidget);
        btnCancle->setObjectName(QString::fromUtf8("btnCancle"));
        btnCancle->setFont(font);

        horizontalLayout->addWidget(btnCancle);


        retranslateUi(dialogUserEdit);

        QMetaObject::connectSlotsByName(dialogUserEdit);
    } // setupUi

    void retranslateUi(QDialog *dialogUserEdit)
    {
        dialogUserEdit->setWindowTitle(QCoreApplication::translate("dialogUserEdit", "Dialog", nullptr));
        labUser->setText(QCoreApplication::translate("dialogUserEdit", "User name            ", nullptr));
        labPwd->setText(QCoreApplication::translate("dialogUserEdit", "Password", nullptr));
        labPwdChk->setText(QCoreApplication::translate("dialogUserEdit", "Password check", nullptr));
        groupBox->setTitle(QString());
        btnAdmin->setText(QCoreApplication::translate("dialogUserEdit", "Admin", nullptr));
        btnOperator->setText(QCoreApplication::translate("dialogUserEdit", "Operator", nullptr));
        btnView->setText(QCoreApplication::translate("dialogUserEdit", "View", nullptr));
        labMsg->setText(QString());
        btnOk->setText(QCoreApplication::translate("dialogUserEdit", "ok", nullptr));
        btnCancle->setText(QCoreApplication::translate("dialogUserEdit", "Cancle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialogUserEdit: public Ui_dialogUserEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGUSEREDIT_H
