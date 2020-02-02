#include "registertime.h"
#include "ui_registertime.h"
#include <QMessageBox>

registerTime::registerTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerTime)
{
    ui->setupUi(this);
}

registerTime::~registerTime()
{
    delete ui;
}

void registerTime::on_pushButton_register_clicked()
{
    regUsername = ui -> lineEdit_username -> text().toStdString();
    regPassword = ui -> lineEdit_password -> text().toStdString();
    regConfpass = ui -> lineEdit_confpass -> text().toStdString();
    if((regUsername.length()<4  || regUsername.length()>32) || (regPassword.length()<4  || regPassword.length()>32) ){
        QMessageBox::critical(nullptr,"FAILED TO REGISTER !","Userul si parola trebuie sa fie cuprinse intre 4 si 32 caractere. ");
    }
    else if(regPassword != regConfpass) {
        QMessageBox::critical(nullptr,"FAILED TO REGISTER !","Parolele nu corespund!");
    }
    else {
        this->close();
    }
}
