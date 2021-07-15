#ifndef DIALOGUSEREDIT_H
#define DIALOGUSEREDIT_H

#include <QDialog>

namespace Ui {
class dialogUserEdit;
}

class dialogUserEdit : public QDialog
{
    Q_OBJECT

public:
    explicit dialogUserEdit(QWidget *parent = nullptr);
	dialogUserEdit(const QString &user, QWidget *parent = nullptr);
    ~dialogUserEdit();

	QString username();
	QString password();
	QString authority();

private:
    Ui::dialogUserEdit *ui;

private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
};

#endif // DIALOGUSEREDIT_H
