#ifndef DIALOGDEVICE_H
#define DIALOGDEVICE_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include "SecureUdp.h"

namespace Ui {
class dialogDevice;
}

class dialogDevice : public QDialog
{
    Q_OBJECT

public:
    explicit dialogDevice(QWidget *parent = nullptr);
    ~dialogDevice();

	void updateDevInfo(const QJsonObject &obj, Device *dev);
	static const int btnUserEdit = 2;
	static const int btnOk = 3;

private:
    Ui::dialogDevice *ui;

	void setDevInfo(QJsonObject &obj);

private slots:
	void dhcpOn();
	void dhcpOff();
	void setNetwork();
	void userEditReturn();
	void dialogQuit() { done(btnOk); };

signals:
	void setNetworkSignal(QJsonObject *obj);
};

#endif // DIALOGDEVICE_H
