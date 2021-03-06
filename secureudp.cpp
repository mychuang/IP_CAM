#include "secureudp.h"
#include <QMessageBox>

extern uint8_t mac[6]; // local mac address
QList<Device *> deviceList;

#if QThreadEnabled
SecureUdp::SecureUdp(QObject *parent) : QThread(parent), m_done(false)
{
	generateAesKey();
	groupAddress = QHostAddress(QStringLiteral(MCAST_ADDR));
}
#else
SecureUdp::SecureUdp(QObject *parent) : QObject(parent)
{
	generateAesKey();
	groupAddress = QHostAddress(QStringLiteral(MCAST_ADDR));

	bool bindResult = udpReceiver.bind(MCAST_PORT + 1, QUdpSocket::ShareAddress);
	if (!bindResult) {
		if(SHOWDEBUG) qDebug() << "error bind";
	}
	else {
		if (SHOWDEBUG) qDebug() << "binding in" << MCAST_PORT + 1;
	}
	connect(&udpReceiver, &QUdpSocket::readyRead, this, &SecureUdp::processPendingDatagrams);
}
#endif

void SecureUdp::generateAesKey(){
	if (SHOWDEBUG) qDebug() << __func__;
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
	if (SHOWDEBUG) qDebug() << __func__;

	struct Message msg;
	msg.magic = MCAST_MSG_MAGIC;
	msg.type = MCAST_MSG_PROBE;
	memcpy(msg.from, mac, sizeof(msg.from));
	memset(msg.to, 0, sizeof(msg.to));
	msg.size = 0;

	udpSender.writeDatagram((const char *)&msg, offsetof(struct Message, data) + msg.size, groupAddress, MCAST_PORT);
}

#if QThreadEnabled == 1
void SecureUdp::run() {
	struct Message msg;
	bool bindResult = udpReceiver.bind(MCAST_PORT + 1, QUdpSocket::ShareAddress);
	if (!bindResult) {
		if (SHOWDEBUG) qDebug() << "error bind";
	}
	else {
		if (SHOWDEBUG) qDebug() << "binding in" << MCAST_PORT + 1;
	}

	while (!m_done) {
		if (!udpReceiver.waitForReadyRead(30))
			continue;
		memset(&msg, 0, sizeof(msg));
		udpReceiver.readDatagram((char *)&msg, sizeof(msg));
		
		if (msg.magic != MCAST_MSG_MAGIC)
			continue;

		if (memcmp(msg.to, mac, 6)) {
			if (SHOWDEBUG) qDebug() << "I'm not receiver";
			continue;
		}

		if (SHOWDEBUG) qDebug("type: %02x", msg.type);
		switch (msg.type) {
		case MCAST_MSG_PROBE_RESPONSE: {
			if (SHOWDEBUG) qDebug() << "run: handle Response";
			handleProbeResponse(&msg);
			break;
		}
		case MCAST_MSG_GETPUBKEY_RESPONSE: {
			if (SHOWDEBUG) qDebug() << "run: get PUBKEY";
			Device *dev = findDevice(msg.from);
			if (dev) {
				dev->pKey = loadPUBLICKeyFromString((const char *)msg.data);
				setAesKey(dev);
			}
			break;
		}
		case MCAST_MSG_SETAESKEY_ACK: {
			if (SHOWDEBUG) qDebug() << "run: AES ok!";
			Device *dev = findDevice(msg.from);
			if (dev) {
				dev->aes_ready = true;
			}
			break;
		}
		case MCAST_MSG_CIPHERDATA: {
			if (SHOWDEBUG) qDebug() << "run: get CIPHERDATA";
			Device *dev = findDevice(msg.from);
			if (dev) {
				handleCipherdata(dev, &msg);
			}
			break;
		}
		default:
			if (SHOWDEBUG) qDebug() << "%s: unhanlded message type" << msg.type;
		}
	}
}
#endif

void SecureUdp::processPendingDatagrams() {

	struct Message msg;
	do {
		memset(&msg, 0, sizeof(msg));
		udpReceiver.readDatagram((char *)&msg, sizeof(msg));

		if (msg.magic != MCAST_MSG_MAGIC)
			continue;
		if (memcmp(msg.to, mac, 6) != 0) {
			if (SHOWDEBUG) qDebug() << "I'm not receiver";
			continue;
		}

		if (SHOWDEBUG) qDebug("type: %02x", msg.type);
		switch (msg.type) {
		case MCAST_MSG_PROBE_RESPONSE: {
			if (SHOWDEBUG) qDebug() << "run: handle Response";
			handleProbeResponse(&msg);
			break;
		}
		case MCAST_MSG_GETPUBKEY_RESPONSE: {
			if (SHOWDEBUG) qDebug() << "run: get PUBKEY";
			Device *dev = findDevice(msg.from);
			if (dev) {
				dev->pKey = loadPUBLICKeyFromString((const char *)msg.data);
				setAesKey(dev);
			}
			break;
		}
		case MCAST_MSG_SETAESKEY_ACK: {
			if (SHOWDEBUG) qDebug() << "run: AES ok!";
			Device *dev = findDevice(msg.from);
			if (dev) {
				dev->aes_ready = true;
			}
			break;
		}
		case MCAST_MSG_CIPHERDATA: {
			if (SHOWDEBUG) qDebug() << "run: get CIPHERDATA";
			Device *dev = findDevice(msg.from);
			if (dev) {
				handleCipherdata(dev, &msg);
			}
			break;
		}
		default:
			if (SHOWDEBUG) qDebug() << "%s: unhanlded message type" << msg.type;
		}
	} while (udpReceiver.hasPendingDatagrams());

}

void SecureUdp::handleProbeResponse(Message *msg) {
	Device *dev = findDevice(msg->from);
	if (dev) {
		if (SHOWDEBUG) qDebug() << __func__ << "duplicate probe response";
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
	if (SHOWDEBUG) qDebug() << dev->model;
	if (SHOWDEBUG) qDebug() << dev->name;
	if (SHOWDEBUG) qDebug() << dev->ip;

	QString from;
	from.sprintf("%02x:%02x:%02x:%02x:%02x:%02x",
		msg->from[0], msg->from[1], msg->from[2], msg->from[3], msg->from[4], msg->from[5]);

	emit newDeviceIn(dev);
	requestPublicKey(msg->from);

}

Device* SecureUdp::findDevice(uint8_t *mac) {

	for (int i = 0; i < deviceList.size(); i++) {
		if (memcmp(deviceList[i]->mac, mac, 6) == 0) {
			if (SHOWDEBUG) qDebug("find_device: %02x:%02x:%02x:%02x:%02x:%02x",
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], mac[6]);
			return deviceList[i];
		}
	}
	if (SHOWDEBUG) qDebug(" %s New Device in !! ", stderr);
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
	if (SHOWDEBUG) qDebug() << __func__;

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
	if (SHOWDEBUG) qDebug() << __func__;

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

void SecureUdp::cmdSend(const QString &cmd, const QJsonObject *data) {
	if (SHOWDEBUG) qDebug() << "cmd:" << cmd;

	if (!device) {
		if (SHOWDEBUG) qDebug() << "no active device";
		return;
	}
	else {
		struct Message msg;
		msg.magic = MCAST_MSG_MAGIC;
		msg.type = MCAST_MSG_CIPHERDATA;
		memcpy(msg.from, mac, 6);
		memcpy(msg.to, device->mac, 6);
		memset(msg.data, 0, sizeof(msg.data));

		QJsonObject header;
		header["user"] = device->username;
		header["pass"] = device->password;
		QJsonObject root;
		root["header"] = header;
		root["cmd"] = cmd;
		// insert all key/value pairs in data into root object
		if (data) {
			QStringList keys = data->keys();
			foreach(const QString &key, keys) {
				root[key] = (*data)[key];
			}
		}

		//QByteArray bytes;
		QJsonDocument jsonDoc(root);
		QByteArray secureCmd;
		//bytes = jsonDoc.toJson();//
		secureCmd = jsonDoc.toJson();
		if (SHOWDEBUG) qDebug() << "json message:" << secureCmd;

		unsigned char msgDataIn[1024];
		memset(msgDataIn, 0, secureCmd.size());
		memcpy(msgDataIn, secureCmd.constData(), secureCmd.size());
		// including nul terminate, must be times of 16 bytes (AES key length)
		msg.size = size_with_padding(secureCmd.size()); 

		AES_cbc_encrypt(msgDataIn, msg.data, msg.size, &enc_key, device->iv, AES_ENCRYPT);
		udpSender.writeDatagram((const char *)&msg, offsetof(struct Message, data) + msg.size, groupAddress, MCAST_PORT);
		if (SHOWDEBUG) qDebug() << "--- write cmd Datagram ---";

	}
}

void SecureUdp::handleCipherdata(Device *dev, struct Message *msg) {
	if (SHOWDEBUG) qDebug() << __func__;
	char plain[1400];
	AES_cbc_encrypt(msg->data, (unsigned char *)plain, msg->size,
		&dec_key, dev->iv, AES_DECRYPT);
	// if parse json failed => call set_aes_key() again

	QByteArray byteArray(plain);
	QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray);
	if (jsonDoc.isNull()) {
		QMessageBox msgbox;
		msgbox.setText("parse error! check secureUdp or Device");
		msgbox.exec();
		return;
	}

	QJsonObject obj = jsonDoc.object();
	//qDebug() << obj;
	if (SHOWDEBUG) qDebug() << obj["response"];
	//qDebug() << obj["nowauth"];
	//qDebug() << obj["nowuser"];
	if (SHOWDEBUG) qDebug() << obj["users"];
	
	emit deviceResponse(dev, obj);

}

void SecureUdp::setDevice(Device *dev) {
	device = dev;
}

void SecureUdp::cmdDelUser(QString username) {
	QJsonObject obj;
	obj["username"] = username;

	cmdSend("DelUser", &obj);
}

void SecureUdp::cmdSetUser(QString username, QString password, QString authority) {
	QJsonObject obj;
	obj["username"] = username;
	obj["password"] = password;
	obj["authority"] = authority;
	cmdSend("SetUser", &obj);
}

void SecureUdp::cmdAddUser(QString username, QString password, QString authority) {
	QJsonObject obj;
	obj["username"] = username;
	obj["password"] = password;
	obj["authority"] = authority;
	cmdSend("AddUser", &obj);
}