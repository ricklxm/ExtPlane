#include "explanedemo.h"
#include <QAbstractSocket>
#include <QThread>
#include "extplaneclient.h"
#include "extplaneconnection.h"

ExplaneDemo::ExplaneDemo(const QString host, uint port, QObject *parent)
    : QObject(parent), m_host(host), m_port(port)
{

}

void ExplaneDemo::test()
{
    auto conn = new ExtPlaneConnection();
    connect(conn, &ExtPlaneConnection::connected, this, [=](){
        qDebug() << "connected!!!";
        qDebug() << "state: " << conn->state();
    });
    connect(conn, &ExtPlaneConnection::connectionMessage, this, [](QString msg) {
        qDebug() << "connectionMessage: " << msg;
    });
    qDebug() << "try to connect to " << m_host;
    conn->connectTo(m_host, m_port);
    auto client = new ExtPlaneClient(Q_NULLPTR, "ExplaneDemo", conn);
    conn->registerClient(client);
    double m_minNotableChange = 0.000001;
    ClientDataRef * ref = client->subscribeDataRef("sim/flightmodel/position/latitude", m_minNotableChange);
    connect(ref, &ClientDataRef::changed, this, [=](ClientDataRef* r){
        qDebug() << r->doubleValue();
    });
}
