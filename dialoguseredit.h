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
	dialogUserEdit(const QString &user, const QString &auth, QWidget *parent = nullptr);
    ~dialogUserEdit();

	QString username();
	QString password();
	QString authority();

private:
    Ui::dialogUserEdit *ui;

private slots:
	void onOkClick();
	void onCancelClick();
};

#endif // DIALOGUSEREDIT_H
