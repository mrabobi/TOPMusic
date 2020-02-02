#include "addsongwindow.h"
#include "ui_addsongwindow.h"
#include <QMessageBox>

addSongWIndow::addSongWIndow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSongWIndow)
{
    ui -> setupUi(this);

    ui -> comboBox_genList -> addItem("None");
    ui -> comboBox_genList -> addItem("Pop");
    ui -> comboBox_genList -> addItem("Rock");
    ui -> comboBox_genList -> addItem("Chill");
    ui -> comboBox_genList -> addItem("Indie");
    ui -> comboBox_genList -> addItem("Latino");
    ui -> comboBox_genList -> addItem("Manele");
    ui -> comboBox_genList -> addItem("Hip-Hop");
    ui -> comboBox_genList -> addItem("Electro");
    ui -> comboBox_genList -> addItem("Populara");


}

addSongWIndow::~addSongWIndow()
{
    delete ui;
}

void addSongWIndow::on_pushButton_addSong_clicked()
{
    addSongName = ui -> lineEdit_addSongNume -> text().toStdString();
    addUrl = ui -> lineEdit_addSongUrl -> text().toStdString();
    addGen = ui -> comboBox_genList -> currentText().toStdString();
    addDesc = ui -> lineEdit_addDesc -> text().toStdString();
    if(addSongName == "" || addUrl == "" || addGen == "None")
        QMessageBox::critical(nullptr,"EROARE LA ADAUGARE!","Te rog sa completezi toate campurile si sa alegi genul muzica. ");
    else if (addUrl.find("www.") == std::string::npos )
        QMessageBox::critical(nullptr,"EROARE LA ADAUGARE!","URL invalid! ");
    else if (addDesc.length() > 50)
        QMessageBox::critical(nullptr,"EROARE LA ADAUGARE!","Descrierea contine mai mult de 50 de caractere!");
    else {
        if(addDesc == "")
            addDesc = "-";
       this->close();
    }
}
