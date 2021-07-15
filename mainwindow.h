#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Secureudp.h"
#include "dialoguser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	SecureUdp secUdp;
	dialogUser dialogUserObj;

private:
    Ui::MainWindow *ui;

	void initialUI();

private slots:
	void scanning();
	void cleanTable();
	void updateTable(Device *dev);
	void signInOpen(int row, int column);
	void handleResponse(Device *dev, const QJsonObject &obj);
	//hangle userDialog
	void handleUserAdd(QString username, QString password, QString authority) { 
		secUdp.cmdAddUser(username, password, authority);
	};
	void handleUserEdit(QString username, QString password, QString authority) { 
		secUdp.cmdSetUser(username, password, authority);
	};
	void handleUserDel(QString username) { secUdp.cmdDelUser(username);};
	void handleUserQuit() { secUdp.prob(); };
};

#endif // MAINWINDOW_H
