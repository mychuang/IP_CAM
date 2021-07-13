#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>

namespace Ui {
class dialogLogin;
}

class dialogLogin : public QDialog
{
    Q_OBJECT

public:
	explicit dialogLogin(QString user = "", QString pass = "", QWidget *parent = 0);
    ~dialogLogin();

	QString getUsername();
	QString getPassword();

private:
    Ui::dialogLogin *ui;
};

#endif // DIALOGLOGIN_H
