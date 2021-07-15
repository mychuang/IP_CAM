#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogLogin.h"
#include "dialogDevice.h"

uint8_t mac[6];
extern QList<Device *> deviceList;
QString getMacAddress(uint8_t *mac) {
	QString from;

	foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces()) {
		qDebug() << netInterface.addressEntries().at(1).ip();
		if (!(netInterface.flags() & QNetworkInterface::IsLoopBack)) {
			QString strMac = netInterface.hardwareAddress();

			for (int i = 0; i < 6; i++) {
				mac[i] = (uint8_t)(strMac.mid(i * 3, 2).toInt(NULL, 16));
			}
			qDebug() << strMac;
			return strMac;
		}
	}
	return NULL;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), secUdp(NULL)
{
    ui->setupUi(this);

    //UI
	initialUI();
    //get local MAC
	getMacAddress(mac);

	//UI object connection
	connect(ui->probBtn, &QPushButton::clicked, this, &MainWindow::scanning);
	connect(ui->cleanBtn, &QPushButton::clicked, this, &MainWindow::cleanTable);
	connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, this, &MainWindow::signInOpen);
    //model connection
	connect(&secUdp, &SecureUdp::newDeviceIn, this, &MainWindow::updateTable);
	connect(&secUdp, &SecureUdp::deviceResponse, this, &MainWindow::handleResponse);
	//dialogUser connection
	connect(&dialogUserObj, &dialogUser::userDelSignal, this, &MainWindow::handleUserDel);
	connect(&dialogUserObj, &dialogUser::userQuitSignal, this, &MainWindow::handleUserQuit);
	connect(&dialogUserObj, &dialogUser::userAddSignal, this, &MainWindow::handleUserAdd);
	connect(&dialogUserObj, &dialogUser::userEditSignal, this, &MainWindow::handleUserEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialUI() {
	ui->tableWidget->setRowCount(0);
	ui->tableWidget->setColumnWidth(0, 180);
	ui->tableWidget->setColumnWidth(1, 210);
	ui->tableWidget->setColumnWidth(2, 210);
	ui->tableWidget->setColumnWidth(3, 180);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//Btn UI
	ui->probBtn->setStyleSheet("background-color: rgb(166, 225, 252);"
		"font: 87 12pt Arial Black;"
		"color: rgb(0, 0, 0)");
	ui->cleanBtn->setStyleSheet("background-color: rgb(167,251,183);"
		"font: 87 12pt Arial Black;"
		"color: rgb(0, 0, 0)");
}

void MainWindow::scanning() {
	ui->probBtn->setStyleSheet("background-color: rgb(179, 179, 179);""color: rgb(255, 255, 255)");
	ui->probBtn->setEnabled(false);
	secUdp.prob();
}

void MainWindow::cleanTable() {
	qDebug() << __func__;
	ui->tableWidget->clear();
	ui->tableWidget->setRowCount(0);
	secUdp.cleanDeviceList();
	ui->probBtn->setEnabled(true);
    ui->probBtn->setStyleSheet("background-color: rgb(166, 225, 252);"
		"font: 87 12pt Arial Black;"
		"color: rgb(0, 0, 0)");
	QStringList tableHeader = { "MAC", "Model", "Name", "IP" };
	ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
}

void MainWindow::updateTable(Device *dev)
{
	qDebug() << __func__;
	int row = ui->tableWidget->rowCount();

	QString from;
	from.sprintf("%02x:%02x:%02x:%02x:%02x:%02x",
		dev->mac[0], dev->mac[1], dev->mac[2], dev->mac[3], dev->mac[4], dev->mac[5]);

	ui->tableWidget->setRowCount(row + 1);
	ui->tableWidget->setItem(row, 0, new QTableWidgetItem(from));
	ui->tableWidget->setItem(row, 1, new QTableWidgetItem(dev->model));
	ui->tableWidget->setItem(row, 2, new QTableWidgetItem(dev->name));
	ui->tableWidget->setItem(row, 3, new QTableWidgetItem(dev->ip));
}

void MainWindow::signInOpen(int row, int column){
	qDebug() << __func__;

	Device *dev = deviceList[row];

	dialogLogin dialog(ui->userNameEdit->text(), ui->passwordEdit->text(), this);

	if (dialog.exec() == QDialog::Accepted) {
		dev->username = dialog.getUsername();
		dev->password = dialog.getPassword();
		secUdp.setDevice(dev);
		secUdp.cmdSend("GetNetwork", NULL);
	}
}

void MainWindow::handleResponse(Device *dev, const QJsonObject &obj) {
	qDebug() << "MainWindow::handleResponse";

	if (obj["response"] == "error") {
		QMessageBox msgbox;
		msgbox.setText(obj["detail"].toString());
		msgbox.exec();
		return;
	}
	else if (obj["response"] == "SetNetwork") {
		cleanTable();
		scanning();
		return;
	}
	else if (obj["response"] == "GetNetwork") {
		dialogDevice dialog(&secUdp, this);
		dialog.updateDevInfo(obj);
		
		int ret = dialog.exec();
		if (ret == dialogDevice::btnUserEdit) { // edit users
			secUdp.cmdSend("GetUsers", NULL);
		}
		return;
	}
	else if (obj["response"] == "GetUsers") {
		dialogUserObj.updateUserinfo(obj);
		int ret = dialogUserObj.exec();
		if (ret == dialogUser::btnQuit) {
			dialogUserObj.close();
		}
		return;
	}
	else if (obj["response"] == "DelUser" ||
		     obj["response"] == "AddUser" ||
		     obj["response"] == "SetUser") {
		secUdp.cmdSend("GetUsers", NULL);
		return;
	}
}

