#ifndef SECUREUDP_H
#define SECUREUDP_H
#define QThreadEnabled 1

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

#if QThreadEnabled
class SecureUdp : public QThread 
#else
class SecureUdp : public QObject
#endif
{
	Q_OBJECT

#if QThreadEnabled
private:
	bool m_done;
protected:
	virtual void run();
public:
	void stop() {
		m_done = true;
	}
#endif

public:
	explicit SecureUdp(QObject *parent = nullptr);

	void prob();
	void cleanDeviceList();
	void setDevice(Device *dev); //update device from view
	Device* getDevice() { return device; }
	void cmdSend(const QString &cmd, const QJsonObject *data);
	void cmdDelUser(QString username);
	void cmdAddUser(QString username, QString password, QString authority);
	void cmdSetUser(QString username, QString password, QString authority);

private:
	void generateAesKey();
	void requestPublicKey(uint8_t *devMac);
	void setAesKey(Device *dev);
	void handleProbeResponse(Message *msg);
	void handleCipherdata(Device *dev, struct Message *msg);
	Device *findDevice(uint8_t *mac);

	QHostAddress groupAddress;
	QUdpSocket udpSender;
	QUdpSocket udpReceiver;
	Device *device;

private slots:
	void processPendingDatagrams();

signals:
	void newDeviceIn(Device *dev);
	void deviceResponse(Device *dev, const QJsonObject &obj);
};

#endif // SECUREUDP_H
