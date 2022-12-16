#include "login.h"
#include "ui_login.h"



login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowFlags ( Qt::FramelessWindowHint ); //Frameless

    // push button initialization
    ui->pushButton->setStyleSheet(
                                     "border: 2px solid rgb(0,0,0);"
                                     "background-color: rgb(255, 0, 255);"
                                     "color: rgb(0, 0, 127);"
                                     "font: 12pt  Copperplate Gothic Bold;"
                                     "background-color: qlineargradient(spread:repeat, x1:0, y1:0, x2:1, y2:1, stop:0        rgba(172, 0, 255, 255), stop:1 rgba(33, 212, 253, 255));"
                                 );

    // database connecting

   // AccountsDB = DatabaseControl("C:/Users/Nader/Desktop/RemoteMedicalMonitor/Src/Server/AMServer/database/annmedics.db");
    AccountsDB = DatabaseControl("./database/annmedics.db");

    if(AccountsDB.GetConnectionStatus())
    {
        LogStatus("connected to database successfully....");
    }
    else
    {
        LogStatus("failed to connect to database ....");
    }




}
void login::LogStatus(QString status)
{
    ui->status->setText(status);
}
login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
   // get username and password
   username = ui->name_text->text();
   password = ui->password_text->text();

   //problem is how to get no of accs

   LogStatus("Authihenticating....");

   // Authorizing the user name
   bool uname_auth = AccountsDB.ReadFromTable("accounts","name",username);
   if(uname_auth)
   {
      LogStatus("valid username......");



      // Authorizing the password
      bool password_auth = AccountsDB.ReadFromTable("accounts","password",password);
      if(password_auth)
      {
         LogStatus("Authorized successfully......");
         //open the profiles
         //close();
      }
      else
      {
          LogStatus("invalid password , try again ......");
      }



   }
   else
   {
       LogStatus("username doesnt exist in database......");
   }





   // qDebug() <<data;
   //   LogStatus(data);
   // AccountsDB.ReadTableRecord("accounts","password",4);



}

void login::on_pushButton_toggled(bool checked)
{

}

void login::on_pushButton_pressed()
{
    // change login button color
    ui->pushButton->setStyleSheet("border: 2px solid rgb(0,0,0);"
                                  "background-color: rgb(255, 0, 255);"
                                  "color: rgb(255, 0, 255);"
                                  "font: 12pt  Copperplate Gothic Bold;"
                                  "border-image: url(:/images/textbox.png);"
                                  );
}

void login::on_pushButton_released()
{
 // change login button color
    ui->pushButton->setStyleSheet(
                                     "border: 2px solid rgb(0,0,0);"
                                     "background-color: rgb(255, 0, 255);"
                                     "color: rgb(0, 0, 127);"
                                     "font: 12pt  Copperplate Gothic Bold;"
                                     "background-color: qlineargradient(spread:repeat, x1:0, y1:0, x2:1, y2:1, stop:0        rgba(172, 0, 255, 255), stop:1 rgba(33, 212, 253, 255));"
                                 );
}


void login::on_pushButton_2_clicked()
{
    close();
}

