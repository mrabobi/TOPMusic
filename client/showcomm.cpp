#include "showcomm.h"
#include "ui_showcomm.h"
#include <QMessageBox>

showcomm::showcomm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showcomm)
{
    ui->setupUi(this);
}

showcomm::~showcomm()
{
    delete ui;
}

void showcomm::on_pushButton_4_clicked()
{
    this->close();
}

void showcomm::on_pushButton_2_clicked()
{
    comboBox = ui->comboBox_2-> currentText().toStdString();
    comment = ui->lineEdit_3->text().toStdString();
    if(comboBox == "Select method")
        QMessageBox::critical(nullptr,"EROARE!","Te rog sa alegi o metoda de cautare!");
    else if (comment == "")
        QMessageBox::critical(nullptr,"EROARE !","Te rog sa completezi campul aferent!");
       else {
        if(comboBox == "Link")
            showCommentFlag = 1; //LINK = 1
        else if (comboBox == "Name")
            showCommentFlag = 2;
        this->close();
    }
}
