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
    explicit dialogDevice(SecureUdp *s, QWidget *parent = nullptr);
    ~dialogDevice();

	void updateDevInfo(const QJsonObject &obj);
	static const int btnUserEdit = 2;
private:
    Ui::dialogDevice *ui;

	SecureUdp *secUdp;
	void setDevInfo(QJsonObject &obj);

private slots:
	void dhcpOn();
	void dhcpOff();
	void setNetwork();
	void userEditReturn();
};

#endif // DIALOGDEVICE_H
