#include "adminpanel.h"
#include "ui_adminpanel.h"
#include <QMessageBox>
adminPanel::adminPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminPanel)
{
    ui->setupUi(this);
}

adminPanel::~adminPanel()
{
    delete ui;
}

void adminPanel::on_pushButton_2_clicked()
{
    user = ui->lineEdit->text().toStdString();
    voteAcces = ui->comboBox_voteAcces->currentText().toStdString();
    levelAcces = ui->comboBox_userAcces->currentText().toStdString();

    if(voteAcces == "Choose"|| levelAcces == "Choose")
        QMessageBox::critical(nullptr,"EROARE!","Te rog sa alegi gradele de acces!");
    else if (user == "")
        QMessageBox::critical(nullptr,"EROARE!","Te rog sa completezi username-ul!");
    else
        this->close();

}
