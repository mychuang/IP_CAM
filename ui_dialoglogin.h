/********************************************************************************
** Form generated from reading UI file 'dialoglogin.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLOGIN_H
#define UI_DIALOGLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialogLogin
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *userlab;
    QLineEdit *userEdit;
    QLabel *pwdLab;
    QLineEdit *pwdEdit;

    void setupUi(QDialog *dialogLogin)
    {
        if (dialogLogin->objectName().isEmpty())
            dialogLogin->setObjectName(QString::fromUtf8("dialogLogin"));
        dialogLogin->resize(517, 234);
        buttonBox = new QDialogButtonBox(dialogLogin);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(160, 180, 341, 32));
        QFont font;
        font.setPointSize(12);
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        formLayoutWidget = new QWidget(dialogLogin);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 30, 491, 121));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        userlab = new QLabel(formLayoutWidget);
        userlab->setObjectName(QString::fromUtf8("userlab"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        userlab->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, userlab);

        userEdit = new QLineEdit(formLayoutWidget);
        userEdit->setObjectName(QString::fromUtf8("userEdit"));
        userEdit->setMinimumSize(QSize(30, 50));
        userEdit->setFont(font);

        formLayout->setWidget(0, QFormLayout::FieldRole, userEdit);

        pwdLab = new QLabel(formLayoutWidget);
        pwdLab->setObjectName(QString::fromUtf8("pwdLab"));
        pwdLab->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, pwdLab);

        pwdEdit = new QLineEdit(formLayoutWidget);
        pwdEdit->setObjectName(QString::fromUtf8("pwdEdit"));
        pwdEdit->setMinimumSize(QSize(20, 50));

        formLayout->setWidget(1, QFormLayout::FieldRole, pwdEdit);


        retranslateUi(dialogLogin);
        QObject::connect(buttonBox, SIGNAL(accepted()), dialogLogin, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dialogLogin, SLOT(reject()));

        QMetaObject::connectSlotsByName(dialogLogin);
    } // setupUi

    void retranslateUi(QDialog *dialogLogin)
    {
        dialogLogin->setWindowTitle(QCoreApplication::translate("dialogLogin", "Dialog", nullptr));
        userlab->setText(QCoreApplication::translate("dialogLogin", "User Name :", nullptr));
        pwdLab->setText(QCoreApplication::translate("dialogLogin", "Password :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialogLogin: public Ui_dialogLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOGIN_H
