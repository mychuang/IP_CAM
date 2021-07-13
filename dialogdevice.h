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

private:
    Ui::dialogDevice *ui;

	SecureUdp *secUdp;
};

#endif // DIALOGDEVICE_H
