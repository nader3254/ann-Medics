#ifndef SYSTEMERRORS_H
#define SYSTEMERRORS_H

#include <QObject>
#include <QVariant>
#include <QObject>
#include <QTimer>

class systemErrors : public QObject
{
    Q_OBJECT
public:
    explicit systemErrors(QObject *parent = nullptr);
    void add_error(QString msg);
    void add_warning(QString msg);
public slots:
void err_task();
void stop();

signals:
private:
    QObject *s_err_txt;
    QObject *warning;
    QObject *err;
    QTimer *tmr;

bool external_warning=false;
bool external_error=false;
bool prev_warning=false;
bool prev_error=false;
void toggle_warning();
void toggle_err();

};



#endif // SYSTEMERRORS_H
