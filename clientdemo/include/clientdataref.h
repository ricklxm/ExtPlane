#ifndef CLIENTDATAREF_H
#define CLIENTDATAREF_H

#include <QObject>
#include <QStringList>

/**
 * Represents a single dataref in client side. Can contain multiple
 * values, if ref is a array.
 *
 * You get a ClientDataRef by calling ExtPlaneConnection::subscribeDataRef().
 *
 * To unsubscribe, call ClientDataRef::unsubscribe().
 *
 * Never call delete or deleteLater() on this - memory is managed by ExtPlaneConnection.
 */
class ClientDataRef : public QObject {
    Q_OBJECT
public:
    explicit ClientDataRef(QObject *parent, QString newName, double accuracy=0);
    QString& name();
    QString& valueString(); // Returns first value
    QStringList& valueStrings(); // Returns all values
    double accuracy();
    void updateValue(QString newValue); // Update single value
    void updateValue(QStringList &newValues); // Update full array
    int subscribers();
    double doubleValue(int index = 0, bool* ok = 0, double defaultValue = 0);
    void setSubscribers(int sub);
    void setValue(double _newValue, int index=0);
    void setValue(QList<double> _newValues);
    void setValue(QStringList _newValues);
    bool isArray();
    void unsubscribe(); // Call to unsubscribe ref.
signals:
    void changed(ClientDataRef *ref);
    void valueSet(ClientDataRef *ref);
    void unsubscribed(ClientDataRef *ref);
private:
    QString _name;
    QStringList _values;
    double _accuracy;
    int _subscribers;
};

#endif // CLIENTDATAREF_H
