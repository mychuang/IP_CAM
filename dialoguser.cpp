#include "dialoguser.h"
#include "ui_dialoguser.h"

dialogUser::dialogUser(SecureUdp *s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogUser), secUdp(s)
{
    ui->setupUi(this);
	ui->tableWidget->setColumnWidth(0, 410);

	connect(secUdp, &SecureUdp::UserResponse, this, &dialogUser::handleResponse);
	secUdp->cmdSend("GetUsers", NULL);

}

dialogUser::~dialogUser()
{
    delete ui;
}

void dialogUser::handleResponse(Device *dev, const QJsonObject &obj) {
	qDebug() << "DialogUsers::handle_response" << obj;

	if (obj["response"].toString() == "GetUsers") {
		qDebug() << "GetUsers";
	//	update_userinfo(obj);
	}
	else if (obj["response"].toString() == "AddUser") { // success, reload
		qDebug() << "AddUsers";
		secUdp->cmdSend("GetUsers", NULL);
	}
	else if (obj["response"].toString() == "DelUser") { // success, reload
		qDebug() << "DelUser";
		secUdp->cmdSend("GetUsers", NULL);
	}
}