#ifndef DIALOGUSER_H
#define DIALOGUSER_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include "SecureUdp.h"

namespace Ui {
class dialogUser;
}

class dialogUser : public QDialog
{
    Q_OBJECT

public:
    explicit dialogUser(SecureUdp *s, QWidget *parent = nullptr);
    ~dialogUser();

private:
    Ui::dialogUser *ui;

	SecureUdp *secUdp;

private slots:
	void handleResponse(Device *dev, const QJsonObject &obj);
};

#endif // DIALOGUSER_H
