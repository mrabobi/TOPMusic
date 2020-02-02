#include "addcomm.h"
#include "ui_addcomm.h"
#include "QMessageBox"

addComm::addComm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addComm)
{
    ui->setupUi(this);
}

addComm::~addComm()
{
    delete ui;
}

void addComm::on_pushButton_3_clicked()
{
    this->close();
}

void addComm::on_pushButton_clicked()
{
    comboBox = ui->comboBox-> currentText().toStdString();
    lineEdit = ui->lineEdit-> text().toStdString();
    comment = ui->lineEdit_2->text().toStdString();
    if(comboBox == "Select method")
        QMessageBox::critical(nullptr,"EROARE!","Te rog sa alegi o metoda de cautare!");
    else if (lineEdit == "" || comment == "")
        QMessageBox::critical(nullptr,"EROARE !","Te rog sa completezi toate campurile!");
    else if (comment.length() < 3 || comment.length() > 64)
        QMessageBox::critical(nullptr,"EROARE !","Numarul de caractere pe care trebuie sa-l contina un comentariu este cuprins intre 3 si 64 caractere!");
    else {
        if(comboBox == "Link")
            addCommentFlag = 1; //LINK = 1
        else if (comboBox == "Name")
            addCommentFlag = 2;
        this->close();
    }
}
