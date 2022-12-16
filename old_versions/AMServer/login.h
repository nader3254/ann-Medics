#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "./abstract/databasecontrol.h"

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_toggled(bool checked);

    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_2_clicked();

private:
    Ui::login *ui;
    DatabaseControl AccountsDB;
    void LogStatus(QString status);

    QString username;
    QString password;
};

#endif // LOGIN_H
