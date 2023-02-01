#ifndef SPO2_CONTROLLER_H
#define SPO2_CONTROLLER_H

#include <QObject>

#include "./SystemGraphics/alltexts.h"
#include "./SystemGraphics/spo2graph.h"

class spo2_controller : public QObject
{
    Q_OBJECT
public:
    explicit spo2_controller(QObject *parent = nullptr);
    po2_controller(Spo2graph *graph,AllTexts *txt);

signals:

};

#endif // SPO2_CONTROLLER_H
