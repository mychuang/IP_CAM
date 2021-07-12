#ifndef SECUREUDP_H
#define SECUREUDP_H

#include "crypto.h"
#include <QObject>
#include <QNetworkInterface>
#include <QUdpSocket>
#include <QThread>

#include "crypto.h"
//#include "message.h"
//#include "device.h"

class SecureUdp
{
	//Q_OBJECT

public:
	SecureUdp();

	//void prob();
	//void cleanDeviceList();

private:
    //void generateAesKey();
	//void requestPublicKey(uint8_t *devMac);
	//void setAesKey(Device *dev);
	//void handleProbeResponse(Message *msg);
	//Device *find_device(uint8_t *mac);

	QHostAddress groupAddress;
	QUdpSocket udpSender;
	QUdpSocket udpReceiver;
	//Device *device;

//private slots:
	//void processPendingDatagrams();

//signals:
	//void newDeviceIn(Device *dev);

};

#endif // SECUREUDP_H
