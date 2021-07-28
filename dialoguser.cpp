#include "dialoguser.h"
#include "ui_dialoguser.h"
#include <QMessageBox>
#include <QRegExpValidator>
#include "dialoguseredit.h"
#include "Utils.h"

dialogUser::dialogUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogUser)
{
    ui->setupUi(this);
	setWindowTitle("User List");
	ui->tableWidget->setColumnWidth(0, 300);

	connect(ui->btnAdd, &QPushButton::clicked, this, &dialogUser::userAddOpen);
	connect(ui->btnEdit, &QPushButton::clicked, this, &dialogUser::userEditOpen);
	connect(ui->btnDel, &QPushButton::clicked, this, &dialogUser::userDel);
	connect(ui->btnQuit, &QPushButton::clicked, this, &dialogUser::userQuit);
	connect(ui->tableWidget, &QTableWidget::cellClicked, this, &dialogUser::DelBtnUI);
	
	//Utils::enableButtonWithUI(true, nullptr);
}

dialogUser::~dialogUser()
{
    delete ui;
}

void dialogUser::updateUserinfo(const QJsonObject &obj, Device *dev) {
	if (SHOWDEBUG) qDebug() << __func__;
	currentUser = dev->username;
	ui->label->setText(currentUser + "  Login");

	ui->tableWidget->setRowCount(0);
	QJsonArray array = obj["users"].toArray();

	foreach(const QJsonValue & value, array) {
		QJsonObject user = value.toObject();
		int row = ui->tableWidget->rowCount();
		ui->tableWidget->setRowCount(row + 1);
		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(user["username"].toString()));
		QString auth = user["userauth"].toString();
		if (SHOWDEBUG) qDebug() << auth;
		if (QString::compare(auth, "0") == 0) {
			ui->tableWidget->setItem(row, 1, new QTableWidgetItem("Admin"));
		}
		else if (QString::compare(auth, "1") == 0) {
			ui->tableWidget->setItem(row, 1, new QTableWidgetItem("Operator"));
		}
		else if (QString::compare(auth, "2") == 0) {
			ui->tableWidget->setItem(row, 1, new QTableWidgetItem("Viewer"));
		}
		else {
			ui->tableWidget->setItem(row, 1, new QTableWidgetItem("Null"));
		}
	}
	ui->tableWidget->setColumnWidth(0, 135);
	ui->tableWidget->setColumnWidth(1, 135);

	emit ui->tableWidget->cellClicked(0, 0);
}

void dialogUser::userAddOpen(){
	if (SHOWDEBUG) qDebug() << __func__;
	dialogUserEdit dialog(this);

	if (dialog.exec() == QDialog::Accepted) {
		emit userAddSignal(dialog.username(), dialog.password(), dialog.authority());
		dialog.done(btnInt);
		done(btnInt);
	}

}

void dialogUser::userEditOpen(){
	if (SHOWDEBUG) qDebug() << __func__;
	int index;
	index = ui->tableWidget->currentRow();
	if (index >= 0) {
		QString user = ui->tableWidget->item(index, 0)->text();
		QString auth = ui->tableWidget->item(index, 1)->text();
		dialogUserEdit dialog(user, auth, this);
		if (dialog.exec() == QDialog::Accepted) {
			emit userEditSignal(user, dialog.password(), dialog.authority());
			dialog.done(btnInt);
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
	if (SHOWDEBUG) qDebug() << "currentRow:" << ui->tableWidget->currentRow();

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
	//emit userQuitSignal();
	done(btnQuit);
}

void dialogUser::DelBtnUI(int row, int column) {
	if (QString::compare(currentUser, ui->tableWidget->item(row, 0)->text()) == 0) {
		ui->btnDel->setEnabled(false);
		ui->btnDel->setStyleSheet("background-color: rgb(206, 207, 192);"
			                      "color: rgb(255, 255, 255)");
	}
	else {
		ui->btnDel->setEnabled(true);
		ui->btnDel->setStyleSheet("hover {background-color: #dade73; color: #0dadde}"
			                      "background-color: #bcaaa4");
	}

}