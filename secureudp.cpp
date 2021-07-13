#include "secureudp.h"
#include <QJsonDocument>
#include <QJsonObject>

extern uint8_t mac[6]; // local mac address
QList<Device *> deviceList;

SecureUdp::SecureUdp(QObject *parent) : QObject(parent)
{
	generateAesKey();
	groupAddress = QHostAddress(QStringLiteral(MCAST_ADDR));

	//reading data
	bool bindResult = udpReceiver.bind(MCAST_PORT + 1, QUdpSocket::ShareAddress);
	if (!bindResult) {
		qDebug() << "error bind";
	}
	else {
		qDebug() << "binding in" << MCAST_PORT + 1;
	}

	connect(&udpReceiver, &QUdpSocket::readyRead, this, &SecureUdp::processPendingDatagrams);
}

void SecureUdp::generateAesKey(){
    qDebug() << __func__;
        int i;
        int j;
        int r;

        uint8_t *p = aes;
        srand(time(NULL));
        for(i=0;i<4;i++) {
            r = rand();
            for(j=0;j<4;j++) {
                *p++ = r & 0xff;
                r >>= 8;
            }
        }

        AES_set_encrypt_key(aes, sizeof(aes)*8, &enc_key);
        AES_set_decrypt_key(aes, sizeof(aes)*8, &dec_key);
}

void SecureUdp::prob() {
	qDebug() << __func__;

	struct Message msg;
	msg.magic = MCAST_MSG_MAGIC;
	msg.type = MCAST_MSG_PROBE;
	memcpy(msg.from, mac, sizeof(msg.from));
	memset(msg.to, 0, sizeof(msg.to));
	msg.size = 0;

	udpSender.writeDatagram((const char *)&msg, offsetof(struct Message, data) + msg.size, groupAddress, MCAST_PORT);
}

void SecureUdp::processPendingDatagrams() {

	struct Message msg;
	do {
		memset(&msg, 0, sizeof(msg));
		udpReceiver.readDatagram((char *)&msg, sizeof(msg));

		if (msg.magic != MCAST_MSG_MAGIC)
			continue;
		if (memcmp(msg.to, mac, 6) != 0) {
			qDebug() << "I'm not receiver";
			continue;
		}

		qDebug("type: %02x", msg.type);
		switch (msg.type) {
		case MCAST_MSG_PROBE_RESPONSE: {
			qDebug() << "run: handle Response";
			handleProbeResponse(&msg);
			break;
		}
		case MCAST_MSG_GETPUBKEY_RESPONSE: {
			qDebug() << "run: get PUBKEY";
			Device *dev = findDevice(msg.from);
			if (dev) {
				dev->pKey = loadPUBLICKeyFromString((const char *)msg.data);
				setAesKey(dev);
			}
			break;
		}
		case MCAST_MSG_SETAESKEY_ACK: {
			qDebug() << "run: AES ok!";
			Device *dev = findDevice(msg.from);
			if (dev) {
				dev->aes_ready = true;
			}
			break;
		}
		default:
			qDebug() << "%s: unhanlded message type" << msg.type;
		}
	} while (udpReceiver.hasPendingDatagrams());

	for (int i = 0; i < deviceList.size(); i++) {
		qDebug() << deviceList[i]->aes_ready;
	}
}

void SecureUdp::handleProbeResponse(Message *msg) {
	Device *dev = findDevice(msg->from);
	if (dev) {
		qDebug() << __func__ << "duplicate probe response";
		return;
	}

	// add new device to list
	dev = new Device;
	memset(dev->mac, 0, sizeof(dev->mac));
	memset(dev->iv, 0, sizeof(dev->iv));
	dev->pKey = NULL;
	dev->aes_ready = false;

	QJsonDocument jsonDoc = QJsonDocument::fromJson(QString((char *)(msg->data)).toUtf8());
	QJsonObject jsonObj = jsonDoc.object();

	memcpy(dev->mac, msg->from, 6);
	dev->model = jsonObj["model"].toString();
	dev->name = jsonObj["name"].toString();
	dev->ip = jsonObj["ip"].toString();
	deviceList.push_back(dev);
	qDebug() << dev->model;
	qDebug() << dev->name;
	qDebug() << dev->ip;

	QString from;
	from.sprintf("%02x:%02x:%02x:%02x:%02x:%02x",
		msg->from[0], msg->from[1], msg->from[2], msg->from[3], msg->from[4], msg->from[5]);

	emit newDeviceIn(dev);
	requestPublicKey(msg->from);
}

Device* SecureUdp::findDevice(uint8_t *mac) {

	for (int i = 0; i < deviceList.size(); i++) {
		if (memcmp(deviceList[i]->mac, mac, 6) == 0) {
			qDebug("find_device: %02x:%02x:%02x:%02x:%02x:%02x",
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], mac[6]);
			return deviceList[i];
		}
	}
	qDebug(" %s New Device in !! ", stderr);
	return NULL;
}

void SecureUdp::cleanDeviceList() {
	for (int i = 0; i < deviceList.size(); i++) {
		RSA_free(deviceList[i]->pKey);
		delete deviceList[i];
	}
	deviceList.clear();
}

void SecureUdp::requestPublicKey(uint8_t *devMac) {
	qDebug() << __func__;

	struct Message msg;
	msg.magic = MCAST_MSG_MAGIC;
	msg.type = MCAST_MSG_GETPUBKEY;
	memcpy(msg.from, mac, 6);
	memcpy(msg.to, devMac, 6);
	msg.size = 0;
	udpSender.writeDatagram((const char *)&msg, offsetof(struct Message, data) + msg.size,
		groupAddress, MCAST_PORT);
}

void SecureUdp::setAesKey(Device *dev) {
	qDebug() << __func__;

	struct Message msg;
	uint8_t buf[256]; // 2048bits
	msg.magic = MCAST_MSG_MAGIC;
	msg.type = MCAST_MSG_SETAESKEY;
	memcpy(msg.from, mac, 6);
	memcpy(msg.to, dev->mac, 6);
	memset(dev->iv, 0, sizeof(dev->iv));
	memset(buf, 0, sizeof(buf));
	memcpy(buf, aes, AES_BLOCK_SIZE);

	msg.size = RSA_public_encrypt(AES_BLOCK_SIZE, buf, msg.data, dev->pKey, RSA_PKCS1_OAEP_PADDING);

	udpSender.writeDatagram((const char *)&msg, offsetof(struct Message, data) + msg.size,
		groupAddress, MCAST_PORT);
}