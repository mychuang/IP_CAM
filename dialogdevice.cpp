#include "dialogdevice.h"
#include "ui_dialogdevice.h"
#include <QJsonArray>

dialogDevice::dialogDevice(SecureUdp *s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogDevice), secUdp(s)
{
    ui->setupUi(this);

	QString mac;
	Device *dev = s->getDevice();
	mac.sprintf("%02x:%02x:%02x:%02x:%02x:%02x",
		dev->mac[0], dev->mac[1], dev->mac[2], dev->mac[3], dev->mac[4], dev->mac[5]);
	ui->labelMAC->setText(mac);
	ui->editName->setText(dev->name);
	ui->labelModel->setText(QString(dev->model));
	ui->labUser->setText("\"" + dev->username + "\"  Login");
	ui->labUser->setStyleSheet("color: rgb(89, 95, 207)");

	//
	connect(ui->btnOn, &QAbstractButton::clicked, this, &dialogDevice::dhcpOn);
	connect(ui->btnOff, &QAbstractButton::clicked, this, &dialogDevice::dhcpOff);
}

dialogDevice::~dialogDevice()
{
    delete ui;
}

void dialogDevice::updateDevInfo(const QJsonObject &obj) {
	qDebug() << __func__;
	QString dns;
	QJsonArray array = obj["dns"].toArray();

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
		qDebug() << "hi";
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
}

void dialogDevice::dhcpOn(){
	qDebug() << __func__;

	ui->editIP->setDisabled(true);
	ui->editNetmask->setDisabled(true);
	ui->editGateway->setDisabled(true);
	ui->editDNS->setDisabled(true);
}

void dialogDevice::dhcpOff(){
	qDebug() << __func__;

	ui->editIP->setDisabled(false);
	ui->editNetmask->setDisabled(false);
	ui->editGateway->setDisabled(false);
	ui->editDNS->setDisabled(false);
}