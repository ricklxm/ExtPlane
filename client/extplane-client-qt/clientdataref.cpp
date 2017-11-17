#include "clientdataref.h"

ClientDataRef::ClientDataRef(QObject *parent, QString newName, double accuracy) : QObject(parent), _name(newName), _accuracy(accuracy) {
    _subscribers = 0;
    _values.reserve(1); // Always at least 1 size
}

QString& ClientDataRef::name() {
    return _name;
}

QString& ClientDataRef::valueString() {
    return _values.first();
}

QStringList& ClientDataRef::valueStrings() {
    return _values;
}

void ClientDataRef::updateValue(QString newValue) {
    if(!_values.isEmpty() && newValue == _values.first()) return;

    if(_values.isEmpty()) {
        _values.push_back(newValue);
    } else {
        _values.replace(0, newValue);
    }
    emit changed(this);
}

void ClientDataRef::updateValue(QStringList &newValues) {
    if(newValues == _values) return;
    _values = newValues;
    emit changed(this);
}

double ClientDataRef::accuracy() {
    return _accuracy;
}

int ClientDataRef::subscribers() {
    return _subscribers;
}

void ClientDataRef::setSubscribers(int sub) {
    _subscribers = sub;
}

double ClientDataRef::doubleValue(int index, bool* ok, double defaultValue)
{
    if (_values.size() <= index) {
        ok = false;
        return defaultValue;
    }
    bool success;
    double v = _values[index].toDouble(&success);
    if (!success) v = defaultValue;
    if (ok != 0) {
        *ok = success;
    }
    return v;
}

void ClientDataRef::setValue(double _newValue, int index) {
    if(_values.size() < index + 1) {
        int currentSize = _values.size();
        int expectedSize = index + 1;
        _values.reserve(expectedSize);
        QString str;
        while (currentSize++ < expectedSize) {
            _values.append(str);
        }
    }

    _values[index] = QString::number(_newValue);
    emit valueSet(this);
}

// add by rick
void ClientDataRef::setValue(QList<double> _newValues) {
    if(_values.size() < _newValues.count() + 1)
        _values.reserve(_newValues.count() + 1);
    _values.clear();
    for (double v : _newValues) {
        _values.append(QString::number(v));
    }
    emit valueSet(this);
}

// add by rick
void ClientDataRef::setValue(QStringList _newValues) {
    _values = _newValues;
    emit valueSet(this);
}

void ClientDataRef::unsubscribe() {
    emit unsubscribed(this);
}

bool ClientDataRef::isArray() {
    return _values.size() > 1;
}
