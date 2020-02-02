#include "voteasong.h"
#include "ui_voteasong.h"
#include <QMessageBox>

voteasong::voteasong(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::voteasong)
{
    ui->setupUi(this);
}

voteasong::~voteasong()
{
    delete ui;
}

void voteasong::on_pushButton_clicked()
{
    comboBox = ui->comboBox-> currentText().toStdString();
    lineEdit = ui->lineEdit-> text().toStdString();
    if(comboBox == "Select method")
        QMessageBox::critical(nullptr,"EROARE!","Te rog sa alegi o metoda de cautare!");
    else if (lineEdit == "")
        QMessageBox::critical(nullptr,"EROARE !","Te rog sa completezi campul aferent!");
    else {
        if(comboBox == "Link")
            votesongflag = 1; //LINK = 1
        else if (comboBox == "Name")
            votesongflag = 2;
        this->close();
    }
}

void voteasong::on_pushButton_3_clicked()
{
    this->close();
}

void voteasong::on_pushButton_2_clicked()
{
    comboBox = ui->comboBox-> currentText().toStdString();
    lineEdit = ui->lineEdit-> text().toStdString();
    if(comboBox == "Select method")
        QMessageBox::critical(nullptr,"EROARE!","Te rog sa alegi o metoda de cautare!");
    else if (lineEdit == "")
        QMessageBox::critical(nullptr,"EROARE !","Te rog sa completezi campul aferent!");
    else {
        if(comboBox == "Link")
            votesongflag = 3; //LINK = 1
        else if (comboBox == "Name")
            votesongflag = 4;
        this->close();
    }
}
