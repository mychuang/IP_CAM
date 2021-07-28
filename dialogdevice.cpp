#include "dialogdevice.h"
#include "dialoguser.h"
#include "ui_dialogdevice.h"
#include <QJsonArray>
#include <QRegExpValidator>
#include <QMessageBox>

dialogDevice::dialogDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogDevice)
{
    ui->setupUi(this);
	setWindowTitle("Device Information");
	connect(ui->btnOn, &QAbstractButton::clicked, this, &dialogDevice::dhcpOn);
	connect(ui->btnOff, &QAbstractButton::clicked, this, &dialogDevice::dhcpOff);
	connect(ui->btnExit, &QAbstractButton::clicked, this, &dialogDevice::dialogQuit);
	connect(ui->btnUpdate, &QAbstractButton::clicked, this, &dialogDevice::setNetwork);
	connect(ui->btnEdit, &QAbstractButton::clicked, this, &dialogDevice::userEditReturn);
}

dialogDevice::~dialogDevice()
{
    delete ui;
}

void dialogDevice::updateDevInfo(const QJsonObject &obj, Device *dev) {
	if (SHOWDEBUG) qDebug() << __func__;
	QString dns;
	QJsonArray array = obj["dns"].toArray();
	if (SHOWDEBUG) qDebug() << obj;

	if (array.size() > 0) {
		dns = array[0].toString();
		for (int i = 1; i < array.size(); i++)
			dns += "," + array[i].toString();
	}

	ui->btnOff->setChecked(!obj["dhcp"].toBool());
	ui->btnOn->setChecked(obj["dhcp"].toBool());
	ui->editIP->setText(obj["ip"].toString());
	ui->editNetmask->setText(obj["netmask"].toString());
	ui->editGateway->setText(obj["gateway"].toString());
	ui->editDNS->setText(dns);
	
	if (obj["dhcp"].toBool()) {
		ui->editIP->setDisabled(true);
		ui->editNetmask->setDisabled(true);
		ui->editGateway->setDisabled(true);
		ui->editDNS->setDisabled(true);
	}
	else {
		ui->editIP->setDisabled(false);
		ui->editNetmask->setDisabled(false);
		ui->editGateway->setDisabled(false);
		ui->editDNS->setDisabled(false);
	}

	//set other UI
	QString mac;
	mac.sprintf("%02x:%02x:%02x:%02x:%02x:%02x",
		dev->mac[0], dev->mac[1], dev->mac[2], dev->mac[3], dev->mac[4], dev->mac[5]);
	ui->labelMAC->setText(mac);
    ui->editName->setText(dev->name);
	ui->labelModel->setText(QString(dev->model));

	//set User Label
	QString nowAuth = obj["nowauth"].toString();
	QString nowUser = obj["nowuser"].toString();

	if(QString::compare(nowAuth, "0") == 0) {
		ui->labUser->setText("\"" + nowUser + "\" Login (Admin)");
		ui->btnEdit->setEnabled(true);
		ui->btnEdit->setStyleSheet("hover {color: #laadad};" "background-color: #e0baba;");
	}
	else if (QString::compare(nowAuth, "1") == 0) {
		ui->labUser->setText("\"" + nowUser + "\" Login (Operator)");
		ui->btnEdit->setEnabled(false);
		ui->btnEdit->setStyleSheet("background-color: gray; color: white");
	}
	else if (QString::compare(nowAuth, "2") == 0) {
		ui->labUser->setText("\"" + nowUser + "\" Login (Viewer)");
		ui->btnEdit->setEnabled(false);
		ui->btnEdit->setStyleSheet("background-color: gray; color: white");
	}
	else {
		ui->labUser->setText("\"" + dev->username + "\"  Login");
		ui->btnEdit->setEnabled(true);
	}
	ui->labUser->setStyleSheet("color: rgb(89, 95, 207)");
}

void dialogDevice::dhcpOn(){
	if (SHOWDEBUG) qDebug() << __func__;

	ui->editIP->setDisabled(true);
	ui->editNetmask->setDisabled(true);
	ui->editGateway->setDisabled(true);
	ui->editDNS->setDisabled(true);
}

void dialogDevice::dhcpOff(){
	if (SHOWDEBUG) qDebug() << __func__;

	ui->editIP->setDisabled(false);
	ui->editNetmask->setDisabled(false);
	ui->editGateway->setDisabled(false);
	ui->editDNS->setDisabled(false);
}

void dialogDevice::setNetwork() {
	if (SHOWDEBUG) qDebug() << __func__;
	QJsonObject obj;

	if (setDevInfo(obj) == true) {
		emit setNetworkSignal(&obj);
		done(btnOk);
	}
}

bool dialogDevice::setDevInfo(QJsonObject &obj) {
	QStringList errInfo;
	QRegExp rx;
	rx.setPattern("\\S+");
	QRegExpValidator v(rx, 0);
	v.setRegExp(rx);
	int pos = 0;

	if (v.validate(ui->editName->text(), pos) == QValidator::Invalid ||
		v.validate(ui->editName->text(), pos) == QValidator::Intermediate) {
		if (SHOWDEBUG) qDebug() << "name error";
		errInfo.append("Name");
	}
	else {
		obj["devname"] = ui->editName->text();
		obj["dhcp"] = ui->btnOn->isChecked();
	}

	
	if (ui->btnOn->isChecked()) {
		if (SHOWDEBUG) qDebug() << "DHCP ON -> no others message";
	}

	if (ui->btnOff->isChecked()) {
		rx.setPattern("^(?:25[0-5]|2[0-4]\\d|[0-1]?\\d{1,2})(?:\\.(?:25[0-5]|2[0-4]\\d|[0-1]?\\d{1,2})){3}$");
		v.setRegExp(rx);
		int pos = 0;
		if (v.validate(ui->editIP->text(), pos) == QValidator::Invalid ||
			v.validate(ui->editIP->text(), pos) == QValidator::Intermediate) {
			errInfo.append("IP");
		}
		else {
			obj["ip"] = ui->editIP->text();
		}
		if (v.validate(ui->editNetmask->text(), pos) == QValidator::Invalid ||
			v.validate(ui->editNetmask->text(), pos) == QValidator::Intermediate) {
			errInfo.append("Netmask");
		}
		else {
			obj["netmask"] = ui->editNetmask->text();
		}
		if (v.validate(ui->editGateway->text(), pos) == QValidator::Invalid ||
			v.validate(ui->editGateway->text(), pos) == QValidator::Intermediate) {
			errInfo.append("Gateway");
		}
		else {
			obj["gateway"] = ui->editGateway->text();
		}

		QStringList dnsList = ui->editDNS->text().split(",", QString::SkipEmptyParts);
		int dnsErrorCnt = 0;
		for (int i = 0; i < dnsList.count(); i++) {
			if (v.validate(dnsList[i], pos) == QValidator::Invalid ||
				v.validate(dnsList[i], pos) == QValidator::Intermediate) {
				dnsErrorCnt++;
			}
		}
		if (dnsErrorCnt > 0) {
			errInfo.append("DNS");
		}
		else {
			QJsonArray array;
			for (int i = 0; i < dnsList.count(); i++) {
				array.append(dnsList[i]);
				if (SHOWDEBUG) qDebug() << "DNS: " << dnsList[i];
			}
			obj.insert("dns", array);
		}
	}

	if (errInfo.size() == 0) {
		return true;
	}
	else {
		QString errMsg = errInfo.join(",");
		QMessageBox msgbox;
		msgbox.setText("Invalid input: " + errMsg);
		msgbox.exec();
		return false;
	}
}

void dialogDevice::userEditReturn() {
	done(btnUserEdit);
}

