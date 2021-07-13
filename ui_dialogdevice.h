/********************************************************************************
** Form generated from reading UI file 'dialogdevice.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDEVICE_H
#define UI_DIALOGDEVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialogDevice
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *labModel;
    QLabel *labelModel;
    QLabel *labMAC;
    QLabel *labelMAC;
    QLabel *labName;
    QLineEdit *editName;
    QLabel *labDHCP;
    QHBoxLayout *horizontalLayout;
    QRadioButton *btnOn;
    QRadioButton *btnOff;
    QSpacerItem *horizontalSpacer;
    QLabel *labIP;
    QLineEdit *editIP;
    QLabel *labNetmask;
    QLineEdit *editNetmask;
    QLabel *labGateway;
    QLineEdit *editGateway;
    QLabel *labDNS;
    QLineEdit *editDNS;
    QLabel *labUser;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnUpdate;
    QPushButton *btnEdit;
    QPushButton *btnExit;

    void setupUi(QDialog *dialogDevice)
    {
        if (dialogDevice->objectName().isEmpty())
            dialogDevice->setObjectName(QString::fromUtf8("dialogDevice"));
        dialogDevice->resize(435, 446);
        formLayoutWidget = new QWidget(dialogDevice);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(50, 50, 321, 286));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        labModel = new QLabel(formLayoutWidget);
        labModel->setObjectName(QString::fromUtf8("labModel"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        labModel->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, labModel);

        labelModel = new QLabel(formLayoutWidget);
        labelModel->setObjectName(QString::fromUtf8("labelModel"));
        QFont font1;
        font1.setPointSize(14);
        labelModel->setFont(font1);

        formLayout->setWidget(0, QFormLayout::FieldRole, labelModel);

        labMAC = new QLabel(formLayoutWidget);
        labMAC->setObjectName(QString::fromUtf8("labMAC"));
        labMAC->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, labMAC);

        labelMAC = new QLabel(formLayoutWidget);
        labelMAC->setObjectName(QString::fromUtf8("labelMAC"));
        labelMAC->setFont(font1);

        formLayout->setWidget(1, QFormLayout::FieldRole, labelMAC);

        labName = new QLabel(formLayoutWidget);
        labName->setObjectName(QString::fromUtf8("labName"));
        labName->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, labName);

        editName = new QLineEdit(formLayoutWidget);
        editName->setObjectName(QString::fromUtf8("editName"));
        editName->setFont(font1);

        formLayout->setWidget(2, QFormLayout::FieldRole, editName);

        labDHCP = new QLabel(formLayoutWidget);
        labDHCP->setObjectName(QString::fromUtf8("labDHCP"));
        labDHCP->setFont(font);

        formLayout->setWidget(3, QFormLayout::LabelRole, labDHCP);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnOn = new QRadioButton(formLayoutWidget);
        btnOn->setObjectName(QString::fromUtf8("btnOn"));
        btnOn->setFont(font1);

        horizontalLayout->addWidget(btnOn);

        btnOff = new QRadioButton(formLayoutWidget);
        btnOff->setObjectName(QString::fromUtf8("btnOff"));
        btnOff->setFont(font1);

        horizontalLayout->addWidget(btnOff);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout);

        labIP = new QLabel(formLayoutWidget);
        labIP->setObjectName(QString::fromUtf8("labIP"));
        labIP->setFont(font);

        formLayout->setWidget(4, QFormLayout::LabelRole, labIP);

        editIP = new QLineEdit(formLayoutWidget);
        editIP->setObjectName(QString::fromUtf8("editIP"));
        editIP->setFont(font1);

        formLayout->setWidget(4, QFormLayout::FieldRole, editIP);

        labNetmask = new QLabel(formLayoutWidget);
        labNetmask->setObjectName(QString::fromUtf8("labNetmask"));
        labNetmask->setFont(font);

        formLayout->setWidget(5, QFormLayout::LabelRole, labNetmask);

        editNetmask = new QLineEdit(formLayoutWidget);
        editNetmask->setObjectName(QString::fromUtf8("editNetmask"));
        editNetmask->setFont(font1);

        formLayout->setWidget(5, QFormLayout::FieldRole, editNetmask);

        labGateway = new QLabel(formLayoutWidget);
        labGateway->setObjectName(QString::fromUtf8("labGateway"));
        labGateway->setFont(font);

        formLayout->setWidget(6, QFormLayout::LabelRole, labGateway);

        editGateway = new QLineEdit(formLayoutWidget);
        editGateway->setObjectName(QString::fromUtf8("editGateway"));
        editGateway->setFont(font1);

        formLayout->setWidget(6, QFormLayout::FieldRole, editGateway);

        labDNS = new QLabel(formLayoutWidget);
        labDNS->setObjectName(QString::fromUtf8("labDNS"));
        labDNS->setFont(font);

        formLayout->setWidget(7, QFormLayout::LabelRole, labDNS);

        editDNS = new QLineEdit(formLayoutWidget);
        editDNS->setObjectName(QString::fromUtf8("editDNS"));
        editDNS->setFont(font1);

        formLayout->setWidget(7, QFormLayout::FieldRole, editDNS);

        labUser = new QLabel(dialogDevice);
        labUser->setObjectName(QString::fromUtf8("labUser"));
        labUser->setGeometry(QRect(50, 10, 141, 41));
        labUser->setFont(font1);
        horizontalLayoutWidget_2 = new QWidget(dialogDevice);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(50, 340, 321, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnUpdate = new QPushButton(horizontalLayoutWidget_2);
        btnUpdate->setObjectName(QString::fromUtf8("btnUpdate"));
        btnUpdate->setMinimumSize(QSize(30, 50));
        btnUpdate->setFont(font1);

        horizontalLayout_2->addWidget(btnUpdate);

        btnEdit = new QPushButton(horizontalLayoutWidget_2);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));
        btnEdit->setMinimumSize(QSize(30, 50));
        btnEdit->setFont(font1);

        horizontalLayout_2->addWidget(btnEdit);

        btnExit = new QPushButton(horizontalLayoutWidget_2);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setMinimumSize(QSize(30, 50));
        btnExit->setFont(font1);

        horizontalLayout_2->addWidget(btnExit);


        retranslateUi(dialogDevice);

        QMetaObject::connectSlotsByName(dialogDevice);
    } // setupUi

    void retranslateUi(QDialog *dialogDevice)
    {
        dialogDevice->setWindowTitle(QCoreApplication::translate("dialogDevice", "Dialog", nullptr));
        labModel->setText(QCoreApplication::translate("dialogDevice", "Model", nullptr));
        labelModel->setText(QString());
        labMAC->setText(QCoreApplication::translate("dialogDevice", "MAC", nullptr));
        labelMAC->setText(QString());
        labName->setText(QCoreApplication::translate("dialogDevice", "Name", nullptr));
        labDHCP->setText(QCoreApplication::translate("dialogDevice", "DHCP", nullptr));
        btnOn->setText(QCoreApplication::translate("dialogDevice", "on", nullptr));
        btnOff->setText(QCoreApplication::translate("dialogDevice", "off", nullptr));
        labIP->setText(QCoreApplication::translate("dialogDevice", "IP", nullptr));
        labNetmask->setText(QCoreApplication::translate("dialogDevice", "Netmask", nullptr));
        labGateway->setText(QCoreApplication::translate("dialogDevice", "Gateway", nullptr));
        labDNS->setText(QCoreApplication::translate("dialogDevice", "DNS", nullptr));
        labUser->setText(QCoreApplication::translate("dialogDevice", "user Login", nullptr));
        btnUpdate->setText(QCoreApplication::translate("dialogDevice", "Update", nullptr));
        btnEdit->setText(QCoreApplication::translate("dialogDevice", "User Edit", nullptr));
        btnExit->setText(QCoreApplication::translate("dialogDevice", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialogDevice: public Ui_dialogDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDEVICE_H
