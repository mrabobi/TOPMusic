#include "showtopgeneral.h"
#include "ui_showtopgeneral.h"
#include <QTableWidgetItem>
#include <iostream>
showTopGeneral::showTopGeneral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showTopGeneral)
{
    ui->setupUi(this);
}

showTopGeneral::showTopGeneral(std::string songs, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showTopGeneral)
{
    QStringList titles;
    titles << "Likes" << "Nume" << "Descriere" << "Gen" << "Link" ;
    ui->setupUi(this);

    std::string delimiter = "#!";
    std::string token;
    size_t pos = 0;


    int i,j;
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setHorizontalHeaderLabels(titles);
    ui->tableWidget->setColumnWidth(0,37);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,200);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,200);


for(i=0 ; i < 10 ; i++)
   for(j=0 ; j < 5 ; j++)
   {
       if ((pos = songs.find(delimiter)) != std::string::npos) {
           token = songs.substr(0, pos);
           ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString(token.data())));
           songs.erase(0, pos + delimiter.length());

       }
       else {
          // ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString(songs.data())));
           break;
       }
   }


}

showTopGeneral::~showTopGeneral()
{
    delete ui;
}

void showTopGeneral::on_pushButton_clicked()
{
    this->close();
}
