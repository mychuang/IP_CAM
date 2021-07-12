#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Secureudp.h"

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

private:
    Ui::MainWindow *ui;

	void initialUI();

private slots:
	void scanning();
	void cleanTable();
	void updateTable(Device *dev);
};

#endif // MAINWINDOW_H
