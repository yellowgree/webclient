#include "widget.h"
#include "ui_widget.h"


int tcp=1;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    QObject::connect(&socket_s, &QAbstractSocket::connected, this, &Widget::doConnected);
    QObject::connect(&socket_s, &QAbstractSocket::disconnected, this, &Widget::doDisconnected);
    QObject::connect(&socket_s, &QAbstractSocket::readyRead, this, &Widget::doreadyRead);

    QObject::connect(&socket_t, &QAbstractSocket::connected, this, &Widget::doConnected);
    QObject::connect(&socket_t, &QAbstractSocket::disconnected, this, &Widget::doDisconnected);
    QObject::connect(&socket_t, &QAbstractSocket::readyRead, this, &Widget::doreadyRead);
    updateButtonState();

    }





Widget::~Widget()
{
    delete ui;
}

void Widget::doConnected() {
    ui->message->insertPlainText("Connected \n");
    updateButtonState();
}

void Widget::doDisconnected() {
    ui->message->insertPlainText("Disconnected \n");
    updateButtonState();
}

void Widget::doreadyRead() {
    if (tcp==0)
    {
        ui->message->insertPlainText(socket_s.readAll());
    }

    else{ui->message->insertPlainText(socket_t.readAll());}
}




void Widget::on_pbconnect_clicked()
{
    if (tcp==0)
    {socket_s.connectToHostEncrypted(ui->lehost->text(), ui->leport->text().toUShort());}

    else {socket_t.connectToHost(ui->lehost->text(), ui->leport->text().toUShort());}

}


void Widget::on_pbdisconnect_clicked()
{
    if(tcp==0)
    {
        socket_s.close();
    }
    else{
        socket_t.close();
    }
}


void Widget::on_pbSend_clicked()
{
    if(tcp==0)
    {
        socket_s.write(ui->pteSend->toPlainText().toUtf8());
    }

    else {socket_t.write(ui->pteSend->toPlainText().toUtf8());}
}


void Widget::on_pbSsl_stateChanged()
{
    if(ui->pbSsl->isChecked())
    {
        tcp=0;
    }

    else{tcp=1;}


}


void Widget::on_pbclear_clicked()
{
    ui->message->clear();
}


void Widget::updateButtonState()
{
    if (tcp == 0) // SSL 사용 중
    {
        ui->pbconnect->setEnabled(!socket_s.isOpen()); // 소켓이 열려있지 않은 경우에만 연결 버튼 활성화
        ui->pbdisconnect->setEnabled(socket_s.isOpen()); // 소켓이 열려있는 경우에만 연결 해제 버튼 활성화
    }
    else // 일반 TCP 사용 중
    {
        ui->pbconnect->setEnabled(!socket_t.isOpen()); // 소켓이 열려있지 않은 경우에만 연결 버튼 활성화
        ui->pbdisconnect->setEnabled(socket_t.isOpen()); // 소켓이 열려있는 경우에만 연결 해제 버튼 활성화
    }
}
