#include "dialoguseredit.h"
#include "ui_dialoguseredit.h"
#include <QAbstractButton>
#include <QDebug>
#include <QRegExpValidator>

dialogUserEdit::dialogUserEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogUserEdit)
{
    ui->setupUi(this);
	setWindowTitle("User Edit");
	ui->btnAdmin->setChecked(true);
	connect(ui->btnOk, &QPushButton::clicked, this, &dialogUserEdit::onOkClick);
	connect(ui->btnCancle, &QPushButton::clicked, this, &dialogUserEdit::onCancelClick);

}

dialogUserEdit::dialogUserEdit(const QString &user, const QString &auth, QWidget *parent):
	QDialog(parent),
	ui(new Ui::dialogUserEdit) 
{
	ui->setupUi(this);
	ui->editUser->setReadOnly(true);
	ui->editUser->setText(user);

	if (QString::compare(auth, "Admin") == 0) {
		ui->btnAdmin->setChecked(true);
	}
	else if (QString::compare(auth, "Operator") == 0) {
		ui->btnOperator->setChecked(true);
	}
	else {
		ui->btnView->setChecked(true);
	}

	connect(ui->btnOk, &QPushButton::clicked, this, &dialogUserEdit::onOkClick);
	connect(ui->btnCancle, &QPushButton::clicked, this, &dialogUserEdit::onCancelClick);
}

dialogUserEdit::~dialogUserEdit()
{
    delete ui;
}

void dialogUserEdit::onCancelClick(){
	reject();
}

void dialogUserEdit::onOkClick(){
	QRegExp rx;
	rx.setPattern("\\S+");
	QRegExpValidator v(rx, 0);
	v.setRegExp(rx);
	int pos = 0;

	ui->labMsg->setText("");
	if (v.validate(ui->editUser->text(), pos) == QValidator::Invalid ||
		v.validate(ui->editUser->text(), pos) == QValidator::Intermediate ||
		v.validate(ui->editPwd->text(), pos) == QValidator::Invalid ||
		v.validate(ui->editPwd->text(), pos) == QValidator::Intermediate) {
		ui->labMsg->setText("Invalid name or password");
	}
	else {
		if (QString::compare(ui->editPwd->text(), ui->editPwdChk->text()) == 0) {
			accept();
		}
		else {
			ui->labMsg->setText("Please confirm password");
		}
	}

}

QString dialogUserEdit::username(){
	return ui->editUser->text();
}

QString dialogUserEdit::password(){
	return ui->editPwd->text();
}

QString dialogUserEdit::authority() {
	if (ui->btnAdmin->isChecked()) {
		return QString("0");
	}
	else if (ui->btnOperator->isChecked()) {
		return QString("1");
	}
	else if (ui->btnView->isChecked()) {
		return QString("2");
	}
}