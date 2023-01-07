#ifndef ECG_CONTROLLER_H
#define ECG_CONTROLLER_H

#include <QObject>

class ecg_controller : public QObject
{
    Q_OBJECT
public:
    explicit ecg_controller(QObject *parent = nullptr);

signals:

};

#endif // ECG_CONTROLLER_H
