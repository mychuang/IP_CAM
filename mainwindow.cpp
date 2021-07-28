#include <QMessageBox>
#include <QMovie>
#include <QSize>
#include <QDir>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogLogin.h"



uint8_t mac[6];
extern QList<Device *> deviceList;
QString getMacAddress(uint8_t *mac) {
	QString from;

	foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces()) {
		
		if (!(netInterface.flags() & QNetworkInterface::IsLoopBack)) {
			QString strMac = netInterface.hardwareAddress();

			for (int i = 0; i < 6; i++) {
				mac[i] = (uint8_t)(strMac.mid(i * 3, 2).toInt(NULL, 16));
			}
			if (SHOWDEBUG) qDebug() << strMac;
			return strMac;
		}
	}
	return NULL;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), secUdp(NULL),
	dialogDeviceObj(this), dialogUserObj(this)
{
    ui->setupUi(this);

#if QThreadEnabled == 1
	secUdp.start();
#endif

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
	connect(&dialogUserObj, &dialogUser::userAddSignal, this, &MainWindow::handleUserAdd);
	connect(&dialogUserObj, &dialogUser::userEditSignal, this, &MainWindow::handleUserEdit);
	//dialogDevice connection
	connect(&dialogDeviceObj, &dialogDevice::setNetworkSignal, this, &MainWindow::handleSetNetwork);
}

MainWindow::~MainWindow()
{
#if QThreadEnabled == 1
	secUdp.stop();
	secUdp.wait();
#endif
    delete ui;
}

void MainWindow::initialUI() {
	setWindowTitle("Lumens Device Search v2.3");
	ui->tableWidget->setRowCount(0);
	ui->tableWidget->setColumnWidth(0, 180);
	ui->tableWidget->setColumnWidth(1, 210);
	ui->tableWidget->setColumnWidth(2, 210);
	ui->tableWidget->setColumnWidth(3, 180);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


	//Btn UI
	ui->probBtn->setStyleSheet("background-color: rgb(166, 225, 252);"
		"font: 87 12pt Arial Black;" 
		"color: rgb(0, 0, 0);");
	ui->cleanBtn->setStyleSheet("background-color: rgb(167,251,183);"
		                       "font: 87 12pt Arial Black;"
		                       "color: rgb(0, 0, 0)");
}

void MainWindow::waitAnimation(bool running) {

	QString imageFile = NULL;
	imageFile = QDir::currentPath() + "/Image/loading-noise.gif";

	QSize si(ui->labFig->width(), ui->labFig->height());
	QMovie *m_movie = new QMovie(imageFile);

	m_movie->setScaledSize(si);
	if (running == true) {
		m_movie->start();
		ui->labFig->setMovie(m_movie);
	}
	else {
		ui->labFig->setMovie(NULL);
	}

	ui->tableWidget->blockSignals(true);
	ui->tableWidget->setAlternatingRowColors(true);
	ui->tableWidget->setStyleSheet("alternate-background-color: #8080ab;" 
		                           "background: white; color: #21d9c9;" 
		                          );
}

void MainWindow::scanning() {
	ui->probBtn->setStyleSheet("background-color: rgb(179, 179, 179);""color: rgb(255, 255, 255)");
	ui->probBtn->setEnabled(false);
	secUdp.prob();
}

void MainWindow::cleanTable() {
	if (SHOWDEBUG) qDebug() << __func__;
	ui->tableWidget->clear();
	ui->tableWidget->setRowCount(0);
	secUdp.cleanDeviceList();
	ui->probBtn->setEnabled(true);
    ui->probBtn->setStyleSheet("background-color: rgb(166, 225, 252);"
		"font: 87 12pt Arial Black;"
		"color: rgb(0, 0, 0)");
	QStringList tableHeader = { "MAC", "Model", "Name", "IP" };
	ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
	//ui->cleanBtn->setStyleSheet("background-color: rgb(166, 225, 252);"
	//	                        "font: 87 8pt Arial Black;"
	//	                        "color: rgb(0, 0, 0)");
}

void MainWindow::updateTable(Device *dev)
{
	if (SHOWDEBUG) qDebug() << __func__;
	int row = ui->tableWidget->rowCount();

	QString from;
	from.sprintf("%02x:%02x:%02x:%02x:%02x:%02x",
		dev->mac[0], dev->mac[1], dev->mac[2], dev->mac[3], dev->mac[4], dev->mac[5]);

	ui->tableWidget->setRowCount(row + 1);
	ui->tableWidget->setItem(row, 0, new QTableWidgetItem(from));
	ui->tableWidget->setItem(row, 1, new QTableWidgetItem(dev->model));
	ui->tableWidget->setItem(row, 2, new QTableWidgetItem(dev->name));
	ui->tableWidget->setItem(row, 3, new QTableWidgetItem(dev->ip));

	//ui setting
	ui->tableWidget->setAlternatingRowColors(true);
	ui->tableWidget->setStyleSheet("alternate-background-color: #e1eef0;" 
		                           "background: white; color: #2126cc;" 
		                           "font: 10pt Comic Sans MS;");
}

void MainWindow::signInOpen(int row, int column){
	if (SHOWDEBUG) qDebug() << __func__;

	Device *dev = deviceList[row];

	dialogLogin dialog(ui->userNameEdit->text(), ui->passwordEdit->text(), this);

	if (dialog.exec() == QDialog::Accepted) {
		QRegExp rx;
		rx.setPattern("\\S+");
		QRegExpValidator v(rx, 0);
		v.setRegExp(rx);
		int pos = 0;

		if (v.validate(dialog.getUsername(), pos) == QValidator::Invalid || 
			v.validate(dialog.getPassword(), pos) == QValidator::Intermediate) {
			QMessageBox msgbox;
			msgbox.setText("Invalid input");
			msgbox.exec();
		}
		else {
			dev->username = dialog.getUsername();
			dev->password = dialog.getPassword();
			secUdp.setDevice(dev);
			secUdp.cmdSend("GetNetwork", NULL);
		}
	}
}

void MainWindow::handleResponse(Device *dev, const QJsonObject &obj) {
	if (SHOWDEBUG) qDebug() << "MainWindow::handleResponse";

	if (obj["response"] == "error") {
		QMessageBox msgbox;
		msgbox.setText(obj["detail"].toString());
		msgbox.exec();
		waitAnimation(false);
		ui->tableWidget->blockSignals(false);
		ui->tableWidget->setAlternatingRowColors(true);
		ui->tableWidget->setStyleSheet("alternate-background-color: #dcf2d8; background:" 
			                           "white; color: #152ae8;"
		                               "font: 10pt Comic Sans MS;");
		return;
	}
	else if (obj["response"] == "SetNetwork") {
		cleanTable();
		scanning();
		return;
	}
	else if (obj["response"] == "GetNetwork") {
		Device *dev = secUdp.getDevice();
		dialogDeviceObj.updateDevInfo(obj, dev);
		
		int ret = dialogDeviceObj.exec();
		if (ret == dialogDevice::btnUserEdit) { // edit users
			secUdp.cmdSend("GetUsers", NULL);
		}
		return;
	}
	else if (obj["response"] == "GetUsers") {
		Device *dev = secUdp.getDevice();
		if (SHOWDEBUG) qDebug() << dev->username;
		dialogUserObj.updateUserinfo(obj, dev);
		dialogUserObj.exec();
		return;
	}
	else if (obj["response"] == "DelUser" ||
		     obj["response"] == "AddUser" ||
		     obj["response"] == "SetUser") {
		waitAnimation(false);
		ui->tableWidget->blockSignals(false);
		ui->tableWidget->setAlternatingRowColors(true);
		ui->tableWidget->setStyleSheet("alternate-background-color: #dcf2d8;" 
			                           "background: white; color: #152ae8;" 
			                           "font: 10pt Comic Sans MS;");
		secUdp.cmdSend("GetUsers", NULL);
		return;
	}
	else {
		QMessageBox msgbox;
		msgbox.setText("Unknow Json Obj");
		msgbox.exec();
		return;
	}
}

void MainWindow::handleUserAdd(QString username, QString password, QString authority) {
	secUdp.cmdAddUser(username, password, authority);
	waitAnimation(true);
};

void MainWindow::handleUserEdit(QString username, QString password, QString authority) {
	secUdp.cmdSetUser(username, password, authority);
	waitAnimation(true);
};
void MainWindow::handleUserDel(QString username) {
	secUdp.cmdDelUser(username);
	waitAnimation(true);
};
