#ifndef SCRIPTRUNNER_H
#define SCRIPTRUNNER_H
#include <QThread>

class scriptRunner: public QThread
{
public:
    scriptRunner(QString script);
    void run() override;
    void retry();

    QString scrpt;
    bool en=true;

};

#endif // SCRIPTRUNNER_H
