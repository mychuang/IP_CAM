#include "dialoglogin.h"
#include "ui_dialoglogin.h"

dialogLogin::dialogLogin(QString user, QString pass, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogLogin)
{
    ui->setupUi(this);
	setWindowTitle("Login");
	ui->userEdit->setText(user);
	ui->pwdEdit->setText(pass);
}

dialogLogin::~dialogLogin()
{
    delete ui;
}

QString dialogLogin::getUsername(){
	return ui->userEdit->text();
}

QString dialogLogin::getPassword(){
	return ui->pwdEdit->text();
}
