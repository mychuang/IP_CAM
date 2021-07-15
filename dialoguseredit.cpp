#include "dialoguseredit.h"
#include "ui_dialoguseredit.h"
#include <QAbstractButton>

dialogUserEdit::dialogUserEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogUserEdit)
{
    ui->setupUi(this);
	ui->btnAdmin->setChecked(true);
}

dialogUserEdit::dialogUserEdit(const QString &user, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::dialogUserEdit) 
{
	ui->setupUi(this);
	ui->editUser->setReadOnly(true);
	ui->editUser->setText(user);

	ui->btnAdmin->setChecked(true);

}

dialogUserEdit::~dialogUserEdit()
{
    delete ui;
}

void dialogUserEdit::on_buttonBox_rejected(){
	reject();
}

void dialogUserEdit::on_buttonBox_accepted(){

	ui->labMsg->setText("");

	if (ui->editUser->text() == NULL || ui->editPwd->text() == NULL) {
		ui->labMsg->setText("Please add name or password");
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