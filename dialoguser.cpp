#include "dialoguser.h"
#include "ui_dialoguser.h"
#include <QMessageBox>
#include "dialoguseredit.h"


dialogUser::dialogUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogUser)
{
    ui->setupUi(this);
	ui->tableWidget->setColumnWidth(0, 300);

	connect(ui->btnAdd, &QPushButton::clicked, this, &dialogUser::userAddOpen);
	connect(ui->btnEdit, &QPushButton::clicked, this, &dialogUser::userEditOpen);

	connect(ui->btnDel, &QPushButton::clicked, this, &dialogUser::userDel);
	connect(ui->btnQuit, &QPushButton::clicked, this, &dialogUser::userQuit);
}

dialogUser::~dialogUser()
{
    delete ui;
}

void dialogUser::updateUserinfo(const QJsonObject &obj) {
	ui->tableWidget->setRowCount(0);
	QJsonArray array = obj["users"].toArray();

	foreach(const QJsonValue & value, array) {
		QJsonObject user = value.toObject();
		int row = ui->tableWidget->rowCount();
		ui->tableWidget->setRowCount(row + 1);
		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(user["username"].toString()));
	}
	ui->tableWidget->setCurrentCell(0, 0);
}

void dialogUser::userAddOpen(){
	qDebug() << __func__;
	dialogUserEdit dialog(this);

	if (dialog.exec() == QDialog::Accepted) {
		emit userAddSignal(dialog.username(), dialog.password(), dialog.authority());
		dialog.done(3);
		done(btnInt);
	}

}

void dialogUser::userEditOpen(){
	qDebug() << __func__;
	int index;
	index = ui->tableWidget->currentRow();
	if (index >= 0) {
		QString user = ui->tableWidget->item(index, 0)->text();
		dialogUserEdit dialog(user, this);
		if (dialog.exec() == QDialog::Accepted) {
			emit userEditSignal(user, dialog.password(), dialog.authority());
			dialog.done(3);
			done(btnInt);
		}
	}
}

void dialogUser::userDel(){
	int reply;

	if (ui->tableWidget->rowCount() == 1) {
		reply = QMessageBox::question(this, "User Delete", "You cannot delete the last user.  ", QMessageBox::Ok);
		return;
	}

	int index;
	index = ui->tableWidget->currentRow();
	qDebug() << "currentRow:" << ui->tableWidget->currentRow();

	reply = QMessageBox::question(this, "User Delete", "Do you want delecte user:" + 
		ui->tableWidget->item(index, 0)->text() + " ?",
		QMessageBox::Yes | QMessageBox::No);

	if (reply == QMessageBox::Yes) {
		if (index >= 0) {
			emit userDelSignal(ui->tableWidget->item(index, 0)->text());
			done(btnInt);
		}
	}
}

void dialogUser::userQuit(){
	emit userQuitSignal();
	done(btnQuit);
}