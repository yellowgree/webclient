#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QTcpSocket>
#include <QSslSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QTcpSocket socket_t;
    QSslSocket socket_s;


    //QUdpSocket socket_;

public slots:
    void doConnected();
    void doDisconnected();
    void doreadyRead();
    void updateButtonState();


private slots:

    void on_pbconnect_clicked();

    void on_pbdisconnect_clicked();

    void on_pbSend_clicked();

    void on_pbSsl_stateChanged();

    void on_pbclear_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
