#ifndef DIALOGUSER_H
#define DIALOGUSER_H

#include <QDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include "secureUdp.h"

namespace Ui {
class dialogUser;
}

class dialogUser : public QDialog
{
    Q_OBJECT

public:
    explicit dialogUser(QWidget *parent = nullptr);
    ~dialogUser();

	void updateUserinfo(const QJsonObject &obj, Device *dev);
	static const int btnQuit = 2;
	static const int btnInt = 3;

private:
    Ui::dialogUser *ui;
	QString currentUser;


private slots:
	void userEditOpen();
	void userAddOpen();
	void userDel();
	void userQuit();
	void updateDelBtnUI(int row, int column);

signals:
	void userQuitSignal();
	void userDelSignal(QString username);
	void userEditSignal(QString username, QString password, QString authority);
	void userAddSignal(QString username, QString password, QString authority);
};

#endif // DIALOGUSER_H
