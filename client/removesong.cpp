#include "removesong.h"
#include "ui_removesong.h"
#include <QMessageBox>

removesong::removesong(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::removesong)
{
    ui->setupUi(this);
}

removesong::~removesong()
{
    delete ui;
}

void removesong::on_pushButton_clicked()
{
    std::string box = ui->comboBox-> currentText().toStdString();
      song = ui->lineEdit ->text().toStdString();
    if(box == "Choose")
        QMessageBox::critical(nullptr,"EROARE!","Te rog sa alegi o metoda de cautare!");
    else if (song == "" )
        QMessageBox::critical(nullptr,"EROARE !","Te rog sa completezi campul aferent!");
    else {
    if(box == "Name")
        removeFlag = 1;
    else
        removeFlag = 2;
    this->close();
}
}
