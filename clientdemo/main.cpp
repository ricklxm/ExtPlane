#include <QCoreApplication>
#include <QAbstractSocket>
#include <QThread>
#include <QObject>
#include "explanedemo.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString host = "127.0.0.1";
    uint port = 51000;

    ExplaneDemo demo(host, port);
    demo.test();
    return a.exec();
}

//if (aircraftId == 0) {
//    latRef = "sim/flightmodel/position/latitude";
//    lonRef = "sim/flightmodel/position/longitude";
//    altRef = "sim/flightmodel/position/elevation";
//    pitchRef = "sim/flightmodel/position/theta";
//    headingRef = "sim/flightmodel/position/psi";
//    rollRef = "sim/flightmodel/position/phi";
//    speedRef = "sim/flightmodel/position/indicated_airspeed";
//}
//else
//{
//    latRef = String.Format("sim/multiplayer/position/plane{0}_lat", aircraftId);
//    lonRef = String.Format("sim/multiplayer/position/plane{0}_lon", aircraftId);
//    altRef = String.Format("sim/multiplayer/position/plane{0}_el", aircraftId);
//    pitchRef = String.Format("sim/multiplayer/position/plane{0}_the", aircraftId);
//    headingRef = String.Format("sim/multiplayer/position/plane{0}_psi", aircraftId);
//    rollRef = String.Format("sim/multiplayer/position/plane{0}_phi", aircraftId);
//    speedRef = "sim/flightmodel/position/indicated_airspeed"; // TODO: fix me!!!
//}
