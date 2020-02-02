#include "banwindow.h"
#include "ui_banwindow.h"
#include <QMessageBox>

banWindow::banWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::banWindow)
{
    ui->setupUi(this);
}

banWindow::~banWindow()
{
    delete ui;
}

void banWindow::on_pushButton_clicked()
{
    command = ui->comboBox-> currentText().toStdString();
    username = ui->lineEdit-> text().toStdString();
    if(command == "Choose")
        QMessageBox::critical(nullptr,"EROARE!","Te rog sa alegi o comanda!");
    else if (username == "")
        QMessageBox::critical(nullptr,"EROARE !","Te rog sa completezi campul aferent!");
    else {
        if(command == "Ban")
            banFlag = 1; //BAN = 1
        else if (command == "Unban")
            banFlag = 2; // UNBAN = 2
        this->close();
    }
}
