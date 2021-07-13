#include "dialogdevice.h"
#include "ui_dialogdevice.h"

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


	
}

dialogDevice::~dialogDevice()
{
    delete ui;
}

