#include "showcommwindow.h"
#include "ui_showcommwindow.h"
#include <iostream>
#include<string>

showcommwindow::showcommwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showcommwindow)
{
    ui->setupUi(this);
}

showcommwindow::showcommwindow(std::string answer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showcommwindow)
{
    ui->setupUi(this);
    ui->pushButton->setHidden(true);

    QStringList titles;
    titles << "Author" <<"Comment"  ;
    ui->setupUi(this);

    std::string delimiter = "#!";
    std::string token;
    size_t pos = 0;


    int i,j;
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(50);
    ui->tableWidget->setHorizontalHeaderLabels(titles);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,500);

    std::string namesong;
    std::string linksong;
    char str[1000];
    strcpy(str,answer.data());
    char *token2 = strtok(str, "#!");
    namesong = token2;
    token2 = strtok(nullptr, "#!");
    linksong = token2;

    answer.erase(0, pos + namesong.length());
    answer.erase(0, pos + linksong.length());
    answer.erase(0, pos + delimiter.length());
    answer.erase(0, pos + delimiter.length());

    ui->nameSongLabel->setText("Numele melodiei:" + QString(namesong.data()) );
    ui->linkSongLabel->setText("Link-ul melodiei: " + QString(linksong.data()) );

for(i=0 ; i < 100 ; i++)
   for(j=0 ; j < 2 ; j++)
   {
       if ((pos = answer.find(delimiter)) != std::string::npos) {
           token = answer.substr(0, pos);
           ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString(token.data())));
           answer.erase(0, pos + delimiter.length());

       }
       else {
          break;
       }
   }

}

showcommwindow::~showcommwindow()
{
    delete ui;
}


void showcommwindow::on_pushButton_clicked()
{

}
