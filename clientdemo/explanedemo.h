#ifndef EXPLANEDEMO_H
#define EXPLANEDEMO_H

#include <QObject>

class ExplaneDemo : public QObject
{
    Q_OBJECT
public:
    explicit ExplaneDemo(const QString host, uint port, QObject *parent = 0);
    void test();

private:
    QString m_host;
    uint m_port;
};

#endif // EXPLANEDEMO_H
