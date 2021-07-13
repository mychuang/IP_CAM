#ifndef SECUREUDP_H
#define SECUREUDP_H

#include "crypto.h"
#include <QObject>
#include <QNetworkInterface>
#include <QUdpSocket>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>

#include "crypto.h"
#include "message.h"
#include "device.h"

class SecureUdp : public QObject
{
	Q_OBJECT

public:
	explicit SecureUdp(QObject *parent = nullptr);

	void prob();
	void cleanDeviceList();
	//void cmdSend(const QString &cmd, const QJsonObject *data);

private:
    void generateAesKey();
	void requestPublicKey(uint8_t *devMac);
	void setAesKey(Device *dev);
	void handleProbeResponse(Message *msg);
	Device *findDevice(uint8_t *mac);

	QHostAddress groupAddress;
	QUdpSocket udpSender;
	QUdpSocket udpReceiver;
	Device *device;

private slots:
	void processPendingDatagrams();

signals:
	void newDeviceIn(Device *dev);

};

#endif // SECUREUDP_H
