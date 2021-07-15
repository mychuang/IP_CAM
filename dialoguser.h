#ifndef DIALOGUSER_H
#define DIALOGUSER_H

#include <QDialog>
#include <QJsonArray>
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
    explicit dialogUser(QWidget *parent = nullptr);
    ~dialogUser();

	void updateUserinfo(const QJsonObject &obj);
	static const int btnQuit = 2;
	static const int btnDel = 3;

private:
    Ui::dialogUser *ui;

	SecureUdp *secUdp;

private slots:
	void handleResponse(Device *dev, const QJsonObject &obj);
	void userEditOpen();
	void userAddOpen();
	void userDel();
	void userQuit();

signals:
	void userQuitSignal();
	void userDelSignal(QString username);
};

#endif // DIALOGUSER_H
