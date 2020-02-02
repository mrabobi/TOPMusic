#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <registertime.h>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    closeValue = "true";
    delete ui;
}

void login::on_loginButton_clicked()
{
    closeValue = "false";
    username = ui -> lineEdit_username -> text().toStdString();
    password = ui -> lineEdit_password -> text().toStdString();
    if((username.length()<4  || username.length()>32) || (password.length()<4  || password.length()>32) ){
        QMessageBox::critical(nullptr,"FAILED TO LOGIN !","Userul si parola trebuie sa fie cuprinse intre 4 si 32 caractere. Mai incearca! ");
    }
    else {
        this->close();
    }
}

void login::on_pushButton_clear_clicked()
{
  closeValue = "true";
  this->close();
}

void login::on_registerButton_clicked()
{
    closeValue = "false";
    registerTime registerWindow;
    registerWindow.setModal(true);
    registerWindow.exec();
    regAnswer = "register " + registerWindow.regUsername + " " + registerWindow.regPassword;
    if(regAnswer == "register  ")
        regAnswer = "";
    this->close();
}
